#ifndef SHOWCASEGL_SHADER_HPP__
#define SHOWCASEGL_SHADER_HPP__

#include <glm/glm.hpp>

#include <expected>
#include <memory>
#include <string>

#include "error.hpp"

namespace showcasegl {

class Shader {
public:
    /**
     * @brief compiles shaders and links them to a shader program
     *
     * @details
     *
     * @param[in] vertexSource
     * @param[in] fragmentSource
     *
     * @return
     */
    static std::expected<Shader, ShaderError>
    create(const std::string& vertexSource, const std::string& fragmentSource);

    // delete copy (implicit) and allow move
    ~Shader();
    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    void bind() const;
    static void unbind();

    //! TODO: hot reloading shaders

    // scalar uniform setters
    void setBool(const std::string& uniformName, bool val) const;
    void setInt(const std::string& uniformName, int val) const;
    void setUInt(const std::string& uniformName, unsigned int val) const;
    void setFloat(const std::string& uniformName, float val) const;

    // vector uniform setters
    void setVec2(const std::string& uniformName, float x, float y) const;
    void setVec2(const std::string& uniformName, const glm::vec2& val) const;

    void setVec3(const std::string& uniformName, float x, float y, float z) const;
    void setVec3(const std::string& uniformName, const glm::vec3& val) const;

    void setVec4(const std::string& uniformName, float x, float y, float z, float w) const;
    void setVec4(const std::string& uniformName, const glm::vec4& val) const;

    // matrix uniform setters
    void setMat2(const std::string& uniformName, const glm::mat2& val) const;
    void setMat3(const std::string& uniformName, const glm::mat3& val) const;
    void setMat4(const std::string& uniformName, const glm::mat4& val) const;

private:
    struct ShaderState;
    std::unique_ptr<ShaderState> m_state;

    explicit Shader(std::unique_ptr<ShaderState> state);

    // find uniform location in cache or query for it otherwise
    [[nodiscard]] int32_t getUniLoc(const std::string& name) const;
};

}; // namespace showcasegl

#endif // SHOWCASEGL_SHADER_HPP__