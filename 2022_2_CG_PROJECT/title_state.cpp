#include "title_state.h"

namespace Title {
	GLvoid enter() {
		std::cout << "enter - title" << std::endl;
	}

	GLvoid exit() {
		std::cout << "exit - title" << std::endl;
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

	}
	GLvoid key_down(unsigned char key, int x, int y) {

	}

	GLvoid key_up(unsigned char key, int x, int y) {

	}
}