#ifndef SHOWCASEGL_ERROR_HPP__
#define SHOWCASEGL_ERROR_HPP__

#include <string_view>

namespace showcasegl {

// error types

enum class ApplicationError {
    GlfwInitializationFailed,
    GlfwWindowCreationFailed,
    GladInitializationFailed,
    InvalidWindowName,
    InvalidWindowSize,
};

enum class ShaderError {
    VertexShaderCompilationFailed,
    FragmentShaderCompilationFailed,
    ShaderProgramLinkFailed,
};

// error to string conversion helpers

constexpr static std::string_view enumToString(showcasegl::ApplicationError errorCode) {
    switch (errorCode) {
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

constexpr static std::string_view enumToString(showcasegl::ShaderError errorCode) {
    switch (errorCode) {
        case showcasegl::ShaderError::VertexShaderCompilationFailed:
            return "showcasegl::ShaderError::VertexShaderCompilationFailed";
        case showcasegl::ShaderError::FragmentShaderCompilationFailed:
            return "showcasegl::ShaderError::FragmentShaderCompilationFailed";
        case showcasegl::ShaderError::ShaderProgramLinkFailed:
            return "showcasegl::ShaderError::ShaderProgramLinkFailed";
    }
    return "Unknown ShaderError";
}

// error to string public api

template <typename T> constexpr std::string_view errorToString(T errorCode) {
    return enumToString(errorCode);
}

}; // namespace showcasegl

#endif // SHOWCASEGL_ERROR_HPP__