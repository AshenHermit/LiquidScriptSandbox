#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 uvCoords;
  
out vec4 vertexColor; // specify a color output to the fragment shader
out vec2 uv;

uniform mat4 view;
uniform mat4 transform;

void main()
{
    gl_Position = view * transform * vec4(aPos, 1.0);
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
    uv = uvCoords;
}