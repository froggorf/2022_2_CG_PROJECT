#include "title_state.h"

namespace Title {
	GLuint VAO_title = -1, VBO_title[2] = { -1,-1 };
	GLuint title_main_image = -1;
	GLuint title_mountain_image = -1;
	GLuint title_game_name_image = -1;
	GLuint title_mario_image = -1;
	GLuint title_start_image = -1;
	GLuint title_exit_image = -1;
	GLuint title_hand_image[5];
	glm::vec3 title_main_image_pos[6] = {
		glm::vec3(-1.0f,1.0f,0.0f),glm::vec3(-1.0f,-1.0f,0.0f),glm::vec3(1.0f,-1.0f,0.0f),
		glm::vec3(-1.0f,1.0f,0.0f),glm::vec3(1.0f,-1.0f,0.0f),glm::vec3(1.0f,1.0f,0.0f),
	};
	glm::vec3 title_mountain_image_pos[6];
	glm::vec3 title_game_name_pos[6];
	glm::vec3 title_mario_pos[6];
	glm::vec2 texture_pos[6] = {
		glm::vec2(0.001f,0.999f),glm::vec2(0.001f,0.001f),glm::vec2(0.999f,0.001f),
		glm::vec2(0.001f,0.999f),glm::vec2(0.999f,0.001f),glm::vec2(0.999f,0.999f),
	};
	int mountain_update_check = 0;
	int game_name_update_check = 0;
	int mario_update_check = 0;
	GLboolean update_check[3];
	GLfloat hand_frame;
	int select_number = 0;
	MCI_OPEN_PARMS openBgm;

