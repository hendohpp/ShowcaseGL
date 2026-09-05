#ifndef SHOWCASEGL_ERROR_HPP__
#define SHOWCASEGL_ERROR_HPP__

#include <string_view>

namespace showcasegl {

enum class ApplicationError {
    None,
    GlfwInitializationFailed,
    GlfwWindowCreationFailed,
    GladInitializationFailed,
    InvalidWindowName,
    InvalidWindowSize,
};

constexpr static std::string_view enumToString(showcasegl::ApplicationError errorCode) {
    switch (errorCode) {
        case showcasegl::ApplicationError::None:
            return "showcasegl::ApplicationError::None";
        case showcasegl::ApplicationError::GlfwInitializationFailed:
            return "showcasegl::ApplicationError::GlfwInitializationFailed";
        case showcasegl::ApplicationError::GlfwWindowCreationFailed:
            return "showcasegl::ApplicationError::GlfwWindowCreationFailed";
        case showcasegl::ApplicationError::GladInitializationFailed:
            return "showcasegl::ApplicationError::GladInitializationFailed";
        case showcasegl::ApplicationError::InvalidWindowName:
            return "showcasegl::ApplicationError::InvalidWindowName";
        case showcasegl::ApplicationError::InvalidWindowSize:
            return "showcasegl::ApplicationError::InvalidWindowSize";
    }
    return "Unknown ApplicationError";
}

template <typename T> constexpr std::string_view errorToString(T errorCode) {
    return enumToString(errorCode);
}

}; // namespace showcasegl

#endif // SHOWCASEGL_ERROR_HPP__