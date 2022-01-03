#pragma once

#include <Core/Engine.h>

#include "Transform3D.h"
#include "Globals.h"
#include "Colors.h"

#define BASE_OBJECT_GRAVITATIONAL_ACCELERATION (50.0f)
#define BASE_OBJECT_DECAY_LENGTH (2.0f)

#define BASE_OBJECT_MATERIAL_KD (0.5f)
#define BASE_OBJECT_MATERIAL_KS (0.5f)
#define BASE_OBJECT_MATERIAL_SHININESS (30)

class BaseObject {

protected:
	glm::vec3 position = glm::vec3(0);
	glm::vec3 rotation = glm::vec3(0);
	glm::vec3 scale = glm::vec3(1);
	glm::vec3 velocity = glm::vec3(0);

	enum class ObjectState { ALIVE, DECAYING, DEAD };

	ObjectState objState = ObjectState::ALIVE;

	float decayTime = 0;

	BaseObject();
	~BaseObject();

	virtual void UpdateTrajectory(double deltaTimeSeconds);
	virtual void UpdateAlive(double deltaTimeSeconds);
	virtual void UpdateDecay(double deltaTimeSeconds);

	virtual float GetGravitationalAcceleration();
	virtual float GetDecayLength();

public:
	void Update(double deltaTimeSeconds);

	virtual std::vector<std::string> GetModels();
	virtual	std::string GetTexture();
	virtual std::vector<BaseObject*> GetObjectsToRender();

	virtual void StartDecay();
	virtual bool IsHudElement();
	virtual bool IsInBounds();

	virtual float GetMaterialKd();
	virtual float GetMaterialKs();
	virtual int GetMaterialShininess();

	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();
	glm::vec3 GetVelocity();
	glm::mat4 GetModelMatrix();

	bool IsAlive();
	bool IsDecaying();
	bool IsDead();

};