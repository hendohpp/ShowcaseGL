#include "showcasegl/Shader.hpp"

#include <glad/glad.h>
#include <unordered_map>

namespace showcasegl {

// hidden internal state contains the shader uniform location cache
// to avoid including unordered map in other compilations units
struct Shader::ShaderState {
    uint32_t id{0};
    std::unordered_map<std::string, int32_t> uniformCache;

    ~ShaderState() {
        if (id == 0) {
            return;
        }
        glDeleteProgram(id);
    }
};

std::expected<Shader, ShaderError>
Shader::create(const std::string& vertexSource, const std::string& fragmentSource) {
    // create local c style strings since rvalues cannot be used for shader compilation
    const GLchar* vertexSourceCStr = static_cast<const GLchar*>(vertexSource.c_str());
    const GLchar* fragmentSourceCStr = static_cast<const GLchar*>(fragmentSource.c_str());

    // compile vertex shader
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexSourceCStr, nullptr);
    glCompileShader(vs);

    int success{0};
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glDeleteShader(vs);
        return std::unexpected(ShaderError::VertexShaderCompilationFailed);
    }

    // compile fragment shader
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentSourceCStr, nullptr);
    glCompileShader(fs);

    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success) {
        glDeleteShader(vs);
        glDeleteShader(fs);
        return std::unexpected(ShaderError::FragmentShaderCompilationFailed);
    }

    // link shaders to shader program
    uint32_t shaderProgramId = glCreateProgram();
    glAttachShader(shaderProgramId, vs);
    glAttachShader(shaderProgramId, fs);
    glLinkProgram(shaderProgramId);

    glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
    if (!success) {
        glDeleteShader(vs);
        glDeleteShader(fs);
        glDeleteProgram(shaderProgramId);
        return std::unexpected(ShaderError::ShaderProgramLinkFailed);
    }

    // clean up shader objects after successful link
    glDetachShader(shaderProgramId, vs);
    glDetachShader(shaderProgramId, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);

    auto state = std::make_unique<ShaderState>();
    state->id = shaderProgramId;

    return Shader(std::move(state));
}

Shader::Shader(std::unique_ptr<ShaderState> state)
    : m_state(std::move(state)) {}

Shader::~Shader() = default;
Shader::Shader(Shader&&) noexcept = default;
Shader& Shader::operator=(Shader&&) noexcept = default;

void Shader::bind() const {
    if (!m_state) {
        glUseProgram(0);
        return;
    }
    glUseProgram(m_state->id);
}

void Shader::unbind() {
    glUseProgram(0);
}

void Shader::setBool(const std::string& uniformName, bool val) const {
    glUniform1i(getUniLoc(uniformName), static_cast<int>(val));
}

void Shader::setInt(const std::string& uniformName, int val) const {
    glUniform1i(getUniLoc(uniformName), val);
}

void Shader::setUInt(const std::string& uniformName, unsigned int val) const {
    glUniform1ui(getUniLoc(uniformName), val);
}

void Shader::setFloat(const std::string& uniformName, float val) const {
    glUniform1f(getUniLoc(uniformName), val);
}

void Shader::setVec2(const std::string& uniformName, float x, float y) const {
    glUniform2f(getUniLoc(uniformName), x, y);
}

void Shader::setVec2(const std::string& uniformName, const glm::vec2& val) const {
    glUniform2f(getUniLoc(uniformName), val.x, val.y);
}

void Shader::setVec3(const std::string& uniformName, float x, float y, float z) const {
    glUniform3f(getUniLoc(uniformName), x, y, z);
}

void Shader::setVec3(const std::string& uniformName, const glm::vec3& val) const {
    glUniform3f(getUniLoc(uniformName), val.x, val.y, val.z);
}

void Shader::setVec4(const std::string& uniformName, float x, float y, float z, float w) const {
    glUniform4f(getUniLoc(uniformName), x, y, z, w);
}

void Shader::setVec4(const std::string& uniformName, const glm::vec4& val) const {
    glUniform4f(getUniLoc(uniformName), val.x, val.y, val.z, val.w);
}

void Shader::setMat2(const std::string& uniformName, const glm::mat2& val) const {
    glUniformMatrix2fv(getUniLoc(uniformName), 1, GL_FALSE, &val[0][0]);
}

void Shader::setMat3(const std::string& uniformName, const glm::mat3& val) const {
    glUniformMatrix3fv(getUniLoc(uniformName), 1, GL_FALSE, &val[0][0]);
}

void Shader::setMat4(const std::string& uniformName, const glm::mat4& val) const {
    glUniformMatrix4fv(getUniLoc(uniformName), 1, GL_FALSE, &val[0][0]);
}

int32_t Shader::getUniLoc(const std::string& name) const {
    if (!m_state) {
        return -1;
    }

    auto it = m_state->uniformCache.find(name);
    if (it != m_state->uniformCache.end()) {
        return it->second;
    }

    int32_t uniLoc = glGetUniformLocation(m_state->id, name.c_str());
    m_state->uniformCache[name] = uniLoc;
    return uniLoc;
}

} // namespace showcasegl