#include "EndGamePlatform.h"

EndGamePlatform::EndGamePlatform(glm::vec3& position)
	: BasePlatform(position) {

}

EndGamePlatform::~EndGamePlatform() {

}

void EndGamePlatform::ApplySpecialEffect(Player* player) {
	player->LoseLifePoint();
}

std::string EndGamePlatform::GetSpecialTexture() {
	return END_GAME_PLATFORM_TEXTURE;
}