#include "mushroom.h"

glm::vec2 mushroom_text_pos[] = {
	glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
	glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),

	glm::vec2(0.9f,1.0f),glm::vec2(0.9f,0.9f),glm::vec2(1.0f,0.9f),
	glm::vec2(0.9f,1.0f),glm::vec2(1.0f,0.9f),glm::vec2(1.0f,1.0f),

	glm::vec2(0.9f,1.0f),glm::vec2(0.9f,0.9f),glm::vec2(1.0f,0.9f),
	glm::vec2(0.9f,1.0f),glm::vec2(1.0f,0.9f),glm::vec2(1.0f,1.0f),

	glm::vec2(0.9f,1.0f),glm::vec2(0.9f,0.9f),glm::vec2(1.0f,0.9f),
	glm::vec2(0.9f,1.0f),glm::vec2(1.0f,0.9f),glm::vec2(1.0f,1.0f),

	glm::vec2(0.9f,1.0f),glm::vec2(0.9f,0.9f),glm::vec2(1.0f,0.9f),
	glm::vec2(0.9f,1.0f),glm::vec2(1.0f,0.9f),glm::vec2(1.0f,1.0f),

	glm::vec2(0.9f,1.0f),glm::vec2(0.9f,0.9f),glm::vec2(1.0f,0.9f),
	glm::vec2(0.9f,1.0f),glm::vec2(1.0f,0.9f),glm::vec2(1.0f,1.0f),
};

glm::vec3 test_mushroom_vertices[] = {
	glm::vec3(-0.5,0.5,0.5),glm::vec3(-0.5,-0.5,0.5), glm::vec3(0.5,-0.5,0.5),		// 1, 4, 5		¾Õ¸é
	glm::vec3(-0.5,0.5,0.5),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.5,0.5,0.5),			// 1, 5, 2

	glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,0.5,0.5),glm::vec3(0.5,0.5,0.5),		// 0, 1, 2		À­¸é
	glm::vec3(-0.5,0.5,-0.5),glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,0.5,-0.5),		// 0, 2, 3

	glm::vec3(-0.5,-0.5,-0.5),glm::vec3(0.5,-0.5,-0.5),glm::vec3(0.5,-0.5,0.5),	// 7, 6, 5		¾Æ·§¸é
	glm::vec3(-0.5,-0.5,-0.5), glm::vec3(0.5,-0.5,0.5),glm::vec3(-0.5,-0.5,0.5),	// 7, 5, 4

	glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.5,-0.5,-0.5),		// 2, 5, 6
	glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,-0.5,-0.5), glm::vec3(0.5,0.5,-0.5),		// 2, 6, 3

	glm::vec3(0.5,0.5,-0.5), glm::vec3(0.5,-0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),	// 3, 6, 7
	glm::vec3(0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),glm::vec3(-0.5,0.5,-0.5),		// 3, 7, 0

	glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),glm::vec3(-0.5,-0.5,0.5),	// 0, 7, 4
	glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,0.5), glm::vec3(-0.5,0.5,0.5),		// 0, 4, 1
};

GLuint mushroom_texture = -1;

Mushroom::Mushroom() {
	InitBuffer();
	Init();
	this->trans = glm::vec3(0.0, 0.0, 0.0);
	this->rot = glm::vec3(0.0, 0.0, 0.0);
	this->scale = glm::vec3(1.0, 1.0, 1.0);
};
Mushroom::Mushroom(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate) {
	InitBuffer();
	Init();
	this->trans = trans;
	this->scale = scale;
	this->rot = rotate;
};
Mushroom::~Mushroom() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(3, VBO);
};


GLvoid Mushroom::Init() {
	frame = 0;
	degree = 0.0;
	dir = 1;
	isAppear = true;
	appearing = 0.0;
}
GLvoid Mushroom::InitBuffer() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, VBO);
	if (mushroom_texture == -1) {
		std::string str = "resource/Item/mushroom.png";
		LoadTexture(mushroom_texture, str.c_str());
	}
}

GLvoid Mushroom::update() {
	if (isAppear) {
		appearing += 0.05 ;
		if (appearing >= scale.y) {
			appearing = 0.0;
			isAppear = false;
			trans.y += scale.y;
		}
	}
	else {
		trans.y -= 0.3;

		//if (++frame >= 39) frame = 0;

		degree += 2;
		if (degree > 360)degree = 0;

		if (dir > 0) {		// 2D RIght
			trans.x += 0.05;
			if (trans.x >= 127) dir = 0;
		}
		else {				// 2D Left
			trans.x -= 0.05;
			if (trans.x <= 0) dir = 1;
		}
	}
}

GLvoid Mushroom::collision_handling(Cube* other) {
	if (!isAppear) {
		Cube* groundCast = dynamic_cast<Ground*>(other);
		Cube* brickCast = dynamic_cast<Brick*>(other);
		Cube* mysteryblockCast = dynamic_cast<MysteryBlock*>(other);
		Cube* marioCast = dynamic_cast<Mario*>(other);
		Cube* wallCast = dynamic_cast<Wall*>(other);
		if (groundCast != nullptr || brickCast != nullptr || mysteryblockCast != nullptr) {
			trans.y += 0.3;

		}
		else if (marioCast != nullptr) {
			isCanDelete = true;
			PlaySound(TEXT(GETMUSHROOMSOUND), NULL, SND_ASYNC | SND_ALIAS);
		}
		else if (wallCast != nullptr) { }
		else {
			std::cout << "Mushroom collision handling" << std::endl;
			if (dir > 0) {
				trans.x -= 0.05;
				dir = 0;
			}
			else {
				trans.x += 0.05;
				dir = 1;
			}
		}
	}
}


GLvoid Mushroom::draw(GLuint cType) {
 	glUseProgram(Gets_program_texture());
	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 T = glm::mat4(1.0f);
	glm::mat4 R = glm::mat4(1.0f);
	glm::mat4 S = glm::mat4(1.0f);


	T = glm::translate(T, glm::vec3(trans.x, trans.y + appearing, trans.z));
	S = glm::scale(S, glm::vec3(scale.x, scale.y, scale.z));
	R = glm::rotate(R, glm::radians(degree), glm::vec3(0.0, 1.0, 0.0));

	TR = T * S * R * TR;

	unsigned int modelLocation = glGetUniformLocation(Gets_program_texture(), "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);

	glBindVertexArray(VAO);

	//Á¶¸í o
	glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(test_mushroom_vertices), test_mushroom_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXTURE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mushroom_text_pos), mushroom_text_pos, GL_STATIC_DRAW);
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(5);

	int tLocation = glGetUniformLocation(Gets_program_texture(), "outTexture"); //--- outTexture1 À¯´ÏÆû »ùÇÃ·¯ÀÇ À§Ä¡¸¦ °¡Á®¿È
	glActiveTexture(mushroom_texture);
	glBindTexture(GL_TEXTURE_2D, mushroom_texture);
	glUniform1i(tLocation, 0);

	glDrawArrays(GL_TRIANGLES, 0, sizeof(test_mushroom_vertices) / sizeof(test_mushroom_vertices[0]));
}