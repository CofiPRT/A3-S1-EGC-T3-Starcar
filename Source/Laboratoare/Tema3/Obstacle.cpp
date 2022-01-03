#include "Obstacle.h"

Obstacle::Obstacle(glm::vec3 position) {
	this->position = position;
	this->scale = glm::vec3(OBSTACLE_SCALE_X, OBSTACLE_SCALE_Y, OBSTACLE_SCALE_Z);
}

Obstacle::~Obstacle() {

}

void Obstacle::UpdateAlive(double deltaTimeSeconds) {
	UpdateTrajectory(deltaTimeSeconds);
}

float Obstacle::GetGravitationalAcceleration() {
	return IsAlive() ? 0 : BaseObject::GetGravitationalAcceleration();
}

bool Obstacle::IsInBounds() {
	return position.z > -PLATFORM_LENGTH;
}

void Obstacle::Launch(glm::vec3 velocity) {
	this->velocity = velocity;
}

void Obstacle::SetSpeed(float speed) {
	this->velocity = -AXIS_OZ * speed;
}

bool Obstacle::TestCollision(Player* player) {
	
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

std::vector<std::string> Obstacle::GetModels() {
	return { OBSTACLE_MODEL };
}

std::string Obstacle::GetTexture() {
	return OBSTACLE_TEXTURE;
}