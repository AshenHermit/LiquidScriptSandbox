#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Shader.h"
#include "glm/glm.hpp"
#include "../../Utils/stb_image.h"

namespace graphics {
	struct Vertex{
		glm::vec3 position;
		glm::vec2 uv;
	};

	class Texture {
	public:
		Texture();
		Texture(std::string data);
		~Texture();

		int channels=0;
		int width=0;
		int height=0;

		GLuint gl_tex=0;

		void LoadFromFile(std::string path);
		void LoadFromRawData(std::string data);
		void LoadFromImageData(unsigned char* data);
		void Use();
	};

	class Mesh {
	public:
		Mesh();
		Mesh(std::vector<float>* vertices);
		~Mesh();

		void Build(std::vector<float>* vertices);

		unsigned int vbo;
		unsigned int vao;
		int verticesCount;
	};

	class Camera {
	public:
		Camera();
		glm::vec2 position;
		float rotation=0.0f;
		float zoom=1.0f;
		float ratio=1.0f;

		void UpdateViewMatrix(glm::mat4& matrix);
	};

	class Graphics {
	public:
		Graphics();
		~Graphics();
		
		Shader shader;
		Mesh square;
		
		Camera camera;

		glm::mat4 transfrom;
		glm::mat4 view;

		void StartDraw();
		void DrawSquare();

	};

	// shaders
	//std::string(*CodeProcessingFunc)(std::string)
	int CreateShaderProgram(std::string vertex_shader_path, std::string fragment_shader_path);
	static void ShaderLog(int shader);
	static void ShaderProgramLog(int shaderProgram);

	// meshes
	static void CreateStaticBuffers(unsigned int& vbo, unsigned int& vao, int& verticesCount, std::vector<float>* vertices);

	// gl wrap
	static void DrawMesh(Mesh* mesh);
}
