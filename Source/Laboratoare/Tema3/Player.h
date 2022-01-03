#pragma once

#include "BaseObject.h"
#include "SettingsStore.h"
#include "FuelIndicatorBackground.h"
#include "FuelIndicatorForeground.h"
#include "CarChassisModel.h"
#include "PlayerWheel.h"
#include "LightData.h"
#include "MathUtils.h"

#define PLAYER_ACCELERATION (20.f)
#define PLAYER_DECELERATION (40.f)
#define PLAYER_BASE_DECELERATION (5.f)

#define PLAYER_JUMP_STRENGTH (25.f)
#define PLAYER_LATERAL_SPEED (10.f)

#define PLAYER_OVERDRIVE_MULTIPLIER (1.5f)
#define PLAYER_MAX_FUEL_AMOUNT		(1000.f)
#define PLAYER_BOUND_MIN_Y			(-100.f)

#define PLAYER_INITIAL_LIFE_POINTS	(3)

#define PLAYER_HEADLIGHT_ANGLE		(M_PI / 10.f)
#define PLAYER_HEADLIGHT_COLOR		(COLOR_WHITE)
#define PLAYER_HEADLIGHT_CUTOFF		(M_PI / 3.f)
#define PLAYER_HEADLIGHT_INTENSITY	(3.f)

#define PLAYER_HEADLIGHT_INVULNERABLE_COLOR				(COLOR_BLUE)
#define PLAYER_HEADLIGHT_INVULNERABLE_COLOR_STEP		(0.01f)
#define PLAYER_HEADLIGHT_INVULNERABLE_CUTOFF			(M_PI)
#define PLAYER_HEADLIGHT_INVULNERABLE_CUTOFF_STEP		(PLAYER_HEADLIGHT_INVULNERABLE_CUTOFF / 50.f)
#define PLAYER_HEADLIGHT_INVULNERABLE_INTENSITY			(9.f)
#define PLAYER_HEADLIGHT_INVULNERABLE_INTENSITY_STEP	(PLAYER_HEADLIGHT_INTENSITY / 50.f)

#define PLAYER_FAKE_HEADLIGHT_INTENSITY (0.15f)

#define PLAYER_BRAKELIGHT_COLOR			(COLOR_RED)
#define PLAYER_BRAKELIGHT_INTENSITY		(0.5f)

#define PLAYER_BRAKELIGHT_BRAKE_INTENSITY		(1.f)
#define PLAYER_BRAKELIGHT_BRAKE_INTENSITY_STEP	(PLAYER_BRAKELIGHT_INTENSITY / 5.f)

#define PLAYER_BRAKELIGHT_OVERDRIVE_INTENSITY		(0.f)
#define PLAYER_BRAKELIGHT_OVERDRIVE_INTENSITY_STEP	(PLAYER_BRAKELIGHT_INTENSITY / 50.f)


#define PLAYER_MODEL	(CAR_CHASSIS_MODEL)
#define PLAYER_TEXTURE	(CAR_CHASSIS_TEXTURE)

#define PLAYER_SCALE_X (1.f)
#define PLAYER_SCALE_Y (1.f)
#define PLAYER_SCALE_Z (1.f)

class Player : public BaseObject {

private:
	enum class PowerUpEffect { NONE, OVERDRIVE, INVULNERABLE };
	enum class PlayerState { STATIONARY, GROUND, AIR };

	PowerUpEffect powerUp = PowerUpEffect::NONE;
	PlayerState state = PlayerState::GROUND;

	// this field is used for game logic; it moves the platforms, not the player
	float speed = 0;
	float powerUpTimer = 0;
	float fuel = PLAYER_MAX_FUEL_AMOUNT;

	bool isSupported = false;

	int lifePoints = PLAYER_INITIAL_LIFE_POINTS;

	float minSpeed = 0;
	float maxSpeed = 0;
	float fuelConsumptionIdle = 0;
	float fuelConsumptionAcceleration = 0;

	float currentHeaglightIntensity = 0;
	float targetHeadlightIntensity = PLAYER_HEADLIGHT_INTENSITY;

	float currentHeadlightCutoff = 0;
	float targetHeadlightCutoff = PLAYER_HEADLIGHT_CUTOFF;

	glm::vec3 currentHeadlightColor = PLAYER_HEADLIGHT_COLOR;
	glm::vec3 targetHeadlightColor = PLAYER_HEADLIGHT_COLOR;

	MathUtils::FloatMapping fakeHeadlightIntensity = MathUtils::MapLinear(
		0, 
		PLAYER_HEADLIGHT_INTENSITY,
		0, 
		PLAYER_FAKE_HEADLIGHT_INTENSITY
	);

	bool braking = false;
	float currentBrakelightIntensity = 0;
	float targetBrakelightIntensity = PLAYER_BRAKELIGHT_INTENSITY;
	float brakelightIntensityStep = PLAYER_BRAKELIGHT_OVERDRIVE_INTENSITY_STEP;

	PlayerWheel* frontLeftWheel = new PlayerWheel(false);
	PlayerWheel* frontRightWheel = new PlayerWheel(true);
	PlayerWheel* rearLeftWheel = new PlayerWheel(false);
	PlayerWheel* rearRightWheel = new PlayerWheel(true);

	void UpdateIdle(double deltaTimeSeconds);
	void UpdatePowerUpTimer(double deltaTimeSeconds);
	void UpdateWheelRotations(double deltaTimeSeconds);
	void UpdateHeadlightColor(double deltaTimeSeconds);
	void UpdateHeadlightCutoff(double deltaTimeSeconds);
	void UpdateHeadlightIntensity(double deltaTimeSeconds);
	void UpdateBrakelightIntensity(double deltaTimeSeconds);
	void UpdateWheelPositions();

	void IncreaseSpeed(float amount);
	void DecreaseSpeed(float amount);
	void ApplyBaseDeceleration(double deltaTimeSeconds);

	bool Protect();
	void TestFall();
	float ComputeMaxSpeed();

protected:
	void UpdateTrajectory(double deltaTimeSeconds) override;
	void UpdateAlive(double deltaTimeSeconds) override;
	void UpdateDecay(double deltaTimeSeconds) override;

public:
	Player(glm::vec3 position);
	~Player();

	std::vector<std::string> GetModels() override;
	std::string GetTexture() override;
	std::vector<BaseObject*> GetObjectsToRender() override;
	void StartDecay() override;
	bool IsInBounds() override;

	void Accelerate(double deltaTime);
	void Decelerate(double deltaTime, bool applyBrakes);
	void MoveLeft(double deltaTime);
	void MoveRight(double deltaTime);
	void Jump();
	void Land();

	void Refuel(float amount);
	void LoseFuel(float amount);
	void ApplyOverdrivePowerUp(float time);
	void ApplyInvulnerablePowerUp(float time);
	void LoseLifePoint();

	void SetSupported(bool value);
	void FreeFall();

	void LoadSettings(std::string difficulty);

	std::vector<LightData> GetLightDatas();
	float GetFuel();
	float GetSpeed();
	float GetMinSpeed();
	float GetMaxSpeed();
	int GetLifePoints();

	bool IsOnGround();

};