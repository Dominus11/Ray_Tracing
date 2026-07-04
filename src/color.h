# ifndef COLOR_H
# define COLOR_H

#include "common.h"
#include "interval.h"

using Color = Vec3;

void write_color(std::ostream& out, const Color& pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Translate the [0,1] component values to the byte range [0,255].
    static const Interval intensity = Interval(0, 0.999);
    auto rbyte = int(256*intensity.clamp(r));
    auto gbyte = int(256*intensity.clamp(g));
    auto bbyte = int(256*intensity.clamp(b));

    // Write out the pixel color components.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif