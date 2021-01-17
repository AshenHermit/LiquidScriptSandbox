#include "Graphics.h"
#include "../../Utils/ExceptionTranslator.h"
#include "../../Utils/FileManager.h"
#include "../Global.h"
#include <thread>

using namespace graphics;

int graphics::CreateShaderProgram(std::string vertex_shader_path, std::string fragment_shader_path)
{
	// reading shaders from files
	std::string vertexCodeString = utils::ReadFile(vertex_shader_path);
	std::string fragmentCodeString = utils::ReadFile(fragment_shader_path);
	const GLchar* vertexShaderText = (const GLchar*)vertexCodeString.c_str();
	const GLchar* fragmentShaderText = (const GLchar*)fragmentCodeString.c_str();
	//const char* vertexShaderText = utils::ReadFile(vertex_shader_path).c_str();
	//const char* fragmentShaderText = utils::ReadFile(fragment_shader_path).c_str();
	//if (CodeProcessingFunc != nullptr){
	//	vertexShaderText = CodeProcessingFunc(vertexShaderText).c_str();
	//	fragmentShaderText = CodeProcessingFunc(fragmentShaderText).c_str();
	//}

	// creating shaders
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderText, NULL);
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderText, NULL);
	//delete vertexShaderText; delete fragmentShaderText;

	// compiling shaders
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	// log shaders status
	ShaderLog(vertexShader);
	ShaderLog(fragmentShader);

	// creating shader program
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glValidateProgram(shaderProgram);

	ShaderProgramLog(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

void graphics::ShaderLog(int shader)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	glGetShaderInfoLog(shader, 512, NULL, infoLog);
	if (!success)
	{
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "" << std::endl;
	}
}

void graphics::ShaderProgramLog(int shaderProgram)
{
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	if (!success) {
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	else {
		std::cout << "" << std::endl;
	}
}

void graphics::CreateStaticBuffers(unsigned int& vbo, unsigned int& vao, int& verticesCount, std::vector<float>* vertices)
{
	//glGenVertexArrays(1, &vao);

	//glGenBuffers(1, &vbo);

	//unsigned int uvbo;
	//glGenBuffers(1, &uvbo);

	// activating vao and binding vbo to it
	//glBindVertexArray(vao);

	//triangleCount = vertices.size() / 3;

	//glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices.data()), vertices.data(), GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//glEnableVertexAttribArray(0);
	//
	//glBindBuffer(GL_ARRAY_BUFFER, uvbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords.data()), textureCoords.data(), GL_STATIC_DRAW);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//glEnableVertexAttribArray(1);

	verticesCount = vertices->size()/(3+2);

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	// 1. bind Vertex Array Object
	glBindVertexArray(vao);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(float), &vertices->front(), GL_STATIC_DRAW);
	// 3. then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void graphics::DrawMesh(Mesh* mesh)
{
	glBindVertexArray(mesh->vao);
	glDrawArrays(GL_TRIANGLES, 0, mesh->verticesCount);
	glBindVertexArray(0);
}

graphics::Mesh::Mesh()
{

}

graphics::Mesh::Mesh(std::vector<float>* vertices)
{
	graphics::CreateStaticBuffers(vbo, vao, verticesCount, vertices);
}

graphics::Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void graphics::Mesh::Build(std::vector<float>* vertices)
{
	graphics::CreateStaticBuffers(vbo, vao, verticesCount, vertices);
}

graphics::Graphics::Graphics()
{
	// loading default shader
	shader.LoadFromFiles("../Resources/shaders/default.vert", "../Resources/shaders/default.frag");
	shader.Use();

	// building square 

	std::vector<float> vertices = {
		-0.5,-0.5, 0.0,  0.0, 0.0,
		-0.5, 0.5, 0.0,  0.0, 1.0,
		 0.5, 0.5, 0.0,  1.0, 1.0,

		-0.5,-0.5, 0.0,  0.0, 0.0,
		 0.5,-0.5, 0.0,  1.0, 0.0,
		 0.5, 0.5, 0.0,  1.0, 1.0,
	};

	square = Mesh();
	square.Build(&vertices);


	view = glm::mat4(1.0);
	transfrom = glm::mat4(1.0);
}

graphics::Graphics::~Graphics()
{

}

void graphics::Graphics::StartDraw()
{
	camera.ratio = (float)global.win_width / (float)global.win_height;
	camera.UpdateViewMatrix(view);
	shader.setMatrix("view", view);
}

void graphics::Graphics::DrawSquare()
{
	shader.setMatrix("transform", transfrom);
	graphics::DrawMesh(&square);
}

graphics::Camera::Camera()
{
	position = glm::vec2(0.0, 0.0);
}

void graphics::Camera::UpdateViewMatrix(glm::mat4& matrix)
{
	matrix = glm::mat4(1.0);
	//matrix = glm::translate(matrix, glm::vec3(-0.5f, -0.5f, 0.0f));
	matrix = glm::scale(matrix, glm::vec3(zoom / ratio, -zoom, 1.0f));
	matrix = glm::translate(matrix, glm::vec3(-position.x, -position.y, 0.0f));
	matrix = glm::rotate(matrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
}

graphics::Texture::Texture()
{

}

graphics::Texture::Texture(std::string data)
{
	LoadFromRawData(data);
}

graphics::Texture::~Texture()
{
	glDeleteTextures(1, &gl_tex);
}

void graphics::Texture::ThreadedDownloadFromUrl(std::string url)
{
	global.mutex.lock();
	std::string data = global.requests.Get(url);
	pixelData = stbi_load_from_memory((unsigned char*)&data[0], data.size(), &width, &height, &channels, 0);
	global.mutex.unlock();
}

void graphics::Texture::DownloadFromUrl(std::string url)
{
	std::thread th(&graphics::Texture::ThreadedDownloadFromUrl, this, url);
	th.detach();
}

void graphics::Texture::LoadFromFile(std::string path)
{
	// load from file
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	// gen gl texture
	LoadFromImageData(data);
	// free memory
	stbi_image_free(data);
}

void graphics::Texture::LoadFromRawData(std::string data)
{
	try {
		// load from memory
		pixelData = stbi_load_from_memory((unsigned char*)&data[0], data.size(), &width, &height, &channels, 0);
		// gen gl texture
		LoadFromImageData(pixelData);
		// free memory
		stbi_image_free(pixelData);
	}
	catch (const std::exception& e) {
		std::cout << "Failed to read image. exception: " + std::string(e.what()) << std::endl;
	}
}
void TryGLTexImage2d(int channels, int width, int height, unsigned char* data) {
	__try 
	{
		if (channels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		if (channels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	__finally
	{
		//std::cout << "Failed to write image to graphics card." << std::endl;
	}
}
void graphics::Texture::LoadFromImageData(unsigned char* data)
{
	glGenTextures(1, &gl_tex);
	glBindTexture(GL_TEXTURE_2D, gl_tex);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	try
	{
		TryGLTexImage2d(channels, width, height, data);
	}
	catch (const SE_Exception& e)
	{
		std::cout << "An exception was caught. SE_Exception: " << e.getSeNumber() << std::endl;
	}
	loaded = true;
}

void graphics::Texture::Use()
{
	if (!loaded && width != 0) {
		LoadFromImageData(pixelData);
		stbi_image_free(pixelData);
	}
	else if(loaded) {
		glBindTexture(GL_TEXTURE_2D, gl_tex);
	}
	else {
		global.placeholderTexture->Use();
	}
}
