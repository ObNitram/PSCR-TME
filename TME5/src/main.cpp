#include "Color.hpp"
#include "Pool.hpp"
#include "Rayon.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Vec3D.hpp"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>

void fillScene(pr::Scene &scene, std::default_random_engine &re, int nb_de_sphere)
{
    // Nombre de spheres (rend le probleme plus dur)

    // on remplit la scene de spheres colorees de taille position et couleur aleatoire
    std::uniform_int_distribution<int> distrib(0, 200);
    std::uniform_real_distribution<double> distribd(-200, 200);
    for (int i = 0; i < nb_de_sphere; i++)
    {
        // position autour de l'angle de la camera
        // rayon entre 3 et 33, couleur aleatoire
        // distrib(re) rend un entier aleatoire extrait de re
        scene.add(pr::Sphere({50 + distribd(re), 50 + distribd(re), 120 + distribd(re)},
                             static_cast<double>(distrib(re) % 30) + 3.0, pr::Color::random()));
    }
    // quelques spheres de plus pour ajouter du gout a la scene
    scene.add(pr::Sphere({50, 50, 40}, 15.0, pr::Color::red));
    scene.add(pr::Sphere({100, 20, 50}, 55.0, pr::Color::blue));
}

// produit une image dans path, représentant les pixels.
void exportImage(const char *path, size_t width, size_t height, pr::Color *pixels)
{
    // ppm est un format ultra basique
    std::ofstream img(path);
    // P3 signifie : les pixels un par un en ascii
    img << "P3" << std::endl; // ascii format, colors
    // largeur hauteur valeur max d'une couleur (=255 un char)
    img << width << "\n"
        << height << "\n"
        << "255" << std::endl;
    // tous les pixels au format RGB
    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            pr::Color &pixel = pixels[x * height + y];
            img << pixel << '\n';
        }
    }
    // oui ca fait un gros fichier :D
    img.close();
}

int compute_raw(pr::Scene &scene, std::vector<pr::Vec3D> &lights, pr::Color *pixels)
{
    // les points de l'ecran, en coordonnées 3D, au sein de la Scene.
    // on tire un rayon de l'observateur vers chacun de ces points
    const pr::Scene::screen_t &screen = scene.getScreenPoints();

    // pour chaque pixel, calculer sa couleur
    for (int x = 0; x < scene.getWidth(); x++)
    {
        for (int y = 0; y < scene.getHeight(); y++)
        {
            // le point de l'ecran par lequel passe ce rayon
            auto &screenPoint = screen[y][x];
            // le rayon a inspecter
            pr::Rayon ray(scene.getCameraPos(), screenPoint);

            int targetSphere = pr::Utils::findClosestInter(scene, ray);

            if (targetSphere == -1)
            {
                // keep background color
                continue;
            }
            else
            {
                const pr::Sphere &obj = *(scene.begin() + targetSphere);
                // pixel prend la couleur de l'objet
                pr::Color finalcolor = pr::Utils::computeColor(obj, ray, scene.getCameraPos(), lights);
                // le point de l'image (pixel) dont on vient de calculer la couleur
                pr::Color &pixel = pixels[y * scene.getHeight() + x];
                // mettre a jour la couleur du pixel dans l'image finale.
                pixel = finalcolor;
            }
        }
    }

    return 0;
}

int compute_with_pixel_jobs(pr::Scene &scene, std::vector<pr::Vec3D> &lights, pr::Color *pixels, int pool_size,
                            int nb_thread)
{
    // les points de l'ecran, en coordonnées 3D, au sein de la Scene.
    // on tire un rayon de l'observateur vers chacun de ces points
    const pr::Scene::screen_t &screen = scene.getScreenPoints();

    auto pool = pr::Pool(pool_size);

    pool.start(nb_thread);

    // pour chaque pixel, calculer sa couleur
    for (int x = 0; x < scene.getWidth(); x++)
    {
        for (int y = 0; y < scene.getHeight(); y++)
        {
            // le point de l'ecran par lequel passe ce rayon
            auto &screenPoint = screen[y][x];
            pool.submit(new pr::PixelJob(screenPoint, scene, pixels, lights, x, y));
        }
    }

    pool.stop();

    return 0;
}

// exportImage("toto.ppm", scene.getWidth(), scene.getHeight(), pixels);

