#include "Player.h"
#include "BasePlatform.h"

Player::Player(glm::vec3 position) {
	this->position = position;
	this->scale = glm::vec3(PLAYER_SCALE_X, PLAYER_SCALE_Y, PLAYER_SCALE_Z);

	UpdateWheelPositions();
}

Player::~Player() {
	
}

void Player::UpdateTrajectory(double deltaTimeSeconds) {
	BaseObject::UpdateTrajectory(deltaTimeSeconds);

	if (isSupported && position.y <= PLATFORM_HEIGHT / 2 + PLAYER_WHEEL_RANGE)
		Land();

	UpdateWheelPositions();
}

void Player::UpdateAlive(double deltaTimeSeconds) {

	UpdateHeadlightColor(deltaTimeSeconds);
	UpdateHeadlightCutoff(deltaTimeSeconds);
	UpdateHeadlightIntensity(deltaTimeSeconds);
	UpdateBrakelightIntensity(deltaTimeSeconds);

	UpdatePowerUpTimer(deltaTimeSeconds);

	UpdateWheelPositions();

	if (!isSupported)
		FreeFall();

	switch (powerUp) {
	case PowerUpEffect::OVERDRIVE:
		Accelerate(deltaTimeSeconds);
		break;
	default:
		ApplyBaseDeceleration(deltaTimeSeconds);
	}

	switch (state) {
	case PlayerState::AIR:
		UpdateTrajectory(deltaTimeSeconds);
		TestFall();
		break;
	case PlayerState::GROUND:
		UpdateIdle(deltaTimeSeconds);
		UpdateWheelRotations(deltaTimeSeconds);
		break;
	default:
		break;
	}

}

void Player::UpdateDecay(double deltaTimeSeconds) {
	UpdateWheelPositions();

	BaseObject::UpdateDecay(deltaTimeSeconds);
}

void Player::UpdateIdle(double deltaTimeSeconds) {

	fuel = fmax(0, fuel - fuelConsumptionIdle * deltaTimeSeconds);

	if (speed < minSpeed)
		Accelerate(deltaTimeSeconds);

	if (speed > ComputeMaxSpeed())
		Decelerate(deltaTimeSeconds, false);

	if (speed == 0)
		LoseLifePoint();

}

void Player::UpdatePowerUpTimer(double deltaTimeSeconds) {

	// nothing to do
	if (powerUp == PowerUpEffect::NONE)
		return;

	powerUpTimer -= deltaTimeSeconds;

	if (powerUpTimer > 0)
		return;

	// special operations at the end of the powerup
	if (powerUp == PowerUpEffect::OVERDRIVE) {
		targetBrakelightIntensity = PLAYER_BRAKELIGHT_INTENSITY;
		brakelightIntensityStep = PLAYER_BRAKELIGHT_OVERDRIVE_INTENSITY_STEP;
	}

	if (powerUp == PowerUpEffect::INVULNERABLE) {
		targetHeadlightIntensity = PLAYER_HEADLIGHT_INTENSITY;
		targetHeadlightCutoff = PLAYER_HEADLIGHT_CUTOFF;
		targetHeadlightColor = PLAYER_HEADLIGHT_COLOR;
	}

	// end power-up
	powerUp = PowerUpEffect::NONE;
	powerUpTimer = 0;

}

void Player::UpdateWheelRotations(double deltaTimeSeconds) {

	float distance = deltaTimeSeconds * speed;

	frontLeftWheel->Advance(distance);
	frontRightWheel->Advance(distance);
	rearLeftWheel->Advance(distance);
	rearRightWheel->Advance(distance);

}

void Player::UpdateHeadlightColor(double deltaTimeSeconds) {

	// X
	if (abs(targetHeadlightColor.x - currentHeadlightColor.x) < PLAYER_HEADLIGHT_INVULNERABLE_COLOR_STEP)
		currentHeadlightColor.x = targetHeadlightColor.x;

	else if (currentHeadlightColor.x > targetHeadlightColor.x)
		currentHeadlightColor.x -= PLAYER_HEADLIGHT_INVULNERABLE_COLOR_STEP;

	else if (currentHeadlightColor.x < targetHeadlightColor.x)
		currentHeadlightColor.x += PLAYER_HEADLIGHT_INVULNERABLE_COLOR_STEP;

	// Y
	if (abs(targetHeadlightColor.y - currentHeadlightColor.y) < PLAYER_HEADLIGHT_INVULNERABLE_COLOR_STEP)
		currentHeadlightColor.y = targetHeadlightColor.y;

	else if (currentHeadlightColor.y > targetHeadlightColor.y)
		currentHeadlightColor.y -= PLAYER_HEADLIGHT_INVULNERABLE_COLOR_STEP;

	else if (currentHeadlightColor.y < targetHeadlightColor.y)
		currentHeadlightColor.y += PLAYER_HEADLIGHT_INVULNERABLE_COLOR_STEP;

	// Z
	if (abs(targetHeadlightColor.z - currentHeadlightColor.z) < PLAYER_HEADLIGHT_INVULNERABLE_COLOR_STEP)
		currentHeadlightColor.z = targetHeadlightColor.z;

	else if (currentHeadlightColor.z > targetHeadlightColor.z)
		currentHeadlightColor.z -= PLAYER_HEADLIGHT_INVULNERABLE_COLOR_STEP;

	else if (currentHeadlightColor.z < targetHeadlightColor.z)
		currentHeadlightColor.z += PLAYER_HEADLIGHT_INVULNERABLE_COLOR_STEP;

}

