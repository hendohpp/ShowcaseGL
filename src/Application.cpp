#include "showcasegl/Application.hpp"

// clang-format off
// ensures glad included before glfw
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

namespace showcasegl {

std::expected<Application, ApplicationError>
Application::create(const std::string& winName, int winWidth, int winHeight) {
    if (!glfwInit()) {
        return std::unexpected(ApplicationError::GlfwInitializationFailed);
    }

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#else
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    std::unique_ptr<GLFWwindow, GLFWWindowDeleter> window{
        glfwCreateWindow(winWidth, winHeight, winName.c_str(), nullptr, nullptr)
    };

    if (!window) {
        glfwTerminate();
        return std::unexpected(ApplicationError::GlfwWindowCreationFailed);
    }

    glfwMakeContextCurrent(window.get());

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        window.reset();
        glfwTerminate();
        return std::unexpected(ApplicationError::GladInitializationFailed);
    }

    return Application{std::move(window)};
}

Application::Application(std::unique_ptr<GLFWwindow, GLFWWindowDeleter> window)
    : m_win(std::move(window)) {}

Application::~Application() {
    if (!m_win) {
        return;
    }
    m_win.reset();
    glfwTerminate();
}

// compiler manages move semantics
Application::Application(Application&&) noexcept = default;
Application& Application::operator=(Application&&) noexcept = default;

void Application::GLFWWindowDeleter::operator()(GLFWwindow* win) const noexcept {
    if (win) {
        glfwDestroyWindow(win);
    }
}

bool Application::isRunning() const {
    return m_win && !glfwWindowShouldClose(m_win.get());
}

void Application::beginFrame() {
    float currFrameTime = static_cast<float>(glfwGetTime());
    m_deltaTime = currFrameTime - m_prevFrameTime;
    m_prevFrameTime = currFrameTime;

    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Application::endFrame() {
    if (!m_win) {
        return;
    }
    glfwSwapBuffers(m_win.get());
}

float Application::getDeltaTime() const noexcept {
    return m_deltaTime;
}

} // namespace showcasegl