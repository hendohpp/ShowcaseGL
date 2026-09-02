#ifndef SHOWCASEGL_ERROR_HPP__
#define SHOWCASEGL_ERROR_HPP__

#include <string_view>

namespace showcasegl {


enum class ApplicationError {
    None,
    GlfwInitializationFailed,
    GlfwWindowCreationFailed,
    GladInitializationFailed,
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
    }
    return "Unknown ApplicationError";
}

template <typename T> constexpr std::string_view errorToString(T errorCode) {
    return enumToString(errorCode);
}

}; // namespace showcasegl

#endif // SHOWCASEGL_ERROR_HPP__