#include <array>
#include "camera.h"
#include "visualization.h"

#include <iostream>
#include <vector>

#include <glm/glm.hpp>

#include "polyscope/curve_network.h"
#include "polyscope/point_cloud.h"

int main()
{
    // World units: meters (m)
    point3 camera_position(0.3, 0.4, 0.5);  // Camera position
    point3 look_at(0, 0, 0);                // Look-at point
    vec3 up(0, 0, 1);                       // Up direction
    double focal_length_mm = 35.0;
    double sensor_height_mm = 24.0;         // full-frame sensor
    int pixel_width = 16;
    int pixel_height = 9;
    
    camera cam(camera_position, look_at, up, focal_length_mm, sensor_height_mm, pixel_width, pixel_height);

    // Initialize Polyscope
    viz::init_polyscope_zup();

    // Iterate over pixels, build visualization data (and print)
    point3 cam_center = cam.get_center();

    std::vector<glm::vec3> camera_point = {viz::to_glm_vec3(cam_center)};

    std::vector<glm::vec3> pixel_points;
    pixel_points.reserve(cam.pixel_width * cam.pixel_height);

    std::vector<glm::vec3> ray_nodes;
    std::vector<std::array<size_t, 2>> ray_edges;
    ray_nodes.reserve(2 * cam.pixel_width * cam.pixel_height);
    ray_edges.reserve(cam.pixel_width * cam.pixel_height);

    for (int j = 0; j < cam.pixel_height; j++) {
        for (int i = 0; i < cam.pixel_width; i++) {
            point3 pixel_pos = cam.get_pixel_position(i, j);
            pixel_points.push_back(viz::to_glm_vec3(pixel_pos));

            // Camera -> Pixel segment
            size_t cam_node_idx = ray_nodes.size();
            ray_nodes.push_back(viz::to_glm_vec3(cam_center));
            size_t pixel_node_idx = ray_nodes.size();
            ray_nodes.push_back(viz::to_glm_vec3(pixel_pos));
            ray_edges.push_back({cam_node_idx, pixel_node_idx});

            std::cout << "Pixel (" << i << ", " << j << "): " << pixel_pos << std::endl;
        }
    }

    // Register data with Polyscope
    bool radius_is_relative = true;

    auto* cam_cloud = polyscope::registerPointCloud("Camera Position", camera_point);
    cam_cloud->setPointRadius(0.01, /*isRelative=*/radius_is_relative);

    auto* pixel_cloud = polyscope::registerPointCloud("Pixel Positions", pixel_points);
    pixel_cloud->setPointRadius(0.003, /*isRelative=*/radius_is_relative);

    auto* ray_network = polyscope::registerCurveNetwork("Camera Rays", ray_nodes, ray_edges);
    ray_network->setRadius(0.001, /*isRelative=*/radius_is_relative);

    // Add axes and run the visualization UI
    double axis_length = 0.5;
    viz::AxesVizOptions axes_opt;
    axes_opt.radius_is_relative = true;
    axes_opt.axis_radius = 0.005;
    viz::register_axes(axis_length, glm::vec3(0.0f, 0.0f, 0.0f), axes_opt);
    viz::show();

    return 0;
}
