#include "ImageManager.h"

void LoadTexture(GLuint& texture, const char* img_name) {
	stbi_set_flip_vertically_on_load(true);
	int w, h, channel;
	glGenTextures(1, &texture); //--- �ؽ�ó ����
	glBindTexture(GL_TEXTURE_2D, texture); //--- �ؽ�ó ���ε�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //--- ���� ���ε��� �ؽ�ó�� �Ķ���� �����ϱ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 

	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ZERO, GL_ONE);
	unsigned char* data = stbi_load(img_name, &w, &h, &channel, 4); //--- �ؽ�ó�� ����� ��Ʈ�� �̹��� �ε��ϱ�
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //---�ؽ�ó �̹��� ����	https://stackoverflow.com/questions/72057406/access-violation-in-nvoglv64-dll-when-using-opengl ���� ���� ����
	stbi_image_free(data);
}