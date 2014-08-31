#ifndef OLYMPUS__COMMON__TEST_BLOCK
#define OLYMPUS__COMMON__TEST_BLOCK

#include <glm/glm.hpp>

bool expect_color_block(unsigned x, unsigned y,
                        unsigned width, unsigned height,
                        float r, float g, float b);
glm::vec3 average_color_block(unsigned x, unsigned y,
                              unsigned width, unsigned height);
#endif