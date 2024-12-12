#pragma once
#include <Scene.hpp>
#include <fstream>
namespace pr
{
class Utils
{
  public:
    // return the index of the closest object in the scene that intersects "ray"
    // or -1 if the ray does not intersect any object.
    static int findClosestInter(const pr::Scene &scene, const pr::Rayon &ray)
    {
        auto minz = std::numeric_limits<float>::max();
        int targetSphere = -1;
        int index = 0;
        for (const auto &obj : scene)
        {
            // rend la distance de l'objet a la camera
            auto zinter = obj.intersects(ray);
            // si intersection plus proche  ?
            if (zinter < minz)
            {
                minz = zinter;
                targetSphere = index;
            }
            index++;
        }
        return targetSphere;
    }

    // Calcule l'angle d'incidence du rayon à la sphere, cumule l'éclairage des lumières
    // En déduit la couleur d'un pixel de l'écran.
    static pr::Color computeColor(const pr::Sphere &obj, const pr::Rayon &ray, const pr::Vec3D &camera,
                                  std::vector<pr::Vec3D> &lights)
    {
        pr::Color finalcolor = obj.getColor();

        // calcul du rayon et de sa normale a la sphere
        // on prend le vecteur de la camera vers le point de l'ecran (dest - origine)
        // on le normalise a la longueur 1, on multiplie par la distance à l'intersection
        pr::Vec3D rayInter = (ray.dest - ray.ori).normalize() * obj.intersects(ray);
        // le point d'intersection
        pr::Vec3D intersection = rayInter + camera;
        // la normale a la sphere au point d'intersection donne l'angle pour la lumiere
        pr::Vec3D normal = obj.getNormale(intersection);
        // le niveau d'eclairage total contribue par les lumieres 0 sombre 1 total lumiere
        double dt = 0;
        // modifier par l'eclairage la couleur
        for (const auto &light : lights)
        {
            // le vecteur de la lumiere au point d'intersection
            pr::Vec3D tolight = (light - intersection);
            // si on est du bon cote de la sphere, i.e. le rayon n'intersecte pas avant de l'autre cote
            if (obj.intersects(pr::Rayon(light, intersection)) >= tolight.length() - 0.05)
            {                                       //  epsilon 0.05 for double issues
                dt += tolight.normalize() & normal; // l'angle (scalaire) donne la puissance de la lumiere reflechie
            }
        }
        // eclairage total
        finalcolor = finalcolor * dt + finalcolor * 0.2; // *0.2 = lumiere speculaire ambiante

        return finalcolor;
    }

    // produit une image dans path, représentant les pixels.
    static void exportImage(const char *path, size_t width, size_t height, pr::Color *pixels)
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

};
}