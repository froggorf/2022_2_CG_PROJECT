#include "background.h"

glm::vec3 background_screen_pos[6] = {
	glm::vec3(-1.0f,1.0f,0.0f),glm::vec3(-1.0f,-1.0f,0.0f),glm::vec3(1.0f,-1.0f,0.0f),
	glm::vec3(-1.0f,1.0f,0.0f),glm::vec3(1.0f,-1.0f,0.0f),glm::vec3(1.0f,1.0f,0.0f),
};

glm::vec2 background_texture_pos[6] = {
	glm::vec2(0.0f,1.0f),glm::vec2(0.0f,0.1f),glm::vec2(1.0f,0.1f),
	glm::vec2(0.0f,1.0f),glm::vec2(1.0f,0.1f),glm::vec2(1.0f,1.0f),
};
GLvoid BackGround::InitBuffer() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(2, VBO);
	LoadTexture(texture, "resource/BackGround/forest_background.png");
}
GLvoid BackGround::Draw(){
	glUseProgram(Gets_program_screen());
	glDisable(GL_DEPTH_TEST);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(background_texture_pos), background_texture_pos, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);



	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(background_screen_pos), background_screen_pos, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	int tLocation = glGetUniformLocation(Gets_program_screen(), "outTexture11"); //--- outTexture1 À¯´ÏÆû »ùÇÃ·¯ÀÇ À§Ä¡¸¦ °¡Á®¿È
	glActiveTexture(texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(tLocation, 0);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(background_screen_pos) / sizeof(background_screen_pos[0]));

	glEnable(GL_DEPTH_TEST);
	glUseProgram(Gets_program_texture());
}