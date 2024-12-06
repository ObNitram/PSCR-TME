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

    pr::Pool pool = pr::Pool(pool_size);

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

int main(int argc, char *argv[])
{
    // exportImage("toto.ppm", scene.getWidth(), scene.getHeight(), pixels);

    pr::Scene scene(1000, 1000);
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
    fillScene(scene, re, 1000);

    std::vector<pr::Vec3D> lights;
    lights.reserve(3);
    lights.emplace_back(50, 50, -50);
    lights.emplace_back(50, 50, 120);
    lights.emplace_back(200, 0, 120);

    auto *pixels = new pr::Color[scene.getWidth() * scene.getHeight()];

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    compute_raw(scene, lights, pixels);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time for compute_raw : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << "ms.\n";

    std::vector<int> poolSizes = {100, 1000, 2000, 5000}; // Valeurs pour les tailles de pool
    std::vector<int> threadCounts = {1, 2, 4, 8, 12, 16, 20, 24, 60};

    std::cout << std::setw(15) << std::left << "Pool Size" << std::setw(15) << std::left << "Nb Threads"
              << std::setw(20) << std::left << "Execution Time (ms)"
              << "\n";
    std::cout << std::string(50, '-') << "\n";

    for (int pool : poolSizes)
    {
        for (int nb_thread : threadCounts)
        {
            start = std::chrono::steady_clock::now();

            // Appel de la fonction à mesurer
            compute_with_pixel_jobs(scene, lights, pixels, pool, nb_thread);

            end = std::chrono::steady_clock::now();
            auto execTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

            // Affichage dans un tableau
            std::cout << std::setw(15) << std::left << pool << std::setw(15) << std::left << nb_thread << std::setw(20)
                      << std::left << execTime << "\n";
        }
    }

    delete[] pixels;
}

/*
Time for compute_raw : 4648ms.
Pool Size      Nb Threads     Execution Time (ms)
--------------------------------------------------
100            1              7611
100            2              4587
100            4              3019
100            8              2105
100            12             2059
100            16             1651
100            20             1781
100            24             3047
100            60             9342
1000           1              6180
1000           2              3791
1000           4              2687
1000           8              1908
1000           12             1678
1000           16             1586
1000           20             1597
1000           24             2292
1000           60             8424
2000           1              6378
2000           2              3891
2000           4              2708
2000           8              1989
2000           12             1807
2000           16             1591
2000           20             1511
2000           24             1856
2000           60             7365
5000           1              6540
5000           2              3798
5000           4              2674
5000           8              2236
5000           12             1657
5000           16             1581
5000           20             1430
5000           24             1478
5000           60             4934
 */
