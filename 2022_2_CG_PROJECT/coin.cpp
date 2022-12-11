#include "coin.h"

glm::vec2 coin_text_pos[] = {
	glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
	glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),

	//glm::vec2(0.9f,1.0f),glm::vec2(0.9f,0.9f),glm::vec2(1.0f,0.9f),
	//glm::vec2(0.9f,1.0f),glm::vec2(1.0f,0.9f),glm::vec2(1.0f,1.0f),

	//glm::vec2(0.9f,1.0f),glm::vec2(0.9f,0.9f),glm::vec2(1.0f,0.9f),
	//glm::vec2(0.9f,1.0f),glm::vec2(1.0f,0.9f),glm::vec2(1.0f,1.0f),

	//glm::vec2(0.9f,1.0f),glm::vec2(0.9f,0.9f),glm::vec2(1.0f,0.9f),
	//glm::vec2(0.9f,1.0f),glm::vec2(1.0f,0.9f),glm::vec2(1.0f,1.0f),

	//glm::vec2(0.9f,1.0f),glm::vec2(0.9f,0.9f),glm::vec2(1.0f,0.9f),
	//glm::vec2(0.9f,1.0f),glm::vec2(1.0f,0.9f),glm::vec2(1.0f,1.0f),

	//glm::vec2(0.9f,1.0f),glm::vec2(0.9f,0.9f),glm::vec2(1.0f,0.9f),
	//glm::vec2(0.9f,1.0f),glm::vec2(1.0f,0.9f),glm::vec2(1.0f,1.0f),
};

glm::vec3 test_coin_vertices[] = {
	glm::vec3(-0.5,0.5,0.5),glm::vec3(-0.5,-0.5,0.5), glm::vec3(0.5,-0.5,0.5),		// 1, 4, 5		¾Õ¸é
	glm::vec3(-0.5,0.5,0.5),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.5,0.5,0.5),			// 1, 5, 2

	//glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,0.5,0.5),glm::vec3(0.5,0.5,0.5),		// 0, 1, 2		À­¸é
	//glm::vec3(-0.5,0.5,-0.5),glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,0.5,-0.5),		// 0, 2, 3

	//glm::vec3(-0.5,-0.5,-0.5),glm::vec3(0.5,-0.5,-0.5),glm::vec3(0.5,-0.5,0.5),	// 7, 6, 5		¾Æ·§¸é
	//glm::vec3(-0.5,-0.5,-0.5), glm::vec3(0.5,-0.5,0.5),glm::vec3(-0.5,-0.5,0.5),	// 7, 5, 4

	//glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.5,-0.5,-0.5),		// 2, 5, 6
	//glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,-0.5,-0.5), glm::vec3(0.5,0.5,-0.5),		// 2, 6, 3

	//glm::vec3(0.5,0.5,-0.5), glm::vec3(0.5,-0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),	// 3, 6, 7
	//glm::vec3(0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),glm::vec3(-0.5,0.5,-0.5),		// 3, 7, 0

	//glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),glm::vec3(-0.5,-0.5,0.5),	// 0, 7, 4
	//glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,0.5), glm::vec3(-0.5,0.5,0.5),		// 0, 4, 1
};

GLuint coin_texture[8] = { -1, };
MCI_OPEN_PARMS sound;

Coin::Coin() {
	InitBuffer();
	Init();
	this->trans = glm::vec3(0.0, 0.0, 0.0);
	this->rot = glm::vec3(0.0, 0.0, 0.0);
	this->scale = glm::vec3(1.0, 1.0, 1.0);
};
Coin::Coin(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate) {
	InitBuffer();
	Init();
	this->trans = trans;
	this->scale = scale;
	this->rot = rotate;
};
Coin::Coin(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate, GLboolean isOnGround) {
	InitBuffer();
	Init();
	this->trans = trans;
	this->scale = scale;
	this->rot = rotate;
	this->isOnGround = false;
};
Coin::~Coin() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(3, VBO);
};


GLvoid Coin::Init() {
	frame = 0;
	isOnGround = true;
	appearMoveFigure = 0.0;
	isMovingUp = true;
	coinSound.lpstrElementName = TEXT(GETCOINSOUND);
	coinSound.lpstrDeviceType = TEXT("mpegvideo");
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&coinSound);
}
GLvoid Coin::InitBuffer() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, VBO);
	if (coin_texture[0] == -1) {
		for (int i = 0; i < 8; i++) {
			std::string str = "resource/Item/coin" + std::to_string(i) + ".png";
			LoadTexture(coin_texture[i], str.c_str());
		}
		SetBgm(GETCOINSOUND, sound);
	}
}

GLvoid Coin::update() {
	if (++frame >= 39) frame = 0;
	if (!isOnGround) {
		if (isMovingUp) {
			appearMoveFigure += 0.2;
			if (appearMoveFigure >= 1.6) isMovingUp = false;
		}
		else {
			appearMoveFigure -= 0.2;
			if (appearMoveFigure >= 0.0) {
				appearMoveFigure = 0.0;
				isMovingUp = false;
				Play::SetMarioCoin(1);
 				//PlaySoundMP3(coinSound, false);
				SoundToStart(sound);
				PlaySoundMP3(GETCOINSOUND, false, sound);
				isCanDelete = true;
			}
		}
	}
}

GLvoid Coin::collision_handling(Cube* other) {
	Cube* marioCast = dynamic_cast<Mario*>(other);
	if (marioCast != nullptr and !isCanDelete) {
		std::cout << "Coin collision handling" << std::endl;
		Play::SetMarioCoin(1);
		SoundToStart(sound);
		PlaySoundMP3(GETCOINSOUND, false, sound);
		isCanDelete = true;
	}
}

GLvoid Coin::draw(GLuint cType) {
	glUseProgram(Gets_program_texture());
	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 T = glm::mat4(1.0f);
	glm::mat4 R = glm::mat4(1.0f);
	glm::mat4 S = glm::mat4(1.0f);


	T = glm::translate(T, glm::vec3(trans.x, trans.y + appearMoveFigure, trans.z));
	S = glm::scale(S, glm::vec3(scale.x, scale.y, scale.z));
	if(cType == D3_VIEW)
		R = glm::rotate(R, glm::radians(-90.0f), glm::vec3(0.0, 1.0, 0.0));

	TR = T * S * R * TR;

	unsigned int modelLocation = glGetUniformLocation(Gets_program_texture(), "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);

	glBindVertexArray(VAO);

	//Á¶¸í o
	glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(test_coin_vertices), test_coin_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXTURE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coin_text_pos), coin_text_pos, GL_STATIC_DRAW);
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(5);

	int tLocation = glGetUniformLocation(Gets_program_texture(), "outTexture"); //--- outTexture1 À¯´ÏÆû »ùÇÃ·¯ÀÇ À§Ä¡¸¦ °¡Á®¿È
	glActiveTexture(coin_texture[frame / 5]);
	glBindTexture(GL_TEXTURE_2D, coin_texture[frame / 5]);
	glUniform1i(tLocation, 0);

	glDrawArrays(GL_TRIANGLES, 0, sizeof(test_coin_vertices) / sizeof(test_coin_vertices[0]));
}