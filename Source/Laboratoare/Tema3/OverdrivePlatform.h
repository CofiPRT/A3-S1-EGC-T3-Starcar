#pragma once

#include "BasePlatform.h"

#define OVERDRIVE_PLATFORM_TEXTURE ("texture.platform.overdrive")

#define OVERDRIVE_PLATFORM_TIMER (5.f)

class OverdrivePlatform : public BasePlatform {

protected:
	virtual std::string GetSpecialTexture() override;
	virtual void ApplySpecialEffect(Player* player) override;

public:
	OverdrivePlatform(glm::vec3& position);
	~OverdrivePlatform();

};