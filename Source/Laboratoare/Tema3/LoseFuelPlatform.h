#pragma once

#include "BasePlatform.h"

#define LOSE_FUEL_PLATFORM_TEXTURE ("texture.platform.lose_fuel")

#define LOSE_FUEL_PLATFORM_AMOUNT	(100.f)

class LoseFuelPlatform : public BasePlatform {

protected:
	virtual std::string GetSpecialTexture() override;
	virtual void ApplySpecialEffect(Player* player) override;

public:
	LoseFuelPlatform(glm::vec3& position);
	~LoseFuelPlatform();

};