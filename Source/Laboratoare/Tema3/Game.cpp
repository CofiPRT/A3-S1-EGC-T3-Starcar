#include "Game.h"

Game::Game() {
	NewGame();

	deltaToRotationX = MathUtils::MapSmooth(
		GAME_START_DURATION, 0,
		M_PI / 12, 0,
		GAME_START_ANIMATION_SMOOTHNESS
	);

	deltaToRotationY = MathUtils::MapSmooth(
		GAME_START_DURATION, 0,
		-M_PI, 0,
		GAME_START_ANIMATION_SMOOTHNESS
	);

	deltaToPositionX = MathUtils::MapSmooth(
		GAME_START_DURATION, 0,
		5.f * PLATFORM_WIDTH * GAME_COLUMN_COUNT, player->GetPosition().x,
		GAME_START_ANIMATION_SMOOTHNESS
	);

	deltaToPositionY = MathUtils::MapSmooth(
		GAME_START_DURATION, 0,
		1.1f * PLATFORM_HEIGHT, player->GetPosition().y,
		GAME_START_ANIMATION_SMOOTHNESS
	);

	deltaToPositionZ = MathUtils::MapSmooth(
		GAME_START_DURATION, 0,
		2.5f * PLATFORM_LENGTH, player->GetPosition().z,
		GAME_START_ANIMATION_SMOOTHNESS
	);

	deltaToCDistance = MathUtils::MapSmooth(
		GAME_START_DURATION, 0,
		20.f * CAMERA_INITIAL_3RD_PERSON_DISTANCE, CAMERA_INITIAL_3RD_PERSON_DISTANCE,
		GAME_START_ANIMATION_SMOOTHNESS
	);

	lamppostSpawnChanceDist = FloatDist(0.f, 1.f);
	obamiumSpawnChanceDist = FloatDist(0.f, 1.f);
	obstacleSpawnChanceDist = FloatDist(0.f, 1.f);
	collectibleSpawnChanceDist = FloatDist(0.f, 1.f);

}

Game::~Game() {

}

void Game::Update(double deltaTimeSeconds) {

	deltaTimeSeconds *= currGameTick;

	if (startDelta > -1)
		startDelta -= deltaTimeSeconds;

	if (IsPaused())
		return;

	UpdateStartAnimations(deltaTimeSeconds);

	if (IsStarting())
		return;

	UpdateDistanceTraveled(deltaTimeSeconds);
	UpdateDifficulty();
	UpdateObjects(deltaTimeSeconds);

	glm::vec3 cameraPos = player->GetPosition();

	if (!camera->IsThirdPerson())
		cameraPos += glm::vec3(0, 2 * PLAYER_WHEEL_RANGE, 0);

	camera->Set(cameraPos + GetCameraShake());

	if (!IsPlaying())
		return;

	AttemptSpawn();

}

