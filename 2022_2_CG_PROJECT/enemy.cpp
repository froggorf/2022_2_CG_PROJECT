#include "enemy.h"

Enemy::Enemy() {
};
Enemy::Enemy(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate) {
};
Enemy::~Enemy() {
};


GLvoid Enemy::Init() {

}
GLvoid Enemy::InitBuffer() {
}

GLvoid Enemy::update() {
	if (++frame > 110) frame = 0;
}

GLvoid Enemy::draw() {
}