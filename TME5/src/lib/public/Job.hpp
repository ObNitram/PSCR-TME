#pragma once
#include "Utils.hpp"
#include "Vec3D.hpp"

#include <Rayon.hpp>
#include <Scene.hpp>
#include <Sphere.hpp>
#include <thread>

namespace pr
{

class Job
{
  public:
    virtual void run() = 0;
    virtual ~Job() = default;
};

// Job concret : exemple

class SleepJob : public Job
{
    int calcul(int v)
    {
        std::cout << "Computing for arg =" << v << std::endl;
        // traiter un gros calcul
        std::this_thread::sleep_for(std::chrono::milliseconds(v));
        int ret = v % 255;
        std::cout << "Obtained for arg =" << arg << " result " << ret << std::endl;
        return ret;
    }
    int arg;
    int *ret;

  public:
    SleepJob(int arg, int *ret) : arg(arg), ret(ret) {}
    void run() { *ret = calcul(arg); }
    ~SleepJob() {}
};

class PixelJob final : public Job
{
    const Vec3D &screenPoint;
    Scene &scene;
    Color *pixels;
    std::vector<Vec3D> &lights;
    int _x;
    int _y;

  public:
    PixelJob(const Vec3D &screen_point, Scene &scene, Color *pixels, std::vector<Vec3D> &lights, const int x,
             const int y)
        : screenPoint(screen_point), scene(scene), pixels(pixels), lights(lights), _x(x), _y(y)
    {
    }

    void run() override
    {
        Rayon ray(scene.getCameraPos(), screenPoint);

        int targetSphere = Utils::findClosestInter(scene, ray);

        if (targetSphere == -1)
        {
            // keep background color
            return;
        }
        else
        {
            const pr::Sphere &obj = *(scene.begin() + targetSphere);
            // pixel prend la couleur de l'objet
            pr::Color finalcolor = Utils::computeColor(obj, ray, scene.getCameraPos(), lights);
            // le point de l'image (pixel) dont on vient de calculer la couleur
            pr::Color &pixel = pixels[_y * scene.getHeight() + _x];
            // mettre a jour la couleur du pixel dans l'image finale.
            pixel = finalcolor;
        }
    }
};

} // namespace pr