void Game::UpdateObjects(double deltaTimeSeconds) {
	
	bool supported = false; // the player can only touch one platform at a time

	glm::vec3 playerPos = player->GetPosition();

	// PLATFORMS
	{
		auto it = platforms.begin();

		// PLATFORMS
		while (it != platforms.end()) {
			BasePlatform* platform = (*it);

			glm::vec3 platformPos = platform->GetPosition();

			platform->SetSpeed(player->GetSpeed());
			platform->Update(deltaTimeSeconds);

			if (platform->IsDead() || (player->IsDecaying() && glm::distance(platformPos, playerPos) < ON_DEATH_DESTROY_RADIUS)) {
				it = platforms.erase(it);
				delete platform;
				continue;
			}

			if (!supported && platform->IsBelow(player))
				supported = true;

			it++;
		}
	}

	// LAMPPOSTS
	{
		auto it = lampposts.begin();

		while (it != lampposts.end()) {
			LampPost* lamppost = (*it);

			glm::vec3 lamppostPos = lamppost->GetPosition();

			lamppost->SetSpeed(player->GetSpeed());
			lamppost->Update(deltaTimeSeconds);

			if (lamppost->IsDead() || (player->IsDecaying() && glm::distance(lamppostPos, playerPos) < ON_DEATH_DESTROY_RADIUS)) {
				it = lampposts.erase(it);
				delete lamppost;
				continue;
			}

			it++;
		}
	}

	// OBAMIUMS
	{
		auto it = obamiums.begin();

		while (it != obamiums.end()) {
			Obamium* obamium = (*it);

			glm::vec3 obamiumPos = obamium->GetPosition();

			obamium->SetSpeed(player->GetSpeed());
			obamium->Update(deltaTimeSeconds);

			if (obamium->IsDead() || (player->IsDecaying() && glm::distance(obamiumPos, playerPos) < ON_DEATH_DESTROY_RADIUS)) {
				it = obamiums.erase(it);
				delete obamium;
				continue;
			}

			it++;
		}
	}

	// OBSTACLES
	{
		auto it = obstacles.begin();

		while (it != obstacles.end()) {
			Obstacle* obstacle = (*it);

			glm::vec3 obstaclePos = obstacle->GetPosition();

			if (obstacle->IsAlive()) {
				if (obstacle->TestCollision(player)) {
					player->LoseLifePoint();
					obstacle->StartDecay();
					obstacle->Launch((obstaclePos - playerPos) * glm::vec3(1, 1, 1.2));
				}
				else {
					obstacle->SetSpeed(player->GetSpeed());
				}
			}

			obstacle->Update(deltaTimeSeconds);

			if (obstacle->IsDead() || (player->IsDecaying() && glm::distance(obstaclePos, playerPos) < ON_DEATH_DESTROY_RADIUS)) {
				it = obstacles.erase(it);
				delete obstacle;
				continue;
			}

			it++;
		}
	}

	// COLLECTIBLES
	{
		auto it = collectibles.begin();

		while (it != collectibles.end()) {
			Collectible* collectible = (*it);

			glm::vec3 collectiblePos = collectible->GetPosition();

			if (collectible->IsAlive()) {
				if (collectible->TestCollision(player)) {
					score += SCORE_COLLECTIBLE;
					collectible->StartDecay();
					collectible->Launch((collectiblePos - playerPos) * glm::vec3(1, 0, 1.2) + glm::vec3(0, PLAYER_JUMP_STRENGTH, 0));
				}
				else {
					collectible->SetSpeed(player->GetSpeed());
				}
			}

			collectible->Update(deltaTimeSeconds);

			if (collectible->IsDead() || (player->IsDecaying() && glm::distance(collectiblePos, playerPos) < ON_DEATH_DESTROY_RADIUS)) {
				it = collectibles.erase(it);
				delete collectible;
				continue;
			}

			it++;
		}
	}

	// PLAYER
	player->SetSupported(supported);
	player->Update(deltaTimeSeconds);

	// HUD - FUEL INDICATOR
	fuelForeground->RevealAt(fuelBackground->GetPosition(), player->GetFuel() / PLAYER_MAX_FUEL_AMOUNT);

	if (player->IsDead())
		EndGame();

}

void Game::UpdateDistanceTraveled(double deltaTimeSeconds) {
	float distance = player->GetSpeed() * deltaTimeSeconds;

	distanceTraveled += distance;
	distToNextSpawn -= distance;

	score += distance * SCORE_DISTANCE;
}

void Game::UpdateStartAnimations(double deltaTimeSeconds) {

	if (!IsStarting())
		return;

	float cameraPosX = deltaToPositionX(startDelta);
	float cameraPosY = deltaToPositionY(startDelta);
	float cameraPosZ = deltaToPositionZ(startDelta);

	float cameraRotX = deltaToRotationX(startDelta);
	float cameraRotY = deltaToRotationY(startDelta);

	float cameraDist = deltaToCDistance(startDelta);

	camera->Set(glm::vec3(cameraPosX, cameraPosY, cameraPosZ));
	camera->RotateThirdPerson_OX(cameraRotX);
	camera->RotateThirdPerson_OY(cameraRotY);
	camera->SetDistanceToTarget(cameraDist);

	if (startDelta < 0) {
		state = GameState::PLAYING;
		camera->SetDistanceToTarget(CAMERA_INITIAL_3RD_PERSON_DISTANCE);
	}

}

void Game::UpdateDifficulty() {

	if (currDifficulty == DIFFICULTY_EASY && distanceTraveled > GAME_DIFFICULTY_MEDIUM_DISTANCE_THRESHOLD)
		LoadSettings(DIFFICULTY_MEDIUM);
	else if (currDifficulty == DIFFICULTY_MEDIUM && distanceTraveled > GAME_DIFFICULTY_HARD_DISTANCE_THRESHOLD)
		LoadSettings(DIFFICULTY_HARD);

}

