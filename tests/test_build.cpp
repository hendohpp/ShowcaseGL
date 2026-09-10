#include <iostream>
#include "showcasegl/Application.hpp"
#include "showcasegl/error.hpp"

int main(void) {
    std::cout << "build_test ran successfully\n";

    auto app = showcasegl::Application::create("win", -1, -1, false);
    if (!app) {
        std::cout << showcasegl::errorToString(app.error()) << "\n";
    }

    return 0;
}