	GLvoid enter() {
		std::cout << "enter - title" << std::endl;
		glUseProgram(Gets_program_screen());
		glDisable(GL_DEPTH_TEST);
		if (title_main_image == -1) {
			LoadTexture(title_main_image, "resource/Title/title_main_image.png");
			LoadTexture(title_mountain_image, "resource/Title/title_mountain_image.png");
			LoadTexture(title_game_name_image, "resource/Title/title_game_name.png");
			LoadTexture(title_mario_image, "resource/Title/title_mario_image.png");
			LoadTexture(title_start_image, "resource/Title/title_start.png");
			LoadTexture(title_exit_image, "resource/Title/title_exit.png");
			for (int i = 0; i < 5; ++i) {
				std::string resourcedir = "resource/Title/title_hand_" + std::to_string(i) + ".png";
				LoadTexture(title_hand_image[i], resourcedir.c_str());
			}
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
		mciSendCommand(openBgm.wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
		PlaySoundMP3("resource/Sound/title_state.mp3", true, openBgm);
	}

	GLvoid exit() {
		std::cout << "exit - title" << std::endl;
		glUseProgram(Gets_program_texture());
		glEnable(GL_DEPTH_TEST);
		mciSendCommand(openBgm.wDeviceID, MCI_STOP, MCI_NOTIFY, (DWORD)(LPVOID)&openBgm);
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
		UpdateMountainImage();
		UpdateGameNameImage();
		UpdateMarioImage();
		hand_frame += 0.2;
		if (hand_frame >= 5) hand_frame = 0;
	}

	GLvoid draw() {
		glUseProgram(Gets_program_screen());
		DrawMainImage();
		DrawMountainImage();
		DrawGameNameImage();
		DrawMarioImage();
		if (update_check[0] && update_check[1] && update_check[2]) {
			DrawSelect();
		}
	}
	GLvoid key_down(unsigned char key, int x, int y) {
		if (key == 'w') {
			select_number -= 1;
			if (select_number < 0)select_number = 1;
		}
		else if (key == 's') {
			select_number += 1;
			if (select_number > 1)select_number = 0;
		}
		else if (key == ' ' || key == 13) {
			if (select_number == 0) {
				change_state(SELECTSTAGE);
			}
			else if (select_number == 1) {
				quit();
			}
		}
	}

	GLvoid key_up(unsigned char key, int x, int y) {

	}


	GLvoid UpdateMountainImage() {
		if (mountain_update_check == 0) {
			title_mountain_image_pos[0].y += 0.04f;
			title_mountain_image_pos[3].y += 0.04f;
			title_mountain_image_pos[5].y += 0.04f;
			if (title_mountain_image_pos[0].y >= 0.2f) {
				title_mountain_image_pos[0].y = 0.2f;
				title_mountain_image_pos[3].y = 0.2f;
				title_mountain_image_pos[5].y = 0.2f;
				mountain_update_check = 1;
			}
		}
		else if (mountain_update_check == 1) {
			title_mountain_image_pos[0].y -= 0.02f;
			title_mountain_image_pos[3].y -= 0.02f;
			title_mountain_image_pos[5].y -= 0.02f;
			if (title_mountain_image_pos[0].y <= -0.4f) {
				title_mountain_image_pos[0].y = -0.4f;
				title_mountain_image_pos[3].y = -0.4f;
				title_mountain_image_pos[5].y = -0.4f;
				mountain_update_check = 2;
			}
		}
		else if (mountain_update_check == 2) {
			title_mountain_image_pos[0].y += 0.01f;
			title_mountain_image_pos[3].y += 0.01f;
			title_mountain_image_pos[5].y += 0.01f;
			if (title_mountain_image_pos[0].y >= 0.0f) {
				title_mountain_image_pos[0].y = 0.0f;
				title_mountain_image_pos[3].y = 0.0f;
				title_mountain_image_pos[5].y = 0.0f;
				mountain_update_check = 3;
				update_check[0] = true;
			}
		}

	}
	GLvoid UpdateGameNameImage() {
		if (game_name_update_check == 0) {
			for (int i = 0; i < 6; ++i) {
				title_game_name_pos[i].y -= 0.03f;
			}
			if (title_game_name_pos[0].y <= 0.6f) {
				title_game_name_pos[0].y = 0.6f;	//0,3,5 °¡ À­ÂÊ ¼±		//1,2,4°¡ ¾Æ·§ÂÊ ¼±
				title_game_name_pos[3].y = 0.6f;
				title_game_name_pos[5].y = 0.6f;
				title_game_name_pos[1].y = 0.0f;
				title_game_name_pos[2].y = 0.0f;
				title_game_name_pos[4].y = 0.0f;
				game_name_update_check = 1;
			}
		}
		if (game_name_update_check == 1) {
			for (int i = 0; i < 6; ++i) {
				title_game_name_pos[i].y += 0.005f;
			}
			if (title_game_name_pos[0].y >= 0.8f) {
				title_game_name_pos[0].y = 0.8f;	//0,3,5 °¡ À­ÂÊ ¼±		//1,2,4°¡ ¾Æ·§ÂÊ ¼±
				title_game_name_pos[3].y = 0.8f;
				title_game_name_pos[5].y = 0.8f;
				title_game_name_pos[1].y = 0.2f;
				title_game_name_pos[2].y = 0.2f;
				title_game_name_pos[4].y = 0.2f;
				game_name_update_check = 2;
				update_check[1] = true;
			}
		}
	}
	GLvoid UpdateMarioImage() {
		if (mario_update_check < 60) {
			++mario_update_check;
			glm::mat4 gotostartingpoint = glm::mat4(1.0f);
			gotostartingpoint = glm::translate(gotostartingpoint, glm::vec3(0.65, 0.7, 0.0));
			glm::mat4 rotatestartingpoint = glm::mat4(1.0f);
			rotatestartingpoint = glm::rotate(rotatestartingpoint, glm::radians(-1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 backtostartingpoint = glm::mat4(1.0f);
			backtostartingpoint = glm::translate(backtostartingpoint, glm::vec3(-0.65, -0.7, 0.0));

			glm::vec3 mario_starting_point = glm::vec3(title_mario_pos[0].x + 0.3f, title_mario_pos[0].y - 0.3f, 0.0f);
			mario_starting_point = backtostartingpoint * rotatestartingpoint * gotostartingpoint * glm::vec4(mario_starting_point, 1.0f);
			mario_starting_point.x += 0.01;
			mario_starting_point.y += 0.0025;
			glm::vec3 end_mario_pos[6] = {
			glm::vec3(mario_starting_point.x - 0.3f,mario_starting_point.y + 0.3f,0.0f),glm::vec3(mario_starting_point.x - 0.3f,mario_starting_point.y - 0.3f,0.0f),glm::vec3(mario_starting_point.x + 0.3f,mario_starting_point.y - 0.3f,0.0f),
			glm::vec3(mario_starting_point.x - 0.3f,mario_starting_point.y + 0.3f,0.0f),glm::vec3(mario_starting_point.x + 0.3f,mario_starting_point.y - 0.3f,0.0f),glm::vec3(mario_starting_point.x + 0.3f,mario_starting_point.y + 0.3f,0.0f),

			//0,3,5 °¡ À­ÂÊ ¼±		//1,2,4°¡ ¾Æ·§ÂÊ ¼±
			};
			memcpy(title_mario_pos, end_mario_pos, sizeof(title_mario_pos));


		}
		else {
			update_check[2] = true;
		}
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
	}
	GLvoid DrawMountainImage() {
		glBindBuffer(GL_ARRAY_BUFFER, VBO_title[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(title_mountain_image_pos), title_mountain_image_pos, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 À¯´ÏÆû »ùÇÃ·¯ÀÇ À§Ä¡¸¦ °¡Á®¿È
		glActiveTexture(title_mountain_image);
		glBindTexture(GL_TEXTURE_2D, title_mountain_image);
		glUniform1i(tLocation, 0);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(title_mountain_image_pos) / sizeof(title_mountain_image_pos[0]));
	}
	GLvoid DrawGameNameImage() {
		glBindBuffer(GL_ARRAY_BUFFER, VBO_title[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(title_game_name_pos), title_game_name_pos, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 À¯´ÏÆû »ùÇÃ·¯ÀÇ À§Ä¡¸¦ °¡Á®¿È
		glActiveTexture(title_game_name_image);
		glBindTexture(GL_TEXTURE_2D, title_game_name_image);
		glUniform1i(tLocation, 0);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(title_game_name_pos) / sizeof(title_game_name_pos[0]));
	}
	GLvoid DrawMarioImage() {
		glBindBuffer(GL_ARRAY_BUFFER, VBO_title[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(title_mario_pos), title_mario_pos, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 À¯´ÏÆû »ùÇÃ·¯ÀÇ À§Ä¡¸¦ °¡Á®¿È
		glActiveTexture(title_mario_image);
		glBindTexture(GL_TEXTURE_2D, title_mario_image);
		glUniform1i(tLocation, 0);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(title_mario_pos) / sizeof(title_mario_pos[0]));
	}
	GLvoid EarlyInitValue() {
		glm::vec3 early_mountain_pos[6] = {
			glm::vec3(-1.0f,-1.0f,0.0f),glm::vec3(-1.0f,-1.0f,0.0f), glm::vec3(1.0f,-1.0f,0.0f),
			glm::vec3(-1.0f,-1.0f,0.0f),glm::vec3(1.0f,-1.0f,0.0f),glm::vec3(1.0f,-1.0f,0.0f),
			//0,3,5 °¡ À­ÂÊ ¼±
		};
		memcpy(title_mountain_image_pos, early_mountain_pos, sizeof(title_mountain_image_pos));
		mountain_update_check = 0;


		glm::vec3 early_game_name_pos[6] = {
			glm::vec3(-0.6f,1.6f,0.0f),glm::vec3(-0.6f,1.0f,0.0f), glm::vec3(0.6f,1.0f,0.0f),
			glm::vec3(-0.6f,1.6f,0.0f),glm::vec3(0.6f,1.0f,0.0f),glm::vec3(0.6f,1.6f,0.0f),
			//0,3,5 °¡ À­ÂÊ ¼±		//1,2,4°¡ ¾Æ·§ÂÊ ¼±
		};
		memcpy(title_game_name_pos, early_game_name_pos, sizeof(title_game_name_pos));
		game_name_update_check = 0;

		glm::vec3 early_mario_pos[6] = {
			glm::vec3(-1.6f,-0.4f,0.0f),glm::vec3(-1.6f,-1.0f,0.0f),glm::vec3(-1.0f,-1.0f,0.0f),
			glm::vec3(-1.6f,-0.4f,0.0f),glm::vec3(-1.0f,-1.0f,0.0f),glm::vec3(-1.0f,-0.4f,0.0f),
			//0,3,5 °¡ À­ÂÊ ¼±		//1,2,4°¡ ¾Æ·§ÂÊ ¼±
		};
		memcpy(title_mario_pos, early_mario_pos, sizeof(title_mario_pos));
		mario_update_check = 0;

		update_check[0] = false;
		update_check[1] = false;
		update_check[2] = false;
		hand_frame = 0;
		select_number = 0;
	}



	GLvoid DrawSelect() {
		{//start ±×¸®±â
			glm::vec3 start_pos[6] = {
				glm::vec3(0.31f,-0.05f,0.0f),glm::vec3(0.31f,-0.17f,0.0f),glm::vec3(0.69f,-0.17f,0.0f),
				glm::vec3(0.31f,-0.05f,0.0f),glm::vec3(0.69f,-0.17f,0.0f),glm::vec3(0.69f,-0.05f,0.0f),
			};
			glBindBuffer(GL_ARRAY_BUFFER, VBO_title[0]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(start_pos), start_pos, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 À¯´ÏÆû »ùÇÃ·¯ÀÇ À§Ä¡¸¦ °¡Á®¿È
			glActiveTexture(title_start_image);
			glBindTexture(GL_TEXTURE_2D, title_start_image);
			glUniform1i(tLocation, 0);
			glDrawArrays(GL_TRIANGLES, 0, sizeof(start_pos) / sizeof(start_pos[0]));

		}
		{//end ±×¸®±â
			glm::vec3 exit_pos[6] = {
				glm::vec3(0.31f,-0.35f,0.0f),glm::vec3(0.31f,-0.47f,0.0f),glm::vec3(0.61f,-0.47f,0.0f),
				glm::vec3(0.31f,-0.35f,0.0f),glm::vec3(0.61f,-0.47f,0.0f),glm::vec3(0.61f,-0.35f,0.0f),
			};
			glBindBuffer(GL_ARRAY_BUFFER, VBO_title[0]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(exit_pos), exit_pos, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 À¯´ÏÆû »ùÇÃ·¯ÀÇ À§Ä¡¸¦ °¡Á®¿È
			glActiveTexture(title_exit_image);
			glBindTexture(GL_TEXTURE_2D, title_exit_image);
			glUniform1i(tLocation, 0);
			glDrawArrays(GL_TRIANGLES, 0, sizeof(exit_pos) / sizeof(exit_pos[0]));
		}
		{//¼ÕÁþ ±×¸®±â
			if (select_number == 0) {
				glm::vec3 hand_pos[6] = {
				glm::vec3(0.121667f,-0.05f,0.0f),glm::vec3(0.121667f,-0.17f,0.0f),glm::vec3(0.251667f,-0.17f,0.0f),
				glm::vec3(0.121667f,-0.05f,0.0f),glm::vec3(0.251667f,-0.17f,0.0f),glm::vec3(0.251667f,-0.05f,0.0f),
				};
				glBindBuffer(GL_ARRAY_BUFFER, VBO_title[0]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(hand_pos), hand_pos, GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);
			}
			else if (select_number == 1) {
				glm::vec3 hand_pos[6] = {
				glm::vec3(0.121667f,-0.35f,0.0f),glm::vec3(0.121667f,-0.47f,0.0f),glm::vec3(0.251667f,-0.47f,0.0f),
				glm::vec3(0.121667f,-0.35f,0.0f),glm::vec3(0.251667f,-0.47f,0.0f),glm::vec3(0.251667f,-0.35f,0.0f),
				};
				glBindBuffer(GL_ARRAY_BUFFER, VBO_title[0]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(hand_pos), hand_pos, GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);
			}

			int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 À¯´ÏÆû »ùÇÃ·¯ÀÇ À§Ä¡¸¦ °¡Á®¿È
			glActiveTexture(title_hand_image[(int)hand_frame]);
			glBindTexture(GL_TEXTURE_2D, title_hand_image[(int)hand_frame]);
			glUniform1i(tLocation, 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}
}