void Game::OnInputUpdate(WindowObject* window, float deltaTime, int mods) {

	if (!IsPlaying())
		return;

	if (window->KeyHold(GLFW_KEY_W))
		player->Accelerate(deltaTime);

	if (window->KeyHold(GLFW_KEY_S))
		player->Decelerate(deltaTime, true);

	if (window->KeyHold(GLFW_KEY_A))
		player->MoveLeft(deltaTime);

	if (window->KeyHold(GLFW_KEY_D))
		player->MoveRight(deltaTime);

}

void Game::OnKeyPress(int key, int mods) {

	if (key == GLFW_KEY_R)
		Restart();

	if (IsEnded() && IsStarting())
		return;

	if (key == GLFW_KEY_P)
		TogglePause();

	if (!IsPlaying())
		return;

	switch (key) {
	case GLFW_KEY_C:
		camera->ToggleThirdPerson();
		fuelBackground->TogglePosition();
		fuelForeground->TogglePosition();
		frame->TogglePosition();
		break;

	case GLFW_KEY_SPACE:
		player->Jump();
		break;

	case GLFW_KEY_LEFT_BRACKET:
		DecreaseGameTick();
		break;

	case GLFW_KEY_RIGHT_BRACKET:
		IncreaseGameTick();
		break;

	default:
		break;
	}

}

void Game::OnMouseMove(WindowObject* window, int mouseX, int mouseY, int deltaX, int deltaY) {

	if (IsStarting())
		return;

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
		camera->MouseRotate(player->GetPosition(), deltaX, deltaY);
	else
		camera->StopMouseRotation(player->GetPosition());

}

void Game::SpawnNewGamePlatforms() {

	// prepare a starting area full of platforms for the player
	for (int row = 0; row < GAME_SPAWN_DISTANCE; row++)
		for (int column = 0; column < GAME_COLUMN_COUNT; column++)
			platforms.push_back(new BasePlatform(glm::vec3(PLATFORM_WIDTH * column, 0, PLATFORM_LENGTH * row)));

}

void Game::NewGame() {
	
	state = GameState::STARTING;

	delete player;
	player = new Player(glm::vec3(PLATFORM_WIDTH / 2 * (GAME_COLUMN_COUNT - 1), PLATFORM_HEIGHT / 2 + PLAYER_WHEEL_RANGE, 0));

	for (auto platform : platforms)
		delete platform;
	platforms.clear();

	for (auto lamppost : lampposts)
		delete lamppost;
	lampposts.clear();

	for (auto obamium : obamiums)
		delete obamium;
	obamiums.clear();

	for (auto obstacle : obstacles)
		delete obstacle;
	obstacles.clear();

	for (auto collectible : collectibles)
		delete collectible;
	collectibles.clear();

	delete skybox;
	skybox = new SkyBox();

	delete fuelBackground;
	delete fuelForeground;
	delete frame;

	fuelBackground = new FuelIndicatorBackground();
	fuelForeground = new FuelIndicatorForeground();
	frame = new Frame();

	distanceTraveled = 0.f;
	score = 0.f;
	distToNextSpawn = 0.f;

	prevGameTick = 1.f;
	currGameTick = 1.f;
	
	LoadSettings(DIFFICULTY_EASY);

	SpawnNewGamePlatforms();

	delete camera;
	camera = new Student::Camera();

	startDelta = GAME_START_DURATION;

}

void Game::EndGame() {
	state = GameState::ENDED;
	currGameTick = 0;
}

