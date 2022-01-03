#include "FuelIndicatorForeground.h"

std::string FuelIndicatorForeground::GetTexture() {
	return INDICATOR_FOREGROUND_TEXTURE;
}

void FuelIndicatorForeground::RevealAt(glm::vec3 position, float percentage) {
	this->position = position + glm::vec3((percentage - 1) * INDICATOR_WIDTH / 2, 0, 0);
	this->scale = glm::vec3(percentage * INDICATOR_WIDTH / 2, INDICATOR_HEIGHT / 2, INDICATOR_LENGTH / 2);
}