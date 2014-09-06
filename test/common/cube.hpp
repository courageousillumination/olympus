#ifndef OLYMPUS__COMMON__CREATE_CUBE
#define OLYMPUS__COMMON__CREATE_CUBE

#include "olympus.hpp"

/* Creates a simple cube at the given position with the given scale. 
 * The faces will all be red (1, 0, 0)
 */
olympus::Renderable *create_cube(float x, float y, float z, float size);
olympus::Renderable *create_cube(float x, float y, float z, float size, olympus::Renderer *renderer);
void destroy_cube(olympus::Renderable *renderable);
#endif