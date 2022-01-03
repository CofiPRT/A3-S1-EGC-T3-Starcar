#include "BaseFuelIndicator.h"

BaseFuelIndicator::BaseFuelIndicator() {
	this->position = glm::vec3(INDICATOR_POS_X, INDICATOR_POS_Y, INDICATOR_POS_Z);
	this->scale = glm::vec3(INDICATOR_WIDTH / 2, INDICATOR_HEIGHT / 2, INDICATOR_LENGTH / 2);
}

BaseFuelIndicator::~BaseFuelIndicator() {
	
}

std::vector<std::string> BaseFuelIndicator::GetModels() {
	return { FUEL_INDICATOR_MODEL };
}
