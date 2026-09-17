#include "showcasegl/Application.hpp"

// clang-format off
// ensures glad included before glfw
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

namespace showcasegl {

// private internal state definition.
// the app state is held in a smart pointer, its members need to be accessed via ->
// client code doesn't need to know that
struct Application::AppState {
    struct GLFWWindowDeleter {
        void operator()(GLFWwindow* win) const noexcept {
            if (win) {
                glfwDestroyWindow(win);
            }
        }
    };

    std::unique_ptr<GLFWwindow, GLFWWindowDeleter> win;
    float deltaTime{0.0f};
    float prevFrameTime{0.0f};

    ~AppState() {
        win.reset();
        glfwTerminate();
    }
};

std::expected<Application, ApplicationError>
Application::create(const std::string& winName, int winWidth, int winHeight, bool resizable) {
    if (winWidth <= 0 || winHeight <= 0) {
        return std::unexpected(ApplicationError::InvalidWindowSize);
    }

    if (winName.empty()) {
        return std::unexpected(ApplicationError::InvalidWindowName);
    }

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
    glfwWindowHint(GLFW_RESIZABLE, resizable);

    std::unique_ptr<GLFWwindow, AppState::GLFWWindowDeleter> win{
        glfwCreateWindow(winWidth, winHeight, winName.c_str(), nullptr, nullptr)
    };

    if (!win) {
        glfwTerminate();
        return std::unexpected(ApplicationError::GlfwWindowCreationFailed);
    }

    glfwMakeContextCurrent(win.get());

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        return std::unexpected(ApplicationError::GladInitializationFailed);
    }

    auto appState = std::make_unique<AppState>();
    appState->win = std::move(win);

    return Application(std::move(appState));
}

Application::Application(std::unique_ptr<AppState> appState)
    : m_appState(std::move(appState)) {}

Application::~Application() = default;
Application::Application(Application&&) noexcept = default;
Application& Application::operator=(Application&&) noexcept = default;

bool Application::isRunning() const {
    return m_appState && m_appState->win && !glfwWindowShouldClose(m_appState->win.get());
}

void Application::beginFrame() {
    if (!m_appState || !m_appState->win) {
        return;
    }

    float currFrameTime{static_cast<float>(glfwGetTime())};
    m_appState->deltaTime = currFrameTime - m_appState->prevFrameTime;
    m_appState->prevFrameTime = currFrameTime;

    glfwPollEvents();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Application::endFrame() {
    if (!m_appState || !m_appState->win) {
        return;
    }

    glfwSwapBuffers(m_appState->win.get());
}

float Application::getDeltaTime() const noexcept {
    if (!m_appState) {
        return 0.0f;
    }

    return m_appState->deltaTime;
}

} // namespace showcasegl