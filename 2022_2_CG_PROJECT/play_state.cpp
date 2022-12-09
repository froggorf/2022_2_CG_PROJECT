#include "play_state.h"
#include "fileManager.h"

namespace Play {
	//ī�޶� ���� ����
	Camera camera;
	int cType;                              //ī�޶� Ÿ��(2d�� / 3d��)


	//��
	std::vector<Cube*> map;      //cube* ���� cube�� �ٲ����� ����Ǵ��� Ȯ���ϱ�

	//TODO: �� ���� �ڵ� �ٸ������οű�°� �̻�����
	std::vector<Enemy*> enemyVec;


	//������
	Mario mario;

	//function - ����
	GLvoid enter() {
		InitValue();
		InitBuffer();
	}

	GLvoid exit() {
		std::cout << "exit - play" << std::endl;
		map.clear();

		//DelBuffer();
		//DelValue();
	}

	GLvoid pause() {
		std::cout << "pause - play" << std::endl;
	}

	GLvoid resume() {
		std::cout << "resume - play" << std::endl;
		cType = 1 - cType;
		if (cType == D3_VIEW) {
			camera.cameraPos = GetMarioPos();
			camera.cameraDirection = glm::vec3(1.0f, 0.0f, 0.0f);
			camera.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		}
		else {
			camera.cameraPos = GetMarioPos();
			camera.cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
			camera.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
		}
	}

	GLvoid handle_events() {

	}

	GLvoid update() {
		mario.update();
		camera.update(GetMarioPos(), cType);
		if (GetKeyDown()[press5]) {
			glm::mat4 rot = glm::mat4(1.0f);
			rot = glm::rotate(rot, glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			camera.cameraPos = rot * glm::vec4(camera.cameraPos, 1.0f);
			camera.cameraDirection = rot * glm::vec4(camera.cameraDirection, 1.0f);
			camera.cameraUp = rot * glm::vec4(camera.cameraUp, 1.0f);
		}
		if (GetKeyDown()[press4]) {
			camera.cameraPos.x -= 0.1;
		}
		if (GetKeyDown()[press6]) {
			camera.cameraPos.x += 0.1;
		}
		if (GetKeyDown()[press8]) {
			camera.cameraPos.y -= 0.1;
		}
		if (GetKeyDown()[press5]) {
			camera.cameraPos.y += 0.1;
		}

	}

	GLvoid drawObject() {
		for (int i = 0; i < map.size(); ++i) {
			map[i]->draw();
		}
		for (int i = 0; i < enemyVec.size(); ++i) {
			enemyVec[i]->draw();
		}
		//for (auto v : enemyVec)
		//{
		//	v->draw();
		//}
		mario.draw(cType);
	}

	GLvoid draw() {
		SetTransformationMatrix();
		drawObject();
	}

	GLvoid key_down(unsigned char key, int x, int y) {
		if (key == 'e' || key == 'E')
			push_state(CHANGEDIMENSION);
		else
			mario.handle_events(GLUT_KEY_DOWN, key);
	}

	GLvoid key_up(unsigned char key, int x, int y) {
		mario.handle_events(GLUT_KEY_UP, key);
	}

	GLvoid InitBuffer() {
		loadStage1(map);
		mario.InitBuffer();

		Enemy* temp0 = new Goomba(glm::vec3(1.0, 1.0, 1.0), glm::vec3(30.0, 0.5, 3.0), glm::vec3(0.0, 0.0, 0.0));
		Enemy* temp1 = new Goomba(glm::vec3(1.0, 1.0, 1.0), glm::vec3(65.0, 0.5, 0.0), glm::vec3(0.0, 0.0, 0.0));
		Enemy* temp2 = new Goomba(glm::vec3(1.0, 1.0, 1.0), glm::vec3(98.0, 0.5, -3.0), glm::vec3(0.0, 0.0, 0.0));
		enemyVec.push_back(temp0);
		enemyVec.push_back(temp1);
		enemyVec.push_back(temp2);
	}

	GLvoid InitValue() {
		{   //ī�޶� �� �ʱ�ȭ
			//camera.cameraPos = glm::vec3(0.0f, 12.0f, 50.0f);
			//camera.cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
			//camera.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

			camera.cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
			camera.cameraDirection = glm::vec3(1.0f, 0.0f, 0.0f);
			camera.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


			cType = D3_VIEW;
		}

		{//������ ����
			mario.init();
		}
	}

	GLvoid SetTransformationMatrix() {
		{//model ��ȯ
			glm::mat4 TR = glm::mat4(1.0f);
			unsigned int modelLocation = glGetUniformLocation(Gets_program_texture(), "model");
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &TR[0][0]);
		}

		{//ī�޶� ��ȯ
			glm::mat4 view = glm::mat4(1.0f);
			view = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraDirection, camera.cameraUp);
			unsigned int viewLocation = glGetUniformLocation(Gets_program_texture(), "view");
			glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
		}

		{//���� ��ȯ
			glm::mat4 projection = glm::mat4(1.0f);
			if (cType == D3_VIEW) {      //3D ��
				projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 500.0f);
				projection = glm::translate(projection, glm::vec3(0.0, 0.0, 0.0));
				//projection = glm::perspective(glm::radians(45.0f), GLfloat(WIDTH)/HEIGHT, 0.1f, (GLfloat)CameraViewSize);
				//projection = glm::translate(projection, glm::vec3(0.0, 0.0, -3.0));
			}
			else {                  //2D ��
				projection = glm::ortho(-CameraViewSize / 40, CameraViewSize / 40, -CameraViewSize / 40, CameraViewSize / 40, 0.1f, CameraViewSize);
				//projection = glm::ortho(-CameraViewSize/20,CameraViewSize/20, -CameraViewSize/20, CameraViewSize/20, 0.1f, CameraViewSize);
			}
			unsigned int projectLoc = glGetUniformLocation(Gets_program_texture(), "projection");
			glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
		}

		//unsigned int viewPosLocation = glGetUniformLocation(Gets_program(), "viewPos");
		//glUniform3f(viewPosLocation, camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);

	}

	Camera getCamera() { return camera; }
	GLuint getcType() { return cType; }

	std::vector<Cube*> GetGround() {
		return map;
	}

	glm::vec3 GetMarioPos() {
		return mario.boundingBox.trans;
	}
}



