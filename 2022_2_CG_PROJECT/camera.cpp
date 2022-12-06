#include "camera.h"

GLvoid Camera::update(glm::vec3 marioPos) {
	switch (cType) {
	case D3_VIEW:
		cameraPos = marioPos;
		cameraPos.y += 10.0f;
		cameraPos.z += 30.0f;
		break;
	case D2_VIEW:
		break;
	}

}