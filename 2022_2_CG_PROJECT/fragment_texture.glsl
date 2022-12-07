#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D outTexture;

void main(){
	FragColor = texture(outTexture,TexCoord);
	//FragColor = vec4(1.0f,0.0f,0.0f,1.0f);
}