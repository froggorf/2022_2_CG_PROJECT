#include "logo_state.h"

namespace Logo {
	GLvoid enter() {
		std::cout << "enter - Logo" << std::endl;


	}
	GLvoid exit() {
		std::cout << "exit - Logo" << std::endl;
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
	}

	GLvoid draw() {

	}

	GLvoid key_down(unsigned char, int, int) {

	}

	GLvoid key_up(unsigned char, int, int) {

	}
}