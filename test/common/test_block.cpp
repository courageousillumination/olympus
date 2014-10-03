#include "olympus.hpp"
#include "test_block.hpp"

#define DELTA 0.01

bool within_delta(float expected, float value) {
    return value <= expected + DELTA && value >= expected - DELTA;
}

bool expect_color_block(unsigned x, unsigned y,
                        unsigned width, unsigned height,
                        float r, float g, float b) {
    float *data = new float[width * height * 3];
    glReadPixels(x, y, width, height, GL_RGB, GL_FLOAT, data);
    bool valid = true;
    for (unsigned i = 0; i < width * height; i++) {
        if (!within_delta(r, data[i * 3]) ||
            !within_delta(g, data[i * 3 + 1]) ||
            !within_delta(b, data[i * 3 + 2])) {
            //LOG(olympus::Logger::ERROR, "Expected %f %f %f, but found %f %f %f at pixel %d",
            //    r, g, b, data[i * 3], data[i * 3 + 1], data[i * 3 + 2], i);
            valid = false;
            break;
        }
    }
    delete []data;
    return valid;
}

glm::vec3 average_color_block(unsigned x, unsigned y,
                              unsigned width, unsigned height) {
    float *data = new float[width * height * 3];
    glReadPixels(x, y, width, height, GL_RGB, GL_FLOAT, data);
    double r = 0, g = 0, b = 0;
    
    for (unsigned i = 0; i < width * height; i++) {
        r += data[i * 3];
        g += data[i * 3 + 1];
        b += data[i * 3 + 2];
    }
    
    delete []data;
    return glm::vec3(r / (width * height), g / (width * height), b / (width * height));
    
}