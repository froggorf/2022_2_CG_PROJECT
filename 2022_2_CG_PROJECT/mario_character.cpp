#include "mario_character.h"


GLuint mario_max_frame[MARIOSTATEEND];

enum HANDLE_COLLISION {
	X_DOWN, X_UP, Y_DOWN, Y_UP, Z_DOWN, Z_UP
};

GLvoid Mario::Init() {
	trans = glm::vec3(5.0f, 0.0f, 0.0f);
	rot = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	scale = glm::vec3(1.2f, 1.5f, 0.3f);
	speed = MarioSpeed;
	gravity = 0;
	flag_jump = true;
	frame = 0;
	face = RIGHT;
	cur_state = IDLE_RIGHT;
	hp = MarioMaxHp;
	coin_num = 0;
}

GLvoid Mario::update() {
	{
		//PLEASEDELETELATER_PRINTCURSTATEFUNCTION();
	}

	frame += 0.2;
	if (frame >= mario_max_frame[cur_state]) {
		frame = 0;
	}


	if (dir[X] != 0)
		move(X);
	if (dir[Z] != 0)
		move(Z);
	if (dir[X] == 0 && dir[Z] == 0) {
		CheckHittingByEnemy();
		CheckGetItem();
	}
		

	{
		falling_gravity();

	}

	if(Play::getcType()==D2_VIEW)
		StateDo_2D();
}

glm::vec3 mario_vertices[6]{
	glm::vec3(-0.5,0.5,0.5),glm::vec3(-0.5,-0.5,0.5), glm::vec3(0.5,-0.5,0.5),
	glm::vec3(-0.5,0.5,0.5),glm::vec3(0.5,-0.5,0.5),glm::vec3(0.5,0.5,0.5),
};
glm::vec2 mario_texture[6]{
	 glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
	glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),
};

GLvoid Mario::draw(GLuint cType) {
	//boundingBox.draw();

	glm::mat4 TR = glm::mat4(1.0f);

	glm::mat4 T = glm::mat4(1.0f);
	T = glm::translate(T, glm::vec3(trans.x, trans.y, trans.z));

	glm::mat4 S = glm::mat4(1.0f);
	S = glm::scale(S, glm::vec3(scale.x, scale.y, scale.z));

	glm::mat4 rot = glm::mat4(1.0f);
	if(cType == D3_VIEW)
		rot = glm::rotate(rot, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));


	TR = T * rot * S * TR;

	unsigned int modelLocation = glGetUniformLocation(Gets_program_texture(), "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);

	glBindVertexArray(VAO);

	//���� o
	glBindBuffer(GL_ARRAY_BUFFER, VBO[POS]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mario_vertices), mario_vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(3);

	//glBindBuffer(GL_ARRAY_BUFFER, VBO[NORMAL]);	//�븻���Ϳ� ���õ� ���̿��� �ӽ÷� Ȯ���ϱ� ���� ���
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

	int tLocation = glGetUniformLocation(Gets_program_texture(), "outTexture"); //--- outTexture1 ������ ���÷��� ��ġ�� ������


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
	//TODO: IDLE_RIGHT_UP, IDLE_LEFT_UP �� ���� �̹����� ������ �� �ֱ�
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
		trans.x += dir[X] * speed;
		break;
	case Z:
		trans.z += dir[Z] * speed;
		break;

	}
	handle_collision(XYZ, Play::GetGround());
	CheckHittingByEnemy();
	CheckGetItem();

}

GLvoid Mario::CheckGetItem() {
	std::vector<Item*> items = Play::GetItem();
	switch (Play::getcType()) {
	case D2_VIEW:
		for (int i = 0; i < items.size(); ++i) {
			if (CheckAABB_2D(*this, *items[i])) {
				Item* check_mushroom = dynamic_cast<Mushroom*>(items[i]);
				if (check_mushroom != nullptr) {
					items[i]->collision_handling(this);
					hp += 10;
					if (hp >= MarioMaxHp) {
						hp = MarioMaxHp;
					}
				}

				Item* check_coin = dynamic_cast<Coin*>(items[i]);
				if (check_coin != nullptr) {
					items[i]->collision_handling(this);
					coin_num += 1;
				}
			}
		}
		break;
	case D3_VIEW:
		for (int i = 0; i < items.size(); ++i) {
			if (CheckAABB(*this, *items[i])) {
				Item* check_mushroom = dynamic_cast<Mushroom*>(items[i]);
				if (check_mushroom != nullptr) {
					items[i]->collision_handling(this);
					hp += 10;
					if (hp >= MarioMaxHp) {
						hp = MarioMaxHp;
					}
				}

				Item* check_coin = dynamic_cast<Coin*>(items[i]);
				if (check_coin != nullptr) {
					items[i]->collision_handling(this);
					coin_num += 1;
				}
			}
		}
		break;
	}
	

}

