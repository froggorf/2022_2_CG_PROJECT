#include "ImageManager.h"

void LoadTexture(GLuint& texture, const char* img_name) {
	stbi_set_flip_vertically_on_load(true);
	int w, h, channel;
	glGenTextures(1, &texture); //--- 텍스처 생성
	glBindTexture(GL_TEXTURE_2D, texture); //--- 텍스처 바인딩
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- 현재 바인딩된 텍스처의 파라미터 설정하기
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE);
	unsigned char* data = stbi_load(img_name, &w, &h, &channel, 4); //--- 텍스처로 사용할 비트맵 이미지 로드하기
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //---텍스처 이미지 정의	https://stackoverflow.com/questions/72057406/access-violation-in-nvoglv64-dll-when-using-opengl 에서 오류 수정
	stbi_image_free(data);
}