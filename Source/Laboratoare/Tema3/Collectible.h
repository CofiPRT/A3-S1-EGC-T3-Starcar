#pragma once

#include "BaseObject.h"
#include "LightData.h"
#include "BasePlatform.h"
#include "CubeModel.h"

#define COLLECTIBLE_TEXTURE	("texture.collectible")
#define COLLECTIBLE_MODEL	(CUBE_MODEL_NAME)

#define COLLECTIBLE_SCALE_X (0.5f)
#define COLLECTIBLE_SCALE_Y (0.5f)
#define COLLECTIBLE_SCALE_Z (0.5f)

#define COLLECTIBLE_HEIGHT (PLATFORM_HEIGHT)

#define COLLECTIBLE_ROTATION_SPEED (2.f)

class Collectible : public BaseObject {
protected:
	void UpdateAlive(double deltaTimeSeconds) override;
	float GetGravitationalAcceleration() override;
	bool IsInBounds() override;

public:
	Collectible(glm::vec3 position);
	~Collectible();

	void Launch(glm::vec3 velocity);
	void SetSpeed(float speed);

	bool TestCollision(Player* player);

	std::vector<std::string> GetModels() override;
	std::string GetTexture() override;
};