void Player::UpdateHeadlightCutoff(double deltaTimeSeconds) {

	if (abs(targetHeadlightCutoff - currentHeadlightCutoff) < PLAYER_HEADLIGHT_INVULNERABLE_CUTOFF_STEP)
		currentHeadlightCutoff = targetHeadlightCutoff;

	else if (currentHeadlightCutoff > targetHeadlightCutoff)
		currentHeadlightCutoff -= PLAYER_HEADLIGHT_INVULNERABLE_CUTOFF_STEP;

	else if (currentHeadlightCutoff < targetHeadlightCutoff)
		currentHeadlightCutoff += PLAYER_HEADLIGHT_INVULNERABLE_CUTOFF_STEP;

}

void Player::UpdateHeadlightIntensity(double deltaTimeSeconds) {

	if (abs(targetHeadlightIntensity - currentHeaglightIntensity) < PLAYER_HEADLIGHT_INVULNERABLE_INTENSITY_STEP)
		currentHeaglightIntensity = targetHeadlightIntensity;

	else if (currentHeaglightIntensity > targetHeadlightIntensity)
		currentHeaglightIntensity -= PLAYER_HEADLIGHT_INVULNERABLE_INTENSITY_STEP;

	else if (currentHeaglightIntensity < targetHeadlightIntensity)
		currentHeaglightIntensity += PLAYER_HEADLIGHT_INVULNERABLE_INTENSITY_STEP;

}

void Player::UpdateBrakelightIntensity(double deltaTimeSeconds) {

	if (abs(targetBrakelightIntensity - currentBrakelightIntensity) < brakelightIntensityStep)
		currentBrakelightIntensity = targetBrakelightIntensity;

	else if (currentBrakelightIntensity > targetBrakelightIntensity)
		currentBrakelightIntensity -= brakelightIntensityStep;

	else if (currentBrakelightIntensity < targetBrakelightIntensity)
		currentBrakelightIntensity += brakelightIntensityStep;

	if (braking) {
		targetBrakelightIntensity = PLAYER_BRAKELIGHT_INTENSITY;
		braking = false;
	}

}

void Player::UpdateWheelPositions() {

	// set positions relative to the chassis
	frontLeftWheel->SetPosition(position +
		glm::vec3(-CAR_CHASSIS_FRONT_WINDSHIELD_END_X, 0, (CAR_CHASSIS_FRONT_WINDSHIELD_END_Z + CAR_CHASSIS_FRONT_BUMPER_END_Z) / 2) * scale
	);

	frontRightWheel->SetPosition(position +
		glm::vec3(CAR_CHASSIS_FRONT_WINDSHIELD_END_X, 0, (CAR_CHASSIS_FRONT_WINDSHIELD_END_Z + CAR_CHASSIS_FRONT_BUMPER_END_Z) / 2) * scale
	);

	rearLeftWheel->SetPosition(position +
		glm::vec3(-CAR_CHASSIS_REAR_WINDSHIELD_END_X, 0, (CAR_CHASSIS_REAR_WINDSHIELD_START_Z + CAR_CHASSIS_REAR_WINDSHIELD_END_Z) / 2) * scale
	);

	rearRightWheel->SetPosition(position +
		glm::vec3(CAR_CHASSIS_REAR_WINDSHIELD_END_X, 0, (CAR_CHASSIS_REAR_WINDSHIELD_START_Z + CAR_CHASSIS_REAR_WINDSHIELD_END_Z) / 2) * scale
	);

}

void Player::Accelerate(double deltaTime) {
	
	if ((state != PlayerState::GROUND && powerUp != PowerUpEffect::OVERDRIVE) || fuel == 0)
		return;

	IncreaseSpeed(PLAYER_ACCELERATION * deltaTime);
	fuel = fmax(0, fuel - fuelConsumptionAcceleration * deltaTime);

}

