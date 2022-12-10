#include "changeDimension_state.h"
// TODO: 3번(스테이지 진입키)눌렀을때 이상한경우 있음
namespace ChangeDimension {
	// 매개변수
	GLfloat u = 0;
	GLboolean start = false;		// start ? 2D -> 3D : 3D -> 2D

	GLuint wait = 0;

	Camera changeCamera;
	glm::vec3 newCameraPos;
	glm::vec3 marioPos;
	int changeCType;

	GLvoid enter() {
		std::cout << "enter - changeDimension" << std::endl;
		changeCType = 1 - Play::getcType();
		changeCamera = Play::getCamera();
		marioPos = Play::GetMarioPos();
		u = 0.0;
		if (start) {
			changeCamera.cameraPos = glm::vec3(0.0, 1.5, 15.0);
		}
		else {
			changeCamera.cameraPos = glm::vec3(-15.0, 1.5, 0.0);
		}
		changeCamera.cameraDirection = Play::GetMarioPos();
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
		//wait++;
		//if (wait % 10 == 0) {
		if (start) {
			u -= 3;
			if (u <= -90) {pop_state(); }
		}
		else {
			u += 3;
			if (u >= 90) {pop_state(); }
		}
		//}

		glm::mat4 R = glm::mat4(1.0f);
		glm::mat4 T = glm::mat4(1.0f);
		newCameraPos = changeCamera.cameraPos;

		R = glm::rotate(R, glm::radians(u), glm::vec3(0.0, 1.0, 0.0));
		T = glm::translate(T, glm::vec3(marioPos.x, marioPos.y + 0.5, marioPos.z));
		newCameraPos = T * R * glm::vec4(newCameraPos, 1.0f);

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
			projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 500.0f);
			projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.0));
			unsigned int projectLoc = glGetUniformLocation(Gets_program_texture(), "projection");
			glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
		}

		//unsigned int viewPosLocation = glGetUniformLocation(Gets_program(), "viewPos");
		//glUniform3f(viewPosLocation, camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);

	}
}