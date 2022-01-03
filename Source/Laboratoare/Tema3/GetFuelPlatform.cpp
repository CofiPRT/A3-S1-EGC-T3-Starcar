#include "GetFuelPlatform.h"

GetFuelPlatform::GetFuelPlatform(glm::vec3& position)
	: BasePlatform(position) {

}

GetFuelPlatform::~GetFuelPlatform() {

}

void GetFuelPlatform::ApplySpecialEffect(Player* player) {
	player->Refuel(GET_FUEL_PLATFORM_AMOUNT);
}

std::string GetFuelPlatform::GetSpecialTexture() {
	return GET_FUEL_PLATFORM_TEXTURE;
}