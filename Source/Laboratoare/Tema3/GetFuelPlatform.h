#pragma once

#include "BasePlatform.h"

#define GET_FUEL_PLATFORM_TEXTURE ("texture.platform.get_fuel")

#define GET_FUEL_PLATFORM_AMOUNT	(250.f)

class GetFuelPlatform : public BasePlatform {

protected:
	virtual std::string GetSpecialTexture() override;
	virtual void ApplySpecialEffect(Player* player) override;

public:
	GetFuelPlatform(glm::vec3& position);
	~GetFuelPlatform();

};