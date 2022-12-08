#include "changeDimension_state.h"

namespace ChangeDimension {
	// 매개변수
	GLfloat u = 0;
	GLboolean start = false;

	Camera changeCamera;
	glm::vec3 newCameraPos;
	int changeCType;

	GLvoid enter() {
		std::cout << "enter - changeDimension" << std::endl;
		changeCamera = Play::getCamera();
		changeCamera.cameraDirection = Play::GetMarioPos();
		changeCType = 1 - Play::getcType();
		std::cout << (start?"True":"False") << std::endl;
	}

	GLvoid exit() {
		std::cout << "exit - changeDimension" << std::endl;
		start = 1 - start;
	}

	GLvoid pause() {
		std::cout << "pause - changeDimension" << std::endl;
	}

	GLvoid resume() {
		std::cout << "resume - changeDimension" << std::endl;
	}

	GLvoid handle_events() {

	}

	GLvoid update() {
		if (start) {
			u -= 3;
			if (u <= 0) pop_state();
		}
		else {
			u += 3;
			if (u >= 90) pop_state();
		}

		glm::mat4 R = glm::mat4(1.0f);
		newCameraPos = changeCamera.cameraPos;

		R = glm::rotate(R, glm::radians(u), glm::vec3(0.0, 1.0, 0.0));
		newCameraPos = R * glm::vec4(newCameraPos, 1.0f);

		std::cout << u << std::endl;
	}

	GLvoid draw() {
		SetTransformationMatrix();
		Play::drawObject();
	}
	GLvoid key_down(unsigned char key, int x, int y) {

	}

	GLvoid key_up(unsigned char key, int x, int y) {

	}
	
	GLvoid InitBuffer() {

	}

	GLvoid InitValue() {}

	GLvoid SetTransformationMatrix() {
		{//model 변환
			glm::mat4 TR = glm::mat4(1.0f);
			unsigned int modelLocation = glGetUniformLocation(Gets_program_texture(), "model");
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
		}

		{//카메라 변환
			glm::mat4 view = glm::mat4(1.0f);
			view = glm::lookAt(newCameraPos, changeCamera.cameraDirection, changeCamera.cameraUp);
			unsigned int viewLocation = glGetUniformLocation(Gets_program_texture(), "view");
			glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
		}

		{//투영 변환
			glm::mat4 projection = glm::mat4(1.0f);
			if (changeCType == D3_VIEW) {      //3D 뷰
				projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 500.0f);
				projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.0));
				//projection = glm::perspective(glm::radians(45.0f), GLfloat(WIDTH)/HEIGHT, 0.1f, (GLfloat)CameraViewSize);
				//projection = glm::translate(projection, glm::vec3(0.0, 0.0, -3.0));
			}
			else {                  //2D 뷰
				projection = glm::ortho(-CameraViewSize / 20, CameraViewSize / 20, -CameraViewSize / 20, CameraViewSize / 20, 0.1f, CameraViewSize);
			}
			unsigned int projectLoc = glGetUniformLocation(Gets_program_texture(), "projection");
			glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
		}

		//unsigned int viewPosLocation = glGetUniformLocation(Gets_program(), "viewPos");
		//glUniform3f(viewPosLocation, camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);

	}
}