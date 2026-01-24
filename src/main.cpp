#include <iostream>
#include "camera.h"

int main()
{
    // Create a camera with position, width, and height
    point3 camera_position(1, 2, 3);
    int image_width = 16;
    int image_height = 9;
    
    camera cam(camera_position, image_width, image_height);
    
    // Traverse all pixels by x, y index and print their positions
    for (int j = 0; j < image_height; j++) {
        for (int i = 0; i < image_width; i++) {
            point3 pixel_pos = cam.get_pixel_position(i, j);
            std::cout << "Pixel (" << i << ", " << j << "): " << pixel_pos << std::endl;
        }
    }

    return 0;
}
