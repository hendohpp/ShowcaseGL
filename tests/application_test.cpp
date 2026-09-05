#include <cassert>
#include <iostream>

#include "showcasegl/Application.hpp"
#include "showcasegl/error.hpp"

int main() {
    auto res = showcasegl::Application::create("Test Application Window", 1920, 1080, true);
    if (!res) {
        std::cout << showcasegl::errorToString(res.error()) << "\n";
        return -1;
    }
    showcasegl::Application app{std::move(*res)};

    while (app.isRunning()) {
        app.beginFrame();

        app.endFrame();
    }

    return 0;
}