#include <algorithm>
#include <cassert>
#include <cstring>
#include <chrono>
#include <execution>
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>
#include <iomanip>
#include "tbb/tbb.h"

#include "utils/vector3d/vector3d.h"
#include "utils/material/material.h"
#include "utils/ray/ray.h"
#include "object/visibleobject/sphere/sphere.h"
#include "object/invisibleobject/camera/camera.h"
#include "object/invisibleobject/kdtree/kdtree.h"
#include "object/visibleobject/box/box.h"
#include "image.hpp"
#include "object/invisibleobject/lightsource/lightsource.h"
#include "object/visibleobject/triangle/triangle.h"
#include "reader/stl_reader.h"


#ifndef MODELS_PATH
    #define MODELS_PATH "./models/"
#endif

#ifndef MODELS_FILE_TYPE
    #define MODELS_FILE_TYPE ".stl"
#endif


std::vector<std::shared_ptr<Object>> scene_objects;

Vector3D castRay(const Ray &r, const LightSource &source, const KDTree &scene, const int depth, HitInfo &data)
{
    Vector3D color(0.0f);

    if (scene.hit(r, 0.0f, MAXFLOAT, data))
    {
        const Ray sunray = source.get_ray(data.hit_point);
        Vector3D sunlight = source.intensity();

        HitInfo dummydata;
        if (scene.hit(sunray, 0.0f, MAXFLOAT, dummydata))
            sunlight *= 0.2f;

        color += data.material->ambient();
        color += data.material->diffuse() * sunlight;

        HitInfo buffer_data;
        Vector3D attenuation;
        Ray reflected_ray;

        data.material->get_reflect_ray(r, data, attenuation, reflected_ray);

        if (depth < 3)
            color += data.material->reflective() * castRay(reflected_ray, source, scene, depth + 1, buffer_data);
    }

    return color;
}

auto spawn_sphere(const Vector3D &position, const float radius, const std::shared_ptr<Material> &material)
{
    std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(position, radius, material);
    scene_objects.emplace_back(sphere);
    return sphere;
}

auto spawn_box(const Vector3D &position, const Vector3D &dimensions, const std::shared_ptr<Material> &material)
{
    std::shared_ptr<Box> box = std::make_shared<Box>(position, dimensions, material);
    scene_objects.emplace_back(box);
    return box;
}

auto spawn_triangle(const Vector3D &p1, const Vector3D &p2, const Vector3D &p3, const Vector3D &normal, const std::shared_ptr<Material> &material)
{
    std::shared_ptr<Triangle> triangle = std::make_shared<Triangle>(p1, p2, p3, normal, material);
    scene_objects.emplace_back(triangle);
    return triangle;
}

