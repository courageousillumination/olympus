#include <chrono>

#include "debug/logger.hpp"
#include "debug/fps.hpp"

using namespace std::chrono;

static bool LOG_FPS = false;
static double running_fps = 0.0;
static double running_spf = 0.0;
static high_resolution_clock::time_point last_time;
static unsigned num_frames = 0;


void olympus::fps::enable_fps_logging(bool flag) {
    LOG_FPS = flag;
}

void olympus::fps::fps_tick() {
    num_frames++;
    high_resolution_clock::time_point current_time = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(current_time - last_time);
    if (time_span.count() > 0.5) {
        running_fps = num_frames / time_span.count();
        running_spf = time_span.count() / num_frames;
        num_frames = 0;
        if (LOG_FPS) {
            LOG(Logger::INFO, "FPS: %f, SPF: %f", running_fps, running_spf);
        }
        last_time = current_time;
    }
}

double olympus::fps::get_fps() {
    high_resolution_clock::time_point current_time = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(current_time - last_time);
    return num_frames / time_span.count();
}