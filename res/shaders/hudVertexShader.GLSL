#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoordIn;

out vec2 texCoordOut;

// uniform mat4 translate;

uniform sampler2D ourTexture;

void main(){
	gl_Position = vec4(position, 1.0);
	texCoordOut = texCoordIn;
}