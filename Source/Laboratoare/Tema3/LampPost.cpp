#include "LampPost.h"

LampPost::LampPost(glm::vec3 position, bool isRight) {
	this->position = position;
	this->scale = glm::vec3(LAMPPOST_SCALE_X, LAMPPOST_SCALE_Y, LAMPPOST_SCALE_Z);
	this->rotation = glm::vec3(0, isRight ? 0 : M_PI, 0);
	this->isRight = isRight;
}

LampPost::~LampPost() {

}

void LampPost::UpdateAlive(double deltaTimeSeconds) {
	UpdateTrajectory(deltaTimeSeconds);
}

float LampPost::GetGravitationalAcceleration() {
	return 0;
}

bool LampPost::IsInBounds() {
	return position.z > -PLATFORM_LENGTH;
}

void LampPost::SetSpeed(float speed) {
	this->velocity = -AXIS_OZ * speed;
}

std::vector<LightData> LampPost::GetLightDatas() {
	glm::vec3 lightSpotPosition = position + LAMPPOST_MODEL_LIGHTBULB_POSITION * scale * glm::vec3(isRight ? 1.f : -1.f, 1.f, 1.f);
	LightData lamppostSpotLightData = LightData(lightSpotPosition, -AXIS_OY, LAMPPOST_LIGHT_COLOR, LAMPPOST_LIGHT_CUTOFF, LAMPPOST_SPOT_LIGHT_INTENSITY, true);

	glm::vec3 lightSourcePosition = position + LAMPPOST_MODEL_LIGHTBULB_POSITION * scale * glm::vec3(isRight ? 1.f : -1.f, 1.f, 1.f);
	LightData lamppostSourceLightData = LightData(lightSourcePosition, glm::vec3(0), LAMPPOST_LIGHT_COLOR, 0, LAMPPOST_SOURCE_LIGHT_INTENSITY, false);

	return { lamppostSpotLightData, lamppostSourceLightData };
}

std::vector<std::string> LampPost::GetModels() {
	return {
		LAMPPOST_MODEL_BASE_NAME,
		LAMPPOST_MODEL_HORIZONTAL_ROD_NAME,
		LAMPPOST_MODEL_VERTICAL_ROD_NAME,
		LAMPPOST_MODEL_LIGHTBULB_NAME
	};
}

std::string LampPost::GetTexture() {
	return LAMPPOST_TEXTURE;
}