#pragma once

#include <Core/Engine.h>

class LightData {
private:
	glm::vec3 lightPosition;
	glm::vec3 lightDirection;
	glm::vec3 lightColor;
	float lightCutoff;
	float lightIntensity;
	bool lightType;

public:
	LightData(
		glm::vec3 lightPosition_,
		glm::vec3 lightDirection_,
		glm::vec3 lightColor_,
		float lightCutoff_,
		float lightIntensity_,
		bool lightType_)

		: lightPosition(lightPosition_),
		lightDirection(lightDirection_),
		lightColor(lightColor_),
		lightCutoff(lightCutoff_),
		lightIntensity(lightIntensity_),
		lightType(lightType_) {

	}

	glm::vec3 GetLightPosition() {
		return lightPosition;
	}

	glm::vec3 GetLightDirection() {
		return lightDirection;
	}

	glm::vec3 GetLightColor() {
		return lightColor;
	}

	float GetLightCutoff() {
		return lightCutoff;
	}

	float GetLightIntensity() {
		return lightIntensity;
	}

	bool GetLightType() {
		return lightType;
	}
};