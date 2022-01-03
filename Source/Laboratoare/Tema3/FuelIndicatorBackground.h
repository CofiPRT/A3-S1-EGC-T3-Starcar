#pragma once

#include "BaseFuelIndicator.h"

#define INDICATOR_BACKGROUND_TEXTURE ("texture.fuel_indicator.background")

class FuelIndicatorBackground : public BaseFuelIndicator {

public:
	std::string GetTexture() override;

};