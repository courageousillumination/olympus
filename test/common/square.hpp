#ifndef OLYMPUS__COMMON__CREATE_SQUARE
#define OLYMPUS__COMMON__CREATE_SQUARE

#include "olympus.hpp"
olympus::Renderable *create_square(float x, float y, float width, float height,
                          float r, float g, float b);
void destroy_square(olympus::Renderable *renderable);
#endif