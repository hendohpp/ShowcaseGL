#ifndef SHOWCASEGL_APPLICATION_HPP__
#define SHOWCASEGL_APPLICATION_HPP__

#include <expected>
#include <memory>
#include <string>

#include "showcasegl/error.hpp"

struct GLFWwindow;

namespace showcasegl {

class Application {
public:
    // creates and initializes the application, GLFW window, and OpenGL context
    static std::expected<Application, ApplicationError>
    create(const std::string& winName, int winWidth = 1280, int winHeight = 720);

    // destroys the GLFW window handle and terminates if window context is owned
    ~Application();

    // disable copy and assignment to prevent GLFW context sharing or duplication
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    // allow transfer of GLFW context with noexcept to optimize for STL container usage
    Application(Application&&) noexcept;
    Application& operator=(Application&&) noexcept;

    // checks if the window is open and active
    bool isRunning() const;
    // prepares the window to render a new frame
    void beginFrame();
    // displays the rendered frame to the screen
    void endFrame();

    // retrieves previous frame duration in seconds
    float getDeltaTime() const noexcept;

private:
    struct GLFWWindowDeleter {
        void operator()(GLFWwindow* win) const noexcept;
    };

    Application(std::unique_ptr<GLFWwindow, GLFWWindowDeleter> win);

    std::unique_ptr<GLFWwindow, GLFWWindowDeleter> m_win;

    float m_deltaTime{0.0f};
    float m_prevFrameTime{0.0f};
};

}; // namespace showcasegl

#endif // SHOWCASEGL_APPLICATION_HPP__