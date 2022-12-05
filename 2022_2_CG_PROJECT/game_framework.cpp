#include "game_framework.h"
#include "logo_state.h"
#include "title_state.h"
#include "play_state.h"
//TODO: #include "item_state.h"
bool running = true;
GameState state[4];
int now = -1;

GLvoid change_state(int state_type) {
	if (now > -1) {
		state[now].exit();
		state[now].init();
		--now;
	}
	++now;
	state[now].setting(state_type);
	state[now].enter();
}

GLvoid push_state(int state_type) {
	if (now > -1) {
		state[now].pause();
	}
	++now;
	state[now].setting(state_type);
	state[now].enter();
}

GLvoid pop_state() {
	if (now > -1) {
		state[now].exit();
		state[now].init();
		--now;
	}
	if (now > -1) {
		state[now].resume();
	}
}

GLvoid quit() {
	running = false;

	while (now > -1) {
		state[now].exit();
		state[now].init();
		--now;
	}

}

GLvoid game_framework_running(int state_type) {
	running = true;
	++now;
	state[now].setting(state_type);
	state[now].enter();


}

GLvoid GameState::init() {
	state_type = NULL;
	enter = nullptr;
	exit = nullptr;
	pause = nullptr;
	resume = nullptr;
	handle_events = nullptr;
	update = nullptr;
	draw = nullptr;
}
GLvoid GameState::setting(int g_state_type) {
	state_type = g_state_type;
	switch (g_state_type) {
	case GameStateType::LOGO:
		enter = Logo::enter;
		exit = Logo::exit;
		pause = Logo::pause;
		resume = Logo::resume;
		handle_events = Logo::handle_events;
		update = Logo::update;
		draw = Logo::draw;
		break;
	case GameStateType::TITLE:
		enter = Title::enter;
		exit = Title::exit;
		pause = Title::pause;
		resume = Title::resume;
		handle_events = Title::handle_events;
		update = Title::update;
		draw = Title::draw;
		break;
	case GameStateType::PLAY:
		enter = Play::enter;
		exit = Play::exit;
		pause = Play::pause;
		resume = Play::resume;
		handle_events = Play::handle_events;
		update = Play::update;
		draw = Play::draw;
		break;
	//TODO:
		/*
		case GameStateType::PLAY:
		enter = Item::enter;
		exit = Item::exit;
		pause = Item::pause;
		resume = Item::resume;
		handle_events = Item::handle_events;
		update = Item::update;
		draw = Item::draw;
		break;
		*/

	}
}

GameState* GetGameState() {
	return state;
}
GLboolean GetRunning() {
	return running;
}
GLint GetNow() {
	return now;
}