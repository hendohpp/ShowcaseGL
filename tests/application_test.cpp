#include <cassert>

#include "showcasegl/Application.hpp"

int main() {
    auto res = showcasegl::Application::create("Test Application Window", 1920, 1080);
    showcasegl::Application app{std::move(*res)};

    while (app.isRunning()) {
        app.beginFrame();

        app.endFrame();
    }
}