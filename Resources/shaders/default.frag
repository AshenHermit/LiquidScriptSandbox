#version 330 core
  
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  
in vec2 uv;

uniform sampler2D tex;

out vec4 FragColor;

void main()
{
	//FragColor = vec4(uv.x, uv.y, 1.0, 1.0);
	vec4 color = texture(tex, uv); 
	//vec4 color = vec4(1.0);
	if(color.a<0.5){discard;}

    FragColor = color;
} 