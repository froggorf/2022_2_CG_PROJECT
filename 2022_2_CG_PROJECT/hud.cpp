#include "hud.h"
#define HP_StartPosX -0.75625f
#define HP_StartPosY 0.96875f
#define StartPosX 0.765f
#define StartPosY 0.96875f
#define NumberX 0.075f
#define NumberY 0.120937f
glm::vec3 hp_screen_pos[6] = {
	glm::vec3(-1.0f,1.0f, 0.0f),	glm::vec3(-1.0f,1.0f - 0.192f,0.0f),			glm::vec3(-1.0f + 0.582f, 1.0f - 0.192f,0.0f),
	glm::vec3(-1.0f,1.0f, 0.0f),	glm::vec3(-1.0f + 0.582f, 1.0f - 0.192f,0.0f),	glm::vec3(-1.0f + 0.582f, 1.0f, 0.0f),
};
glm::vec3 hp_tens_pos[6] = {
	glm::vec3(HP_StartPosX, HP_StartPosY,0.0f),glm::vec3(HP_StartPosX, HP_StartPosY - NumberY,0.0f),glm::vec3(HP_StartPosX + NumberX, HP_StartPosY - NumberY,0.0f),
	glm::vec3(HP_StartPosX, HP_StartPosY,0.0f),glm::vec3(HP_StartPosX + NumberX, HP_StartPosY - NumberY,0.0f),glm::vec3(HP_StartPosX + NumberX, HP_StartPosY,0.0f),
};
glm::vec3 hp_units_pos[6] = {
	glm::vec3(HP_StartPosX + NumberX * 1, HP_StartPosY,0.0f),glm::vec3(HP_StartPosX + NumberX * 1, HP_StartPosY - NumberY,0.0f),glm::vec3(HP_StartPosX + NumberX * 2, HP_StartPosY - NumberY,0.0f),
	glm::vec3(HP_StartPosX + NumberX * 1, HP_StartPosY,0.0f),glm::vec3(HP_StartPosX + NumberX * 2, HP_StartPosY - NumberY,0.0f),glm::vec3(HP_StartPosX + NumberX * 2, HP_StartPosY,0.0f),
};
glm::vec3 hp_slash_pos[6] = {
	glm::vec3(HP_StartPosX + NumberX * 2, HP_StartPosY,0.0f),glm::vec3(HP_StartPosX + NumberX * 2, HP_StartPosY - NumberY,0.0f),glm::vec3(HP_StartPosX + NumberX * 3, HP_StartPosY - NumberY,0.0f),
	glm::vec3(HP_StartPosX + NumberX * 2, HP_StartPosY,0.0f),glm::vec3(HP_StartPosX + NumberX * 3, HP_StartPosY - NumberY,0.0f),glm::vec3(HP_StartPosX + NumberX * 3, HP_StartPosY,0.0f),
};
glm::vec3 max_hp_tens_pos[6] = {
	glm::vec3(HP_StartPosX + NumberX * 3, HP_StartPosY,0.0f),glm::vec3(HP_StartPosX + NumberX * 3, HP_StartPosY - NumberY,0.0f),glm::vec3(HP_StartPosX + NumberX * 4, HP_StartPosY - NumberY,0.0f),
	glm::vec3(HP_StartPosX + NumberX * 3, HP_StartPosY,0.0f),glm::vec3(HP_StartPosX + NumberX * 4, HP_StartPosY - NumberY,0.0f),glm::vec3(HP_StartPosX + NumberX * 4, HP_StartPosY,0.0f),
};
glm::vec3 max_hp_units_pos[6] = {
	glm::vec3(HP_StartPosX + NumberX * 4, HP_StartPosY,0.0f),glm::vec3(HP_StartPosX + NumberX * 4, HP_StartPosY - NumberY,0.0f),glm::vec3(HP_StartPosX + NumberX * 5, HP_StartPosY - NumberY,0.0f),
	glm::vec3(HP_StartPosX + NumberX * 4, HP_StartPosY,0.0f),glm::vec3(HP_StartPosX + NumberX * 5, HP_StartPosY - NumberY,0.0f),glm::vec3(HP_StartPosX + NumberX * 5, HP_StartPosY,0.0f),
};
glm::vec3 coin_tens_pos[6] = {
	glm::vec3(StartPosX + NumberX * 0, StartPosY,0.0f),glm::vec3(StartPosX + NumberX * 0, StartPosY - NumberY,0.0f),glm::vec3(StartPosX + NumberX * 1, StartPosY - NumberY,0.0f),
	glm::vec3(StartPosX + NumberX * 0, StartPosY,0.0f),glm::vec3(StartPosX + NumberX * 1, StartPosY - NumberY,0.0f),glm::vec3(StartPosX + NumberX * 1, StartPosY,0.0f),
};
glm::vec3 coin_units_pos[6] = {
	glm::vec3(StartPosX + NumberX * 1, StartPosY,0.0f),glm::vec3(StartPosX + NumberX * 1, StartPosY - NumberY,0.0f),glm::vec3(StartPosX + NumberX * 2, StartPosY - NumberY,0.0f),
	glm::vec3(StartPosX + NumberX * 1, StartPosY,0.0f),glm::vec3(StartPosX + NumberX * 2, StartPosY - NumberY,0.0f),glm::vec3(StartPosX + NumberX * 2, StartPosY,0.0f),
};
glm::vec3 coin_screen_pos[6] = {
	glm::vec3(1.0f - 0.6f,1.0f,0.0f),glm::vec3(1.0f - 0.6f,1.0f - 0.1875f,0.0f),glm::vec3(1.0f,1.0f - 0.1875f,0.0f),
	glm::vec3(1.0f - 0.6f,1.0f,0.0f), glm::vec3(1.0f,1.0f - 0.1875f,0.0f), glm::vec3(1.0f,1.0f,0.0f),
};
glm::vec2 texture_pos[6] = {
	glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.0f),glm::vec2(1.0f,0.0f),
	glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.0f),glm::vec2(1.0f,1.0f),
};


