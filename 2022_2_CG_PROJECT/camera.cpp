#include "camera.h"

GLvoid Camera::update(glm::vec3 marioPos, GLuint cType) {
	switch (cType) {
	case D3_VIEW:
		cameraPos.x = marioPos.x-5.0f;
		cameraPos.y = marioPos.y+ 1.5f;
		cameraPos.z = marioPos.z;
		break;
	case D2_VIEW:
		cameraPos.x = marioPos.x;
		cameraPos.y = marioPos.y + 1.5f;
		cameraPos.z = marioPos.z + 15.0f;
		break;
	}

}