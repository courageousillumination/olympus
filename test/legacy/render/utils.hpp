#ifndef OLYMPUS__TEST__RENDER__UTILS
#define OLYMPUS__TEST__RENDER__UTILS

#include "olympus.hpp"

/**
 * Checks the currently bound frame buffer to see that an entire
 * block is of the expected color
 */
bool expect_color_block(unsigned x, unsigned y, unsigned width, unsigned height,
                        float r, float g, float b);

olympus::Renderable *create_square(float x, float y, float width, float height,
                          float r, float g, float b);
void destroy_square(olympus::Renderable *renderable);
#endif