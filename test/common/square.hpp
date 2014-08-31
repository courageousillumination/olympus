#ifndef OLYMPUS__COMMON__CREATE_SQUARE
#define OLYMPUS__COMMON__CREATE_SQUARE

#include "olympus.hpp"
olympus::Renderable *create_square(float x, float y, float width, float height,
                          float r, float g, float b);
/**
 * Create a square with a given renderer. Note that this will take possesion
 * and will be destroyed when you destroy_square
 */
olympus::Renderable *create_square(float x, float y, float width, float height,
                                   float r, float g, float b, olympus::Renderer *renderer);
void destroy_square(olympus::Renderable *renderable);
#endif