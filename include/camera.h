#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include <stdexcept>

class camera {
  public:
    // Constructor with parameters
    camera(point3 pos = point3(0, 0, 0), int width = 100, int height = 100)
        : center(pos), image_width(width), image_height(height) {
        initialize();
    }

    int image_width  = 100;
    int image_height = 100;

    // Get pixel position by x, y index
    point3 get_pixel_position(int i, int j) const {
        return pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
    }

  private:
    point3 center;         // Camera center
    point3 pixel00_loc;    // Location of pixel 0, 0
    vec3   pixel_delta_u;  // Offset to pixel to the right
    vec3   pixel_delta_v;  // Offset to pixel below

    void initialize() {
        // Validate image dimensions
        if (image_width < 1) {
            throw std::runtime_error("Error: image_width must be >= 1");
        }
        if (image_height < 1) {
            throw std::runtime_error("Error: image_height must be >= 1");
        }

        // Determine viewport dimensions.
        auto focal_length = 1.0;
        auto viewport_height = 2.0;
        auto viewport_width = viewport_height * (double(image_width)/image_height);

        // Calculate the vectors across the horizontal and down the vertical viewport edges.
        auto viewport_u = vec3(viewport_width, 0, 0);
        auto viewport_v = vec3(0, -viewport_height, 0);

        // Calculate the horizontal and vertical delta vectors from pixel to pixel.
        pixel_delta_u = viewport_u / image_width;
        pixel_delta_v = viewport_v / image_height;

        // Calculate the location of the upper left pixel.
        auto viewport_upper_left =
            center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }
};

#endif