#pragma once

#include "BasePlatform.h"

#define END_GAME_PLATFORM_TEXTURE ("texture.platform.end_game")

class EndGamePlatform : public BasePlatform {

protected:
	virtual std::string GetSpecialTexture() override;
	virtual void ApplySpecialEffect(Player* player) override;

public:
	EndGamePlatform(glm::vec3& position);
	~EndGamePlatform();

};