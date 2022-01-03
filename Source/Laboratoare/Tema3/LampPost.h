#pragma once

#include "BaseObject.h"
#include "LightData.h"
#include "BasePlatform.h"
#include "LampPostModel.h"

#define LAMPPOST_TEXTURE ("texture.lamppost")

#define LAMPPOST_LIGHT_COLOR			(COLOR_ORANGE)
#define LAMPPOST_LIGHT_CUTOFF			(M_PI / 3.f)

#define LAMPPOST_SPOT_LIGHT_INTENSITY	(3.f)
#define LAMPPOST_SOURCE_LIGHT_INTENSITY	(1.f)

#define LAMPPOST_SCALE_X (2.f)
#define LAMPPOST_SCALE_Y (2.f)
#define LAMPPOST_SCALE_Z (2.f)

class LampPost : public BaseObject {
private:
	bool isRight = false;

protected:
	void UpdateAlive(double deltaTimeSeconds) override;
	float GetGravitationalAcceleration() override;
	bool IsInBounds() override;

public:
	LampPost(glm::vec3 position, bool isRight);
	~LampPost();

	void SetSpeed(float speed);

	std::vector<LightData> GetLightDatas();
	std::vector<std::string> GetModels() override;
	std::string GetTexture() override;
};