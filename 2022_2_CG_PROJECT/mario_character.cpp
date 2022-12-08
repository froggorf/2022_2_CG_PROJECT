#include "mario_character.h"

enum HANDLE_COLLISION {
	X_DOWN,X_UP,Y_DOWN,Y_UP,Z_DOWN,Z_UP
};

GLvoid Mario::init() {
	boundingBox.init();
	boundingBox.scale = glm::vec3(1.5f, 1.5f, 1.0f);
	speed = MarioSpeed;
	gravity = 0;
	flag_jump = true;
	frame = 0;
	cur_state = IDLE_RIGHT;
}

GLvoid Mario::update() {
	for (int i = 0; i < KeyBoard::KEYEND; ++i) {
		if (GetKeyDown()[i]) {
			handle_events(i);
		}
	}

	frame += 0.2;
	if (frame >= 4) {
		frame = 0;
	}

	{//중력 처리 -> 함수로 변경 예정
		falling_gravity();
		//중력에 대한 충돌체크 처리
		for (int i = 0; i < Play::GetGround().size(); ++i) {
			if (CheckAABB(boundingBox, Play::GetGround()[i].boundingBox)) {
				boundingBox.trans.y = Play::GetGround()[i].boundingBox.trans.y + 0.5 * Play::GetGround()[i].boundingBox.scale.y + 0.5 * boundingBox.scale.y;
				gravity = 0;
				flag_jump = true;
			}
		}
	}
	

}

glm::vec3 mario_vertices[6]{
	glm::vec3(-0.5,0.5,0.5),glm::vec3(-0.5,-0.5,0.5), glm::vec3(0.5,-0.5,0.5),
	glm::vec3(-0.5,0.5,0.5),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.5,0.5,0.5),
};
glm::vec2 mario_texture[6]{
	 glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
	glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),
};

GLvoid Mario::draw() {
	//boundingBox.draw();

	glm::mat4 TR = glm::mat4(1.0f);
	
	glm::mat4 T = glm::mat4(1.0f);
	T = glm::translate(T, glm::vec3(boundingBox.trans.x, boundingBox.trans.y, boundingBox.trans.z));

	glm::mat4 S = glm::mat4(1.0f);
	S = glm::translate(S, glm::vec3(boundingBox.scale.x, boundingBox.scale.y, boundingBox.scale.z));



	TR = T * S * TR;

	unsigned int modelLocation = glGetUniformLocation(Gets_program_texture(), "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);

	glBindVertexArray(VAO);

	//조명 o
	glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mario_vertices), mario_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(3);
	
	//glBindBuffer(GL_ARRAY_BUFFER, VBO[NORMAL]);	//노말벡터에 관련된 값이오나 임시로 확인하기 위해 사용
	//glm::vec3 norm[36];
	//for (int i = 0; i < 36; ++i) {
	//	norm[i] = glm::mat3(glm::transpose(glm::inverse(TR))) * glm::vec3(cube_normal[i][X], cube_normal[i][Y], cube_normal[i][Z]);
	//}
	//glBufferData(GL_ARRAY_BUFFER, sizeof(norm), norm, GL_STATIC_DRAW);
	//glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(4);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[TEXTURE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mario_texture), mario_texture, GL_STATIC_DRAW);
	glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(5);

	int tLocation = glGetUniformLocation(Gets_program_texture(), "outTexture"); //--- outTexture1 유니폼 샘플러의 위치를 가져옴
	
	glActiveTexture(texture[cur_state][(int)frame]);
	glBindTexture(GL_TEXTURE_2D, texture[cur_state][(int)frame]);
	glUniform1i(tLocation, 0);
	
	

	glDrawArrays(GL_TRIANGLES, 0, sizeof(mario_vertices) / sizeof(mario_vertices[0]));
}

GLuint mario_max_frame[MARIOSTATEEND];

