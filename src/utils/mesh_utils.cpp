#include <vector>

#include "utils/mesh_utils.hpp"

unsigned *olympus::generate_plane_indices(unsigned width, unsigned height) {
    unsigned *indices = new unsigned[(width - 1) * (height - 1) * 6];
    unsigned *ind = indices;

    for (unsigned i = 0; i < height; i++) {
        for (unsigned j = 0; j < width; j++) {
            //No need to make indices for the last row/column
            if (i == width - 1 or j == height - 1) {
                continue;
            }

            *ind++ = i * width + j;
            *ind++ = (i + 1) * width + j;
            *ind++ = (i + 1) * width + j + 1;

            *ind++ = i * width + j;
            *ind++ = (i + 1) * width + j + 1;
            *ind++ = i * width + j + 1;

        }
    }

    return indices;
}

glm::vec3 *olympus::generate_normals(glm::vec3 *verts, unsigned *indices,
                                     unsigned num_indices, unsigned num_verts) {
    glm::vec3 *normals = new glm::vec3[num_verts];
    for (unsigned i = 0; i < num_verts; i++) {
        normals[i] = glm::vec3(0, 0, 0);
    }

    for (unsigned i = 0; i < num_indices; i+= 3) {
        glm::vec3 p1 = verts[indices[i]];
        glm::vec3 p2 = verts[indices[i + 1]];
        glm::vec3 p3 = verts[indices[i + 2]];

        glm::vec3 normal = glm::cross(p2 - p1, p3 - p1);
        normals[indices[i]] += normal;
        normals[indices[i + 1]] += normal;
        normals[indices[i + 2]] += normal;
    }

    for (unsigned i = 0; i < num_verts; i++) {
        normals[i] = glm::normalize(normals[i]);
    }

    return normals;
}

glm::vec3 olympus::position_helper(unsigned width, unsigned height, unsigned x, unsigned y, void *scale) {
    float cell_size = *(float *)scale;
    return glm::vec3(cell_size * x, 0, cell_size * y);
}

glm::vec2 olympus::position_helper_2D(unsigned width, unsigned height, unsigned x, unsigned y, void *scale) {
    float cell_size = *(float *)scale;
    return glm::vec2(cell_size * x, cell_size * y);
}


glm::vec3 olympus::heightmap_sub(unsigned width, unsigned height, unsigned x, unsigned y, void *height_map) {
    return glm::vec3((float) x / width, ((float *) height_map)[y * width + x], (float) y / width);
}


/* Simple function to convert between coordinates */
static glm::vec3 spherical_to_cartesian(double theta, double phi, float radius) {
    return glm::vec3(radius * sin(theta) * cos(phi),
                     radius * sin(theta) * sin(phi),
                     radius * cos(theta));
}

olympus::Mesh *olympus::create_uv_sphere(float radius, unsigned rows, unsigned cols) {
    olympus::Mesh *mesh = new olympus::Mesh(2, olympus::Mesh::TRIANGLES);

    std::vector<glm::vec3> verticies;
    std::vector<glm::vec3> colors;
    std::vector<unsigned> indicies;
    unsigned current_index = 0;

    for(unsigned t = 0; t < rows; t++) {
        double theta1 = (double) t / rows * 3.14;
        double theta2 = (double) (t+1) / rows * 3.14;
        for(unsigned p = 0; p < cols; p++) {
            double phi1 = (double) p / cols * 2 * 3.14;
            double phi2 = (double) (p+1) / cols * 2 * 3.14;

            verticies.push_back(spherical_to_cartesian(theta1, phi1, radius));
            verticies.push_back(spherical_to_cartesian(theta1, phi2, radius));
            verticies.push_back(spherical_to_cartesian(theta2, phi2, radius));
            verticies.push_back(spherical_to_cartesian(theta2, phi1, radius));

            colors.push_back(glm::vec3(0, 1, 0));
            colors.push_back(glm::vec3(0, 1, 0));
            colors.push_back(glm::vec3(0, 1, 0));
            colors.push_back(glm::vec3(0, 1, 0));

            if (t==0) {
                indicies.push_back(current_index);
                indicies.push_back(current_index + 2);
                indicies.push_back(current_index + 3);
            } else if (t + 1 == rows) {
                indicies.push_back(current_index + 2);
                indicies.push_back(current_index);
                indicies.push_back(current_index + 1);
            } else {
                indicies.push_back(current_index);
                indicies.push_back(current_index + 1);
                indicies.push_back(current_index + 3);

                indicies.push_back(current_index + 1);
                indicies.push_back(current_index + 2);
                indicies.push_back(current_index + 3);
            }
            current_index += 4;
        }
    }

    mesh->set_vertex_attribute(0, 3, (int) verticies.size(), &verticies[0][0]);
    mesh->set_vertex_attribute(1, 3, (int) verticies.size(), &colors[0][0]);
    mesh->set_indices(indicies.size(), &indicies[0]);

    return mesh;
}
