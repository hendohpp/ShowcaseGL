#ifndef SHOWCASEGL_ERROR_HPP__
#define SHOWCASEGL_ERROR_HPP__

#include <string_view>
#include <type_traits>
#include <concepts>

namespace showcasegl {

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

enum class MeshError {
    BufferGenerationFailed,
};

std::string_view errorToString(ApplicationError errorCode);
std::string_view errorToString(ShaderError errorCode);
std::string_view errorToString(MeshError errorCode);

}; // namespace showcasegl

#endif // SHOWCASEGL_ERROR_HPP__