#pragma once

#include "BaseObject.h"
#include "LightData.h"
#include "BasePlatform.h"
#include "SquarePyramidModel.h"

#define OBAMIUM_TEXTURE ("texture.obamium")
#define OBAMIUM_MODEL	(SQUARE_PYRAMID_MODEL_NAME)

#define OBAMIUM_LIGHT_COLOR		(COLOR_ORANGE)
#define OBAMIUM_LIGHT_INTENSITY	(5.f)

#define OBAMIUM_SCALE_X (3.f)
#define OBAMIUM_SCALE_Y (10.f)
#define OBAMIUM_SCALE_Z (3.f)

#define OBAMIUM_ROTATION_SPEED (2.f)

class Obamium : public BaseObject {
private:
	bool isRight = false;

protected:
	void UpdateAlive(double deltaTimeSeconds) override;
	float GetGravitationalAcceleration() override;
	bool IsInBounds() override;

public:
	Obamium(glm::vec3 position, bool isRight);
	~Obamium();

	void SetSpeed(float speed);

	std::vector<LightData> GetLightDatas();
	std::vector<std::string> GetModels() override;
	std::string GetTexture() override;
};