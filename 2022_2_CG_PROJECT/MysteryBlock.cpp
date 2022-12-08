#include "MysteryBlock.h"

glm::vec2 mysteryBlock_text_pos[] = {
	glm::vec2(0.5,0.666666),glm::vec2(0.5,0.333333),glm::vec2(0.75,0.333333),
	glm::vec2(0.5,0.666666),glm::vec2(0.75,0.333333),glm::vec2(0.75,0.666666),
	glm::vec2(0.5,0.666666),glm::vec2(0.5,0.333333),glm::vec2(0.75,0.333333),
	glm::vec2(0.5,0.666666),glm::vec2(0.75,0.333333),glm::vec2(0.75,0.666666),

	glm::vec2(0.25,0.333333),glm::vec2(0.5,0.333333),glm::vec2(0.5,0.666666),
	glm::vec2(0.25,0.333333),glm::vec2(0.5,0.666666),glm::vec2(0.25,0.666666),
	glm::vec2(0.25,0.333333),glm::vec2(0.5,0.333333),glm::vec2(0.5,0.666666),
	glm::vec2(0.25,0.333333),glm::vec2(0.5,0.666666),glm::vec2(0.25,0.666666),
	glm::vec2(0.25,0.333333),glm::vec2(0.5,0.333333),glm::vec2(0.5,0.666666),
	glm::vec2(0.25,0.333333),glm::vec2(0.5,0.666666),glm::vec2(0.25,0.666666),
	glm::vec2(0.25,0.333333),glm::vec2(0.5,0.333333),glm::vec2(0.5,0.666666),
	glm::vec2(0.25,0.333333),glm::vec2(0.5,0.666666),glm::vec2(0.25,0.666666),
	glm::vec2(0.25,0.333333),glm::vec2(0.5,0.333333),glm::vec2(0.5,0.666666),
	glm::vec2(0.25,0.333333),glm::vec2(0.5,0.666666),glm::vec2(0.25,0.666666),
};

glm::vec3 test_mysteryBlock_vertices[] = {
	glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,0.5,0.5),glm::vec3(0.5,0.5,0.5),		// 0, 1, 2		윗면
	glm::vec3(-0.5,0.5,-0.5),glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,0.5,-0.5),		// 0, 2, 3

	glm::vec3(-0.5,-0.5,-0.5),glm::vec3(0.5,-0.5,-0.5),glm::vec3(0.5,-0.5,0.5),		// 7, 6, 5		아랫면
	glm::vec3(-0.5,-0.5,-0.5), glm::vec3(0.5,-0.5,0.5),glm::vec3(-0.5,-0.5,0.5),	// 7, 5, 4

	glm::vec3(-0.5,0.5,0.5),glm::vec3(-0.5,-0.5,0.5), glm::vec3(0.5,-0.5,0.5),		// 1, 4, 5		그 외
	glm::vec3(-0.5,0.5,0.5),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.5,0.5,0.5),			// 1, 5, 2

	glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.5,-0.5,-0.5),		// 2, 5, 6
	glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,-0.5,-0.5), glm::vec3(0.5,0.5,-0.5),		// 2, 6, 3

	glm::vec3(0.5,0.5,-0.5), glm::vec3(0.5,-0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),	// 3, 6, 7
	glm::vec3(0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),glm::vec3(-0.5,0.5,-0.5),		// 3, 7, 0

	glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),glm::vec3(-0.5,-0.5,0.5),	// 0, 7, 4
	glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,0.5), glm::vec3(-0.5,0.5,0.5),		// 0, 4, 1

};

GLuint mysteryBlock_texture = -1;

MysteryBlock::MysteryBlock() {
	InitBuffer();
	this->trans = glm::vec3(0.0, 0.0, 0.0);
	this->rot = glm::vec3(0.0, 0.0, 0.0);
	this->scale = glm::vec3(1.0, 1.0, 1.0);
};
MysteryBlock::MysteryBlock(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate) {
	InitBuffer();
	this->trans = trans;
	this->scale = scale;
	this->rot = rotate;
};
MysteryBlock::~MysteryBlock() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(3, VBO);
};


GLvoid MysteryBlock::Init() {

}
GLvoid MysteryBlock::InitBuffer() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, VBO);
	if (mysteryBlock_texture == -1) {
		//임시 코드임 나중에 이미지 수정해야함
		LoadTexture(mysteryBlock_texture, "resource/Map/mystery_box.png");
	}
}

GLvoid MysteryBlock::draw() {
	glUseProgram(Gets_program_texture());
	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 T = glm::mat4(1.0f);
	glm::mat4 S = glm::mat4(1.0f);

	T = glm::translate(T, glm::vec3(trans.x, trans.y, trans .z));
	S = glm::scale(S, glm::vec3(scale.x, scale.y, scale.z));
	TR = T * S * TR;

	unsigned int modelLocation = glGetUniformLocation(Gets_program_texture(), "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);

	glBindVertexArray(VAO);

	//조명 o
	glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(test_mysteryBlock_vertices), test_mysteryBlock_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXTURE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mysteryBlock_text_pos), mysteryBlock_text_pos, GL_STATIC_DRAW);
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(5);

	int tLocation = glGetUniformLocation(Gets_program_texture(), "outTexture"); //--- outTexture1 유니폼 샘플러의 위치를 가져옴
	glActiveTexture(mysteryBlock_texture);
	glBindTexture(GL_TEXTURE_2D, mysteryBlock_texture);
	glUniform1i(tLocation, 0);

	glDrawArrays(GL_TRIANGLES, 0, sizeof(test_mysteryBlock_vertices) / sizeof(test_mysteryBlock_vertices[0]));
}