#version 330 core

//input to be used with our texture to sampel the texture
in vec2 texCoordOut;
in vec3 normalOut;

//output of the program
out vec4 color;

uniform sampler2D ourTexture;

void main()
{
	//we are not doing lighting right now
	/*
	vec3 lightSource = vec3(1,2,3);
	vec3 normLight = normalize(lightSource);
	float mod = clamp(dot(normalOut, normLight), 0.6, 1);
	*/
	//changes the color of every fragment
	float texSize = 3.0;

	float x = texCoordOut[0] * 16 * texSize;
	float x_ = floor(x) / (16.0 * texSize) + 0.01;
	float y= texCoordOut[1] * 16 * texSize + 1.0;
	float y_ = floor(y) / (16.0f * texSize) - 0.01;
	color = texture(ourTexture, vec2(x_, y_));
}