void Game::LoadSettings(std::string difficulty) {

	SettingsStore* instance = SettingsStore::GetInstance();

	// NORMAL PLATFORM
	normalPlatformSpawnCountDist = IntDist(
		instance->GetIntSetting(SETTING_PLATFORM_NORMAL_SPAWN_COUNT_MIN, difficulty),
		instance->GetIntSetting(SETTING_PLATFORM_NORMAL_SPAWN_COUNT_MAX, difficulty)
	);

	// BAD PLATFORMS
	badPlatformSpawnPool.clear();

	badPlatformSpawnPool.push_back({
		[this](glm::vec3 position) {
			platforms.push_back(new EndGamePlatform(position));
		}, instance->GetFloatSetting(SETTING_PLATFORM_BAD_SPAWN_WEIGHT_END_GAME, difficulty)
	});

	badPlatformSpawnPool.push_back({
		[this](glm::vec3 position) {
			platforms.push_back(new OverdrivePlatform(position));
		}, instance->GetFloatSetting(SETTING_PLATFORM_BAD_SPAWN_WEIGHT_OVERDRIVE, difficulty)
	});

	badPlatformSpawnPool.push_back({
		[this](glm::vec3 position) {
			platforms.push_back(new LoseFuelPlatform(position));
		}, instance->GetFloatSetting(SETTING_PLATFORM_BAD_SPAWN_WEIGHT_LOSE_FUEL, difficulty)
	});

	badPlatformSpawnPool.push_back({
		[this](glm::vec3 position) {

		}, instance->GetFloatSetting(SETTING_PLATFORM_BAD_SPAWN_WEIGHT_NONE, difficulty)
	});

	// calculate the total weight of the bad platform spawn pool
	float totalWeight = 0;

	for (auto& entry : badPlatformSpawnPool)
		totalWeight += entry.second;

	badPlatformSpawnWeightDist = FloatDist(0, totalWeight);

	// GOOD PLATFORMS
	goodPlatformSpawnPool.clear();

	goodPlatformSpawnPool.push_back({
		[this](glm::vec3 position) {
			platforms.push_back(new InvulnerabilityPlatform(position));
		}, instance->GetFloatSetting(SETTING_PLATFORM_GOOD_SPAWN_WEIGHT_INVULNERABLE, difficulty)
	});

	goodPlatformSpawnPool.push_back({
		[this](glm::vec3 position) {
			platforms.push_back(new GetFuelPlatform(position));
		}, instance->GetFloatSetting(SETTING_PLATFORM_GOOD_SPAWN_WEIGHT_GET_FUEL, difficulty)
	});

	goodPlatformSpawnPool.push_back({
		[this](glm::vec3 position) {

		}, instance->GetFloatSetting(SETTING_PLATFORM_GOOD_SPAWN_WEIGHT_NONE, difficulty)
	});

	// calculate the total weight of the good platform spawn pool
	totalWeight = 0;

	for (auto& entry : goodPlatformSpawnPool)
		totalWeight += entry.second;

	goodPlatformSpawnWeightDist = FloatDist(0, totalWeight);

	// load player settings
	player->LoadSettings(difficulty);

	float timelessMinSpeed = instance->GetFloatSetting(SETTING_PLAYER_SPEED_MIN, DIFFICULTY_EASY);
	float timelessMaxSpeed = instance->GetFloatSetting(SETTING_PLAYER_SPEED_MAX, DIFFICULTY_HARD);

	speedToShakeFactor = MathUtils::MapLinear(
		timelessMinSpeed, timelessMaxSpeed,
		0.0, 1.0
	);

	speedToFOV = MathUtils::MapLinear(
		timelessMinSpeed, timelessMaxSpeed,
		GAME_FOV_MIN, GAME_FOV_MAX
	);

	currDifficulty = difficulty;

}

