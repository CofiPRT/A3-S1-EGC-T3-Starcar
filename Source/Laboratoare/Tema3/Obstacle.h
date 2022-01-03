#pragma once

#include "BaseObject.h"
#include "LightData.h"
#include "BasePlatform.h"
#include "CubeModel.h"

#define OBSTACLE_TEXTURE	("texture.obstacle")
#define OBSTACLE_MODEL		(CUBE_MODEL_NAME)

#define OBSTACLE_SCALE_X (PLATFORM_WIDTH / 2)
#define OBSTACLE_SCALE_Y (1.5f)
#define OBSTACLE_SCALE_Z (0.5f)

class Obstacle : public BaseObject {
protected:
	void UpdateAlive(double deltaTimeSeconds) override;
	float GetGravitationalAcceleration() override;
	bool IsInBounds() override;

public:
	Obstacle(glm::vec3 position);
	~Obstacle();

	void Launch(glm::vec3 velocity);
	void SetSpeed(float speed);

	bool TestCollision(Player* player);

	std::vector<std::string> GetModels() override;
	std::string GetTexture() override;
};