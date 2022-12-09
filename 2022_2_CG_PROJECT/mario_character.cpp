#include "mario_character.h"


GLuint mario_max_frame[MARIOSTATEEND];

enum HANDLE_COLLISION {
	X_DOWN, X_UP, Y_DOWN, Y_UP, Z_DOWN, Z_UP
};

GLvoid Mario::init() {
	boundingBox.Init();
	boundingBox.scale = glm::vec3(1.5f, 1.5f, 1.0f);
	speed = MarioSpeed;
	gravity = 0;
	flag_jump = true;
	frame = 0;
	face = RIGHT;
	cur_state = IDLE_RIGHT;
}

GLvoid Mario::update() {
	{
		PLEASEDELETELATER_PRINTCURSTATEFUNCTION();
	}

	frame += 0.2;
	if (frame >= mario_max_frame[cur_state]) {
		frame = 0;
	}

	if (dir[X] != 0)
		move(X);
	if (dir[Z] != 0)
		move(Z);


	{//중력 처리 -> 함수로 변경 예정
		falling_gravity();

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
	S = glm::scale(S, glm::vec3(boundingBox.scale.x, boundingBox.scale.y, boundingBox.scale.z));

	glm::mat4 rot = glm::mat4(1.0f);
	rot = glm::rotate(rot, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	TR = T * rot * S * TR;

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


	glActiveTexture(texture[cur_state + face][(int)frame]);
	glBindTexture(GL_TEXTURE_2D, texture[cur_state + face][(int)frame]);
	glUniform1i(tLocation, 0);



	glDrawArrays(GL_TRIANGLES, 0, sizeof(mario_vertices) / sizeof(mario_vertices[0]));
}


GLvoid Mario::InitBuffer() {
	//boundingBox.InitBuffer();
	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, VBO);
	if (mario_max_frame[IDLE_RIGHT] == 0) {
		mario_max_frame[IDLE_RIGHT] = 7;
		mario_max_frame[IDLE_LEFT] = 7;
		mario_max_frame[IDLE_RIGHT_UP] = 4;
		mario_max_frame[IDLE_LEFT_UP] = 4;
		mario_max_frame[WALKING_LEFT] = 4;
		mario_max_frame[WALKING_RIGHT] = 4;
		mario_max_frame[WALKING_RIGHT_UP] = 4;
		mario_max_frame[WALKING_LEFT_UP] = 4;
		mario_max_frame[JUMP_RIGHT] = 1;
		mario_max_frame[JUMP_LEFT] = 1;
		mario_max_frame[JUMP_RIGHT_UP] = 1;
		mario_max_frame[JUMP_LEFT_UP] = 1;
		mario_max_frame[HURT_RIGHT] = 1;
		mario_max_frame[HURT_LEFT] = 1;
	}
	//TODO: IDLE_RIGHT_UP, IDLE_LEFT_UP 에 대한 이미지와 프레임 수 넣기
	for (int i = 0; i < mario_max_frame[IDLE_RIGHT]; ++i) {
		std::string resourcedir = "resource/Mario/IDLE_RIGHT/mario_IDLE_RIGHT_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[IDLE_RIGHT][i], resourcedir.c_str());
	}
	for (int i = 0; i < mario_max_frame[IDLE_LEFT]; ++i) {
		std::string resourcedir = "resource/Mario/IDLE_LEFT/mario_IDLE_LEFT_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[IDLE_LEFT][i], resourcedir.c_str());
	}
	for (int i = 0; i < mario_max_frame[IDLE_RIGHT_UP]; ++i) {
		std::string resourcedir = "resource/Mario/IDLE_RIGHT_UP/mario_IDLE_RIGHT_UP_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[IDLE_RIGHT_UP][i], resourcedir.c_str());
	}
	for (int i = 0; i < mario_max_frame[IDLE_LEFT_UP]; ++i) {
		std::string resourcedir = "resource/Mario/IDLE_LEFT_UP/mario_IDLE_LEFT_UP_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[IDLE_LEFT_UP][i], resourcedir.c_str());
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
		std::string resourcedir = "resource/Mario/WALKING_RIGHT_UP/temp_mario_WALK_RIGHT_UP_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[WALKING_RIGHT_UP][i], resourcedir.c_str());
	}
	for (int i = 0; i < mario_max_frame[WALKING_LEFT_UP]; ++i) {
		std::string resourcedir = "resource/Mario/WALKING_LEFT_UP/temp_mario_WALK_LEFT_UP_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[WALKING_LEFT_UP][i], resourcedir.c_str());
	}
	for (int i = 0; i < mario_max_frame[JUMP_RIGHT]; ++i) {
		std::string resourcedir = "resource/Mario/JUMP_RIGHT/mario_JUMP_RIGHT_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[JUMP_RIGHT][i], resourcedir.c_str());
	}
	for (int i = 0; i < mario_max_frame[JUMP_LEFT]; ++i) {
		std::string resourcedir = "resource/Mario/JUMP_LEFT/mario_JUMP_LEFT_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[JUMP_LEFT][i], resourcedir.c_str());
	}
	for (int i = 0; i < mario_max_frame[JUMP_RIGHT_UP]; ++i) {
		std::string resourcedir = "resource/Mario/JUMP_RIGHT_UP/mario_JUMP_RIGHT_UP_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[JUMP_RIGHT_UP][i], resourcedir.c_str());
	}
	for (int i = 0; i < mario_max_frame[JUMP_LEFT_UP]; ++i) {
		std::string resourcedir = "resource/Mario/JUMP_LEFT_UP/mario_JUMP_LEFT_UP_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[JUMP_LEFT_UP][i], resourcedir.c_str());
	}
	for (int i = 0; i < mario_max_frame[HURT_RIGHT]; ++i) {
		std::string resourcedir = "resource/Mario/HURT_RIGHT/mario_HURT_RIGHT_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[HURT_RIGHT][i], resourcedir.c_str());
	}
	for (int i = 0; i < mario_max_frame[HURT_LEFT]; ++i) {
		std::string resourcedir = "resource/Mario/HURT_LEFT/mario_HURT_LEFT_0" + std::to_string(i + 1) + ".png";
		LoadTexture(texture[HURT_LEFT][i], resourcedir.c_str());
	}

}

GLvoid Mario::move(int XYZ) {
	switch (XYZ) {
	case X:
		boundingBox.trans.x += dir[X] * speed;
		break;
	case Z:
		boundingBox.trans.z += dir[Z] * speed;
		break;

	}
	handle_collision(XYZ, Play::GetGround());


}

GLvoid Mario::falling_gravity() {
	boundingBox.trans.y += gravity;
	gravity -= GravityAcceleration;
	//중력에 대한 충돌체크 처리
	for (int i = 0; i < Play::GetGround().size(); ++i) {
		if (CheckAABB(boundingBox, *Play::GetGround()[i])) {
			if (gravity > 0) {	//위로 점프중일때
				boundingBox.trans.y = Play::GetGround()[i]->trans.y - 0.5 * Play::GetGround()[i]->scale.y - 0.5 * boundingBox.scale.y;
				gravity = 0;
			}
			else {	//밑으로 중력 적용중일떄
				boundingBox.trans.y = Play::GetGround()[i]->trans.y + 0.5 * Play::GetGround()[i]->scale.y + 0.5 * boundingBox.scale.y;
				gravity = 0;
				flag_jump = true;
				if (cur_state == JUMP_RIGHT) {
					StateExit();
					//Mario_Change_State(IDLE_RIGHT);
					StateEnter();
				}
				else if (cur_state == JUMP_RIGHT_UP) {
					StateExit();
					//Mario_Change_State(IDLE_RIGHT_UP);
					StateEnter();
				}
			}


		}
	}



}

GLvoid Mario::DoJump() {
	if (flag_jump&& gravity >=-GravityAcceleration*2) {
		//TODO: 점프 높이에대한 값 조정하기
		gravity = GravityAcceleration * 30;
		flag_jump = false;
	}
}

GLvoid Mario::handle_collision(int XYZ, std::vector<Cube*> map) {
	for (int i = 0; i < map.size(); ++i) {
		if (CheckAABB(boundingBox, *map[i])) {
			switch (XYZ) {
			case X:
				if (dir[X] >= 1) {
					boundingBox.trans.x = map[i]->trans.x - 0.5 * map[i]->scale.x - 0.5 * boundingBox.scale.x;
				}
				else if (dir[X] <= -1) {
					boundingBox.trans.x = map[i]->trans.x + 0.5 * map[i]->scale.x + 0.5 * boundingBox.scale.x;
				}
				break;
			case Z:
				if (dir[Z] >= 1) {
					boundingBox.trans.z = map[i]->trans.z - 0.5 * map[i]->scale.z - 0.5 * boundingBox.scale.z;
				}
				else if (dir[Z] <= -1) {
					boundingBox.trans.z = map[i]->trans.z + 0.5 * map[i]->scale.z + 0.5 * boundingBox.scale.z;
				}
				break;
			}
		}
	}
}

GLvoid Mario::Mario_Change_State(int next_state) {
	if (cur_state == next_state) return;
	cur_state = next_state;
	frame = 0;
}

//파이썬때 class 상태 enter 코드
GLvoid Mario::StateEnter(int type, unsigned char key) {
	switch (cur_state) {
	case IDLE_RIGHT:
	case IDLE_LEFT:
		dir[X] = 0;
		dir[Z] = 0;
		break;
	case IDLE_RIGHT_UP:
	case IDLE_LEFT_UP:
		dir[X] = 0;
		dir[Z] = 0;
		break;
	case WALKING_RIGHT:
	case WALKING_LEFT:
		switch (type) {
		case GLUT_KEY_DOWN:
			switch (key) {
			case 'a':
				face = LEFT;
				
				
				dir[Z] -= 1;
				if (dir[Z] < -1) dir[Z] = -1;
				break;
			case 'd':
				face = RIGHT;
				dir[Z] += 1;
				if (dir[Z] > 1) dir[Z] = 1;
				break;
			case 'w':
				dir[X] += 1;
				if (dir[X] > 1) dir[X] = 1;
				break;
			case 's':
				
				dir[X] -= 1;
				if (dir[X] < -1) dir[X] = -1;
				break;
			}
			break;
		case GLUT_KEY_UP:
			switch (key) {
			case 'a':
				if (!GetKeyDown()[pressS]) {
					face = RIGHT;
				}
				dir[Z] += 1;
				if (dir[Z] > 1) dir[Z] = 1;
				break;
			case 'd':
				if (!GetKeyDown()[pressS]) {
					face = LEFT;
				}
				dir[Z] -= 1;
				if (dir[Z] < -1) dir[Z] = -1;
				
				break;
			case 'w':
				dir[X] -= 1;
				if (dir[X] < -1) dir[X] = -1;
				break;
			case 's':
				dir[X] += 1;
				if (dir[X] > 1) dir[X] = 1;
				break;
			}
			break;
		}
		break;
	case WALKING_RIGHT_UP:
	case WALKING_LEFT_UP:
		switch (type) {
		case GLUT_KEY_DOWN:
			switch (key) {
			case 'a':
				face = LEFT;
				dir[Z] -= 1;
				if (dir[Z] < -1) dir[Z] = -1;
				break;
			case 'd':
				face = RIGHT;
				dir[Z] += 1;
				if (dir[Z] > 1) dir[Z] = 1;
				break;
			case 'w':
				dir[X] += 1;
				if (dir[X] > 1) dir[X] = 1;
				break;
			case 's':
				dir[X] -= 1;
				if (dir[X] < -1) dir[X] = -1;
				break;
			}
			break;
		case GLUT_KEY_UP:
			switch (key) {
			case 'a':
				if (!GetKeyDown()[pressW]) {
					face = RIGHT;
				}
				
				dir[Z] += 1;
				if (dir[Z] > 1) dir[Z] = 1;
				break;
			case 'd':
				if (!GetKeyDown()[pressW]) {
					face = LEFT;
				}
				dir[Z] -= 1;
				if (dir[Z] < -1) dir[Z] = -1;

				break;
			case 'w':
				dir[X] -= 1;
				if (dir[X] < -1) dir[X] = -1;
				break;
			case 's':
				dir[X] += 1;
				if (dir[X] > 1) dir[X] = 1;
				break;
			}
			break;
		}
		break;
	case JUMP_RIGHT:
	case JUMP_LEFT:
		DoJump(); 
		switch (type) {
		case GLUT_KEY_DOWN:
			switch (key) {
			case 'a':
				face = LEFT;
				dir[Z] -= 1;
				if (dir[Z] < -1) dir[Z] = -1;
				break;
			case 'd':
				face = RIGHT;
				dir[Z] += 1;
				if (dir[Z] > 1) dir[Z] = 1;
				break;
			case 'w':
				dir[X] += 1;
				if (dir[X] > 1) dir[X] = 1;
				break;
			case 's':
				dir[X] -= 1;
				if (dir[X] < -1) dir[X] = -1;
				break;
			}
			break;
		case GLUT_KEY_UP:
			switch (key) {
			case 'a':
				if (!GetKeyDown()[pressS]) {
					face = RIGHT;
				}
				
				dir[Z] += 1;
				if (dir[Z] > 1) dir[Z] = 1;
				break;
			case 'd':
				if (!GetKeyDown()[pressS]) {
					face = LEFT;
				}
				
				dir[Z] -= 1;
				if (dir[Z] < -1) dir[Z] = -1;

				break;
			case 'w':
				dir[X] -= 1;
				if (dir[X] < -1) dir[X] = -1;
				break;
			case 's':
				dir[X] += 1;
				if (dir[X] > 1) dir[X] = 1;
				break;
			}
			break;
		}
		break;
	case JUMP_RIGHT_UP:
	case JUMP_LEFT_UP:
		DoJump();
		switch (type) {
		case GLUT_KEY_DOWN:
			switch (key) {
			case 'a':
				face = LEFT;
				dir[Z] -= 1;
				if (dir[Z] < -1) dir[Z] = -1;
				break;
			case 'd':
				face = RIGHT;
				dir[Z] += 1;
				if (dir[Z] > 1) dir[Z] = 1;
				break;
			case 'w':
				dir[X] += 1;
				if (dir[X] > 1) dir[X] = 1;
				break;
			case 's':
				dir[X] -= 1;
				if (dir[X] < -1) dir[X] = -1;
				break;
			}
			break;
		case GLUT_KEY_UP:
			switch (key) {
			case 'a':
				if (!GetKeyDown()[pressW]) {
					face = RIGHT;
				}
				
				dir[Z] += 1;
				if (dir[Z] > 1) dir[Z] = 1;
				break;
			case 'd':
				if (!GetKeyDown()[pressW]) {
					face = LEFT;
				}
				
				dir[Z] -= 1;
				if (dir[Z] < -1) dir[Z] = -1;

				break;
			case 'w':
				dir[X] -= 1;
				if (dir[X] < -1) dir[X] = -1;
				break;
			case 's':
				dir[X] += 1;
				if (dir[X] > 1) dir[X] = 1;
				break;
			}
			break;
		}
		break;
	case HURT_RIGHT:
	case HURT_LEFT:
		break;
	}
	//std::cout << "dir: [" << dir[X] << ", " << dir[Y] << ", " << dir[Z] << "]" << std::endl;
}
//파이썬때 class 상태 exit 코드
GLvoid Mario::StateExit(int type, unsigned char key) {
	switch (cur_state) {
	case IDLE_RIGHT:
	case IDLE_LEFT:

		break;
	case IDLE_RIGHT_UP:
	case IDLE_LEFT_UP:

		break;
	case WALKING_RIGHT:
	case WALKING_LEFT:
		break;
	case WALKING_RIGHT_UP:
	case WALKING_LEFT_UP:
		break;
	case JUMP_RIGHT:
	case JUMP_LEFT:
		if ((GetKeyDown()[pressD] && !GetKeyDown()[pressA])) {
			Mario_Change_State(WALKING_RIGHT);
			StateEnter(GLUT_KEY_DOWN, 'd');
		}
		else if ((GetKeyDown()[pressA] && !GetKeyDown()[pressD])) {
			Mario_Change_State(WALKING_RIGHT);
			StateEnter(GLUT_KEY_DOWN, 'a');
		}
		else if (GetKeyDown()[pressS]) {
			Mario_Change_State(WALKING_RIGHT);
			StateEnter(GLUT_KEY_DOWN, 's');
		}
		else {
			Mario_Change_State(IDLE_RIGHT_UP);
		}
		break;
	case JUMP_RIGHT_UP:
	case JUMP_LEFT_UP:
		if ((GetKeyDown()[pressD] && !GetKeyDown()[pressA])) {
			Mario_Change_State(WALKING_RIGHT_UP);
			StateEnter(GLUT_KEY_DOWN, 'd');
		}
		else if ((GetKeyDown()[pressA] && !GetKeyDown()[pressD])) {
			Mario_Change_State(WALKING_RIGHT_UP);
			StateEnter(GLUT_KEY_DOWN, 'a');
		}
		else if (GetKeyDown()[pressW]) {
			Mario_Change_State(WALKING_RIGHT_UP);
			StateEnter(GLUT_KEY_DOWN, 'w');
		}
		else {
			Mario_Change_State(IDLE_RIGHT_UP);
		}
		break;
	case HURT_RIGHT:
	case HURT_LEFT:
		break;
	}
}

//파이썬때 class 상태 do 코드
GLvoid Mario::handle_events(int type, unsigned char key) {
	CheckNextState(type, key);
	switch (cur_state) {
	case IDLE_RIGHT:
	case IDLE_LEFT:
		break;
	case IDLE_RIGHT_UP:
	case IDLE_LEFT_UP:
		break;
	case WALKING_RIGHT:
	case WALKING_LEFT:
		break;
	case WALKING_RIGHT_UP:
	case WALKING_LEFT_UP:
		break;
	case JUMP_RIGHT:
	case JUMP_LEFT:
		break;
	case JUMP_RIGHT_UP:
	case JUMP_LEFT_UP:
		break;
	case HURT_RIGHT:
	case HURT_LEFT:
		break;
	}
}

GLvoid Mario::CheckNextState(int type, unsigned char key) {
	switch (cur_state) {
	case IDLE_RIGHT:
	case IDLE_LEFT:
		switch (type) {
		case GLUT_KEY_DOWN:
			switch (key) {
			case 'w':
				if (GetKeyDown()[pressW] && GetKeyDown()[pressS]) break;
				StateExit(type, key);
				Mario_Change_State(WALKING_RIGHT_UP);
				StateEnter(type, key);
				break;
			case 's':
				if (GetKeyDown()[pressW] && GetKeyDown()[pressS]) break;
				StateExit(type, key);
				Mario_Change_State(WALKING_RIGHT);
				StateEnter(type, key);
				break;
			case 'a':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				StateExit(type, key);
				Mario_Change_State(WALKING_RIGHT);
				StateEnter(type, key);
				break;
			case 'd':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				StateExit(type, key);
				Mario_Change_State(WALKING_RIGHT);
				StateEnter(type, key);
				break;
			case ' ':
				StateExit(type, key);
				Mario_Change_State(JUMP_RIGHT);
				StateEnter(type, key);
				break;
			}
			break;
		case GLUT_KEY_UP:
			switch (key) {
			case 'w':
				if (GetKeyDown()[pressS]) {
					StateExit(type, key);
					Mario_Change_State(WALKING_RIGHT);
					StateEnter(type, key);
				}
				break;
			case 's':
				if (GetKeyDown()[pressW]) {
					StateExit(type, key);
					Mario_Change_State(WALKING_RIGHT);
					StateEnter(type, key);
				}
				break;
			case 'a':
				if (GetKeyDown()[pressD]) {
					StateExit(type, key);
					Mario_Change_State(WALKING_RIGHT);
					StateEnter(type, key);
				}
				break;
			case 'd':
				if (GetKeyDown()[pressA]) {
					StateExit(type, key);
					Mario_Change_State(WALKING_RIGHT);
					StateEnter(type, key);
				}
				break;
			}
			break;
		}
		break;


	case IDLE_RIGHT_UP:
	case IDLE_LEFT_UP:
		switch (type) {
		case GLUT_KEY_DOWN:
			switch (key) {
			case 'w':
				if (GetKeyDown()[pressW] && GetKeyDown()[pressS]) break;
				StateExit(type, key);
				Mario_Change_State(WALKING_RIGHT_UP);
				StateEnter(type, key);
				break;
			case 's':
				if (GetKeyDown()[pressW] && GetKeyDown()[pressS]) break;
				StateExit(type, key);
				Mario_Change_State(WALKING_RIGHT);
				StateEnter(type, key);
				break;
			case 'a':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				StateExit(type, key);
				Mario_Change_State(WALKING_RIGHT_UP);
				StateEnter(type, key);
				break;
			case 'd':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				StateExit(type, key);
				Mario_Change_State(WALKING_RIGHT_UP);
				StateEnter(type, key);
				break;
			case ' ':
				StateExit(type, key);
				Mario_Change_State(JUMP_RIGHT_UP);
				StateEnter(type, key);
				break;
			}
			break;
		case GLUT_KEY_UP:
			switch (key) {
			case 'w':
				if (GetKeyDown()[pressS]) {
					StateExit(type, key);
					Mario_Change_State(WALKING_RIGHT);
					StateEnter(type, key);
				}
				break;
			case 's':
				if (GetKeyDown()[pressW]) {
					StateExit(type, key);
					Mario_Change_State(WALKING_RIGHT_UP);
					StateEnter(type, key);
				}
				break;
			case 'a':
				if (GetKeyDown()[pressD]) {
					StateExit(type, key);
					Mario_Change_State(WALKING_RIGHT_UP);
					StateEnter(type, key);
				}
				break;
			case 'd':
				if (GetKeyDown()[pressA]) {
					StateExit(type, key);
					Mario_Change_State(WALKING_RIGHT_UP);
					StateEnter(type, key);
				}
				break;
			}
			break;
		}
		break;


	case WALKING_RIGHT:
	case WALKING_LEFT:
		switch (type) {
		case GLUT_KEY_DOWN:
			switch (key) {
			case 'w':
				if (GetKeyDown()[pressW] && GetKeyDown()[pressS]) break;
				if (!GetKeyDown()[pressA] && !GetKeyDown()[pressD]) {	//A와 D를 누르지 않고 S로만 눌러서 밑으로 가는 상황일 때는 w 누르면 아이들 되게
					StateExit(type, key);
					Mario_Change_State(IDLE_RIGHT);
					StateEnter(type, key);
				}
				else {
					StateExit(type, key);
					Mario_Change_State(WALKING_RIGHT_UP);
					StateEnter(type, key);
				}
				break;
			case 's':
				if (GetKeyDown()[pressW] && GetKeyDown()[pressS]) break;
				StateExit(type, key);
				Mario_Change_State(WALKING_RIGHT);
				StateEnter(type, key);
				break;
			case 'a':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				if (GetKeyDown()[pressS]) {	//s가 눌려서 밑으로 가는 상황
					StateExit(type, key);
					Mario_Change_State(WALKING_RIGHT);
					StateEnter(type, key);
					break;
				}
				if (GetKeyDown()[pressD]) {	//s가 안눌린 채로 오른쪽만 가는 상태
					StateExit(type, key);
					Mario_Change_State(IDLE_RIGHT);
					StateEnter(type, key);
				}
				break;
			case 'd':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				if (GetKeyDown()[pressS]) {	//s가 눌려서 밑으로 가는 상황
					StateExit(type, key);
					Mario_Change_State(WALKING_RIGHT);
					StateEnter(type, key);
					break;
				}
				if (GetKeyDown()[pressA]) {	//s가 안눌린 채로 왼쪽만 가는 상태
					StateExit(type, key);
					Mario_Change_State(IDLE_RIGHT);
					StateEnter(type, key);
				}
				break;
			case ' ':
				StateExit(type, key);
				Mario_Change_State(JUMP_RIGHT);
				StateEnter(type, key);
				break;
			}
			break;
		case GLUT_KEY_UP:
			switch (key) {
			case 'w':
				if (GetKeyDown()[pressS]) {
					StateExit(type, key);
					Mario_Change_State(WALKING_RIGHT);
					StateEnter(type, key);
				}
				break;
			case 's':
				if ((!GetKeyDown()[pressA] and GetKeyDown()[pressD]) or (GetKeyDown()[pressD] and !GetKeyDown()[pressD])) {
					StateExit(type, key);
					Mario_Change_State(WALKING_RIGHT);
					StateEnter(type, key);
				}
				else {
					StateExit(type, key);
					Mario_Change_State(IDLE_RIGHT);
					StateEnter(type, key);
				}
				break;
			case 'a':

				if (GetKeyDown()[pressS]) {
					StateExit(type, key);
					Mario_Change_State(WALKING_RIGHT);
					StateEnter(type, key);
				}
				else {
					StateExit(type, key);
					Mario_Change_State(IDLE_RIGHT);
					StateEnter(type, key);
				}
				
				break;
			case 'd':
				if (GetKeyDown()[pressS]) {
					StateExit(type, key);
					Mario_Change_State(WALKING_RIGHT);
					StateEnter(type, key);
				}
				else {
					StateExit(type, key);
					Mario_Change_State(IDLE_RIGHT);
					StateEnter(type, key);
				}
				break;
			}
			break;
		}
		break;
	case WALKING_RIGHT_UP:
	case WALKING_LEFT_UP:
		switch (type) {
		case GLUT_KEY_DOWN:
			switch (key) {
			case 'w':
				if (GetKeyDown()[pressW] && GetKeyDown()[pressS]) break;
				StateExit(type, key);
				Mario_Change_State(WALKING_RIGHT_UP);
				StateEnter(type, key);
				break;
			case 's':
				if (GetKeyDown()[pressW] && GetKeyDown()[pressS]) break;
				if (!GetKeyDown()[pressA]&&!GetKeyDown()[pressD]) {
					StateExit(type, key);
					Mario_Change_State(IDLE_RIGHT);
					StateEnter(type, key);
					break;
				}
				StateExit(type, key);
				Mario_Change_State(WALKING_RIGHT);
				StateEnter(type, key);
				break;
			case 'a':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				if (GetKeyDown()[pressW]) {
					StateExit(type, key);
					Mario_Change_State(WALKING_RIGHT_UP);	//그대로 가게 하고 z축 이동 금지
					StateEnter(type, key);
					break;
				}
				if (GetKeyDown()[pressD]) {
					StateExit(type, key);
					Mario_Change_State(IDLE_RIGHT_UP);	//그대로 가게 하고 z축 이동 금지
					StateEnter(type, key);
					break;
				}
				StateExit(type, key);
				Mario_Change_State(WALKING_RIGHT_UP);	//그대로 가게 하고 z축 이동 금지
				StateEnter(type, key);
				break;
			case 'd':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				if (GetKeyDown()[pressW]) {
					StateExit(type, key);
					Mario_Change_State(WALKING_RIGHT_UP);	//그대로 가게 하고 z축 이동 금지
					StateEnter(type, key);
					break;
				}
				if (GetKeyDown()[pressA]) {
					StateExit(type, key);
					Mario_Change_State(IDLE_RIGHT_UP);	//그대로 가게 하고 z축 이동 금지
					StateEnter(type, key);
					break;
				}
				StateExit(type, key);
				Mario_Change_State(WALKING_RIGHT_UP);	//그대로 가게 하고 z축 이동 금지
				StateEnter(type, key);
				break;
			case ' ':
				StateExit(type, key);
				Mario_Change_State(JUMP_RIGHT_UP);
				StateEnter(type, key);
				break;
			}
			break;
		case GLUT_KEY_UP:
			switch (key) {
			case 'w':
				if (!GetKeyDown()[pressA] && !GetKeyDown()[pressD]) {
					StateExit(type, key);
					Mario_Change_State(IDLE_RIGHT_UP);
					StateEnter(type, key);
					break;
				}
				StateExit(type, key);
				Mario_Change_State(WALKING_RIGHT_UP);
				StateEnter(type, key);
				break;
			case 'a':
				if (GetKeyDown()[pressW]) {
					StateExit(type, key);
					Mario_Change_State(WALKING_RIGHT_UP);
					StateEnter(type, key);
					break;
				}
				else {
					StateExit(type, key);
					Mario_Change_State(IDLE_RIGHT_UP);
					StateEnter(type, key);
					break;
				}
				
				break;
			case 'd':
				if (GetKeyDown()[pressW]) {
					StateExit(type, key);
					Mario_Change_State(WALKING_RIGHT_UP);
					StateEnter(type, key);
					break;
				}
				else {
					StateExit(type, key);
					Mario_Change_State(IDLE_RIGHT_UP);
					StateEnter(type, key);
					break;
				}
				break;
			}
			break;
		}
		break;
	case JUMP_RIGHT:
	case JUMP_LEFT:
		switch (type) {
		case GLUT_KEY_DOWN:
			switch (key) {
			case 'w':
				if (GetKeyDown()[pressW] && GetKeyDown()[pressS]) break;
				StateExit(type, key);
				Mario_Change_State(JUMP_RIGHT_UP);
				StateEnter(type, key);
				break;
			case 's':
				if (GetKeyDown()[pressW] && GetKeyDown()[pressS]) break;
				StateExit(type, key);
				Mario_Change_State(JUMP_RIGHT);
				StateEnter(type, key);
				break;
			case 'a':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				StateExit(type, key);
				Mario_Change_State(JUMP_RIGHT);
				StateEnter(type, key);
				break;
			case 'd':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				StateExit(type, key);
				Mario_Change_State(JUMP_RIGHT);
				StateEnter(type, key);
				break;
					
			}
			break;
		case GLUT_KEY_UP:
			switch (key) {
			case 'w':
				StateExit(type, key);
				Mario_Change_State(JUMP_RIGHT_UP);
				StateEnter(type, key);
				break;
			case 's':
				StateExit(type, key);
				Mario_Change_State(JUMP_RIGHT_UP);
				StateEnter(type, key);
				break;
			case 'a':
				StateExit(type, key);
				Mario_Change_State(JUMP_RIGHT);
				StateEnter(type, key);
				break;
			case 'd':
				StateExit(type, key);
				Mario_Change_State(JUMP_RIGHT);
				StateEnter(type, key);
				break;
			}
			break;
		}
		break;
	case JUMP_RIGHT_UP:
	case JUMP_LEFT_UP:
		switch (type) {
		case GLUT_KEY_DOWN:
			switch (key) {
			case 'w':
				if (GetKeyDown()[pressW] && GetKeyDown()[pressS]) break;
				StateExit(type, key);
				Mario_Change_State(JUMP_RIGHT_UP);
				StateEnter(type, key);
				break;
			case 's':
				if (GetKeyDown()[pressW] && GetKeyDown()[pressS]) break;
				StateExit(type, key);
				Mario_Change_State(JUMP_RIGHT);
				StateEnter(type, key);
				break;
			case 'a':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				StateExit(type, key);
				Mario_Change_State(JUMP_RIGHT_UP);
				StateEnter(type, key);
				break;
			case 'd':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				StateExit(type, key);
				Mario_Change_State(JUMP_RIGHT_UP);
				StateEnter(type, key);
				break;
			}
			break;
		case GLUT_KEY_UP:
			switch (key) {
			case 'w':
				StateExit(type, key);
				Mario_Change_State(JUMP_RIGHT_UP);
				StateEnter(type, key);
				break;
			case 's':
				StateExit(type, key);
				Mario_Change_State(JUMP_RIGHT);
				StateEnter(type, key);
				break;
			case 'a':
				StateExit(type, key);
				Mario_Change_State(JUMP_RIGHT_UP);
				StateEnter(type, key);
				break;
			case 'd':
				StateExit(type, key);
				Mario_Change_State(JUMP_RIGHT_UP);
				StateEnter(type, key);
				break;
			}
			break;
		}
		break;
	case HURT_RIGHT:
	case HURT_LEFT:
		break;
	}
}

//TODO: 나중에 꼭 지워야하는 함수 현재 상태에 대해 출력해주는 함수임
GLvoid Mario::PLEASEDELETELATER_PRINTCURSTATEFUNCTION() {
	//TODO: 나중에 지울 코드(마리오 현재 상태 출력 코드)
	printf("마리오 상태: ");
	switch (cur_state) {
	case IDLE_RIGHT:
	case IDLE_LEFT:
		if (face == RIGHT) {
			printf("IDLE_RIGHT\n");
		}
		else {
			printf("IDLE_LEFT\n");
		}
		break;
	case IDLE_RIGHT_UP:
	case IDLE_LEFT_UP:
		if (face == RIGHT) {
			printf("IDLE_RIGHT_UP\n");
		}
		else {
			printf("IDLE_LEFT_UP\n");
		}
		break;
	case WALKING_RIGHT:
	case WALKING_LEFT:
		if (face == RIGHT) {
			printf("WALKING_RIGHT\n");
		}
		else {
			printf("WALKING_LEFT\n");
		}
		break;
	case WALKING_RIGHT_UP:
	case WALKING_LEFT_UP:
		if (face == RIGHT) {
			printf("WALKING_RIGHT_UP\n");
		}
		else {
			printf("WALKING_LEFT_UP\n");
		}
		break;
	case JUMP_RIGHT:
	case JUMP_LEFT:
		if (face == RIGHT) {
			printf("JUMP_RIGHT\n");
		}
		else {
			printf("JUMP_LEFT\n");
		}
		break;
	case JUMP_RIGHT_UP:
	case JUMP_LEFT_UP:
		if (face == RIGHT) {
			printf("JUMP_RIGHT_UP\n");
		}
		else {
			printf("JUMP_LEFT_UP\n");
		}
		break;
	case HURT_RIGHT:
	case HURT_LEFT:
		if (face == RIGHT) {
			printf("HURT_RIGHT\n");
		}
		else {
			printf("HURT_LEFT\n");
		}
		break;
	}
}