void Game::AttemptSpawn() {

	// don't spawn anything yet
	if (distToNextSpawn > 0)
		return;

	// reset to a platform length, minus the time wasted
	distToNextSpawn += PLATFORM_LENGTH;

	// attempt to spawn a lamppost on the right side
	float lamppostChance = lamppostSpawnChanceDist(RandomUtils::mt);
	if (lamppostChance <= LAMPPOST_SPAWN_CHANCE) {
		lampposts.push_back(new LampPost(glm::vec3(-1.f * PLATFORM_WIDTH, 0, PLATFORM_LENGTH * GAME_SPAWN_DISTANCE), true));
	} else {
		// attempt to spawn an obamium on the right side
		float obamiumChance = obamiumSpawnChanceDist(RandomUtils::mt);
		if (obamiumChance <= OBAMIUM_SPAWN_CHANCE)
			obamiums.push_back(new Obamium(glm::vec3(-1.5f * PLATFORM_WIDTH, 0, PLATFORM_LENGTH * GAME_SPAWN_DISTANCE), true));
	}

	// attempt to spawn a lamppost on the left side
	if (lamppostChance <= LAMPPOST_SPAWN_CHANCE) {
		lampposts.push_back(new LampPost(glm::vec3(GAME_COLUMN_COUNT * PLATFORM_WIDTH, 0, PLATFORM_LENGTH * GAME_SPAWN_DISTANCE), false));
	} else {
		// attempt to spawn an obamium on the left side
		float obamiumChance = obamiumSpawnChanceDist(RandomUtils::mt);
		if (obamiumChance <= OBAMIUM_SPAWN_CHANCE)
			obamiums.push_back(new Obamium(glm::vec3((GAME_COLUMN_COUNT + 0.5f) * PLATFORM_WIDTH, 0, PLATFORM_LENGTH * GAME_SPAWN_DISTANCE), false));
	}

	std::vector<int> availableColumns;
	for (int i = 0; i < GAME_COLUMN_COUNT; i++)
		availableColumns.push_back(i);

	// spawn a specific number of normal platforms
	int normalPlatformsToSpawn = normalPlatformSpawnCountDist(RandomUtils::mt);

	bool firstPlatform = true;

	while (availableColumns.size() > 0 && normalPlatformsToSpawn > 0) {

		glm::vec3 location = ComputeSpawnLocation(availableColumns, firstPlatform && DEBUG);

		// spawn the normal platform
		platforms.push_back(new BasePlatform(location));

		// attempt to spawn an obstacle
		float obstacleChance = obstacleSpawnChanceDist(RandomUtils::mt);
		if (obstacleChance <= OBSTACLE_SPAWN_CHANCE && !firstPlatform)
			obstacles.push_back(new Obstacle(location + glm::vec3(0, PLATFORM_HEIGHT / 2 + OBSTACLE_SCALE_Y, 0)));
		else {
			// attempt to spawn collectibles
			float collectibleChance = collectibleSpawnChanceDist(RandomUtils::mt);
			if (collectibleChance <= COLLECTIBLE_SPAWN_CHANCE) {
				collectibles.push_back(new Collectible(location + glm::vec3(0, PLATFORM_HEIGHT / 2 + COLLECTIBLE_HEIGHT, -PLATFORM_LENGTH / 4)));
				collectibles.push_back(new Collectible(location + glm::vec3(0, PLATFORM_HEIGHT / 2 + COLLECTIBLE_HEIGHT, 0)));
				collectibles.push_back(new Collectible(location + glm::vec3(0, PLATFORM_HEIGHT / 2 + COLLECTIBLE_HEIGHT, PLATFORM_LENGTH / 4)));
			}
		}

		normalPlatformsToSpawn--;
		firstPlatform = false;

	}

	// attempt to spawn a bad platform
	if (availableColumns.size() == 0)
		return;

	SpawnPlatformFromPool(badPlatformSpawnPool, badPlatformSpawnWeightDist, ComputeSpawnLocation(availableColumns, false));

	// attempt to spawn a good platform
	if (availableColumns.size() == 0)
		return;

	SpawnPlatformFromPool(goodPlatformSpawnPool, goodPlatformSpawnWeightDist, ComputeSpawnLocation(availableColumns, false));

}

void Game::SpawnPlatformFromPool(SpawnPool spawnPool, FloatDist dist, glm::vec3 location) {

	float randomWeight = dist(RandomUtils::mt);
	float currWeight = 0;

	for (auto& entry : spawnPool) {
		currWeight += entry.second;

		if (randomWeight < currWeight) {
			entry.first(location); // spawn the object
			return;
		}
	}

}

glm::vec3 Game::ComputeSpawnLocation(std::vector<int>& availableColumns, bool overrideMiddlePlatform) {

	// choose a random column
	platformSpawnColumnDist = IntDist(0, availableColumns.size() - 1);
	int index = overrideMiddlePlatform ? (availableColumns.size() / 2) : platformSpawnColumnDist(RandomUtils::mt);
	int column = availableColumns[index];

	// remove this column from the available ones
	availableColumns.erase(availableColumns.begin() + index);

	return glm::vec3(PLATFORM_WIDTH * column, 0, PLATFORM_LENGTH * GAME_SPAWN_DISTANCE);
}

glm::vec3 Game::GetCameraShake() {

	float shakeFactor = speedToShakeFactor(player->GetSpeed());

	float amplitudeX = CAMERA_SHAKE_AMPLITUDE_X * shakeFactor;
	float amplitudeY = CAMERA_SHAKE_AMPLITUDE_Y * shakeFactor;
	float amplitudeZ = CAMERA_SHAKE_AMPLITUDE_Z * shakeFactor;

	float frequencyX = CAMERA_SHAKE_FREQUENCY_X;
	float frequencyY = CAMERA_SHAKE_FREQUENCY_Y;
	float frequencyZ = CAMERA_SHAKE_FREQUENCY_Z;

	float shakeX = amplitudeX * sin(frequencyX * distanceTraveled + CAMERA_SHAKE_OFFSET_X);
	float shakeY = amplitudeY * sin(frequencyY * distanceTraveled + CAMERA_SHAKE_OFFSET_Y);
	float shakeZ = amplitudeZ * sin(frequencyZ * distanceTraveled + CAMERA_SHAKE_OFFSET_Z);

	return glm::vec3(shakeX, shakeY, shakeZ);

}