GLvoid Mario::InitBuffer() {
	//boundingBox.InitBuffer();
	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, VBO);
	if (mario_max_frame[IDLE_RIGHT] == 0) {
		mario_max_frame[IDLE_RIGHT] = 7;
		mario_max_frame[IDLE_LEFT] = 7;
		mario_max_frame[WALKING_LEFT] = 4;
		mario_max_frame[WALKING_RIGHT] = 4;
		mario_max_frame[WALKING_RIGHT_UP] = 2;
		mario_max_frame[WALKING_LEFT_UP] = 2;
		mario_max_frame[JUMP_RIGHT] = 1;
		mario_max_frame[JUMP_LEFT] = 1;
		mario_max_frame[JUMP_RIGHT_UP] = 1;
		mario_max_frame[JUMP_LEFT_UP] = 1;
		mario_max_frame[HURT_RIGHT] = 1;
		mario_max_frame[HURT_LEFT] = 1;
	}
	for (int i = 0; i < mario_max_frame[IDLE_RIGHT]; ++i) {
		std::string resourcedir = "resource/Mario/IDLE_RIGHT/mario_IDLE_RIGHT_0" + std::to_string(i+1) + ".png";
		LoadTexture(texture[IDLE_RIGHT][i], resourcedir.c_str());
	}
	for (int i = 0; i < mario_max_frame[IDLE_LEFT]; ++i) {
		std::string resourcedir = "resource/Mario/IDLE_LEFT/mario_IDLE_RIGHT_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[IDLE_LEFT][i], resourcedir.c_str());
	}
	for (int i = 0; i < mario_max_frame[WALKING_RIGHT]; ++i) {
		std::string resourcedir = "resource/Mario/WALK_RIGHT/mario_WALK_RIGHT_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[WALKING_RIGHT][i], resourcedir.c_str());
	}
	for (int i = 0; i < mario_max_frame[WALKING_LEFT]; ++i) {
		std::string resourcedir = "resource/Mario/WALK_LEFT/mario_WALK_LEFT_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[WALKING_LEFT][i], resourcedir.c_str());
	}
	for (int i = 0; i < mario_max_frame[WALKING_RIGHT_UP]; ++i) {
		std::string resourcedir = "resource/Mario/WALK_LEFT/mario_WALK_RIGHT_UP_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[WALKING_RIGHT_UP][i], resourcedir.c_str());
	}
	for (int i = 0; i < mario_max_frame[WALKING_LEFT_UP]; ++i) {
		std::string resourcedir = "resource/Mario/WALK_LEFT/mario_WALK_LEFT_UP_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[WALKING_LEFT_UP][i], resourcedir.c_str());
	}
	for (int i = 0; i < mario_max_frame[JUMP_RIGHT]; ++i) {
		std::string resourcedir = "resource/Mario/WALK_LEFT/mario_JUMP_RIGHT_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[JUMP_RIGHT][i], resourcedir.c_str());
	}
	for (int i = 0; i < mario_max_frame[JUMP_LEFT]; ++i) {
		std::string resourcedir = "resource/Mario/WALK_LEFT/mario_JUMP_LEFT_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[JUMP_LEFT][i], resourcedir.c_str());
	}
	for (int i = 0; i < mario_max_frame[JUMP_RIGHT_UP]; ++i) {
		std::string resourcedir = "resource/Mario/WALK_LEFT/mario_JUMP_RIGHT_UP_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[JUMP_RIGHT_UP][i], resourcedir.c_str());
	}
	for (int i = 0; i < mario_max_frame[JUMP_LEFT_UP]; ++i) {
		std::string resourcedir = "resource/Mario/WALK_LEFT/mario_JUMP_LEFT_UP_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[JUMP_LEFT_UP][i], resourcedir.c_str());
	}
	for (int i = 0; i < mario_max_frame[HURT_RIGHT]; ++i) {
		std::string resourcedir = "resource/Mario/WALK_LEFT/mario_HURT_RIGHT_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[HURT_RIGHT][i], resourcedir.c_str());
	}
	for (int i = 0; i < mario_max_frame[HURT_LEFT]; ++i) {
		std::string resourcedir = "resource/Mario/WALK_LEFT/mario_HURT_LEFT_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[HURT_LEFT][i], resourcedir.c_str());
	}
	
}

GLvoid Mario::handle_events(int e) {
	switch (e) {
	case pressW:
		if (GetKeyDown()[pressS]) break;
		move(pressW);
		break;
	case pressS:
		if (GetKeyDown()[pressW]) break;
		move(pressS);
		break;
	case pressA:
		if (GetKeyDown()[pressD]) break;
		move(pressA);
		break;
	case pressD:
		if (GetKeyDown()[pressA]) break;
		move(pressD);
		break;
	case pressSPACE:
		if (flag_jump) {
			//TODO: 점프 높이에대한 값 조정하기
			gravity = GravityAcceleration * 30;
			flag_jump = false;
		}
		
		break;
	}
}

GLvoid Mario::falling_gravity() {
	boundingBox.trans.y += gravity;
	gravity -= GravityAcceleration;
}

GLvoid Mario::move(int events) {
	switch (events) {
	case pressW:
		boundingBox.trans.z -= speed;
		break;
	case pressS:
		boundingBox.trans.z += speed;
		break;
	case pressA:
		boundingBox.trans.x -= speed;
		break;
	case pressD:
		boundingBox.trans.x += speed;
		break;
	}
	handle_collision(events, Play::GetGround());

	
}
GLvoid Mario::handle_collision(int events, std::vector<Ground>& ground) {
	for (int i = 0; i < ground.size(); ++i) {
		if (CheckAABB(boundingBox, ground[i].boundingBox)) {
			switch (events) {
			case pressW:
				boundingBox.trans.z = ground[i].boundingBox.trans.z + 0.5 * ground[i].boundingBox.scale.z + 0.5 * boundingBox.scale.z;
				break;
			case pressS:
				boundingBox.trans.z = ground[i].boundingBox.trans.z - 0.5 * ground[i].boundingBox.scale.z - 0.5 * boundingBox.scale.z;
				break;
			case pressA:
				boundingBox.trans.x = ground[i].boundingBox.trans.x + 0.5 * ground[i].boundingBox.scale.x + 0.5 * boundingBox.scale.x;
				break;
			case pressD:
				boundingBox.trans.x = ground[i].boundingBox.trans.x - 0.5 * ground[i].boundingBox.scale.x - 0.5 * boundingBox.scale.x;
				
				break;
			}
		}
	}
}