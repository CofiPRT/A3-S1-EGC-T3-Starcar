#pragma once

#include "BaseObject.h"
#include "CylinderModel.h"

#define PLAYER_WHEEL_RANGE (0.4f)
#define PLAYER_WHEEL_WIDTH (0.15f)

#define PLAYER_WHEEL_MODEL_LEFT		(CYLINDER_MODEL_TOP_NAME)
#define PLAYER_WHEEL_MODEL_RIGHT	(CYLINDER_MODEL_BOT_NAME)
#define PLAYER_WHEEL_MODEL_OUTLINE	(CYLINDER_MODEL_SIDE_NAME)
#define PLAYER_WHEEL_TEXTURE		("texture.car.wheel")

class PlayerWheel : public BaseObject {
private:
	bool isRight = false;

protected:
	float GetGravitationalAcceleration() override;

public:
	PlayerWheel(bool isRight);
	~PlayerWheel();

	std::vector<std::string> GetModels() override;
	std::string GetTexture() override;

	void SetPosition(glm::vec3 position);
	void Advance(float distance);
};