#include "vec3.h"
#include "color.h"
#include "ray.h"
#include <iostream>

// We can simulate a ray hitting a sphere at the origin of the scene via the following function:

double hit_sphere(const point3& center, double radius, const ray& r) {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = half_b * half_b - a * c;

    if (discriminant < 0) {
        return -1.0;
    }
    else {
        return (-half_b - sqrt(discriminant)) / a;
    }
}


// Computes the ray color and returns a simple gradient background.
// Linear interpolation!

color ray_color(const ray& r) {
    auto t = hit_sphere(point3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        vec3 normal = unit_vector(r.at(t) - vec3(0, 0, -1));
        return 0.5 * color(normal.x() + 1, normal.y() + 1, normal.z() + 1);
    }

    vec3 unit_direciton = unit_vector(r.direction());
    t = 0.5 * (unit_direciton.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {
    // Identifying the image dimensions and properties:

    const auto aspect_ratio = 16.0 / 9.0;
    const int img_width = 400;
    const int img_height = static_cast<int>(img_width / aspect_ratio);

    // Creating the camera:

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

    // Rendering Image in PPM format:

    std::cout << "P3\n" << img_width << ' ' << img_height << "\n255\n";

    for (int i = img_height - 1; i >= 0; --i) {

        // Progress indicator for rendering:
        std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;

        for (int j = 0; j < img_width; ++j) {

            // Construction of rays:

            auto u = double(j) / (img_width - 1);
            auto v = double(i) / (img_height - 1);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "Finished!\n";
}