#include "BasePlatform.h"

BasePlatform::BasePlatform(glm::vec3& position) {
	this->position = position;
	this->scale = glm::vec3(PLATFORM_WIDTH/2, PLATFORM_HEIGHT/2, PLATFORM_LENGTH/2);
}

BasePlatform::~BasePlatform() {}

void BasePlatform::PostIsBelow(Player* player) {

	if (!player->IsOnGround() || status == PlatformStatus::CLAIMED)
		return;

	status = PlatformStatus::CLAIMED;
	ApplySpecialEffect(player);

}

void BasePlatform::ApplySpecialEffect(Player* player) {

}

void BasePlatform::SetSpeed(float speed) {
	this->velocity = -AXIS_OZ * speed;
}

std::vector<std::string> BasePlatform::GetModels() {
	return { BASE_PLATFORM_MODEL };
}

std::string BasePlatform::GetSpecialTexture() {
	return BASE_PLATFORM_TEXTURE;
}

std::string BasePlatform::GetTexture() {
	return status == PlatformStatus::CLAIMED ? BASE_PLATFORM_TEXTURE : GetSpecialTexture();
}

bool BasePlatform::IsBelow(Player* player) {

	// the player is a sphere
	glm::vec3 minimums = position - scale;
	glm::vec3 maximums = position + scale;

	glm::vec3 playerPos = player->GetPosition();
	bool inBoundsX = playerPos.x >= minimums.x && playerPos.x <= maximums.x;
	bool inBoundsY = playerPos.y - PLAYER_WHEEL_RANGE >= maximums.y / 2;
	bool inBoundsZ = playerPos.z >= minimums.z && playerPos.z <= maximums.z;

	bool result = inBoundsX && inBoundsY && inBoundsZ;
	if (result)
		PostIsBelow(player);

	return result;

}

void BasePlatform::UpdateAlive(double deltaTimeSeconds) {
	UpdateTrajectory(deltaTimeSeconds);
}

float BasePlatform::GetGravitationalAcceleration() {
	return 0;
}

bool BasePlatform::IsInBounds() {
	return position.z > -PLATFORM_LENGTH;
}
