#include "brickParticle.h"

glm::vec2 brickParticle_text_pos[] = {
	glm::vec2(0.5f,0.6f),glm::vec2(0.5f,0.5f),glm::vec2(0.6f,0.5f),
	glm::vec2(0.5f,0.6f),glm::vec2(0.6f,0.5f),glm::vec2(0.6f,0.6f),

	glm::vec2(0.5f,0.6f),glm::vec2(0.5f,0.5f),glm::vec2(0.6f,0.5f),
	glm::vec2(0.5f,0.6f),glm::vec2(0.6f,0.5f),glm::vec2(0.6f,0.6f),

	glm::vec2(0.5f,0.6f),glm::vec2(0.5f,0.5f),glm::vec2(0.6f,0.5f),
	glm::vec2(0.5f,0.6f),glm::vec2(0.6f,0.5f),glm::vec2(0.6f,0.6f),

	glm::vec2(0.5f,0.6f),glm::vec2(0.5f,0.5f),glm::vec2(0.6f,0.5f),
	glm::vec2(0.5f,0.6f),glm::vec2(0.6f,0.5f),glm::vec2(0.6f,0.6f),

	glm::vec2(0.5f,0.6f),glm::vec2(0.5f,0.5f),glm::vec2(0.6f,0.5f),
	glm::vec2(0.5f,0.6f),glm::vec2(0.6f,0.5f),glm::vec2(0.6f,0.6f),

	glm::vec2(0.5f,0.6f),glm::vec2(0.5f,0.5f),glm::vec2(0.6f,0.5f),
	glm::vec2(0.5f,0.6f),glm::vec2(0.6f,0.5f),glm::vec2(0.6f,0.6f),
};

glm::vec3 test_brickParticle_vertices[] = {
	glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,0.5,0.5),glm::vec3(0.5,0.5,0.5),		// 0, 1, 2		À­¸é
	glm::vec3(-0.5,0.5,-0.5),glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,0.5,-0.5),		// 0, 2, 3

	glm::vec3(-0.5,-0.5,-0.5),glm::vec3(0.5,-0.5,-0.5),glm::vec3(0.5,-0.5,0.5),	// 7, 6, 5		¾Æ·§¸é
	glm::vec3(-0.5,-0.5,-0.5), glm::vec3(0.5,-0.5,0.5),glm::vec3(-0.5,-0.5,0.5),	// 7, 5, 4

	glm::vec3(-0.5,0.5,0.5),glm::vec3(-0.5,-0.5,0.5), glm::vec3(0.5,-0.5,0.5),		// 1, 4, 5		¾Õ¸é
	glm::vec3(-0.5,0.5,0.5),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.5,0.5,0.5),			// 1, 5, 2

	glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.5,-0.5,-0.5),		// 2, 5, 6
	glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,-0.5,-0.5), glm::vec3(0.5,0.5,-0.5),		// 2, 6, 3

	glm::vec3(0.5,0.5,-0.5), glm::vec3(0.5,-0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),	// 3, 6, 7
	glm::vec3(0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),glm::vec3(-0.5,0.5,-0.5),		// 3, 7, 0

	glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),glm::vec3(-0.5,-0.5,0.5),	// 0, 7, 4
	glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,0.5), glm::vec3(-0.5,0.5,0.5),		// 0, 4, 1
};

GLuint brickParticle_texture = -1;

BrickParticle::BrickParticle() {
	InitBuffer();
	Init();
	this->trans = glm::vec3(0.0, 0.0, 0.0);
	this->rot = glm::vec3(0.0, 0.0, 0.0);
	this->scale = glm::vec3(1.0, 1.0, 1.0);
};
BrickParticle::BrickParticle(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate) {
	InitBuffer();
	Init();
	this->trans = trans;
	this->scale = scale;
	this->rot = rotate;
};
BrickParticle::BrickParticle(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate, int i) {
	InitBuffer();
	Init();
	this->trans = trans;
	this->scale = glm::vec3(scale.x / 5, scale.y / 5, scale.z / 5);
	this->rot = rotate;
	switch (i)
	{
		case 0:
			rotateAxis = glm::normalize(glm::vec3(1.0, 0.0, 1.0));
			break;
		case 1:
			rotateAxis = glm::normalize(glm::vec3(1.0, 0.0, -1.0));
			break;
		case 2:
			rotateAxis = glm::normalize(glm::vec3(-1.0, 0.0, -1.0));
			break;
		case 3:
			rotateAxis = glm::normalize(glm::vec3(-1.0, 0.0, 1.0));
			break;
	default:
		break;
	}
};

BrickParticle::~BrickParticle() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(3, VBO);
};


GLvoid BrickParticle::Init() {
	for (int i = 0; i < 3; i++)
		rotateDegree[i] = 0.0;
	gravity = -0.0098*15;
	speed = 0.002;
	particleNum = -1;
	rotateAxis = glm::vec3(0.0, 1.0, 0.0);
}
GLvoid BrickParticle::InitBuffer() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, VBO);
	if (brickParticle_texture == -1) {
		std::string str = "resource/Map/brick.png";
		LoadTexture(brickParticle_texture, str.c_str());
	}
}

GLvoid BrickParticle::update() {
	gravity += 0.0098;
	trans.x += rotateAxis.x/50;
	trans.y -= gravity;
	trans.z += rotateAxis.z/50;
	rotateDegree[0] += 5;
	if (trans.y < -10)
		isCanDelete = true;
}

GLvoid BrickParticle::collision_handling(Cube* other) {
}

GLvoid BrickParticle::draw() {
	glUseProgram(Gets_program_texture());
	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 T = glm::mat4(1.0f);
	glm::mat4 R = glm::mat4(1.0f);
	glm::mat4 S = glm::mat4(1.0f);


	T = glm::translate(T, glm::vec3(trans.x, trans.y, trans.z));
	S = glm::scale(S, glm::vec3(scale.x, scale.y, scale.z));
	R = glm::rotate(R, glm::radians(rotateDegree[0]), rotateAxis);

	TR = T * S * R * TR;

	unsigned int modelLocation = glGetUniformLocation(Gets_program_texture(), "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);

	glBindVertexArray(VAO);

	//Á¶¸í o
	glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(test_brickParticle_vertices), test_brickParticle_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXTURE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(brickParticle_text_pos), brickParticle_text_pos, GL_STATIC_DRAW);
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(5);

	int tLocation = glGetUniformLocation(Gets_program_texture(), "outTexture"); //--- outTexture1 À¯´ÏÆû »ùÇÃ·¯ÀÇ À§Ä¡¸¦ °¡Á®¿È
	glActiveTexture(brickParticle_texture);
	glBindTexture(GL_TEXTURE_2D, brickParticle_texture);
	glUniform1i(tLocation, 0);

	glDrawArrays(GL_TRIANGLES, 0, sizeof(test_brickParticle_vertices) / sizeof(test_brickParticle_vertices[0]));
}

GLvoid spawnBrickParticle(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate) {
	for (int i = 0; i < 4; i++)
	{
		Particle* newParticle = new BrickParticle(scale, trans, rotate, i);
		Play::GetParticleToAdd().push_back(newParticle);
	}
}