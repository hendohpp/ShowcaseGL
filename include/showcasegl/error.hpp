#ifndef SHOWCASEGL_ERROR_HPP__
#define SHOWCASEGL_ERROR_HPP__

namespace showcasegl {

enum class ApplicationError {
    None,
    GlfwInitializationFailed,
    GlfwWindowCreationFailed,
    GladInitializationFailed,
}; 

//! TODO: functionality for translating error code to string

}; // namespace showcasegl

#endif // SHOWCASEGL_ERROR_HPP__