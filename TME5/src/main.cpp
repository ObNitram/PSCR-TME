#include "Color.hpp"
#include "Pool.hpp"
#include "Rayon.hpp"
#include "Scene.hpp"
#include "Sphere.hpp"
#include "Vec3D.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>

void fillScene(pr::Scene &scene, std::default_random_engine &re)
{
    // Nombre de spheres (rend le probleme plus dur)
    constexpr int NBSPHERES = 2500;

    // on remplit la scene de spheres colorees de taille position et couleur aleatoire
    std::uniform_int_distribution<int> distrib(0, 200);
    std::uniform_real_distribution<double> distribd(-200, 200);
    for (int i = 0; i < NBSPHERES; i++)
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

// NB : en francais pour le cours, preferez coder en english toujours.
// pas d'accents pour eviter les soucis d'encodage

int main_base()
{
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    // on pose une graine basee sur la date
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
    // definir la Scene : resolution de l'image
    pr::Scene scene(1000, 1000);
    // remplir avec un peu d'aléatoire
    fillScene(scene, re);

    // lumieres
    std::vector<pr::Vec3D> lights;
    lights.reserve(3);
    lights.emplace_back(50, 50, -50);
    lights.emplace_back(50, 50, 120);
    lights.emplace_back(200, 0, 120);

    // les points de l'ecran, en coordonnées 3D, au sein de la Scene.
    // on tire un rayon de l'observateur vers chacun de ces points
    const pr::Scene::screen_t &screen = scene.getScreenPoints();

    // Les couleurs des pixels dans l'image finale
    auto *pixels = new pr::Color[scene.getWidth() * scene.getHeight()];

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

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Total time " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms.\n";

    exportImage("toto.ppm", scene.getWidth(), scene.getHeight(), pixels);

    delete[] pixels;

    return 0;
}

int main(int argc, char *argv[])
{
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    // on pose une graine basee sur la date
    std::default_random_engine re(std::chrono::system_clock::now().time_since_epoch().count());
    // definir la Scene : resolution de l'image
    pr::Scene scene(1000, 1000);
    // remplir avec un peu d'aléatoire
    fillScene(scene, re);

    // lumieres
    std::vector<pr::Vec3D> lights;
    lights.reserve(3);
    lights.emplace_back(50, 50, -50);
    lights.emplace_back(50, 50, 120);
    lights.emplace_back(200, 0, 120);

    // les points de l'ecran, en coordonnées 3D, au sein de la Scene.
    // on tire un rayon de l'observateur vers chacun de ces points
    const pr::Scene::screen_t &screen = scene.getScreenPoints();

    // Les couleurs des pixels dans l'image finale
    auto *pixels = new pr::Color[scene.getWidth() * scene.getHeight()];

    pr::Pool pool = pr::Pool(1000);

    pool.start(40);

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

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Total time " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms.\n";

    exportImage("toto.ppm", scene.getWidth(), scene.getHeight(), pixels);

    delete[] pixels;

    return 0;
}


