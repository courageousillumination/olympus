#include <gtest/gtest.h>

#include <chrono>
#include <thread>

#include "olympus.hpp"
#include "debug/fps.hpp"

using namespace olympus;

class FPSTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        fps::enable_fps_logging(false);
    }
};

TEST_F(FPSTest, FPSTest) {
    fps::fps_tick();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    fps::fps_tick();
    EXPECT_TRUE(fps::get_fps() > 8.0 && fps::get_fps() < 12.0);
    
    for (unsigned i = 0; i < 100; i++) {
        fps::fps_tick();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    fps::fps_tick();
    EXPECT_TRUE(fps::get_fps() > 505.0 && fps::get_fps() < 510.0);
}