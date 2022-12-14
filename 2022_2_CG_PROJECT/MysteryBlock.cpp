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
glm::vec2 emptyBlock_text_pos[] = {
	glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
	glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),

	glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
	glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),

	glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
	glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),

	glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
	glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),

	glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
	glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),

	glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
	glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),
};

glm::vec3 test_mysteryBlock_vertices[] = {
	glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,0.5,0.5),glm::vec3(0.5,0.5,0.5),		// 0, 1, 2		????
	glm::vec3(-0.5,0.5,-0.5),glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,0.5,-0.5),		// 0, 2, 3

	glm::vec3(-0.5,-0.5,-0.5),glm::vec3(0.5,-0.5,-0.5),glm::vec3(0.5,-0.5,0.5),		// 7, 6, 5		??????
	glm::vec3(-0.5,-0.5,-0.5), glm::vec3(0.5,-0.5,0.5),glm::vec3(-0.5,-0.5,0.5),	// 7, 5, 4

	glm::vec3(-0.5,0.5,0.5),glm::vec3(-0.5,-0.5,0.5), glm::vec3(0.5,-0.5,0.5),		// 1, 4, 5		?? ??
	glm::vec3(-0.5,0.5,0.5),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.5,0.5,0.5),			// 1, 5, 2

	glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.5,-0.5,-0.5),		// 2, 5, 6
	glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,-0.5,-0.5), glm::vec3(0.5,0.5,-0.5),		// 2, 6, 3

	glm::vec3(0.5,0.5,-0.5), glm::vec3(0.5,-0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),	// 3, 6, 7
	glm::vec3(0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),glm::vec3(-0.5,0.5,-0.5),		// 3, 7, 0

	glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),glm::vec3(-0.5,-0.5,0.5),	// 0, 7, 4
	glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,0.5), glm::vec3(-0.5,0.5,0.5),		// 0, 4, 1

};

GLuint mysteryBlock_texture = -1;
GLuint emptyBlock_texture = -1;

MysteryBlock::MysteryBlock() {
	InitBuffer();
	Init();
	this->trans = glm::vec3(0.0, 0.0, 0.0);
	this->rot = glm::vec3(0.0, 0.0, 0.0);
	this->scale = glm::vec3(1.0, 1.0, 1.0);
	coins = 0;
};
MysteryBlock::MysteryBlock(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate, GLuint coin) {
	InitBuffer();
	Init();
	this->trans = trans;
	this->scale = scale;
	this->rot = rotate;
	coins = coin;
};
MysteryBlock::~MysteryBlock() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(3, VBO);
};


GLvoid MysteryBlock::Init() {
	moving = false;
	isMoveUp = true;
	movingTransFigure = 0.0;
}
GLvoid MysteryBlock::InitBuffer() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, VBO);
	if (mysteryBlock_texture == -1) {
		//???? ?????? ?????? ?????? ??????????
		LoadTexture(mysteryBlock_texture, "resource/Map/mystery_box.png");
		LoadTexture(emptyBlock_texture, "resource/Map/emptyBlock.png");
	}
}

GLvoid MysteryBlock::update() {
	if (moving) {
		if (isMoveUp) {
			movingTransFigure += 0.05;
			if (movingTransFigure >= 0.5) isMoveUp = false;
		}
		else {
			movingTransFigure -= 0.05;
			if (movingTransFigure <= 0.0) {
				movingTransFigure = 0.0;
				isMoveUp = true;
				moving = false; 
			}
		}
	}
}

GLvoid MysteryBlock::collision_handling(Cube* other) {
	Cube* marioCast = dynamic_cast<Mario*>(other);
	if (marioCast != nullptr) {
		std::cout << "MysteryBlock collision handling" << std::endl;
		moving = true;
		if (coins == 100) {
			Item* newMush = new Mushroom(scale, trans, rot);
			Play::GetItemToAdd().push_back(newMush);
			coins = 0;
		}
		else if(coins != 0){
			--coins;
			Item* newMush = new Coin(scale, trans, rot, true);
			Play::GetItemToAdd().push_back(newMush);
		}
	}
}

GLvoid MysteryBlock::draw() {
	glUseProgram(Gets_program_texture());
	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 T = glm::mat4(1.0f);
	glm::mat4 S = glm::mat4(1.0f);

	T = glm::translate(T, glm::vec3(trans.x, trans.y + movingTransFigure, trans .z));
	S = glm::scale(S, glm::vec3(scale.x, scale.y, scale.z));
	TR = T * S * TR;

	unsigned int modelLocation = glGetUniformLocation(Gets_program_texture(), "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);

	glBindVertexArray(VAO);

	//???? o
	glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(test_mysteryBlock_vertices), test_mysteryBlock_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(3);

	

	int tLocation = glGetUniformLocation(Gets_program_texture(), "outTexture"); //--- outTexture1 ?????? ???????? ?????? ??????
	if (coins != 0) {
		glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXTURE]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(mysteryBlock_text_pos), mysteryBlock_text_pos, GL_STATIC_DRAW);
		glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(5);

		glActiveTexture(mysteryBlock_texture);
		glBindTexture(GL_TEXTURE_2D, mysteryBlock_texture);
		glUniform1i(tLocation, 0);
	}
	else {
		glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXTURE]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(emptyBlock_text_pos), emptyBlock_text_pos, GL_STATIC_DRAW);
		glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(5);

		glActiveTexture(emptyBlock_texture);
		glBindTexture(GL_TEXTURE_2D, emptyBlock_texture);
		glUniform1i(tLocation, 0);
	}

	glDrawArrays(GL_TRIANGLES, 0, sizeof(test_mysteryBlock_vertices) / sizeof(test_mysteryBlock_vertices[0]));
}