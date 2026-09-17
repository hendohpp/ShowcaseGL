#ifndef SHOWCASEGL_APPLICATION_HPP__
#define SHOWCASEGL_APPLICATION_HPP__

#include <expected>
#include <memory>
#include <string>

#include "showcasegl/error.hpp"

namespace showcasegl {

class Application {
public:
    /**
     * @brief creates and initializes an application.
     * 
     * @details initializes a window, input handling, and opengl context.
     *          to ensure no runtime exceptions occur, any failure while initializing the window
     *          is returned as an error code, and thus should be checked by the caller.
     * 
     * @param[in] winName the name to be displayed by the window manager
     * @param[in] winWidth number of horizontal screen coordinates
     * @param[in] winHeight number of vertical screen coordinates
     * @param[in] resizable flag that determines if window cam be resized after creation
     * 
     * @return the application object or error code that occured during initialization.
     */
    static std::expected<Application, ApplicationError> create(
        const std::string& winName,
        int winWidth = 1280,
        int winHeight = 720,
        bool resizable = false
    );

    // delete copy (implicit) and allow move
    ~Application();
    Application(Application&&) noexcept;
    Application& operator=(Application&&) noexcept;

    /**
     * @brief checks if the app window is open and active.
     * 
     * @return if the app has not been instructed to stop
     */
    bool isRunning() const;
    
    /**
     * @brief prepares the app window to render a new frame.
     * 
     * @details polls events, clears buffers, and updates delta time
     */
    void beginFrame();
    
    /**
     * @brief displays a rendered frame to the screen.
     * 
     * @details finalizes drawing and swaps front and back buffer
     */
    void endFrame();

    /**
     * @brief retrieves previous frame duration in seconds.
     * 
     * @return the time elapsed from the start of the last frame, and the start of the current frame
     */
    float getDeltaTime() const noexcept;

private:
    struct AppState;
    std::unique_ptr<AppState> m_appState;

    explicit Application(std::unique_ptr<AppState> appState);
};

}; // namespace showcasegl

#endif // SHOWCASEGL_APPLICATION_HPP__