int main(int argc, char *argv[])
{
    int nb_de_sphere = 1000;
    int scene_size = 1000;
    std::string csv_name = "../analyse/execution_results_sort_";

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.find("--nb_de_sphere=") == 0) {
            nb_de_sphere = std::stoi(arg.substr(15));
        } else if (arg.find("--scene_size=") == 0) {
            scene_size = std::stoi(arg.substr(13));
        } else if (arg.find("--csv_name=") == 0) {
            csv_name = arg.substr(11);
        } else {
            std::cerr << "Argument inconnu : " << arg << std::endl;
            return 1;
        }
    }

    // Affichage pour vérification
    std::cout << "Nombre de sphères: " << nb_de_sphere << std::endl;
    std::cout << "Taille de la scène: " << scene_size << std::endl;
    std::cout << "Nom du fichier CSV: " << csv_name << std::endl;

    pr::Scene scene(scene_size, scene_size);
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
    fillScene(scene, re, nb_de_sphere);

    std::vector<pr::Vec3D> lights;
    lights.reserve(6);
    lights.emplace_back(50, 50, -50);
    lights.emplace_back(50, 50, 10);
    lights.emplace_back(200, 0, 120);
    lights.emplace_back(5, 5, -5);
    lights.emplace_back(57, 80, -10);
    lights.emplace_back(20, 2, 12);

    auto *pixels = new pr::Color[scene.getWidth() * scene.getHeight()];

    std::cout << "Test will be done with " << nb_de_sphere << " spheres and a scene of size " << scene_size << "x"
              << scene_size << ".\n";
    csv_name = csv_name + "_" + std::to_string(nb_de_sphere) + "sphere_" + std::to_string(scene_size) + "x" +
               std::to_string(scene_size) + ".csv";

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    compute_raw(scene, lights, pixels);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time for compute_raw : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms.\n";

    std::vector<int> poolSizes = {};

    int max_jobs_size = scene_size * scene_size;
    int fraction_size = max_jobs_size / 10;
/*
    for (int i = 1; i < 12; ++i) {
        poolSizes.push_back(fraction_size * i);
    }
*/


    std::vector threadCounts = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 30, 35, 40, 50, 60};

    poolSizes = {2, 4, 8, 16, 32, 64, 128, 254, 512, 1024, 2048, 4096};

    // Afficher les résultats
    std::cout << std::setw(15) << std::left << "Pool Size" << std::setw(15) << std::left << "Nb Threads"
              << std::setw(20) << std::left << "Execution Time (ms)"
              << "Progress\n";
    std::cout << std::string(60, '-') << "\n";

    // Écriture de l'en-tête du fichier CSV
    std::ofstream file(csv_name);
    if (!file)
    {
        std::cerr << "Impossible d'ouvrir le fichier pour l'écriture !" << std::endl;
        return 1;
    }
    file << "Pool Size,Nb Threads,Execution Time (ms)\n";

    // Créer toutes les combinaisons possibles
    std::vector<std::pair<int, int>> combinations;

    for (int pool : poolSizes)
    {
        for (int nb_thread : threadCounts)
        {
            combinations.emplace_back(pool, nb_thread);
        }
    }

    // Mélanger les combinaisons
    std::random_device rd;
    std::mt19937 g(rd());
    //std::ranges::shuffle(combinations, g);

    size_t i = 0;
    for (const auto &[pool, nb_thread] : combinations)
    {

        start = std::chrono::steady_clock::now();

        // Appel de la fonction à mesurer
        compute_with_pixel_jobs(scene, lights, pixels, pool, nb_thread);

        end = std::chrono::steady_clock::now();
        auto execTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        // Affichage dans la console
        std::cout << std::setw(15) << std::left << pool << std::setw(15) << std::left << nb_thread << std::setw(20)
                  << std::left << execTime << i + 1 << "/" << combinations.size() << "\n";

        // Écriture dans le fichier CSV
        file << pool << "," << nb_thread << "," << execTime << "\n";
        i++;
    }

    delete[] pixels;
}

/*

Test will be done with 1000 spheres and a scene of size 1000x1000.
Time for compute_raw : 4811ms.
Pool Size      Nb Threads     Execution Time (ms)
--------------------------------------------------
100            2              3900
100            4              2661
100            8              1965
100            12             1790
100            16             1610
100            20             1686
100            24             2501
100            60             7870

1000           2              3906
1000           4              2670
1000           8              1999
1000           12             1750
1000           16             1666
1000           20             1580
1000           24             1918
1000           60             6413

2000           2              3957
2000           4              2668
2000           8              1983
2000           12             1682
2000           16             1588
2000           20             1501
2000           24             1720
2000           60             5698

5000           2              3898
5000           4              2711
5000           8              1949
5000           12             1733
5000           16             1591
5000           20             1450
5000           24             1407
5000           60             3565

*/