GLvoid Mario::falling_gravity() {
	gravity -= GravityAcceleration;
	trans.y += gravity;
	std::vector<Cube*> g_ground = Play::GetGround();
	//�߷¿� ���� �浹üũ ó��
	if (Play::getcType() == D3_VIEW) {
		for (int i = 0; i < g_ground.size(); ++i) {
			if (CheckAABB(*this, *g_ground[i])) {
				
					


				if (gravity > 0) {	//���� �������϶�
					Cube* check_brick = dynamic_cast<Brick*>(g_ground[i]);
					if (check_brick != nullptr) {
						std::cout << "���� �浹" << std::endl;
						g_ground[i]->collision_handling(this);
					}
					Cube* check_mysteryBox = dynamic_cast<MysteryBlock*>(g_ground[i]);
					if (check_mysteryBox != nullptr) {
						std::cout << "�̽��׸��ڽ� �浹" << std::endl;
						g_ground[i]->collision_handling(this);
					}

					trans.y = g_ground[i]->trans.y - 0.5 * g_ground[i]->scale.y - 0.5 * scale.y - FLOAT_ERROR_FIGURE;
					gravity = 0;
				}
				else {	//������ �߷� �������ϋ�
					trans.y = g_ground[i]->trans.y + 0.5 * g_ground[i]->scale.y + 0.5 * scale.y + FLOAT_ERROR_FIGURE;
					gravity = 0;
					flag_jump = true;
					if (cur_state == JUMP_RIGHT || cur_state == JUMP_RIGHT_UP) {	
						StateExit_3D();
						StateEnter_3D();
					}
				}
			}
		}
	}
	else {
		for (int i = 0; i < g_ground.size(); ++i) {
			if (CheckAABB_2D(*this, *g_ground[i])) {
				Cube* check_wall = dynamic_cast<Wall*>(g_ground[i]);
				if ( check_wall != nullptr) {
					continue;
				}
				check_wall = dynamic_cast<Door*>(g_ground[i]);
				if (check_wall != nullptr) {
					continue;
				}
					
				if (gravity > 0) {	//���� �������϶�
					Cube* check_brick = dynamic_cast<Brick*>(g_ground[i]);
					if (check_brick != nullptr) {
						std::cout << "���� �浹" << std::endl;
						g_ground[i]->collision_handling(this);
					}
					Cube* check_mysteryBox = dynamic_cast<MysteryBlock*>(g_ground[i]);
					if (check_mysteryBox != nullptr) {
						std::cout << "�̽��׸��ڽ� �浹" << std::endl;
						g_ground[i]->collision_handling(this);
					}

					trans.y = g_ground[i]->trans.y - 0.5 * g_ground[i]->scale.y - 0.5 * scale.y - FLOAT_ERROR_FIGURE;
					gravity = 0;
				}
				else {	//������ �߷� �������ϋ�
					trans.y = g_ground[i]->trans.y + 0.5 * g_ground[i]->scale.y + 0.5 * scale.y + FLOAT_ERROR_FIGURE;
					gravity = 0;
					flag_jump = true;
					if (cur_state == JUMP_RIGHT || cur_state == JUMP_RIGHT_UP) {
						
						StateExit_2D();
						StateEnter_2D();
					
					}
				}
			}
		}
	}
	if (Play::getcType() == D2_VIEW) {
		CheckKillingEnemy();
	}
}

GLvoid Mario::CheckKillingEnemy() {
	if (cur_state == HURT_RIGHT) return;
	std::vector<Enemy*> enemies = Play::GetEnemy();
	for (int i = 0; i < enemies.size(); ++i) {
		if (CheckAABB_2D(*this, *enemies[i])) {
			enemies[i]->collision_handling(this);
			gravity = GravityAcceleration * JumpPower;
			trans.y = enemies[i]->trans.y + 0.5 * enemies[i]->scale.y + 0.5 * scale.y + FLOAT_ERROR_FIGURE;
		}
	}
}

