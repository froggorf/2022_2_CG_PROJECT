#include "particle.h"

Particle::Particle() {
};
Particle::Particle(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate) {
};
Particle::Particle(glm::vec3 scale, glm::vec3 trans, glm::vec3 rotate, GLboolean isOnGround) {
};
Particle::~Particle() {
};


GLvoid Particle::Init() {
}
GLvoid Particle::InitBuffer() {
}

GLvoid Particle::update() {
}

GLvoid Particle::collision_handling(Cube* other) {
}

GLvoid Particle::draw() {
}