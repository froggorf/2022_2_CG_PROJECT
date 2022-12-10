#include "wall.h"

//glm::vec2 pictureWall_text_pos[] = {
//	glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
//	glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),
//
//	glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
//	glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),
//
//	glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
//	glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),
//
//	glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
//	glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),
//
//	glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
//	glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),
//
//	glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
//	glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),
//};
//
//glm::vec3 test_pictureWall_vertices[] = {
//	glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,0.5,0.5),glm::vec3(0.5,0.5,0.5),
//	glm::vec3(-0.5,0.5,-0.5),glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,0.5,-0.5),
//	glm::vec3(-0.5,0.5,0.5),glm::vec3(-0.5,-0.5,0.5), glm::vec3(0.5,-0.5,0.5),
//	glm::vec3(-0.5,0.5,0.5),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.5,0.5,0.5),
//	glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.5,-0.5,-0.5),
//	glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,-0.5,-0.5), glm::vec3(0.5,0.5,-0.5),
//	glm::vec3(0.5,0.5,-0.5), glm::vec3(0.5,-0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),
//	glm::vec3(0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),glm::vec3(-0.5,0.5,-0.5),
//	glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),glm::vec3(-0.5,-0.5,0.5),
//	glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,0.5), glm::vec3(-0.5,0.5,0.5),
//	glm::vec3(-0.5,-0.5,-0.5),glm::vec3(0.5,-0.5,-0.5),glm::vec3(0.5,-0.5,0.5),
//	glm::vec3(-0.5,-0.5,-0.5), glm::vec3(0.5,-0.5,0.5),glm::vec3(-0.5,-0.5,0.5)
//};

//GLuint pictureWall_texture[4] = { -1, };

Wall::Wall() {
	InitBuffer();
	Init();
	this->trans = glm::vec3(0.0, 0.0, 0.0);
	this->rot = glm::vec3(0.0, 0.0, 0.0);
	this->scale = glm::vec3(1.0, 1.0, 1.0);
};
Wall::Wall(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate) {
	InitBuffer();
	Init();
	this->trans = trans;
	this->scale = scale;
	this->rot = rotate;
};
Wall::Wall(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate, GLboolean is2DCollide) {
	InitBuffer();
	Init();
	this->trans = trans;
	this->scale = scale;
	this->rot = rotate;
	this->is2DCollide = true;
};
Wall::~Wall() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(3, VBO);
};


GLvoid Wall::Init() {
	is2DCollide = false;
}
GLvoid Wall::InitBuffer() {
	//glGenVertexArrays(1, &VAO);
	//glGenBuffers(3, VBO);
	//if (pictureWall_texture[0] == -1) {
	//	//임시 코드임 나중에 이미지 수정해야함
	//	LoadTexture(pictureWall_texture[0], "resource/Map/background0.png");
	//	LoadTexture(pictureWall_texture[1], "resource/Map/background1.png");
	//	LoadTexture(pictureWall_texture[2], "resource/Map/background2.png");
	//	LoadTexture(pictureWall_texture[3], "resource/Map/background3.png");
	//}
}

GLvoid Wall::draw() {
	//glUseProgram(Gets_program_texture());
	//glm::mat4 TR = glm::mat4(1.0f);
	//glm::mat4 T = glm::mat4(1.0f);
	//T = glm::translate(T, glm::vec3(trans.x, trans.y, trans.z));
	//glm::mat4 S = glm::mat4(1.0f);
	//S = glm::scale(S, glm::vec3(scale.x, scale.y, scale.z));
	//TR = T * S * TR;
	//
	//unsigned int modelLocation = glGetUniformLocation(Gets_program_texture(), "model");
	//glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
	//
	//glBindVertexArray(VAO);
	//
	////조명 o
	//glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(pictureWall_text_pos), pictureWall_text_pos, GL_STATIC_DRAW);
	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(3);
	//
	//glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXTURE]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(test_pictureWall_vertices), test_pictureWall_vertices, GL_STATIC_DRAW);
	//glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(5);
	//
	//int tLocation = glGetUniformLocation(Gets_program_texture(), "outTexture"); //--- outTexture1 유니폼 샘플러의 위치를 가져옴
	//glActiveTexture(pictureWall_texture[picSel % 4]);
	//glBindTexture(GL_TEXTURE_2D, pictureWall_texture[picSel % 4]);
	//glUniform1i(tLocation, 0);
	//
	//glDrawArrays(GL_TRIANGLES, 0, sizeof(pictureWall_text_pos) / sizeof(pictureWall_text_pos[0]));
}