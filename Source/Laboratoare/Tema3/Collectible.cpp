#include "Collectible.h"

Collectible::Collectible(glm::vec3 position) {
	this->position = position;
	this->scale = glm::vec3(COLLECTIBLE_SCALE_X, COLLECTIBLE_SCALE_Y, COLLECTIBLE_SCALE_Z);
}

Collectible::~Collectible() {

}

void Collectible::UpdateAlive(double deltaTimeSeconds) {
	UpdateTrajectory(deltaTimeSeconds);
	this->rotation += glm::vec3(deltaTimeSeconds);
}

float Collectible::GetGravitationalAcceleration() {
	return IsAlive() ? 0 : BaseObject::GetGravitationalAcceleration();
}

bool Collectible::IsInBounds() {
	return position.z > -PLATFORM_LENGTH;
}

void Collectible::Launch(glm::vec3 velocity) {
	this->velocity = velocity;
}

void Collectible::SetSpeed(float speed) {
	this->velocity = -AXIS_OZ * speed;
}

bool Collectible::TestCollision(Player* player) {
	
	if (!IsAlive())
		return false;

	// AABB vs AABB
	glm::vec3 obstacleMinimums = position - scale;
	glm::vec3 obstacleMaximums = position + scale;

	glm::vec3 playerPosition = player->GetPosition();
	glm::vec3 playerScale = player->GetScale();

	glm::vec3 playerMinimums = playerPosition - playerScale;
	glm::vec3 playerMaximums = playerPosition + playerScale;

	bool intersectX = obstacleMinimums.x <= playerMaximums.x && obstacleMaximums.x >= playerMinimums.x;
	bool intersectY = obstacleMinimums.y <= playerMaximums.y && obstacleMaximums.y >= playerMinimums.y;
	bool intersectZ = obstacleMinimums.z <= playerMaximums.z && obstacleMaximums.z >= playerMinimums.z;

	return intersectX && intersectY && intersectZ;
}

std::vector<std::string> Collectible::GetModels() {
	return { COLLECTIBLE_MODEL };
}

std::string Collectible::GetTexture() {
	return COLLECTIBLE_TEXTURE;
}