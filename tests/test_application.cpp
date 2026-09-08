#include <gtest/gtest.h>

#include "showcasegl/Application.hpp"

TEST(ApplicationTest, CreateApp) {
    {
        auto result = showcasegl::Application::create("Test Application Window", 1920, 1080, true);

        ASSERT_TRUE(result.has_value());

        showcasegl::Application app{std::move(*result)};
        EXPECT_TRUE(app.isRunning());
    }
}