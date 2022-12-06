#include "MainGame.h"

//freeglut.lib glew32.lib

int TimerSpeed = 16;
GLuint vertexShader;
GLuint fragmentShader;
GLuint vs_texture;
GLuint fs_texture;
GLuint s_program;
GLuint s_program_texture;

int main(int argc, char** argv) //--- 윈도우 출력하고 콜백함수 설정 
{ //--- 윈도우 생성하기
	glutInit(&argc, argv); // glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(300, 200);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Example1");
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	glEnable(GL_DEPTH_TEST);


	InitShader();

	glutDisplayFunc(drawScene); // 출력 함수의 지정
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정
	glutKeyboardFunc(KeyBoard);
	glutKeyboardUpFunc(KeyBoardUp);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMove);
	glutSpecialFunc(SpecialKeyboard);
	glutSpecialUpFunc(SpecialKeyUp);

	game_framework_running(GameStateType::PLAY);
	glutTimerFunc(TimerSpeed, MainTimer, 0);

	glutMainLoop(); // 이벤트 처리 시작 

}

GLvoid MainTimer(int value) {
	if (GetRunning()) {
		//state[now].handle_events();
		GetGameState()[GetNow()].update();



	}
	else {
		exit(0);
		return;
	}
	glutTimerFunc(TimerSpeed, MainTimer, value);
	glutPostRedisplay();
}

GLvoid drawScene() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GetGameState()[GetNow()].draw();

	glutSwapBuffers(); // 화면에 출력하기
}

GLvoid KeyBoard(unsigned char key, int x, int y) {
	
	if (key == GLUT_KEY_UP) return;
	switch (key) {
	case 'Q':
	case 'q':
		quit();
		exit(0);
		break;
	
	case '1':
		//GetKeyDown()[press1] = true;
		change_state(GameStateType::LOGO);
		break;
	case '2':
		//GetKeyDown()[press2] = true;
		change_state(GameStateType::TITLE);
		break;
	case '3':
		//GetKeyDown()[press3] = true;
		change_state(GameStateType::PLAY);
		break;
	case '4':
		GetKeyDown()[press4] = true;
		break;
	case '5':
		GetKeyDown()[press5] = true;
		break;
	case '6':
		GetKeyDown()[press6] = true;
		break;
	case '7':
		GetKeyDown()[press7] = true;
		break;
	case '8':
		GetKeyDown()[press8] = true;
		break;
	case '9':
		GetKeyDown()[press9] = true;
		break;
	case '0':
		GetKeyDown()[press0] = true;
		break;
	case 'w':
		GetKeyDown()[pressW] = true;
		break;
	case 'a':
		GetKeyDown()[pressA] = true;
		break;
	case 's':
		GetKeyDown()[pressS] = true;
		break;
	case 'd':
		GetKeyDown()[pressD] = true;
		break;
	case ' ':
		GetKeyDown()[pressSPACE] = true;
		break;
	}
	glutPostRedisplay();
}
GLvoid KeyBoardUp(unsigned char key, int x, int y) {
	switch (key) {
	case '1':
		GetKeyDown()[press1] = false;
		break;
	case '2':
		GetKeyDown()[press2] = false;
		break;
	case '3':
		GetKeyDown()[press3] = false;
		break;
	case '4':
		GetKeyDown()[press4] = false;
		break;
	case '5':
		GetKeyDown()[press5] = false;
		break;
	case '6':
		GetKeyDown()[press6] = false;
		break;
	case '7':
		GetKeyDown()[press7] = false;
		break;
	case '8':
		GetKeyDown()[press8] = false;
		break;
	case '9':
		GetKeyDown()[press9] = false;
		break;
	case '0':
		GetKeyDown()[press0] = false;
		break;
	case 'w':
		GetKeyDown()[pressW] = false;
		break;
	case 'a':
		GetKeyDown()[pressA] = false;
		break;
	case 's':
		GetKeyDown()[pressS] = false;
		break;
	case 'd':
		GetKeyDown()[pressD] = false;
		break;
	case ' ':
		GetKeyDown()[pressSPACE] = false;
		break;
	}
}

