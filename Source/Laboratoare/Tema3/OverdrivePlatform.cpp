#include "OverdrivePlatform.h"

OverdrivePlatform::OverdrivePlatform(glm::vec3& position)
	: BasePlatform(position) {

}

OverdrivePlatform::~OverdrivePlatform() {

}

void OverdrivePlatform::ApplySpecialEffect(Player* player) {
	player->ApplyOverdrivePowerUp(OVERDRIVE_PLATFORM_TIMER);
}

std::string OverdrivePlatform::GetSpecialTexture() {
	return OVERDRIVE_PLATFORM_TEXTURE;
}