void Player::Decelerate(double deltaTime, bool applyBrakes) {

	if (state != PlayerState::GROUND || powerUp == PowerUpEffect::OVERDRIVE)
		return;

	DecreaseSpeed(PLAYER_DECELERATION * deltaTime);

	if (applyBrakes) {
		targetBrakelightIntensity = PLAYER_BRAKELIGHT_BRAKE_INTENSITY;
		brakelightIntensityStep = PLAYER_BRAKELIGHT_BRAKE_INTENSITY_STEP;

		braking = true;
	}

}

void Player::MoveLeft(double deltaTime) {
	position += glm::vec3(PLAYER_LATERAL_SPEED * deltaTime, 0, 0);
}

void Player::MoveRight(double deltaTime) {
	position -= glm::vec3(PLAYER_LATERAL_SPEED * deltaTime, 0, 0);
}

void Player::Jump() {

	if (state != PlayerState::GROUND || !IsAlive())
		return;

	velocity = glm::vec3(0, PLAYER_JUMP_STRENGTH, 0);
	state = PlayerState::AIR;

}

void Player::Land() {

	if (state != PlayerState::AIR)
		return;

	position.y = PLATFORM_HEIGHT / 2 + PLAYER_WHEEL_RANGE;
	velocity = glm::vec3(0);
	state = PlayerState::GROUND;
}

void Player::IncreaseSpeed(float amount) {

	if (speed > ComputeMaxSpeed())
		return;

	speed = fmin(ComputeMaxSpeed(), speed + amount);
}

void Player::DecreaseSpeed(float amount) {

	if (speed < minSpeed && fuel > 0)
		return;

	speed = fmax(fuel > 0 ? minSpeed : 0, speed - amount);

}

void Player::ApplyBaseDeceleration(double deltaTimeSeconds) {

	if (state != PlayerState::GROUND)
		return;

	DecreaseSpeed(PLAYER_BASE_DECELERATION * deltaTimeSeconds);

}

void Player::Refuel(float amount) {
	fuel = fmin(PLAYER_MAX_FUEL_AMOUNT, fuel + amount);
}

void Player::LoseFuel(float amount) {

	if (Protect())
		return;

	fuel = fmax(0, fuel - amount);
}

void Player::ApplyOverdrivePowerUp(float time) {

	if (Protect())
		return;

	powerUp = PowerUpEffect::OVERDRIVE;
	powerUpTimer = time;

	targetBrakelightIntensity = PLAYER_BRAKELIGHT_OVERDRIVE_INTENSITY;
	brakelightIntensityStep = PLAYER_BRAKELIGHT_OVERDRIVE_INTENSITY_STEP;
	braking = false;

}

void Player::ApplyInvulnerablePowerUp(float time) {

	if (powerUp == PowerUpEffect::OVERDRIVE) {
		targetBrakelightIntensity = PLAYER_BRAKELIGHT_INTENSITY;
		brakelightIntensityStep = PLAYER_BRAKELIGHT_OVERDRIVE_INTENSITY_STEP;
	}

	powerUp = PowerUpEffect::INVULNERABLE;
	powerUpTimer = time;

	targetHeadlightIntensity = PLAYER_HEADLIGHT_INVULNERABLE_INTENSITY;
	targetHeadlightCutoff = PLAYER_HEADLIGHT_INVULNERABLE_CUTOFF;
	targetHeadlightColor = PLAYER_HEADLIGHT_INVULNERABLE_COLOR;
}

void Player::LoseLifePoint() {

	if (Protect())
		return;

	if (--lifePoints == 0)
		StartDecay();
	else
		fuel = PLAYER_MAX_FUEL_AMOUNT;

}

void Player::SetSupported(bool value) {
	isSupported = value;
}

void Player::FreeFall() {
	state = PlayerState::AIR;
}

bool Player::Protect() {
	
	if (powerUp != PowerUpEffect::INVULNERABLE)
		return false;

	// consume
	powerUp = PowerUpEffect::NONE;
	powerUpTimer = 0;

	targetHeadlightIntensity = PLAYER_HEADLIGHT_INTENSITY;
	targetHeadlightCutoff = PLAYER_HEADLIGHT_CUTOFF;
	targetHeadlightColor = PLAYER_HEADLIGHT_COLOR;

	return true;

}

void Player::TestFall() {
	if (position.y < -PLATFORM_HEIGHT)
		StartDecay();
}

float Player::ComputeMaxSpeed() {
	return maxSpeed * (powerUp == PowerUpEffect::OVERDRIVE ? PLAYER_OVERDRIVE_MULTIPLIER : 1.0);
}

