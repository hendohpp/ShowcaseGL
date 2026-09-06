#ifndef SHOWCASEGL_SHADER_HPP__
#define SHOWCASEGL_SHADER_HPP__

#include <glm/glm.hpp>

#include <cstdint>
#include <string>

namespace showcasegl {

class Shader {
public:
    // compiles shaders and links them to a shader program
    Shader(const std::string& vertexSource, const std::string& fragmentSource);

    // releases shader program resources
    ~Shader();

    // disable copying to ensure unique ownership of GPU resources
    Shader(const Shader&) = delete;
    Shader& operator=(Shader&) = delete;

    // allow move to transfer GPU handle ownership
    Shader(Shader&&) noexcept;
    Shader& operator=(Shader&&) noexcept;

    // sets the shader program as active
    void bind();

    // scalar uniform setters
    void setBool(const std::string& uniformName, bool val) const;
    void setInt(const std::string& uniformName, int val) const;
    void setFloat(const std::string& uniformName, float val) const;

    // vector uniform setters
    void setVec2(const std::string& uniformName, float x, float y) const;
    void setVec2(const std::string& uniformName, const glm::vec2& val) const;

    void setVec3(const std::string& uniformName, float x, float y, float z) const;
    void setVec3(const std::string& uniformName, const glm::vec3& val) const;

    void setVec4(const std::string& uniformName, float x, float y, float z, float w) const;
    void setVec4(const std::string& uniformName, const glm::vec4& val);

    // matrix uniform setters
    void setMat2(const std::string& name, const glm::mat2& val) const;
    void setMat3(const std::string& name, const glm::mat3& val) const;
    void setMat4(const std::string& name, const glm::mat4& val) const;

private:
    uint32_t id{0};
};

}; // namespace showcasegl

#endif // SHOWCASEGL_SHADER_HPP__