#include "door.h"
#include <string>

glm::vec2 door_text_pos[] = {
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

glm::vec3 test_door_vertices[] = {
	glm::vec3(-0.5,0.5,0.5),glm::vec3(-0.5,-0.5,0.5), glm::vec3(0.5,-0.5,0.5),		// 1, 4, 5		앞면
	glm::vec3(-0.5,0.5,0.5),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.5,0.5,0.5),			// 1, 5, 2

	//glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,0.5,0.5),glm::vec3(0.5,0.5,0.5),		// 0, 1, 2		윗면
	//glm::vec3(-0.5,0.5,-0.5),glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,0.5,-0.5),		// 0, 2, 3

	//glm::vec3(-0.5,-0.5,-0.5),glm::vec3(0.5,-0.5,-0.5),glm::vec3(0.5,-0.5,0.5),	// 7, 6, 5		아랫면
	//glm::vec3(-0.5,-0.5,-0.5), glm::vec3(0.5,-0.5,0.5),glm::vec3(-0.5,-0.5,0.5),	// 7, 5, 4

	//glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.5,-0.5,-0.5),		// 2, 5, 6
	//glm::vec3(0.5,0.5,0.5),glm::vec3(0.5,-0.5,-0.5), glm::vec3(0.5,0.5,-0.5),		// 2, 6, 3

	//glm::vec3(0.5,0.5,-0.5), glm::vec3(0.5,-0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),	// 3, 6, 7
	//glm::vec3(0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),glm::vec3(-0.5,0.5,-0.5),		// 3, 7, 0

	//glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,-0.5),glm::vec3(-0.5,-0.5,0.5),	// 0, 7, 4
	//glm::vec3(-0.5,0.5,-0.5),glm::vec3(-0.5,-0.5,0.5), glm::vec3(-0.5,0.5,0.5),		// 0, 4, 1
};

GLuint door_texture[11] = { -1, };

Door::Door() {
	InitBuffer();
	this->trans = glm::vec3(0.0, 0.0, 0.0);
	this->rot = glm::vec3(0.0, 0.0, 0.0);
	this->scale = glm::vec3(1.0, 1.0, 1.0);
	frame = 0;
};
Door::Door(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate) {
	InitBuffer();
	this->trans = trans;
	this->scale = scale;
	this->rot = rotate;
	frame = 0;
};
Door::~Door() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(3, VBO);
};


GLvoid Door::Init() {

}
GLvoid Door::InitBuffer() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, VBO);
	if (door_texture[0] == -1) {
		//임시 코드임 나중에 이미지 수정해야함
		for (int i = 0; i < 11; i++)
		{
			std::string str = "resource/Map/doorAnimation/door";
			str = str + std::to_string(i) + ".png";
			LoadTexture(door_texture[i], str.c_str());
		}
	}
}

GLvoid Door::update() {
 	frame++;
	if (frame > 110) frame = 0;
}

GLvoid Door::draw() {
	glUseProgram(Gets_program_texture());
	glm::mat4 TR = glm::mat4(1.0f);
	glm::mat4 T = glm::mat4(1.0f);
	T = glm::translate(T, glm::vec3(trans.x, trans.y, trans.z));
	glm::mat4 S = glm::mat4(1.0f);
	S = glm::scale(S, glm::vec3(scale.x, scale.y, scale.z));
	TR = T * S * TR;

	unsigned int modelLocation = glGetUniformLocation(Gets_program_texture(), "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);

	glBindVertexArray(VAO);

	//조명 o
	glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(test_door_vertices), test_door_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXTURE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(door_text_pos), door_text_pos, GL_STATIC_DRAW);
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(5);

	int tLocation = glGetUniformLocation(Gets_program_texture(), "outTexture"); //--- outTexture1 유니폼 샘플러의 위치를 가져옴
	glActiveTexture(door_texture[frame/10]);
	glBindTexture(GL_TEXTURE_2D, door_texture[frame / 10]);
	glUniform1i(tLocation, 0);

	glDrawArrays(GL_TRIANGLES, 0, sizeof(test_door_vertices) / sizeof(test_door_vertices[0]));
}