GLvoid SpecialKeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		GetKeyDown()[pressLEFT] = true;
		break;
	case GLUT_KEY_RIGHT:
		GetKeyDown()[pressRIGHT] = true;
		break;
	case GLUT_KEY_UP:
		GetKeyDown()[pressUP] = true;
		break;
	case GLUT_KEY_DOWN:
		GetKeyDown()[pressDOWN] = true;
		break;
	}
}

GLvoid SpecialKeyUp(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		GetKeyDown()[pressLEFT] = false;
		break;
	case GLUT_KEY_RIGHT:
		GetKeyDown()[pressRIGHT] = false;
		break;
	case GLUT_KEY_UP:
		GetKeyDown()[pressUP] = false;
		break;
	case GLUT_KEY_DOWN:
		GetKeyDown()[pressDOWN] = false;
		break;
	}
}

GLvoid Mouse(int button, int state, int x, int y) {
	//button - GLUT_LEFT_BUTTON / MIDDLE / RIGHT ...
	//state - GLUT_UP, GLUT_DOWN
	glutPostRedisplay();
}

GLvoid MouseMove(int x, int y) {

	glutPostRedisplay();
}

GLvoid Reshape(int w, int h) //--- 콜백 함수: 다시 그리기 콜백 함수 
{
	glViewport(0, 0, w, h);
}
void make_vertexShaders() {
	{//일반 쉐이더
		GLchar* vertexsource;

		vertexsource = filetobuf("vertex.glsl");
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexsource, NULL);
		glCompileShader(vertexShader);

		GLint result;
		GLchar errorlog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
		if (!result) {
			glGetShaderInfoLog(vertexShader, 512, NULL, errorlog);
			std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorlog << std::endl;
			return;
		}
	}
	

	{
		GLchar* vertexsource;

		vertexsource = filetobuf("vertex.glsl");
		vs_texture = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs_texture, 1, &vertexsource, NULL);
		glCompileShader(vs_texture);

		GLint result;
		GLchar errorlog[512];
		glGetShaderiv(vs_texture, GL_COMPILE_STATUS, &result);
		if (!result) {
			glGetShaderInfoLog(vs_texture, 512, NULL, errorlog);
			std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorlog << std::endl;
			return;
		}
	}
}
void make_fragmentShaders() {
	{
		GLchar* fragmentsource;

		fragmentsource = filetobuf("fragment.glsl");
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentsource, NULL);
		glCompileShader(fragmentShader);

		GLint result;
		GLchar errorlog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
		if (!result) {
			glGetShaderInfoLog(fragmentShader, 512, NULL, errorlog);
			std::cerr << "ERROR: fragment shader 컴파일 실패\n" << errorlog << std::endl;
			return;
		}
	}
	
	{
		GLchar* fragmentsource;

		fragmentsource = filetobuf("fragment_texture.glsl");
		fs_texture = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs_texture, 1, &fragmentsource, NULL);
		glCompileShader(fs_texture);

		GLint result;
		GLchar errorlog[512];
		glGetShaderiv(fs_texture, GL_COMPILE_STATUS, &result);
		if (!result) {
			glGetShaderInfoLog(fs_texture, 512, NULL, errorlog);
			std::cerr << "ERROR: fragment_texture shader 컴파일 실패\n" << errorlog << std::endl;
			return;
		}
	}

}
GLvoid InitShader() {
	make_vertexShaders();
	make_fragmentShaders();
	{
		s_program = glCreateProgram();

		glAttachShader(s_program, vertexShader);
		glAttachShader(s_program, fragmentShader);
		glLinkProgram(s_program);

		checkCompileErrors(s_program, "PROGRAM");

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

	}
	
	{
		s_program_texture = glCreateProgram();
		glAttachShader(s_program_texture, vs_texture);
		glAttachShader(s_program_texture, fs_texture);
		glLinkProgram(s_program_texture);
		checkCompileErrors(s_program_texture, "PROGRAM");
		glDeleteShader(vs_texture);
		glDeleteShader(fs_texture);
	}

	glUseProgram(s_program);
	glUseProgram(s_program_texture);
}
void checkCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading
	if (!fptr) // Return NULL on failure
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file
	length = ftell(fptr); // Find out how many bytes into the file we are
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer
	fclose(fptr); // Close the file
	buf[length] = 0; // Null terminator
	return buf; // Return the buffer
}
GLuint Gets_program() {
	return s_program;
}

GLuint Gets_program_texture() {
	return s_program_texture;
}