#include "Shader.h"
#include "Graphics.h"

graphics::Shader::Shader()
{

}

graphics::Shader::~Shader()
{

}

void graphics::Shader::LoadFromFiles(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	shaderProgram = graphics::CreateShaderProgram(vertexShaderPath, fragmentShaderPath);
}

void graphics::Shader::Use()
{
	glUseProgram(shaderProgram);
}

void graphics::Shader::setMatrix(const std::string& name, glm::mat4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}
