#ifndef SHOWCASEGL_HPP__
#define SHOWCASEGL_HPP__

/**
 * @file showcasegl.hpp
 * @brief API entry point (umbrella header) for the ShowcaseGL Framework
 * 
 * Exposes all core ShowcaseGL features.
 * All features reside in the `showcasegl` namespace.
 * 
 * Example:
 * @code
 * #include <showcasegl/showcasegl.hpp>
 * 
 * int main() {
 *     int width{1920};
 *     int height{1080};
 *     showcasegl::Application app("MyScene", width, height);
 * 
 *     // ...
 * }
 * @endcode
 */

#include <showcasegl/Application.hpp>
#include <showcasegl/Camera.hpp>
#include <showcasegl/Mesh.hpp>
#include <showcasegl/Model.hpp>
#include <showcasegl/Scene.hpp>
#include <showcasegl/Shader.hpp>
#include <showcasegl/Texture.hpp>

#endif // SHOWCASEGL_HPP__