float Game::GetFOV() {
	return speedToFOV(player->GetSpeed());
}

float Game::GetStartDelta() {
	return startDelta;
}

Student::Camera* Game::GetCamera() {
	return camera;
}

std::vector<LightData> Game::GetLightDatas() {
	std::vector<LightData> datas;

	for (auto data : player->GetLightDatas())
		datas.push_back(data);

	for (auto lamppost : lampposts)
		for (auto data : lamppost->GetLightDatas())
			datas.push_back(data);

	for (auto obamium : obamiums)
		for (auto data : obamium->GetLightDatas())
			datas.push_back(data);

	return datas;
}

std::vector<BaseObject*> Game::GetObjectsToRender() {

	std::vector<BaseObject*> objects;

	objects.push_back(skybox);

	if (camera->IsThirdPerson()) {
		objects.push_back(player);

		for (auto object : player->GetObjectsToRender())
			objects.push_back(object);
	}

	for (auto obamium : obamiums)
		objects.push_back(obamium);

	for (auto lamppost : lampposts)
		objects.push_back(lamppost);

	for (auto platform : platforms)
		objects.push_back(platform);

	for (auto obstacle : obstacles)
		objects.push_back(obstacle);

	for (auto collectible : collectibles)
		objects.push_back(collectible);

	objects.push_back(fuelForeground);
	objects.push_back(fuelBackground);
	objects.push_back(frame);

	return objects;

}

std::vector<std::pair<std::string, glm::vec3>> Game::GetTextsToRender() {
	std::vector<std::pair<std::string, glm::vec3>> texts;

	bool thirdPerson = camera->IsThirdPerson();
	glm::vec3 upDown = glm::vec3(1.0, thirdPerson ? 1.0 : -1.0, 1.0);
	glm::vec3 offset = glm::vec3(0.0, thirdPerson ? 0.0 : INDICATOR_HEIGHT, 0.0);

	// FUEL
	{
		glm::vec3 origin = glm::vec3(TEXT_FUEL_POS_X, TEXT_FUEL_POS_Y, 1.0);
		glm::vec3 position = origin * upDown + offset;
		texts.push_back({ "Fuel", position });
	}

	// DISTANCE
	{
		glm::vec3 origin = glm::vec3(TEXT_DISTANCE_POS_X, TEXT_DISTANCE_POS_Y, 1.0);
		glm::vec3 position = origin * upDown + offset;
		texts.push_back({ "Distance: " + std::to_string((int) distanceTraveled), position });
	}

	// SCORE
	{
		glm::vec3 origin = glm::vec3(TEXT_SCORE_POS_X, TEXT_SCORE_POS_Y, 1.0);
		glm::vec3 position = origin * upDown + offset;
		texts.push_back({ "Score: " + std::to_string((int)score), position });
	}

	// LIFE POINTS
	{
		glm::vec3 origin = glm::vec3(TEXT_LIFE_POINTS_POS_X, TEXT_LIFE_POINTS_POS_Y, 1.0);
		glm::vec3 position = origin * upDown + offset;
		texts.push_back({ "Life points: " + std::to_string(player->GetLifePoints()), position });
	}

	return texts;
}

void Game::TogglePause() {

	if (IsPlaying()) {
		state = GameState::PAUSED;
		prevGameTick = currGameTick;
		currGameTick = 0;
	} else if (IsPaused()) {
		state = GameState::PLAYING;
		currGameTick = prevGameTick;
	}

}

void Game::Restart() {
	NewGame();
}

void Game::DecreaseGameTick() {
	currGameTick -= GAME_TICK_CHANGE_STEP;

	if (currGameTick <= 0)
		currGameTick = 0;
}

void Game::IncreaseGameTick() {
	currGameTick += GAME_TICK_CHANGE_STEP;
}

bool Game::IsStarting() {
	return state == GameState::STARTING;
}

bool Game::IsPlaying() {
	return state == GameState::PLAYING;
}

bool Game::IsPaused() {
	return state == GameState::PAUSED;
}

bool Game::IsEnded() {
	return state == GameState::ENDED;
}
