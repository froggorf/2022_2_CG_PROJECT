#include "gameover_state.h"

namespace GameOver {
	GLuint gameover_image = -1;
	GLint gameover_time;
	GLuint VAO = -1, VBO[2] = { -1,-1 };

	GLvoid enter() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(3, VBO);
		gameover_time = 0;
		if(gameover_image == -1)
			LoadTexture(gameover_image, "resource/Gameover/gameover.png");
	}
	GLvoid exit() {
		//glDeleteVertexArrays(1, &VAO);
		//glDeleteBuffers(3, VBO);
		//std::cout << "exit - Logo" << std::endl;

	}
	GLvoid pause() {
		std::cout << "pause - GameOver" << std::endl;
	}


	GLvoid resume() {
		std::cout << "resume - GameOver" << std::endl;
	}


	GLvoid handle_events() {

	}

	GLvoid update() {
		//std::cout << "update - logo" << std::endl;
		gameover_time += 16;
		if (gameover_time >= 1000) {
			pop_state();
		}
	}

	GLvoid draw() {
		glUseProgram(Gets_program_screen());

		glBindVertexArray(VAO);

		glm::vec3 image_pos[6] = {
			glm::vec3(-1.0f,1.0f,0.0f),glm::vec3(-1.0f,-1.0f,0.0f),glm::vec3(1.0f,-1.0f,0.0f),
			glm::vec3(-1.0f,1.0f,0.0f),glm::vec3(1.0f,-1.0f,0.0f),glm::vec3(1.0f,1.0f,0.0f),
		};
		glm::vec2 texture_pos[6] = {
			glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.1f),glm::vec2(1.0f,0.1f),
			glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.1f),glm::vec2(1.0f,1.0f),
		};

		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texture_pos), texture_pos, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);



		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(image_pos), image_pos, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 À¯´ÏÆû »ùÇÃ·¯ÀÇ À§Ä¡¸¦ °¡Á®¿È
		glActiveTexture(gameover_image);
		glBindTexture(GL_TEXTURE_2D, gameover_image);
		glUniform1i(tLocation, 0);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(image_pos) / sizeof(image_pos[0]));


		glUseProgram(Gets_program_texture());
	}

	GLvoid key_down(unsigned char, int, int) {

	}

	GLvoid key_up(unsigned char, int, int) {

	}
}