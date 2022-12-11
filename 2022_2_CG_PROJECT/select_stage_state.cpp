#include "select_stage_state.h"

#define MAXSTAGE 3
#define HANDMAXFRAME 5
#define HANDSIZE 0.1

enum SelectStageENUM {
	SELECTSTAGEMAIN=0,
	SELECTSTAGESTAGE1,
	SELECTSTAGESTAGE2,
	SELECTSTAGESTAGE3,
	SELECTSTAGEEND
};

namespace SelectStage {
	GLuint VAO = -1, VBO[2] = { -1,-1 };
	GLuint texture[SELECTSTAGEEND];
	GLuint hand_texture[HANDMAXFRAME];
	glm::vec2 texture_pos[6];
	glm::vec3 image_pos[SELECTSTAGEEND][6];
	glm::vec3 hand_pos[6];
	GLfloat hand_frame;
	
	GLint playable_stage_num;
	GLint select_stage_num;
	GLboolean check_clear;

	GLvoid enter() {
		InitValue();
		InitBuffer();
		glUseProgram(Gets_program_screen());
		glDisable(GL_DEPTH_TEST);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texture_pos), texture_pos, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
	}
	GLvoid exit() {
		glUseProgram(Gets_program_texture());
		glEnable(GL_DEPTH_TEST);
	}
	GLvoid pause() {
		
	}
	GLvoid resume() {
		glUseProgram(Gets_program_screen());
		glDisable(GL_DEPTH_TEST);
		std::cout << playable_stage_num << ", " << select_stage_num << std::endl;
		if (!check_clear) {
			playable_stage_num -= 1;
			select_stage_num -= 1;
		}
		


		if (select_stage_num == playable_stage_num) {
			playable_stage_num += 1;
			if (playable_stage_num > MAXSTAGE) playable_stage_num = MAXSTAGE;
			select_stage_num += 1;
			if (select_stage_num > MAXSTAGE) select_stage_num = MAXSTAGE;
		}
		std::cout << playable_stage_num << ", " << select_stage_num << std::endl;
		
	}
	GLvoid handle_events() {

	}
	GLvoid update() {
		hand_frame += 0.2;
		if (hand_frame >= HANDMAXFRAME) {
			hand_frame = 0;
		}
	}
	GLvoid draw() {
		DrawMainImage();
		DrawStageImage();
		DrawHand();
	}
	GLvoid key_down(unsigned char key, int x , int y) {
		if (key == '+') {
			++playable_stage_num;
		}
		if (key == 'w') {
			select_stage_num -= 1;
			if (select_stage_num < 1) select_stage_num = 1;
		}
		else if (key == 's') {
			select_stage_num += 1;
			if (select_stage_num > playable_stage_num)
				select_stage_num = playable_stage_num;
		}
		else if (key == ' ' || key == 13) {
			push_state(GameStateType::PLAY);
		}
		
		
	}
	GLvoid key_up(unsigned char, int, int) {

	}

	GLvoid InitValue() {
		check_clear = false;
		playable_stage_num = 1;
		select_stage_num = 1;
		hand_frame = 0;
		glm::vec2 temp_texture_pos[6] = {
			glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.1f),glm::vec2(1.0f,0.1f),
			glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.1f),glm::vec2(1.0f,1.0f),
		};
		memcpy(texture_pos, temp_texture_pos, sizeof(texture_pos));
		glm::vec3 temp_main_image_pos[6] = {
			glm::vec3(-1.0f,1.0f,0.0f),glm::vec3(-1.0f,-1.0f,0.0f),glm::vec3(1.0f,-1.0f,0.0f),
			glm::vec3(-1.0f,1.0f,0.0f),glm::vec3(1.0f,-1.0f,0.0f),glm::vec3(1.0f,1.0f,0.0f),
		};
		memcpy(image_pos[SELECTSTAGEMAIN], temp_main_image_pos, sizeof(image_pos[SELECTSTAGEMAIN]));
		glm::vec3 temp_stage1_image_pos[6] = {
			glm::vec3(0.05333f,0.893333f,0.0f),glm::vec3(0.05333f,0.318333f,0.0f), glm::vec3(0.59f, 0.318333f,0.0f),
			glm::vec3(0.05333f,0.893333f,0.0f),glm::vec3(0.59f, 0.318333f,0.0f),glm::vec3(0.59f, 0.893333f,0.0f),
		};
		memcpy(image_pos[SELECTSTAGESTAGE1], temp_stage1_image_pos, sizeof(image_pos[SELECTSTAGESTAGE1]));
		glm::vec3 temp_stage2_image_pos[6] = {
			glm::vec3(-0.736667f,0.643333f,0.0f),glm::vec3(-0.736667f,0.07f,0.0f),glm::vec3(-0.205f,0.07f,0.0f),
			glm::vec3(-0.736667f,0.643333f,0.0f),glm::vec3(-0.205f,0.07f,0.0f),glm::vec3(-0.205f,0.643333f,0.0f),
		};
		memcpy(image_pos[SELECTSTAGESTAGE2], temp_stage2_image_pos, sizeof(image_pos[SELECTSTAGESTAGE2]));
		glm::vec3 temp_stage3_image_pos[6] = {
		glm::vec3(0.16f,0.045f,0.0f),glm::vec3(0.16f,-0.528333f,0.0f),glm::vec3(0.693333f,-0.528333f,0.0f),
		glm::vec3(0.16f,0.045f,0.0f),glm::vec3(0.693333f,-0.528333f,0.0f),glm::vec3(0.693333f,0.045f,0.0f),
		};
		memcpy(image_pos[SELECTSTAGESTAGE3], temp_stage3_image_pos, sizeof(image_pos[SELECTSTAGESTAGE3]));

	}

	GLvoid InitBuffer() {
		if (VAO == -1) {
			glGenVertexArrays(1, &VAO);
			glGenBuffers(2, VBO);
			LoadTexture(texture[SELECTSTAGEMAIN], "resource/SelectStage/select_stage_main_image.png");
			LoadTexture(texture[SELECTSTAGESTAGE1], "resource/SelectStage/select_stage_stage1.png");
			LoadTexture(texture[SELECTSTAGESTAGE2], "resource/SelectStage/select_stage_stage2.png");
			LoadTexture(texture[SELECTSTAGESTAGE3], "resource/SelectStage/select_stage_stage3.png");
			for (int i = 0; i < 5; ++i) {
				std::string resourcedir = "resource/Title/title_hand_" + std::to_string(i) + ".png";
				LoadTexture(hand_texture[i], resourcedir.c_str());
			}
		}
	}

	GLvoid DrawMainImage() {
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(image_pos[SELECTSTAGEMAIN]), image_pos[SELECTSTAGEMAIN], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 À¯´ÏÆû »ùÇÃ·¯ÀÇ À§Ä¡¸¦ °¡Á®¿È
		
		glActiveTexture(texture[SELECTSTAGEMAIN]);
		glBindTexture(GL_TEXTURE_2D, texture[SELECTSTAGEMAIN]);
		glUniform1i(tLocation, 0);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(image_pos[SELECTSTAGEMAIN]) / sizeof(image_pos[SELECTSTAGEMAIN][0]));
	}

	GLvoid DrawStageImage() {
		{//1½ºÅ×ÀÌÁö
			if (playable_stage_num >= 1) {
				glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(image_pos[SELECTSTAGESTAGE1]), image_pos[SELECTSTAGESTAGE1], GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);
				int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 À¯´ÏÆû »ùÇÃ·¯ÀÇ À§Ä¡¸¦ °¡Á®¿È
				glActiveTexture(texture[SELECTSTAGESTAGE1]);
				glBindTexture(GL_TEXTURE_2D, texture[SELECTSTAGESTAGE1]);
				glUniform1i(tLocation, 0);
				glDrawArrays(GL_TRIANGLES, 0, sizeof(image_pos[SELECTSTAGESTAGE1]) / sizeof(image_pos[SELECTSTAGESTAGE1][0]));
			}
		}

		{//2½ºÅ×ÀÌÁö
			if (playable_stage_num >= 2) {
				glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(image_pos[SELECTSTAGESTAGE2]), image_pos[SELECTSTAGESTAGE2], GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);
				int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 À¯´ÏÆû »ùÇÃ·¯ÀÇ À§Ä¡¸¦ °¡Á®¿È
				glActiveTexture(texture[SELECTSTAGESTAGE2]);
				glBindTexture(GL_TEXTURE_2D, texture[SELECTSTAGESTAGE2]);
				glUniform1i(tLocation, 0);
				glDrawArrays(GL_TRIANGLES, 0, sizeof(image_pos[SELECTSTAGESTAGE2]) / sizeof(image_pos[SELECTSTAGESTAGE2][0]));
			}
		}

		{
			if (playable_stage_num >= 3) {
				glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(image_pos[SELECTSTAGESTAGE3]), image_pos[SELECTSTAGESTAGE3], GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);
				int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 À¯´ÏÆû »ùÇÃ·¯ÀÇ À§Ä¡¸¦ °¡Á®¿È
				glActiveTexture(texture[SELECTSTAGESTAGE3]);
				glBindTexture(GL_TEXTURE_2D, texture[SELECTSTAGESTAGE3]);
				glUniform1i(tLocation, 0);
				glDrawArrays(GL_TRIANGLES, 0, sizeof(image_pos[SELECTSTAGESTAGE3]) / sizeof(image_pos[SELECTSTAGESTAGE3][0]));
			}
		}
	}
	GLvoid DrawHand() {
		for (int i = 0; i < 6; ++i)
			hand_pos[i] = image_pos[select_stage_num][0];
		
		hand_pos[0].x -= HANDSIZE; hand_pos[1].x -= HANDSIZE; hand_pos[3].x -= HANDSIZE; 
		hand_pos[2].x += HANDSIZE; hand_pos[4].x += HANDSIZE; hand_pos[5].x += HANDSIZE;
		hand_pos[0].y += HANDSIZE; hand_pos[3].y += HANDSIZE; hand_pos[5].y += HANDSIZE;
		hand_pos[1].y -= HANDSIZE; hand_pos[2].y -= HANDSIZE; hand_pos[4].y -= HANDSIZE;
		
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(hand_pos), hand_pos, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 À¯´ÏÆû »ùÇÃ·¯ÀÇ À§Ä¡¸¦ °¡Á®¿È
		glActiveTexture(hand_texture[(int)hand_frame]);
		glBindTexture(GL_TEXTURE_2D, hand_texture[(int)hand_frame]);
		glUniform1i(tLocation, 0);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(hand_pos) / sizeof(hand_pos[0]));

	}

	GLint& GetSelectStageNum() { return select_stage_num; }
	GLint& GetPlayableStageNum() { return playable_stage_num; }

	GLvoid ClearUpdate(GLboolean is_clear) {
		check_clear = is_clear;
	}
}