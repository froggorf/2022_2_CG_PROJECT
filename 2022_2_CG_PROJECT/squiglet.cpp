#include "squiglet.h"

glm::vec2 squiglet_text_pos[] = {
	glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
	glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),

	//glm::vec2(0.5f,1.0f),glm::vec2(0.5f,0.0f),glm::vec2(1.0f,0.0f),
	//glm::vec2(0.5f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),

	//glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(0.5f,0.0f),
	//glm::vec2(0.0f,1.0f),glm::vec2(0.5f,0.0f),glm::vec2(0.5f,1.0f),

	//glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(0.5f,0.0f),
	//glm::vec2(0.0f,1.0f),glm::vec2(0.5f,0.0f),glm::vec2(0.5f,1.0f),

	//glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(0.5f,0.0f),
	//glm::vec2(0.0f,1.0f),glm::vec2(0.5f,0.0f),glm::vec2(0.5f,1.0f),

	//glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(0.5f,0.0f),
	//glm::vec2(0.0f,1.0f),glm::vec2(0.5f,0.0f),glm::vec2(0.5f,1.0f),
};

glm::vec3 test_squiglet_vertices[] = {
	//glm::vec3(-0.5,0.5,0.5),glm::vec3(-0.5,-0.5,0.5), glm::vec3(0.5,-0.5,0.5),		// 1, 4, 5		¾Õ¸é
	//glm::vec3(-0.5,0.5,0.5),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.5,0.5,0.5),			// 1, 5, 2

	//glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,0.5,0.5),glm::vec3(0.5,0.5,0.5),		// 0, 1, 2		À­¸é
	//glm::vec3(-0.5,0.5,-0.5),glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,0.5,-0.5),		// 0, 2, 3

	//glm::vec3(-0.5,-0.5,-0.5),glm::vec3(0.5,-0.5,-0.5),glm::vec3(0.5,-0.5,0.5),	// 7, 6, 5		¾Æ·§¸é
	//glm::vec3(-0.5,-0.5,-0.5), glm::vec3(0.5,-0.5,0.5),glm::vec3(-0.5,-0.5,0.5),	// 7, 5, 4

	//glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.5,-0.5,-0.5),		// 2, 5, 6
	//glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,-0.5,-0.5), glm::vec3(0.5,0.5,-0.5),		// 2, 6, 3

	//glm::vec3(0.5,0.5,-0.5), glm::vec3(0.5,-0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),	// 3, 6, 7
	//glm::vec3(0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),glm::vec3(-0.5,0.5,-0.5),		// 3, 7, 0

	glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),glm::vec3(-0.5,-0.5,0.5),	// 0, 7, 4
	glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,0.5), glm::vec3(-0.5,0.5,0.5),		// 0, 4, 1
};

GLuint squiglet_texture[2][5] = { -1, };
GLuint squiglet_dead_texture = -1;

Squiglet::Squiglet() {
	InitBuffer();
	Init();
	this->trans = glm::vec3(0.0, 0.0, 0.0);
	this->rot = glm::vec3(0.0, 0.0, 0.0);
	this->scale = glm::vec3(1.0, 1.0, 1.0);
};
Squiglet::Squiglet(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate) {
	InitBuffer();
	Init();
	this->trans = trans;
	this->scale = scale;
	this->rot = rotate;
};
Squiglet::~Squiglet() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(3, VBO);
};


GLvoid Squiglet::Init() {
	frame = 13;
	back = false;
	dead = false;
	dir = 0;
	isStepOn = false;
	timer = 0.0;
}
GLvoid Squiglet::InitBuffer() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, VBO);
	if (squiglet_texture[0][0] == -1) {
		LoadTexture(squiglet_texture[0][0], "resource/Enemy/Squiglet/Squiglet_walk0_left.png");
		LoadTexture(squiglet_texture[0][1], "resource/Enemy/Squiglet/Squiglet_walk1_left.png");
		LoadTexture(squiglet_texture[0][2], "resource/Enemy/Squiglet/Squiglet_walk2_left.png");
		LoadTexture(squiglet_texture[0][3], "resource/Enemy/Squiglet/Squiglet_walk3_left.png");
		LoadTexture(squiglet_texture[0][4], "resource/Enemy/Squiglet/Squiglet_walk4_left.png");
		LoadTexture(squiglet_texture[1][0], "resource/Enemy/Squiglet/Squiglet_walk0_right.png");
		LoadTexture(squiglet_texture[1][1], "resource/Enemy/Squiglet/Squiglet_walk1_right.png");
		LoadTexture(squiglet_texture[1][2], "resource/Enemy/Squiglet/Squiglet_walk2_right.png");
		LoadTexture(squiglet_texture[1][3], "resource/Enemy/Squiglet/Squiglet_walk3_right.png");
		LoadTexture(squiglet_texture[1][4], "resource/Enemy/Squiglet/Squiglet_walk4_right.png");
		LoadTexture(squiglet_dead_texture, "resource/Enemy/Squiglet/Squiglet_dead.png");
	}
}

GLvoid Squiglet::update() {
	if (isStepOn) {
		timer += 0.05;
		if (timer >= 1.0) isCanDelete = true;
	}
	else {
		if (back) {
			if (--frame <= 0) back = false;
		}
		else {
			if (++frame >= 24) back = true;
		}

		if (dir > 0) {		// 2D RIght
			trans.z += 0.02;
			//if (trans.z >= 127) dir = 0;
		}
		else {				// 2D Left
			trans.z -= 0.02;
			//if (trans.z <= 0) dir = 1;
		}
	}
}

GLvoid Squiglet::collision_handling(Cube* other) {
	Cube* marioCast = dynamic_cast<Mario*>(other);
	std::cout << "Squiglet collision handling" << std::endl;
	if (marioCast != nullptr) {
		isStepOn = true;
	}
	else {
		if (dir > 0) {
			trans.z -= 0.02;
			dir = 0;
		}
		else {
			trans.z += 0.02;
			dir = 1;
		}
	}
}

GLvoid Squiglet::draw() {
	glUseProgram(Gets_program_texture());
	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 T = glm::mat4(1.0f);
	glm::mat4 S = glm::mat4(1.0f);

	T = glm::translate(T, glm::vec3(trans.x, trans.y, trans.z));
	S = glm::scale(S, glm::vec3(scale.x, scale.y, scale.z));

	TR = T * S * TR;

	unsigned int modelLocation = glGetUniformLocation(Gets_program_texture(), "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);

	glBindVertexArray(VAO);

	//Á¶¸í o
	glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(test_squiglet_vertices), test_squiglet_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXTURE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(squiglet_text_pos), squiglet_text_pos, GL_STATIC_DRAW);
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(5);

	int tLocation = glGetUniformLocation(Gets_program_texture(), "outTexture"); //--- outTexture1 À¯´ÏÆû »ùÇÃ·¯ÀÇ À§Ä¡¸¦ °¡Á®¿È
	if (isStepOn) {
		glActiveTexture(squiglet_dead_texture);
		glBindTexture(GL_TEXTURE_2D, squiglet_dead_texture);
		glUniform1i(tLocation, 0);
	}
	else {
		glActiveTexture(squiglet_texture[dir][frame / 5]);
		glBindTexture(GL_TEXTURE_2D, squiglet_texture[dir][frame / 5]);
		glUniform1i(tLocation, 0);
	}

	glDrawArrays(GL_TRIANGLES, 0, sizeof(test_squiglet_vertices) / sizeof(test_squiglet_vertices[0]));
}