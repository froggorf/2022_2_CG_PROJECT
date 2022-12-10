#include "title_state.h"

namespace Title {
	GLuint VAO_title = -1, VBO_title[2] = { -1,-1 };
	GLuint title_main_image = -1;
	GLuint title_mountain_image = -1;
	glm::vec3 title_main_image_pos[6] = {
		glm::vec3(-1.0f,1.0f,0.0f),glm::vec3(-1.0f,-1.0f,0.0f),glm::vec3(1.0f,-1.0f,0.0f),
		glm::vec3(-1.0f,1.0f,0.0f),glm::vec3(1.0f,-1.0f,0.0f),glm::vec3(1.0f,1.0f,0.0f),
	};
	glm::vec3 title_mountain_image_pos[6];
	glm::vec2 texture_pos[6] = {
		glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.1f),glm::vec2(1.0f,0.1f),
		glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.1f),glm::vec2(1.0f,1.0f),
	};
	GLvoid enter() {
		std::cout << "enter - title" << std::endl;
		glUseProgram(Gets_program_screen());
		if (title_main_image == -1) {
			LoadTexture(title_main_image, "resource/Title/title_main_image.png");
			LoadTexture(title_mountain_image, "resource/Title/title_main_image.png");
		}
		if (VAO_title == -1) {
			glGenVertexArrays(1, &VAO_title);
			glGenBuffers(2, VBO_title);
		}
		glBindVertexArray(VAO_title);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_title[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texture_pos), texture_pos, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);

		EarlyInitValue();
	}

	GLvoid exit() {
		std::cout << "exit - title" << std::endl;
		glUseProgram(Gets_program_texture());
	}

	GLvoid pause() {
		std::cout << "pause - title" << std::endl;
	}

	GLvoid resume() {
		std::cout << "resume - title" << std::endl;
	}

	GLvoid handle_events() {

	}

	GLvoid update() {
		//std::cout << "update - title" << std::endl;
	}

	GLvoid draw() {
		glUseProgram(Gets_program_screen());


		DrawMainImage();
	}
	GLvoid key_down(unsigned char key, int x, int y) {

	}

	GLvoid key_up(unsigned char key, int x, int y) {

	}

	
	GLvoid DrawMainImage() {
		glBindBuffer(GL_ARRAY_BUFFER, VBO_title[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(title_main_image_pos), title_main_image_pos, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 À¯´ÏÆû »ùÇÃ·¯ÀÇ À§Ä¡¸¦ °¡Á®¿È
		glActiveTexture(title_main_image);
		glBindTexture(GL_TEXTURE_2D, title_main_image);
		glUniform1i(tLocation, 0);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(title_main_image_pos) / sizeof(title_main_image_pos[0]));


		glUseProgram(Gets_program_texture());
	}
	GLvoid EarlyInitValue() {
		title_mountain_image_pos = {
			glm::vec3(-1.0f,-1.0f,0.0f),glm::vec3(-1.0f,-2.0f,0.0f), glm::vec3(1.0f,-2.0f,0.0f),
			glm::vec3(-1.0f,-1.0f,0.0f),glm::vec3(1.0f,-2.0f,0.0f),glm::vec3(1.0f,-1.0f,0.0f),
		}
	}
}