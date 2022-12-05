#include "mario_character.h"

enum HANDLE_COLLISION {
	X_DOWN,X_UP,Y_DOWN,Y_UP,Z_DOWN,Z_UP
};

GLvoid Mario::init() {
	boundingBox.init();
	speed = MarioSpeed;
	gravity = 0;
	flag_jump = true;
}

GLvoid Mario::update() {
	for (int i = 0; i < KeyBoard::KEYEND; ++i) {
		if (GetKeyDown()[i]) {
			handle_events(i);
		}
	}

	{//중력 처리 -> 함수로 변경 예정
		falling_gravity();
		//중력에 대한 충돌체크 처리
		for (int i = 0; i < Play::GetGround().size(); ++i) {
			if (CheckAABB(boundingBox, *Play::GetGround()[i])) {
				boundingBox.trans.y = Play::GetGround()[i]->trans.y + 0.5 * Play::GetGround()[i]->scale.y + 0.5 * boundingBox.scale.y;
				gravity = 0;
				flag_jump = true;
			}
		}
	}
	

}

GLvoid Mario::draw() {
	boundingBox.draw();
}

GLvoid Mario::InitBuffer() {
	boundingBox.InitBuffer();
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
GLvoid Mario::handle_collision(int events, std::vector<Cube*>& ground) {
	for (int i = 0; i < ground.size(); ++i) {
		if (CheckAABB(boundingBox, *ground[i])) {
			switch (events) {
			case pressW:
				printf("z다운중\n");
				boundingBox.trans.z = ground[i]->trans.z + 0.5 * ground[i]->scale.z + 0.5 * boundingBox.scale.z;
				break;
			case pressS:
				printf("z업중\n");
				boundingBox.trans.z = ground[i]->trans.z - 0.5 * ground[i]->scale.z - 0.5 * boundingBox.scale.z;
				break;
			case pressA:
				printf("x다운중\n");
				boundingBox.trans.x = ground[i]->trans.x + 0.5 * ground[i]->scale.x + 0.5 * boundingBox.scale.x;
				break;
			case pressD:
				printf("x업중\n");
				boundingBox.trans.x = ground[i]->trans.x - 0.5 * ground[i]->scale.x - 0.5 * boundingBox.scale.x;
				
				break;
			}
		}
	}
}