GLvoid Mario::DoJump() {
	if (flag_jump&& gravity >=-GravityAcceleration*2) {
		//TODO: ���� ���̿����� �� �����ϱ�
		gravity = GravityAcceleration * JumpPower;
		flag_jump = false;
	}
}

GLvoid Mario::handle_collision(int XYZ, std::vector<Cube*> map) {
	if (Play::getcType() == D3_VIEW) {
		for (int i = 0; i < map.size(); ++i) {
			if (CheckAABB(*this, *map[i])) {
				switch (XYZ) {
				case X:
					if (dir[X] >= 1) {
						trans.x = map[i]->trans.x - 0.5 * map[i]->scale.x - 0.5 * scale.x - FLOAT_ERROR_FIGURE;
					}
					else if (dir[X] <= -1) {
						trans.x = map[i]->trans.x + 0.5 * map[i]->scale.x + 0.5 * scale.x + FLOAT_ERROR_FIGURE;
					}
					break;
				case Z:
					if (dir[Z] >= 1) {
						trans.z = map[i]->trans.z - 0.5 * map[i]->scale.z - 0.5 * scale.z - FLOAT_ERROR_FIGURE;
					}
					else if (dir[Z] <= -1) {
						trans.z = map[i]->trans.z + 0.5 * map[i]->scale.z + 0.5 * scale.z + FLOAT_ERROR_FIGURE;
					}
					break;
				}

			}
			

		}
	}
	else {
		for (int i = 0; i < map.size(); ++i) {
			if (CheckAABB_2D(*this, *map[i])) {
				Cube* check_wall = dynamic_cast<Wall*>(map[i]);
				if (check_wall != nullptr) {
					continue;
				}
				check_wall = dynamic_cast<Door*>(map[i]);
				if (check_wall != nullptr) {
					continue;
				}

				if (dir[X] >= 1) {
					trans.x = map[i]->trans.x - 0.5 * map[i]->scale.x - 0.5 * scale.x - FLOAT_ERROR_FIGURE;
				}
				else if (dir[X] <= -1) {
					trans.x = map[i]->trans.x + 0.5 * map[i]->scale.x + 0.5 * scale.x + FLOAT_ERROR_FIGURE;
				}
			}
		}
	}
}

GLvoid Mario::CheckHittingByEnemy() {
	if (cur_state == HURT_RIGHT) return;
	std::vector<Enemy*> enemies = Play::GetEnemy();
	if (Play::getcType() == D2_VIEW) {
		for (int i = 0; i < enemies.size(); ++i) {
			if (CheckAABB_2D(*this, *enemies[i])) {
				hp -= 1;
				StateExit_2D();
				MarioChangeState(HURT_RIGHT);
				StateEnter_2D();
			}
		}
	}
}

GLvoid Mario::MarioChangeState(int next_state) {
	if (cur_state == next_state) return;
	cur_state = next_state;
	frame = 0;
}

