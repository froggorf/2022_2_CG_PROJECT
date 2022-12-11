#include "game_framework.h"
#include "logo_state.h"
#include "title_state.h"
#include "play_state.h"
#include "select_stage_state.h"
#include "gameover_state.h"
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
	key_down = nullptr;
	key_up = nullptr;

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
		key_down = Logo::key_down;
		key_up = Logo::key_up;
		break;
	case GameStateType::TITLE:
		enter = Title::enter;
		exit = Title::exit;
		pause = Title::pause;
		resume = Title::resume;
		handle_events = Title::handle_events;
		update = Title::update;
		draw = Title::draw;
		key_down = Title::key_down;
		key_up = Title::key_up;
		break;
	case GameStateType::PLAY:
		enter = Play::enter;
		exit = Play::exit;
		pause = Play::pause;
		resume = Play::resume;
		handle_events = Play::handle_events;
		update = Play::update;
		draw = Play::draw;
		key_down = Play::key_down;
		key_up = Play::key_up;
		break;
	case GameStateType::CHANGEDIMENSION:
		enter = ChangeDimension::enter;
		exit = ChangeDimension::exit;
		pause = ChangeDimension::pause;
		resume = ChangeDimension::resume;
		handle_events = ChangeDimension::handle_events;
		update = ChangeDimension::update;
		draw = ChangeDimension::draw;
		key_down = ChangeDimension::key_down;
		key_up = ChangeDimension::key_up;
		break;
	case GameStateType::SELECTSTAGE:
		enter = SelectStage::enter;
		exit = SelectStage::exit;
		pause = SelectStage::pause;
		resume = SelectStage::resume;
		handle_events = SelectStage::handle_events;
		update = SelectStage::update;
		draw = SelectStage::draw;
		key_down = SelectStage::key_down;
		key_up = SelectStage::key_up;
		break;
	case GameStateType::GAMEOVER:
		enter = GameOver::enter;
		exit = GameOver::exit;
		pause = GameOver::pause;
		resume = GameOver::resume;
		handle_events = GameOver::handle_events;
		update = GameOver::update;
		draw = GameOver::draw;
		key_down = GameOver::key_down;
		key_up = GameOver::key_up;
		break;
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