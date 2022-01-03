#pragma once

#include "BaseFuelIndicator.h"

#define INDICATOR_FOREGROUND_TEXTURE ("texture.fuel_indicator.foreground")

class FuelIndicatorForeground : public BaseFuelIndicator {

public:
	std::string GetTexture() override;

	void RevealAt(glm::vec3 position, float percentage);

};