//���̽㶧 class ���� enter �ڵ�
GLvoid Mario::StateEnter_3D(int type, unsigned char key) {
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

GLvoid Mario::StateEnter_2D(int type, unsigned char key) {
	switch (cur_state) {
	case IDLE_RIGHT:
	case IDLE_LEFT:
		dir[X] = 0;
		dir[Z] = 0;
		break;
	case IDLE_RIGHT_UP:
	case IDLE_LEFT_UP:
		break;
	case WALKING_RIGHT:
	case WALKING_LEFT:
		switch (type) {
		case GLUT_KEY_DOWN:
			switch (key) {
			case 'a':
				face = LEFT;
				dir[X] -= 1;
				if (dir[X] < -1) dir[X] = -1;
				break;
			case 'd':
				face = RIGHT;
				dir[X] += 1;
				if (dir[X] > 1) dir[X] = 1;
				break;
			}
			break;
		case GLUT_KEY_UP:
			switch (key) {
			case 'a':
				
				face = RIGHT;
				
				dir[X] += 1;
				if (dir[X] > 1) dir[X] = 1;
				break;
			case 'd':
				
				face = LEFT;
				
				dir[X] -= 1;
				if (dir[X] < -1) dir[X] = -1;

				break;
			}
			break;
		}
		break;
	case WALKING_RIGHT_UP:
	case WALKING_LEFT_UP:
		break;
	case JUMP_RIGHT:
	case JUMP_LEFT:
		DoJump();
		switch (type) {
		case GLUT_KEY_DOWN:
			switch (key) {
			case 'a':
				face = LEFT;


				dir[X] -= 1;
				if (dir[X] < -1) dir[X] = -1;
				break;
			case 'd':
				face = RIGHT;
				dir[X] += 1;
				if (dir[X] > 1) dir[X] = 1;
				break;
			}
			break;
		case GLUT_KEY_UP:
			switch (key) {
			case 'a':
				
				//face = RIGHT;
				
				dir[X] += 1;
				if (dir[X] > 1) dir[X] = 1;
				break;
			case 'd':
				
				//face = LEFT;
				
				dir[X] -= 1;
				if (dir[X] < -1) dir[X] = -1;

				break;
			}
			break;
		}
		break;
	case JUMP_RIGHT_UP:
	case JUMP_LEFT_UP:
		break;
	case HURT_RIGHT:
	case HURT_LEFT:
		if (face == RIGHT) {
			dir[X] = -1;
		}
		else {
			dir[X] = 1;
		}
		dir[Z] = 0;
		hurt_time = HURT_TIME;
		gravity = GravityAcceleration * 15;
		break;
	}
}

//���̽㶧 class ���� exit �ڵ�
GLvoid Mario::StateExit_3D(int type, unsigned char key) {
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
			MarioChangeState(WALKING_RIGHT);
			StateEnter_3D(GLUT_KEY_DOWN, 'd');
		}
		else if ((GetKeyDown()[pressA] && !GetKeyDown()[pressD])) {
			MarioChangeState(WALKING_RIGHT);
			StateEnter_3D(GLUT_KEY_DOWN, 'a');
		}
		else if (GetKeyDown()[pressS]) {
			MarioChangeState(WALKING_RIGHT);
			StateEnter_3D(GLUT_KEY_DOWN, 's');
		}
		else {
			MarioChangeState(IDLE_RIGHT_UP);
		}
		break;
	case JUMP_RIGHT_UP:
	case JUMP_LEFT_UP:
		if ((GetKeyDown()[pressD] && !GetKeyDown()[pressA])) {
			MarioChangeState(WALKING_RIGHT_UP);
			StateEnter_3D(GLUT_KEY_DOWN, 'd');
		}
		else if ((GetKeyDown()[pressA] && !GetKeyDown()[pressD])) {
			MarioChangeState(WALKING_RIGHT_UP);
			StateEnter_3D(GLUT_KEY_DOWN, 'a');
		}
		else if (GetKeyDown()[pressW]) {
			MarioChangeState(WALKING_RIGHT_UP);
			StateEnter_3D(GLUT_KEY_DOWN, 'w');
		}
		else {
			MarioChangeState(IDLE_RIGHT_UP);
		}
		break;
	case HURT_RIGHT:
	case HURT_LEFT:
		break;
	}
}
GLvoid Mario::StateExit_2D(int type, unsigned char key) {
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
		//���� ������ ������ �ִ� Ű������ ó�� �����ϱ�
		if ((!GetKeyDown()[pressA] && GetKeyDown()[pressD])){
			MarioChangeState(WALKING_RIGHT);
			StateEnter_2D(GLUT_KEY_DOWN,'d');
			break;
		}
		else if (GetKeyDown()[pressA] && !GetKeyDown()[pressD]) {
			MarioChangeState(WALKING_RIGHT);
			StateEnter_2D(GLUT_KEY_DOWN,'a');
			break;
		}
		else {
			MarioChangeState(IDLE_RIGHT);
			StateEnter_2D();
		}
		
		break;
	case JUMP_RIGHT_UP:
	case JUMP_LEFT_UP:
		break;
	case HURT_RIGHT:
	case HURT_LEFT:
		break;
	}
}

//���̽㶧 class ���� do �ڵ� //TODO: �ʿ信 ���� 2d���� �ٸ��� do �ϵ��� �ֱ�
GLvoid Mario::StateDo_2D() {
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
		std::cout << hurt_time;
		hurt_time -= 16;
		
		if (hurt_time <= 0) {
			hurt_time = 0;
			StateExit_2D();
			MarioChangeState(IDLE_RIGHT);
			StateEnter_2D();
		}
		break;
	}
}

GLvoid Mario::handle_events(int type, unsigned char key) {
	switch (Play::getcType()) {
	case D3_VIEW:
		CheckNextState_3D(type, key);
		break;
	case D2_VIEW:
		CheckNextState_2D(type, key);
		break;
	}

	//CheckNextState_3D(type, key);
	
}