void Player::LoadSettings(std::string difficulty) {

	SettingsStore* instance = SettingsStore::GetInstance();

	minSpeed = instance->GetFloatSetting(SETTING_PLAYER_SPEED_MIN, difficulty);
	maxSpeed = instance->GetFloatSetting(SETTING_PLAYER_SPEED_MAX, difficulty);
	fuelConsumptionIdle = instance->GetFloatSetting(SETTING_PLAYER_FUEL_CONSUMPTION_IDLE, difficulty);
	fuelConsumptionAcceleration = instance->GetFloatSetting(SETTING_PLAYER_FUEL_CONSUMPTION_ACCELERATION, difficulty);

}

std::vector<std::string> Player::GetModels() {
	return { PLAYER_MODEL };
}

std::string Player::GetTexture() {
	return PLAYER_TEXTURE;
}

std::vector<BaseObject*> Player::GetObjectsToRender() {
	return { frontLeftWheel, frontRightWheel, rearLeftWheel, rearRightWheel };
}

void Player::StartDecay() {

	if (objState != ObjectState::ALIVE)
		return;

	BaseObject::StartDecay();

}

bool Player::IsInBounds() {
	return position.y >= PLAYER_BOUND_MIN_Y;
}

std::vector<LightData> Player::GetLightDatas() {
	float headlightX = CAR_CHASSIS_FRONT_BUMPER_END_X / 2.f;
	float headlightY = CAR_CHASSIS_FRONT_BUMPER_END_Y + (CAR_CHASSIS_FRONT_BUMPER_START_Y - CAR_CHASSIS_FRONT_BUMPER_END_Y) * 3.f / 4.f;
	float headlightZ = 0.3 + (CAR_CHASSIS_FRONT_BUMPER_END_Z + CAR_CHASSIS_FRONT_BUMPER_START_Z) / 2.f;

	float brakelightX = CAR_CHASSIS_REAR_BUMPER_END_X * 3.f / 4.f;
	float brakelightY = CAR_CHASSIS_REAR_BUMPER_END_Y + (CAR_CHASSIS_REAR_BUMPER_START_Y - CAR_CHASSIS_REAR_BUMPER_END_Y) * 2.f / 3.f;
	float brakelightZ = -0.3 + (CAR_CHASSIS_REAR_BUMPER_END_Z + CAR_CHASSIS_REAR_BUMPER_START_Z) / 2.f;

	glm::vec3 leftHeadlightPos = position + scale * glm::vec3(headlightX, headlightY, headlightZ);
	glm::vec3 rightHeadlightPos = position + scale * glm::vec3(-headlightX, headlightY, headlightZ);
	glm::vec3 headlightDirection = { 0, -sin(PLAYER_HEADLIGHT_ANGLE), cos(PLAYER_HEADLIGHT_ANGLE) };

	glm::vec3 leftBrakelightPos = position + scale * glm::vec3(brakelightX, brakelightY, brakelightZ);
	glm::vec3 rightBrakelightPos = position + scale * glm::vec3(-brakelightX, brakelightY, brakelightZ);
	
	LightData leftHeadlightData = LightData(leftHeadlightPos, headlightDirection, currentHeadlightColor, currentHeadlightCutoff, currentHeaglightIntensity, true);
	LightData rightHeadlightData = LightData(rightHeadlightPos, headlightDirection, currentHeadlightColor, currentHeadlightCutoff, currentHeaglightIntensity, true);

	LightData leftFakeHeadlightData = LightData(leftHeadlightPos, glm::vec3(0), currentHeadlightColor, 0, fakeHeadlightIntensity(currentHeaglightIntensity), false);
	LightData rightFakeHeadlightData = LightData(rightHeadlightPos, glm::vec3(0), currentHeadlightColor, 0, fakeHeadlightIntensity(currentHeaglightIntensity), false);

	LightData leftBrakelightData = LightData(leftBrakelightPos, glm::vec3(0), PLAYER_BRAKELIGHT_COLOR, 0, currentBrakelightIntensity, false);
	LightData rightBrakelightData = LightData(rightBrakelightPos, glm::vec3(0), PLAYER_BRAKELIGHT_COLOR, 0, currentBrakelightIntensity, false);

	return { leftHeadlightData, rightHeadlightData, leftFakeHeadlightData, rightFakeHeadlightData, leftBrakelightData, rightBrakelightData };
}

float Player::GetFuel() {
	return fuel;
}

float Player::GetSpeed() {
	return speed;
}

float Player::GetMinSpeed() {
	return minSpeed;
}

float Player::GetMaxSpeed() {
	return maxSpeed;
}

int Player::GetLifePoints() {
	return lifePoints;
}

bool Player::IsOnGround() {
	return state == PlayerState::GROUND;
}