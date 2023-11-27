#pragma once

#include <chrono>
#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "utils/vector3d/vector3d.h"

struct Pixel
{
    Vector3D color;
    int debug_counter;
    std::chrono::steady_clock::duration time;
};

bool pixelTimeComp(const Pixel &a, const Pixel &b) { return a.time < b.time; }

template <typename T>
inline T unit_clamp(T value) { return std::clamp<T>(value, 0.0f, 1.0f); }
template <typename T>
inline T unit8_clamp(T value) { return std::clamp<T>(value, 0.0f, 255.0f); }

class Image
{
    public:
        std::vector<Pixel> pixels;

        void set_dimensions(const int new_width, const int new_height);
        int width() const;
        int height() const;

        void post_process(const double exposure, const double gamma);
        bool write_color_image(const std::string filepath) const;
//        bool write_time_image(const std::string filepath, const double outlier_percentage = 5) const;
//        bool write_depth_image(const std::string filepath, const double outlier_percentage = 5) const;
//        bool write_transform_image(const std::string filepath, std::function<double (const Pixel&)> transform, const double outlier_percentage = 5) const;
   private:
        int _width;
        int _height;
};

void Image::set_dimensions(const int new_width, const int new_height)
{
    _width = new_width;
    _height = new_height;
    pixels.resize(_width * _height);
}

inline Vector3D tone_map(const Vector3D &color, const double exposure)
{
    return Vector3D(1.0f - exp(-color[0] * exposure),
                1.0f - exp(-color[1] * exposure),
                1.0f - exp(-color[2] * exposure));
}

inline Vector3D gamma_correct(const Vector3D &color, const double gamma)
{
    return Vector3D(pow(color[0], 1.0f / gamma),
                pow(color[1], 1.0f / gamma),
                pow(color[2], 1.0f / gamma));
}

void Image::post_process(const double exposure, const double gamma)
{
    std::for_each(std::execution::par_unseq, pixels.begin(), pixels.end(), [&](Pixel &pixel)
    {
        Vector3D c = pixel.color;

        c = tone_map(c, exposure);
        c = gamma_correct(c, gamma);

        pixel.color = c;
    });
}

bool Image::write_color_image(const std::string filepath) const
{
    std::vector<std::tuple<unsigned char, unsigned char, unsigned char>> pixels_8bit;
    pixels_8bit.resize(_width * _height);
    std::transform(std::execution::par_unseq, pixels.begin(), pixels.end(), pixels_8bit.begin(), [&](const Pixel &pixel)
    {
        Vector3D c = pixel.color * 255.99f;
        return std::make_tuple(unit8_clamp(c[2]), unit8_clamp(c[1]), unit8_clamp(c[0]));
    });
    return stbi_write_png(filepath.c_str(), _width, _height, 3, pixels_8bit.data(), _width * 3);
}

//bool Image::write_time_image(const std::string filepath, const double outlier_percentage) const
//{
//    return write_transform_image(filepath, [](const Pixel &pixel) {
//        return static_cast<double>(pixel.time.count());
//    }, outlier_percentage);
//}

//bool Image::write_depth_image(const std::string filepath, const double outlier_percentage) const
//{
//    return write_transform_image(filepath, [](const Pixel &pixel) {
//        return static_cast<double>(pixel.depth);
//    }, outlier_percentage);
//}

//bool Image::write_transform_image(const std::string filepath, std::function<double (const Pixel&)> transform, const double outlier_percentage) const
//{
//    const int num_pixels = _width * _height;
//    std::vector<double> values;
//    values.resize(_width * _height);
//    std::transform(std::execution::par_unseq, pixels.begin(), pixels.end(), values.begin(), transform);

//    // calculate range
//    auto low = values.begin() + static_cast<int>(num_pixels * outlier_percentage / 100.0f);
//    std::nth_element(std::execution::seq, values.begin(), low, values.end());
//    auto high = values.begin() + static_cast<int>(num_pixels - num_pixels * outlier_percentage / 100.0f - 1);
//    std::nth_element(std::execution::seq, values.begin(), high, values.end());

//    auto base = *low;
//    auto range = *high - base;
//    std::cout << *low << " " << *high << " " << base << " " << range << "\n";

//    std::vector<std::tuple<unsigned char, unsigned char, unsigned char>> pixels_8bit;
//    pixels_8bit.resize(_width * _height);
//    std::transform(std::execution::par_unseq, pixels.begin(), pixels.end(), pixels_8bit.begin(), [&](const Pixel &pixel)
//    {
//        const double duration = (transform(pixel) - base) / range;
//        Vec3 c = Vec3(unit8_clamp(duration * 255.99));
//        return std::make_tuple(c[2], c[1], c[0]);
//    });
//    return stbi_write_png(filepath.c_str(), _width, _height, 3, pixels_8bit.data(), _width * 3);
//}
