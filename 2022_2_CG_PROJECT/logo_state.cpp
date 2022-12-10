#include "logo_state.h"

namespace Logo {
	GLuint logo_image = -1;
	GLint logo_time = 0;
	GLuint VAO_logo = -1, VBO_logo[2] = { -1,-1 };
	
	GLvoid enter() {
		//std::cout << "enter - Logo" << std::endl;
		if (logo_image == -1)
			LoadTexture(logo_image, "resource/Logo/tukorea_logo.png");
		logo_time = 0;
		if (VAO_logo == -1) {
			glGenVertexArrays(1, &VAO_logo);
			glGenBuffers(2, VBO_logo);
		}
			
			
	}
	GLvoid exit() {
		//std::cout << "exit - Logo" << std::endl;

	}
	GLvoid pause() {
		std::cout << "pause - Logo" << std::endl;
	}


	GLvoid resume() {
		std::cout << "resume - Logo" << std::endl;
	}


	GLvoid handle_events() {

	}

	GLvoid update() {
		//std::cout << "update - logo" << std::endl;
		logo_time += 16;
		if (logo_time>=1000) {
			change_state(TITLE);
		}
	}

	GLvoid draw() {
		glUseProgram(Gets_program_screen());

		glBindVertexArray(VAO_logo);

		glm::vec3 image_pos[6] = {
			glm::vec3(-1.0f,1.0f,0.0f),glm::vec3(-1.0f,-1.0f,0.0f),glm::vec3(1.0f,-1.0f,0.0f),
			glm::vec3(-1.0f,1.0f,0.0f),glm::vec3(1.0f,-1.0f,0.0f),glm::vec3(1.0f,1.0f,0.0f),
		};
		glm::vec2 texture_pos[6] = {
			glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.1f),glm::vec2(1.0f,0.1f),
			glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.1f),glm::vec2(1.0f,1.0f),
		};

		glBindBuffer(GL_ARRAY_BUFFER, VBO_logo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texture_pos), texture_pos, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);

		

		glBindBuffer(GL_ARRAY_BUFFER, VBO_logo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(image_pos), image_pos, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 À¯´ÏÆû »ùÇÃ·¯ÀÇ À§Ä¡¸¦ °¡Á®¿È
		glActiveTexture(logo_image);
		glBindTexture(GL_TEXTURE_2D, logo_image);
		glUniform1i(tLocation, 0);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(image_pos) / sizeof(image_pos[0]));


		glUseProgram(Gets_program_texture());
	}

	GLvoid key_down(unsigned char, int, int) {

	}

	GLvoid key_up(unsigned char, int, int) {

	}
}