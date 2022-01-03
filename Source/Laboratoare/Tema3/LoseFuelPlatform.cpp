#include "LoseFuelPlatform.h"

LoseFuelPlatform::LoseFuelPlatform(glm::vec3& position)
	: BasePlatform(position) {

}

LoseFuelPlatform::~LoseFuelPlatform() {

}

void LoseFuelPlatform::ApplySpecialEffect(Player* player) {
	player->LoseFuel(LOSE_FUEL_PLATFORM_AMOUNT);
}

std::string LoseFuelPlatform::GetSpecialTexture() {
	return LOSE_FUEL_PLATFORM_TEXTURE;
}