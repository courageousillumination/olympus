#include <gtest/gtest.h>

#include "olympus.hpp"
#include "render/screen.hpp"

#include "render_fixture.hpp"

using namespace olympus;

class ScreenTest : public RenderTest {
protected:
    virtual void SetUp() {
        screen = new Screen; //Should this be using a manager? 
    }
    
    virtual void TearDown() {
        delete screen;
    }
    Screen *screen;
};

TEST_F (ScreenTest, GettersAndSetters) {
    //...test getters and setters.
}
