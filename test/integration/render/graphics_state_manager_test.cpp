#include <gtest/gtest.h>

#include "olympus.hpp"
#include "render/asset.hpp"

#include "common/olympus_environment.hpp"
#include "common/fixtures/window_fixture.hpp"

using namespace olympus;

TEST_F (WindowedTest, GraphicsStateManagerTestStack) {
    GraphicsStateManager &manager = GraphicsStateManager::get_instance();
    GraphicsState *state = new GraphicsState;
    
    manager.push(state);
    
    EXPECT_EQ(state, manager.get_head());
    
    manager.pop();
    
    EXPECT_TRUE(manager.get_head() == nullptr);
    
    //Check some error conditions
    get_test_appender()->set_expect_error(true);
    
    manager.pop();
    
    EXPECT_TRUE(get_test_appender()->contains_string("Tried to pop off of an empty graphics state stack."));
    
    get_test_appender()->set_expect_error(false);
    
    get_test_appender()->set_expect_warning(true);
    
    manager.push(nullptr);
    
    EXPECT_TRUE(get_test_appender()->contains_string("Tried to push a null graphics state onto the stack"));
    
    get_test_appender()->set_expect_warning(false);
    
    delete state;
}