#include "PlayerWheel.h"

PlayerWheel::PlayerWheel(bool isRight) {
	this->isRight = isRight;
	this->rotation = glm::vec3(0, 0, (isRight ? 1.f : -1.f) * M_PI_2);
	this->scale = glm::vec3(PLAYER_WHEEL_RANGE, PLAYER_WHEEL_WIDTH, PLAYER_WHEEL_RANGE);
}

PlayerWheel::~PlayerWheel() {

}

float PlayerWheel::GetGravitationalAcceleration() {
	return 0;
}

std::vector<std::string> PlayerWheel::GetModels() {
	return { PLAYER_WHEEL_MODEL_LEFT, PLAYER_WHEEL_MODEL_RIGHT, PLAYER_WHEEL_MODEL_OUTLINE };
}
std::string PlayerWheel::GetTexture() {
	return PLAYER_WHEEL_TEXTURE;
}

void PlayerWheel::SetPosition(glm::vec3 position) {
	this->position = position;
}

void PlayerWheel::Advance(float distance) {
	this->rotation += glm::vec3(distance / PLAYER_WHEEL_RANGE, 0, 0);
}