//���̽� next_state ������ ����� ���� �ϴ� �Լ�
GLvoid Mario::CheckNextState_3D(int type, unsigned char key) {
	switch (cur_state) {
	case IDLE_RIGHT:
	case IDLE_LEFT:
		switch (type) {
		case GLUT_KEY_DOWN:
			switch (key) {
			case 'w':
				if (GetKeyDown()[pressW] && GetKeyDown()[pressS]) break;
				StateExit_3D(type, key);
				MarioChangeState(WALKING_RIGHT_UP);
				StateEnter_3D(type, key);
				break;
			case 's':
				if (GetKeyDown()[pressW] && GetKeyDown()[pressS]) break;
				StateExit_3D(type, key);
				MarioChangeState(WALKING_RIGHT);
				StateEnter_3D(type, key);
				break;
			case 'a':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				StateExit_3D(type, key);
				MarioChangeState(WALKING_RIGHT);
				StateEnter_3D(type, key);
				break;
			case 'd':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				StateExit_3D(type, key);
				MarioChangeState(WALKING_RIGHT);
				StateEnter_3D(type, key);
				break;
			case ' ':
				StateExit_3D(type, key);
				MarioChangeState(JUMP_RIGHT);
				StateEnter_3D(type, key);
				break;
			}
			break;
		case GLUT_KEY_UP:
			switch (key) {
			case 'w':
				if (GetKeyDown()[pressS]) {
					StateExit_3D(type, key);
					MarioChangeState(WALKING_RIGHT);
					StateEnter_3D(type, key);
				}
				break;
			case 's':
				if (GetKeyDown()[pressW]) {
					StateExit_3D(type, key);
					MarioChangeState(WALKING_RIGHT);
					StateEnter_3D(type, key);
				}
				break;
			case 'a':
				if (GetKeyDown()[pressD]) {
					StateExit_3D(type, key);
					MarioChangeState(WALKING_RIGHT);
					StateEnter_3D(type, key);
				}
				break;
			case 'd':
				if (GetKeyDown()[pressA]) {
					StateExit_3D(type, key);
					MarioChangeState(WALKING_RIGHT);
					StateEnter_3D(type, key);
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
				StateExit_3D(type, key);
				MarioChangeState(WALKING_RIGHT_UP);
				StateEnter_3D(type, key);
				break;
			case 's':
				if (GetKeyDown()[pressW] && GetKeyDown()[pressS]) break;
				StateExit_3D(type, key);
				MarioChangeState(WALKING_RIGHT);
				StateEnter_3D(type, key);
				break;
			case 'a':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				StateExit_3D(type, key);
				MarioChangeState(WALKING_RIGHT_UP);
				StateEnter_3D(type, key);
				break;
			case 'd':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				StateExit_3D(type, key);
				MarioChangeState(WALKING_RIGHT_UP);
				StateEnter_3D(type, key);
				break;
			case ' ':
				StateExit_3D(type, key);
				MarioChangeState(JUMP_RIGHT_UP);
				StateEnter_3D(type, key);
				break;
			}
			break;
		case GLUT_KEY_UP:
			switch (key) {
			case 'w':
				if (GetKeyDown()[pressS]) {
					StateExit_3D(type, key);
					MarioChangeState(WALKING_RIGHT);
					StateEnter_3D(type, key);
				}
				break;
			case 's':
				if (GetKeyDown()[pressW]) {
					StateExit_3D(type, key);
					MarioChangeState(WALKING_RIGHT_UP);
					StateEnter_3D(type, key);
				}
				break;
			case 'a':
				if (GetKeyDown()[pressD]) {
					StateExit_3D(type, key);
					MarioChangeState(WALKING_RIGHT_UP);
					StateEnter_3D(type, key);
				}
				break;
			case 'd':
				if (GetKeyDown()[pressA]) {
					StateExit_3D(type, key);
					MarioChangeState(WALKING_RIGHT_UP);
					StateEnter_3D(type, key);
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
				if (!GetKeyDown()[pressA] && !GetKeyDown()[pressD]) {	//A�� D�� ������ �ʰ� S�θ� ������ ������ ���� ��Ȳ�� ���� w ������ ���̵� �ǰ�
					StateExit_3D(type, key);
					MarioChangeState(IDLE_RIGHT);
					StateEnter_3D(type, key);
				}
				else {
					StateExit_3D(type, key);
					MarioChangeState(WALKING_RIGHT_UP);
					StateEnter_3D(type, key);
				}
				break;
			case 's':
				if (GetKeyDown()[pressW] && GetKeyDown()[pressS]) break;
				StateExit_3D(type, key);
				MarioChangeState(WALKING_RIGHT);
				StateEnter_3D(type, key);
				break;
			case 'a':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				if (GetKeyDown()[pressS]) {	//s�� ������ ������ ���� ��Ȳ
					StateExit_3D(type, key);
					MarioChangeState(WALKING_RIGHT);
					StateEnter_3D(type, key);
					break;
				}
				if (GetKeyDown()[pressD]) {	//s�� �ȴ��� ä�� �����ʸ� ���� ����
					StateExit_3D(type, key);
					MarioChangeState(IDLE_RIGHT);
					StateEnter_3D(type, key);
				}
				break;
			case 'd':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				if (GetKeyDown()[pressS]) {	//s�� ������ ������ ���� ��Ȳ
					StateExit_3D(type, key);
					MarioChangeState(WALKING_RIGHT);
					StateEnter_3D(type, key);
					break;
				}
				if (GetKeyDown()[pressA]) {	//s�� �ȴ��� ä�� ���ʸ� ���� ����
					StateExit_3D(type, key);
					MarioChangeState(IDLE_RIGHT);
					StateEnter_3D(type, key);
				}
				break;
			case ' ':
				StateExit_3D(type, key);
				MarioChangeState(JUMP_RIGHT);
				StateEnter_3D(type, key);
				break;
			}
			break;
		case GLUT_KEY_UP:
			switch (key) {
			case 'w':
				if (GetKeyDown()[pressS]) {
					StateExit_3D(type, key);
					MarioChangeState(WALKING_RIGHT);
					StateEnter_3D(type, key);
				}
				break;
			case 's':
				if ((!GetKeyDown()[pressA] and GetKeyDown()[pressD]) or (GetKeyDown()[pressD] and !GetKeyDown()[pressD])) {
					StateExit_3D(type, key);
					MarioChangeState(WALKING_RIGHT);
					StateEnter_3D(type, key);
				}
				else {
					StateExit_3D(type, key);
					MarioChangeState(IDLE_RIGHT);
					StateEnter_3D(type, key);
				}
				break;
			case 'a':

				if (GetKeyDown()[pressS]) {
					StateExit_3D(type, key);
					MarioChangeState(WALKING_RIGHT);
					StateEnter_3D(type, key);
				}
				else {
					StateExit_3D(type, key);
					MarioChangeState(IDLE_RIGHT);
					StateEnter_3D(type, key);
				}
				
				break;
			case 'd':
				if (GetKeyDown()[pressS]) {
					StateExit_3D(type, key);
					MarioChangeState(WALKING_RIGHT);
					StateEnter_3D(type, key);
				}
				else {
					StateExit_3D(type, key);
					MarioChangeState(IDLE_RIGHT);
					StateEnter_3D(type, key);
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
				StateExit_3D(type, key);
				MarioChangeState(WALKING_RIGHT_UP);
				StateEnter_3D(type, key);
				break;
			case 's':
				if (GetKeyDown()[pressW] && GetKeyDown()[pressS]) break;
				if (!GetKeyDown()[pressA]&&!GetKeyDown()[pressD]) {
					StateExit_3D(type, key);
					MarioChangeState(IDLE_RIGHT);
					StateEnter_3D(type, key);
					break;
				}
				StateExit_3D(type, key);
				MarioChangeState(WALKING_RIGHT);
				StateEnter_3D(type, key);
				break;
			case 'a':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				if (GetKeyDown()[pressW]) {
					StateExit_3D(type, key);
					MarioChangeState(WALKING_RIGHT_UP);	//�״�� ���� �ϰ� z�� �̵� ����
					StateEnter_3D(type, key);
					break;
				}
				if (GetKeyDown()[pressD]) {
					StateExit_3D(type, key);
					MarioChangeState(IDLE_RIGHT_UP);	//�״�� ���� �ϰ� z�� �̵� ����
					StateEnter_3D(type, key);
					break;
				}
				StateExit_3D(type, key);
				MarioChangeState(WALKING_RIGHT_UP);	//�״�� ���� �ϰ� z�� �̵� ����
				StateEnter_3D(type, key);
				break;
			case 'd':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				if (GetKeyDown()[pressW]) {
					StateExit_3D(type, key);
					MarioChangeState(WALKING_RIGHT_UP);	//�״�� ���� �ϰ� z�� �̵� ����
					StateEnter_3D(type, key);
					break;
				}
				if (GetKeyDown()[pressA]) {
					StateExit_3D(type, key);
					MarioChangeState(IDLE_RIGHT_UP);	//�״�� ���� �ϰ� z�� �̵� ����
					StateEnter_3D(type, key);
					break;
				}
				StateExit_3D(type, key);
				MarioChangeState(WALKING_RIGHT_UP);	//�״�� ���� �ϰ� z�� �̵� ����
				StateEnter_3D(type, key);
				break;
			case ' ':
				StateExit_3D(type, key);
				MarioChangeState(JUMP_RIGHT_UP);
				StateEnter_3D(type, key);
				break;
			}
			break;
		case GLUT_KEY_UP:
			switch (key) {
			case 'w':
				if (!GetKeyDown()[pressA] && !GetKeyDown()[pressD]) {
					StateExit_3D(type, key);
					MarioChangeState(IDLE_RIGHT_UP);
					StateEnter_3D(type, key);
					break;
				}
				StateExit_3D(type, key);
				MarioChangeState(WALKING_RIGHT_UP);
				StateEnter_3D(type, key);
				break;
			case 'a':
				if (GetKeyDown()[pressW]) {
					StateExit_3D(type, key);
					MarioChangeState(WALKING_RIGHT_UP);
					StateEnter_3D(type, key);
					break;
				}
				else {
					StateExit_3D(type, key);
					MarioChangeState(IDLE_RIGHT_UP);
					StateEnter_3D(type, key);
					break;
				}
				
				break;
			case 'd':
				if (GetKeyDown()[pressW]) {
					StateExit_3D(type, key);
					MarioChangeState(WALKING_RIGHT_UP);
					StateEnter_3D(type, key);
					break;
				}
				else {
					StateExit_3D(type, key);
					MarioChangeState(IDLE_RIGHT_UP);
					StateEnter_3D(type, key);
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
				StateExit_3D(type, key);
				MarioChangeState(JUMP_RIGHT_UP);
				StateEnter_3D(type, key);
				break;
			case 's':
				if (GetKeyDown()[pressW] && GetKeyDown()[pressS]) break;
				StateExit_3D(type, key);
				MarioChangeState(JUMP_RIGHT);
				StateEnter_3D(type, key);
				break;
			case 'a':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				StateExit_3D(type, key);
				MarioChangeState(JUMP_RIGHT);
				StateEnter_3D(type, key);
				break;
			case 'd':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				StateExit_3D(type, key);
				MarioChangeState(JUMP_RIGHT);
				StateEnter_3D(type, key);
				break;
					
			}
			break;
		case GLUT_KEY_UP:
			switch (key) {
			case 'w':
				StateExit_3D(type, key);
				MarioChangeState(JUMP_RIGHT_UP);
				StateEnter_3D(type, key);
				break;
			case 's':
				StateExit_3D(type, key);
				MarioChangeState(JUMP_RIGHT_UP);
				StateEnter_3D(type, key);
				break;
			case 'a':
				StateExit_3D(type, key);
				MarioChangeState(JUMP_RIGHT);
				StateEnter_3D(type, key);
				break;
			case 'd':
				StateExit_3D(type, key);
				MarioChangeState(JUMP_RIGHT);
				StateEnter_3D(type, key);
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
				StateExit_3D(type, key);
				MarioChangeState(JUMP_RIGHT_UP);
				StateEnter_3D(type, key);
				break;
			case 's':
				if (GetKeyDown()[pressW] && GetKeyDown()[pressS]) break;
				StateExit_3D(type, key);
				MarioChangeState(JUMP_RIGHT);
				StateEnter_3D(type, key);
				break;
			case 'a':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				StateExit_3D(type, key);
				MarioChangeState(JUMP_RIGHT_UP);
				StateEnter_3D(type, key);
				break;
			case 'd':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				StateExit_3D(type, key);
				MarioChangeState(JUMP_RIGHT_UP);
				StateEnter_3D(type, key);
				break;
			}
			break;
		case GLUT_KEY_UP:
			switch (key) {
			case 'w':
				StateExit_3D(type, key);
				MarioChangeState(JUMP_RIGHT_UP);
				StateEnter_3D(type, key);
				break;
			case 's':
				StateExit_3D(type, key);
				MarioChangeState(JUMP_RIGHT);
				StateEnter_3D(type, key);
				break;
			case 'a':
				StateExit_3D(type, key);
				MarioChangeState(JUMP_RIGHT_UP);
				StateEnter_3D(type, key);
				break;
			case 'd':
				StateExit_3D(type, key);
				MarioChangeState(JUMP_RIGHT_UP);
				StateEnter_3D(type, key);
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
GLvoid Mario::CheckNextState_2D(int type, unsigned char key) {
	switch (cur_state) {
	case IDLE_RIGHT:
	case IDLE_LEFT:
		switch (type) {
		case GLUT_KEY_DOWN:
			switch (key) {
			case 'a':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				StateExit_2D(type, key);
				MarioChangeState(WALKING_RIGHT);
				StateEnter_2D(type, key);
				break;
			case 'd':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				StateExit_2D(type, key);
				MarioChangeState(WALKING_RIGHT);
				StateEnter_2D(type, key);
				break;
			case ' ':
				StateExit_2D(type, key);
				MarioChangeState(JUMP_RIGHT);
				StateEnter_2D(type, key);
				break;
			}
			break;
		case GLUT_KEY_UP:
			switch (key) {
			case 'a':
				StateExit_2D(type, key);
				MarioChangeState(WALKING_RIGHT);
				StateEnter_2D(type, key);
				break;
			case 'd':
				StateExit_2D(type, key);
				MarioChangeState(WALKING_RIGHT);
				StateEnter_2D(type, key);
				break;
			}
			break;
		}
		break;


	case IDLE_RIGHT_UP:
	case IDLE_LEFT_UP:
		break;
	case WALKING_RIGHT:
	case WALKING_LEFT:
		switch (type) {
		case GLUT_KEY_DOWN:
			switch (key) {
			case 'a':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				if (GetKeyDown()[pressD]) {
					StateExit_2D(type, key);
					MarioChangeState(IDLE_RIGHT);
					StateEnter_2D(type, key);
				}
				break;
			case 'd':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				if (GetKeyDown()[pressA]) {
					StateExit_2D(type, key);
					MarioChangeState(IDLE_RIGHT);
					StateEnter_2D(type, key);
				}
				break;
			case ' ':
				StateExit_2D(type, key);
				MarioChangeState(JUMP_RIGHT);
				StateEnter_2D(type, key);
				break;
			}
			break;
		case GLUT_KEY_UP:
			switch (key) {
			case 'a':
				StateExit_2D(type, key);
				MarioChangeState(IDLE_RIGHT);
				StateEnter_2D(type, key);
				break;
			case 'd':
				StateExit_2D(type, key);
				MarioChangeState(IDLE_RIGHT);
				StateEnter_2D(type, key);
				break;
			}
			break;
		}
		break;
	case WALKING_RIGHT_UP:
	case WALKING_LEFT_UP:
		break;
	case JUMP_RIGHT:
	case JUMP_LEFT:
		switch (type) {
		case GLUT_KEY_DOWN:
			switch (key) {
			case 'a':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				StateExit_2D(type, key);
				MarioChangeState(JUMP_RIGHT);
				StateEnter_2D(type, key);
				break;
			case 'd':
				if (GetKeyDown()[pressA] && GetKeyDown()[pressD]) break;
				StateExit_2D(type, key);
				MarioChangeState(JUMP_RIGHT);
				StateEnter_2D(type, key);
				break;

			}
			break;
		case GLUT_KEY_UP:
			switch (key) {
			case 'a':
				StateExit_2D(type, key);
				MarioChangeState(JUMP_RIGHT);
				StateEnter_2D(type, key);
				break;
			case 'd':
				StateExit_2D(type, key);
				MarioChangeState(JUMP_RIGHT);
				StateEnter_2D(type, key);
				break;
			}
			break;
		}
		break;
	case JUMP_RIGHT_UP:
	case JUMP_LEFT_UP:
		break;
	case HURT_RIGHT:
	case HURT_LEFT:
		break;
	}
}

//TODO: ���߿� �� �������ϴ� �Լ� ���� ���¿� ���� ������ִ� �Լ���
GLvoid Mario::PLEASEDELETELATER_PRINTCURSTATEFUNCTION() {
	//TODO: ���߿� ���� �ڵ�(������ ���� ���� ��� �ڵ�)
	printf("������ ����: ");
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