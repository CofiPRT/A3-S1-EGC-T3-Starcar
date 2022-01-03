#include "Obamium.h"

Obamium::Obamium(glm::vec3 position, bool isRight) {
	this->position = position;
	this->scale = glm::vec3(OBAMIUM_SCALE_X, OBAMIUM_SCALE_Y, OBAMIUM_SCALE_Z);
	this->isRight = isRight;
}

Obamium::~Obamium() {

}

void Obamium::UpdateAlive(double deltaTimeSeconds) {
	UpdateTrajectory(deltaTimeSeconds);

	this->rotation += glm::vec3(0, deltaTimeSeconds * OBAMIUM_ROTATION_SPEED * (isRight ? -1.f : 1.f), 0);
}

float Obamium::GetGravitationalAcceleration() {
	return 0;
}

bool Obamium::IsInBounds() {
	return position.z > -PLATFORM_LENGTH;
}

void Obamium::SetSpeed(float speed) {
	this->velocity = -AXIS_OZ * speed;
}

std::vector<LightData> Obamium::GetLightDatas() {
	glm::vec3 lightPosition = position + glm::vec3(0, scale.y, 0);
	LightData obamiumLightData = LightData(lightPosition, glm::vec3(0), OBAMIUM_LIGHT_COLOR, 0, OBAMIUM_LIGHT_INTENSITY, false);

	return { obamiumLightData };
}

std::vector<std::string> Obamium::GetModels() {
	return { OBAMIUM_MODEL };
}

std::string Obamium::GetTexture() {
	return OBAMIUM_TEXTURE;
}