Hud::Hud() {

}

GLvoid Hud::InitBuffer() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBO);
	
	LoadTexture(hp_bar_texture, "resource/Hud/hp_bar.png");
	LoadTexture(coin_bar_texture, "resource/Hud/coin_bar.png");
	for (int i = 0; i < 10; ++i) {
		std::string resourcedir = "resource/Hud/number_" + std::to_string(i) + ".png";
		LoadTexture(number_texture[i], resourcedir.c_str());
	}
	LoadTexture(slash_texture, "resource/Hud/hp_slash.png");
}


GLvoid Hud::Draw(int hp, int coin_num) {
	glDisable(GL_DEPTH_TEST);

	glUseProgram(Gets_program_screen());
	

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texture_pos), texture_pos, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	
	{//hp관련
		{//hp_bar 그리기
			glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(hp_screen_pos), hp_screen_pos, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 유니폼 샘플러의 위치를 가져옴
			glActiveTexture(hp_bar_texture);
			glBindTexture(GL_TEXTURE_2D, hp_bar_texture);
			glUniform1i(tLocation, 0);
			glDrawArrays(GL_TRIANGLES, 0, sizeof(hp_screen_pos) / sizeof(hp_screen_pos[0]));
		}
		{//hp_bar 생명력 수치 그리기
			{//현재생명력
				{//십의자리
					if (hp >= 10) {
						glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
						glBufferData(GL_ARRAY_BUFFER, sizeof(hp_tens_pos), hp_tens_pos, GL_STATIC_DRAW);
						glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
						glEnableVertexAttribArray(0);
						int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 유니폼 샘플러의 위치를 가져옴
						glActiveTexture(number_texture[hp / 10]);
						glBindTexture(GL_TEXTURE_2D, number_texture[hp / 10]);
						glUniform1i(tLocation, 0);
						glDrawArrays(GL_TRIANGLES, 0, sizeof(hp_tens_pos) / sizeof(hp_tens_pos[0]));
					}
				}
				{//일의자리
					glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
					glBufferData(GL_ARRAY_BUFFER, sizeof(hp_units_pos), hp_units_pos, GL_STATIC_DRAW);
					glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
					glEnableVertexAttribArray(0);
					int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 유니폼 샘플러의 위치를 가져옴
					glActiveTexture(number_texture[hp % 10]);
					glBindTexture(GL_TEXTURE_2D, number_texture[hp % 10]);
					glUniform1i(tLocation, 0);
					glDrawArrays(GL_TRIANGLES, 0, sizeof(hp_units_pos) / sizeof(hp_units_pos[0]));
				}
			}
			
			{//슬래시
				glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(hp_slash_pos), hp_slash_pos, GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);
				int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 유니폼 샘플러의 위치를 가져옴
				glActiveTexture(slash_texture);
				glBindTexture(GL_TEXTURE_2D, slash_texture);
				glUniform1i(tLocation, 0);
				glDrawArrays(GL_TRIANGLES, 0, sizeof(hp_slash_pos) / sizeof(hp_slash_pos[0]));
			}

			{//맥스생명력
				glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(max_hp_tens_pos), max_hp_tens_pos, GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);
				int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 유니폼 샘플러의 위치를 가져옴
				glActiveTexture(number_texture[1]);
				glBindTexture(GL_TEXTURE_2D, number_texture[1]);
				glUniform1i(tLocation, 0);
				glDrawArrays(GL_TRIANGLES, 0, sizeof(max_hp_tens_pos) / sizeof(max_hp_tens_pos[0]));

				glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(max_hp_units_pos), max_hp_units_pos, GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);
				tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 유니폼 샘플러의 위치를 가져옴
				glActiveTexture(number_texture[0]);
				glBindTexture(GL_TEXTURE_2D, number_texture[0]);
				glUniform1i(tLocation, 0);
				glDrawArrays(GL_TRIANGLES, 0, sizeof(max_hp_units_pos) / sizeof(max_hp_units_pos[0]));
			}
		}
	}
	

	{//코인 관련
		glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(coin_screen_pos), coin_screen_pos, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 유니폼 샘플러의 위치를 가져옴
		glActiveTexture(coin_bar_texture);
		glBindTexture(GL_TEXTURE_2D, coin_bar_texture);
		glUniform1i(tLocation, 0);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(coin_screen_pos) / sizeof(coin_screen_pos[0]));
	}

	{
		{//십의자리
			if (coin_num >= 10) {
				glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(coin_tens_pos), coin_tens_pos, GL_STATIC_DRAW);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);
				int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 유니폼 샘플러의 위치를 가져옴
				glActiveTexture(number_texture[coin_num / 10]);
				glBindTexture(GL_TEXTURE_2D, number_texture[coin_num / 10]);
				glUniform1i(tLocation, 0);
				glDrawArrays(GL_TRIANGLES, 0, sizeof(coin_tens_pos) / sizeof(coin_tens_pos[0]));
			}
		}

		{//일의자리
			glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(coin_units_pos), coin_units_pos, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);
			int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 유니폼 샘플러의 위치를 가져옴
			glActiveTexture(number_texture[coin_num % 10]);
			glBindTexture(GL_TEXTURE_2D, number_texture[coin_num % 10]);
			glUniform1i(tLocation, 0);
			glDrawArrays(GL_TRIANGLES, 0, sizeof(coin_units_pos) / sizeof(coin_units_pos[0]));
		}
	}



	

	



	

	glEnable(GL_DEPTH_TEST);
	glUseProgram(Gets_program_texture());
}
