#include <gtest/gtest.h>

#include "showcasegl/Application.hpp"

TEST(ApplicationTest, CreateApp) {
    {
        auto appResult = showcasegl::Application::create("Test Application Window", 1920, 1080, true);
        ASSERT_TRUE(appResult.has_value());

        showcasegl::Application app = std::move(appResult.value());
        EXPECT_TRUE(app.isRunning());
    }
}