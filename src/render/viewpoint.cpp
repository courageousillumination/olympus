#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>

#include "render/viewpoint.hpp"

using namespace olympus;

Viewpoint::Viewpoint() {
    _fov = 60.0f * (3.1415f / 180.0f);
    _near = 0.5f;
    _far = 10.0f;
    _ratio = 4.0f / 3.0f;
    _update_projection_matrix();
}

void Viewpoint::_update_projection_matrix() {
    _projection_matrix = glm::perspective(_fov, _ratio, _near, _far);
}

glm::mat4 Viewpoint::get_view_matrix() {
    return _model_matrix;
}
glm::mat4 Viewpoint::get_projection_matrix() {
    return _projection_matrix;
}
glm::mat4 Viewpoint::get_view_projection_matrix() {
    return _model_matrix * _projection_matrix;
}

void Viewpoint::set_fov(float fov) {
    _fov = fov;
    _update_projection_matrix();
}
void Viewpoint::set_ratio(float ratio) {
    _ratio = ratio;
    _update_projection_matrix();
}
void Viewpoint::set_near(float near) {
    _near = near;
    _update_projection_matrix();
}
void Viewpoint::set_far(float far) {
    _far = far;
    _update_projection_matrix();
}

void Viewpoint::set_perspective(float fov, float ratio, float near, float far) {
    _fov = fov;
    _ratio = ratio;
    _near = near;
    _far = far;
    _update_projection_matrix();
}

float Viewpoint::get_fov() { return _fov; }
float Viewpoint::get_ratio() { return _ratio; }
float Viewpoint::get_near() { return _near; }
float Viewpoint::get_far() { return _far; }