KDTree make_test_scene()
{
//    auto steel = std::make_shared<Material>(
//        Vector3D(0.2, 0.2, 0.2),
//        Vector3D(0.8, 0.8, 0.8),
//        0.02
//    );
//    auto iron = std::make_shared<Material>(
//        Vector3D(0.2, 0.2, 0.2),
//        Vector3D(0.4, 0.4, 0.4),
//        0.1
//    );
//    auto felt = std::make_shared<Material>(
//        Vector3D(0.8, 0.83, 0.8),
//        Vector3D(0.0),
//        0.0
//    );
//    auto red_felt = std::make_shared<Material>(
//        Vector3D(0.8, 0.2, 0.2),
//        Vector3D(0.0),
//        0.0
//    );
//    auto thing = std::make_shared<Material>(
//        Vector3D(0.5,0.2,0.2),
//        Vector3D(0.2,0.5,0.2),
//        0.01
//    );
    auto some = std::make_shared<Material>(
        Vector3D(0.5,0.2,0.2),
        Vector3D(0.2,0.5,0.2)
    );

//    spawn_sphere(scene, Vector3D(0, -100.5, 0), 100, steel);

//    spawn_sphere(Vector3D(0.5, 0.5, 0), 0.25, some);

//    spawn_sphere(scene, Vector3D(-1, 0, 0), 0.5, steel);
//     spawn_sphere(scene, Vector3D(0, 0, 0), 0.25, thing)->emissive = true;

    std::string ss = "pawn";

    stl_reader::StlMesh <float, unsigned int> mesh (MODELS_PATH + ss + MODELS_FILE_TYPE);

    for (size_t itri = 0; itri < mesh.num_tris(); ++itri)
    {
          Vector3D p [3];

          for(size_t icorner = 0; icorner < 3; ++icorner) {
            const float* c = mesh.tri_corner_coords (itri, icorner);
            p[icorner] = Vector3D(c[0], c[1], c[2]);
//            p[icorner] /= 3;
          }

          const float* n = mesh.tri_normal (itri);
          Vector3D normal(n[0], n[1], n[2]);
          spawn_triangle(p[0], p[1], p[2], normal, some);
    }

//     spawn_triangle(scene, Vec3(10, 0, 100), Vec3(0, 10, 100), Vec3(10, 10, 100), Vec3(0, 0, -1), steel);
//     spawn_triangle(scene, Vec3(10, 0, 50), Vec3(0, 10, 100), Vec3(10, 10, 100), Vec3(0, -1, 0), red_felt);
//     spawn_triangle(scene, Vec3(198, 198, 198), Vec3(105, 105, 105), Vec3(2.8, 2.8, 2.8), Vec3(-0.7, -0.7, 0), red_felt);
//     spawn_triangle(scene, Vec3(10, -5, 50), Vec3(0, -3, 100), Vec3(10, 0, 100), Vec3(0, 1, 0), iron);
//    spawn_triangle(scene, Vec3(10, 0, 100), Vec3(0, 10, 100), Vec3(10, 10, 100), Vec3(0, 0, 1), steel);
//    int w = 5;
//    int h = 5;
//    for (int i = 0; i < w * h; ++i)
//    {
//        Vec3 p = Vec3(i / w, i % w, 0) / w - Vec3(0.4);
//        p[2] = 0.5f;
//        spawn_sphere(scene, p, 0.09, steel);
//    }

//   spawn_box(Vector3D(0, 1, 0), Vector3D(10, 10, 10), some);
//    spawn_box(scene, Vector3D(0, 1, -3), Vector3D(1, 1, 1), red_felt);
//    spawn_box(scene, Vector3D(0, 2, -1), Vector3D(1, 1, 1), iron);

//     spawn_sphere(scene, Vec3(-0.5, 0, 0), 0.5, steel);
//     spawn_sphere(scene, Vec3(0, 0, 0), 0.25, red_felt);
//     spawn_sphere(scene, Vec3(0.5, 0, 0), 0.5, steel);

    KDTree scene(scene_objects);

    return scene;
}

template<typename T>
inline T lerp(double f, T a, T b)
{
    return (1.0f - f) * a + f * b;
}

int main(const int argc, const char* argv[])
{
    const int width = 1900;
    const int height = 1000;

    auto s = make_test_scene();
    Camera camera(Vector3D(210, 110, 0), Vector3D(0, 0, -1), static_cast<double>(width) / height);
    LightSource light(Vector3D(-5000, -5000, 5000), Vector3D(1, 1, 1));

    Image image;
    image.set_dimensions(width, height);

    std::mutex image_save_mutex;
    std::vector<int> indices(width * height);
    std::iota(indices.begin(), indices.end(), 0);


    tbb::parallel_for(0, width * height, 1, [&](int index)
    {
        const int j = height - index / width;
        const int i = index % width;
        Vector3D c{0, 0, 0};
        double t = 0;
        HitInfo data;
        const double u = float(i) / float(width);
        const double v = float(j) / float(height);
        const Ray r = camera.get_ray(u, v);
        c += castRay(r, light, s, 0, data);
        t += data.t;
        Pixel pixel;
        pixel.color = c;
        auto &pix = *(image.pixels.begin() + index);
        pix =  pixel;
    });

    auto filepath = std::ostringstream();
    filepath << "./" << std::setfill('0') << std::setw(3) << "01"<< ".png";

   // image.post_process(1.0f, 2.0f);
    image.write_color_image(filepath.str());
}
