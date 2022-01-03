#pragma once

#include "Player.h"

#include "PlatformModel.h"

#define PLATFORM_HEIGHT		(1.f)
#define PLATFORM_WIDTH		(5.0f)
#define PLATFORM_LENGTH		(50.f)

#define BASE_PLATFORM_TEXTURE ("texture.platform.base")
#define BASE_PLATFORM_MODEL (PLATFORM_MODEL_NAME)

class BasePlatform : public BaseObject {

protected:
	enum class PlatformStatus { UNCLAIMED, CLAIMED };

	PlatformStatus status = PlatformStatus::UNCLAIMED;

	virtual std::string GetSpecialTexture();
	virtual void ApplySpecialEffect(Player* player);

	void UpdateAlive(double deltaTimeSeconds) override;
	float GetGravitationalAcceleration() override;
	bool IsInBounds() override;

	virtual void PostIsBelow(Player* player);

public:
	BasePlatform(glm::vec3& position);
	~BasePlatform();

	std::vector<std::string> GetModels() override;
	std::string GetTexture() override;

	void SetSpeed(float speed);
	bool IsBelow(Player* player);

};