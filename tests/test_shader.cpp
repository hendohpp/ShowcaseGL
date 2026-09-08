#include <showcasegl/Application.hpp>
#include <showcasegl/Shader.hpp>
#include <showcasegl/error.hpp>

#include <glad/glad.h>

#include <gtest/gtest.h>
#include <memory>
#include <optional>

// shaders sources to test on

constexpr const char* VALID_VS = R"(
#version 460 core
layout (location = 0) in vec3 aPos;
uniform mat4 uProjection;
void main() {
    gl_Position = uProjection * vec4(aPos, 1.0);
}
)";

constexpr const char* VALID_FS = R"(
#version 460 core
out vec4 FragColor;
uniform vec4 uColor;
void main() {
    FragColor = uColor;
}
)";

constexpr const char* INVALID_S = R"(
#version 330 core
in vec3 position;
out vec4 fragColor;
void main() {
    fragColor = position * multiplier; 
    int standardCount = 10
}
)";

// test configuration to be used across tests

class ShaderTest : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        auto appRes = showcasegl::Application::create("ShaderTest");
        ASSERT_TRUE(appRes.has_value());
        m_app.emplace(std::move(*appRes));
    }

    static void TearDownTestSuite() {
        m_app.reset();
    }

    static std::optional<showcasegl::Application> m_app;
};

std::optional<showcasegl::Application> ShaderTest::m_app = std::nullopt;

// test helpers

GLint getBoundProgram() {
    GLint program{0};
    glGetIntegerv(GL_CURRENT_PROGRAM, &program);
    return program;
}

// shader creation and compilation tests

TEST_F(ShaderTest, CreateValidShader) {
    auto res = showcasegl::Shader::create(VALID_VS, VALID_FS);
    ASSERT_TRUE(res.has_value());

    showcasegl::Shader shader{std::move(*res)};
    shader.bind();
    EXPECT_GT(getBoundProgram(), 0);
}

TEST_F(ShaderTest, VertexCompilationFail) {
    auto res = showcasegl::Shader::create(INVALID_S, VALID_FS);
    ASSERT_FALSE(res.has_value());
    EXPECT_EQ(res.error(), showcasegl::ShaderError::VertexShaderCompilationFailed);
}

TEST_F(ShaderTest, FragmentCompilationFail) {
    auto res = showcasegl::Shader::create(VALID_VS, INVALID_S);
    ASSERT_FALSE(res.has_value());
    EXPECT_EQ(res.error(), showcasegl::ShaderError::FragmentShaderCompilationFailed);
}

// resource cleanup test

TEST_F(ShaderTest, ShaderProgramDeletion) {
    GLuint id{0};
    {
        auto res = showcasegl::Shader::create(VALID_VS, VALID_FS);
        ASSERT_TRUE(res.has_value());

        showcasegl::Shader shader{std::move(*res)};
        shader.bind();
        id = getBoundProgram();

        ASSERT_NE(id, 0u);
        EXPECT_TRUE(glIsProgram(id));

        showcasegl::Shader::unbind();
    }
    EXPECT_FALSE(glIsProgram(id));
}

// uniform setting test

TEST_F(ShaderTest, SetUniforms) {
    auto result = showcasegl::Shader::create(VALID_VS, VALID_FS);
    ASSERT_TRUE(result.has_value());
    showcasegl::Shader shader{std::move(*result)};

    shader.bind();
    GLint id = getBoundProgram();
    ASSERT_GT(id, 0);

    glm::vec4 testColor(0.4f, 0.4f, 0.4f, 1.0f);
    shader.setVec4("uColor", testColor);

    GLint loc = glGetUniformLocation(id, "uColor");
    ASSERT_NE(loc, -1);

    float readback[4] = {0.0f};
    glGetUniformfv(id, loc, readback);

    EXPECT_FLOAT_EQ(readback[0], testColor.r);
    EXPECT_FLOAT_EQ(readback[1], testColor.g);
    EXPECT_FLOAT_EQ(readback[2], testColor.b);
    EXPECT_FLOAT_EQ(readback[3], testColor.a);
}

// move semantics tests

TEST_F(ShaderTest, TransferOwnership) {
    auto result = showcasegl::Shader::create(VALID_VS, VALID_FS);
    ASSERT_TRUE(result.has_value());

    result->bind();
    GLint originalProgramId = getBoundProgram();

    showcasegl::Shader movedShader{std::move(*result)};

    movedShader.bind();
    EXPECT_EQ(getBoundProgram(), originalProgramId);

    result->bind();
    EXPECT_EQ(getBoundProgram(), 0);
}

TEST_F(ShaderTest, DeleteOldResources) {
    auto shaderA = showcasegl::Shader::create(VALID_VS, VALID_FS);
    auto shaderB = showcasegl::Shader::create(VALID_VS, VALID_FS);

    ASSERT_TRUE(shaderA.has_value() && shaderB.has_value());

    shaderA->bind();
    GLint idA = getBoundProgram();

    shaderB->bind();
    GLint idB = getBoundProgram();

    *shaderA = std::move(*shaderB);

    shaderA->bind();
    EXPECT_EQ(getBoundProgram(), idB);

    EXPECT_FALSE(glIsProgram(idA));
}