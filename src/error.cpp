#include "showcasegl/error.hpp"

namespace showcasegl {

std::string_view errorToString(ApplicationError errorCode) {
    switch (errorCode) {
        case ApplicationError::GlfwInitializationFailed:
            return "showcasegl::ApplicationError::GlfwInitializationFailed";
        case ApplicationError::GlfwWindowCreationFailed:
            return "showcasegl::ApplicationError::GlfwWindowCreationFailed";
        case ApplicationError::GladInitializationFailed:
            return "showcasegl::ApplicationError::GladInitializationFailed";
        case ApplicationError::InvalidWindowName:
            return "showcasegl::ApplicationError::InvalidWindowName";
        case ApplicationError::InvalidWindowSize:
            return "showcasegl::ApplicationError::InvalidWindowSize";
    }
    return "Unknown ApplicationError";
}

std::string_view errorToString(ShaderError errorCode) {
    switch (errorCode) {
        case ShaderError::VertexShaderCompilationFailed:
            return "showcasegl::ShaderError::VertexShaderCompilationFailed";
        case ShaderError::FragmentShaderCompilationFailed:
            return "showcasegl::ShaderError::FragmentShaderCompilationFailed";
        case ShaderError::ShaderProgramLinkFailed:
            return "showcasegl::ShaderError::ShaderProgramLinkFailed";
    }
    return "Unknown ShaderError";
}

std::string_view errorToString(MeshError errorCode) {
    switch (errorCode) {
        case MeshError::BufferGenerationFailed:
            return "showcasegl::MeshError::BufferGenerationFailed";
    }
    return "Unknown MeshError";
}

} // namespace showcasegl