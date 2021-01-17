#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace graphics {
	class Shader
	{
	public:
		Shader();
		~Shader();

		int shaderProgram;

		void LoadFromFiles(std::string vertexShaderPath, std::string fragmentShaderPath);

		void Use();

		void setMatrix(const std::string& name, glm::mat4& matrix);
	};
}

