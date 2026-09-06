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
    static std::expected<Application, ApplicationError> create(
        const std::string& winName,
        int winWidth = 1280,
        int winHeight = 720,
        bool resizable = false
    );

    // cleans up GLFW window and context resources
    ~Application();

    // disable copying to ensure unique onwership of GLFW context
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    // allow move to transfer GLFW ownership
    Application(Application&&) noexcept;
    Application& operator=(Application&&) noexcept;

    // checks if the app window is open and active
    bool isRunning() const;
    // prepares the app window to render a new frame
    void beginFrame();
    // displays a rendered frame to the screen
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