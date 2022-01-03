#include "Tema3.h"

Tema3::Tema3() {}

Tema3::~Tema3() {}

void Tema3::Init() {

	// load meshes/models
	std::vector<ModelDataPart> partsToRender;

	for (auto& part : (new PlatformModel())->GetModelData().GetModels())
		partsToRender.push_back(part);

	for (auto& part : (new SquareModel())->GetModelData().GetModels())
		partsToRender.push_back(part);

	for (auto& part : (new TrapezoidModel())->GetModelData().GetModels())
		partsToRender.push_back(part);

	for (auto& part : (new CylinderModel())->GetModelData().GetModels())
		partsToRender.push_back(part);

	for (auto& part : (new CarChassisModel())->GetModelData().GetModels())
		partsToRender.push_back(part);

	for (auto& part : (new CubeModel())->GetModelData().GetModels())
		partsToRender.push_back(part);

	for (auto& part : (new LampPostModel())->GetModelData().GetModels())
		partsToRender.push_back(part);

	for (auto& part : (new SquarePyramidModel())->GetModelData().GetModels())
		partsToRender.push_back(part);

	for (auto& part : partsToRender) {
		Mesh* mesh = new Mesh(part.GetName());
		mesh->InitFromData(part.GetVertices(), part.GetNormals(), part.GetTextureCoords(), part.GetIndices());
		mesh->SetDrawMode(part.GetPrimitive());
		meshes[part.GetName()] = mesh;
	}

	// load textures
	std::string path = "Source/Laboratoare/Tema3/";

	std::map<std::string, std::string> texturesToLoad = {
		{FRAME_TEXTURE, "frame_texture.jpg"},
		{INDICATOR_BACKGROUND_TEXTURE, "indicator_background_texture.jpg"},
		{INDICATOR_FOREGROUND_TEXTURE, "indicator_foreground_texture.jpg"},
		{BASE_PLATFORM_TEXTURE, "base_platform_texture.jpg"},
		{END_GAME_PLATFORM_TEXTURE, "end_game_platform_texture.jpg"},
		{GET_FUEL_PLATFORM_TEXTURE, "get_fuel_platform_texture.jpg"},
		{INVULNERABILITY_PLATFORM_TEXTURE, "invulnerability_platform_texture.jpg"},
		{LOSE_FUEL_PLATFORM_TEXTURE, "lose_fuel_platform_texture.jpg"},
		{OVERDRIVE_PLATFORM_TEXTURE, "overdrive_platform_texture.jpg"},
		{CAR_CHASSIS_TEXTURE, "car_chassis_texture.jpg"},
		{PLAYER_WHEEL_TEXTURE, "car_wheel_texture.jpg"},
		{SKYBOX_TEXTURE, "skybox_texture.jpg"},
		{LAMPPOST_TEXTURE, "lamppost_texture.jpg"},
		{OBAMIUM_TEXTURE, "obamium_texture.jpg"},
		{OBSTACLE_TEXTURE, "obstacle_texture.jpg"},
		{COLLECTIBLE_TEXTURE, "collectible_texture.jpg"}
	};

	for (auto& texture : texturesToLoad) {
		std::string textureName = texture.first;
		std::string textureFile = texture.second;

		Texture2D* tex = new Texture2D();
		tex->Load2D((path + textureFile).c_str(), GL_REPEAT);
		textures[textureName] = tex;
	}

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Shader* shader = new Shader("Tema3");
		shader->AddShader("Source/Laboratoare/Tema3/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	initialResolution = window->GetResolution();

	projectionMatrix = glm::perspective(RADIANS(game->GetFOV()), window->props.aspectRatio, 0.01f, 200.0f);

}

void Tema3::FrameStart() {
	// clears the color buffer (using the previously set color) and depth buffer
	glm::vec3 clearColor = GAME_CLEAR_COLOR;
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	currResolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, currResolution.x, currResolution.y);

	if (currResolution != oldResolution) {
		delete textRenderer;
		textRenderer = new TextRenderer(currResolution.x, currResolution.y);
		textRenderer->Load("Source/TextRenderer/Fonts/Arial.ttf", 18);

		oldResolution = currResolution;
	}
}

void Tema3::Update(float deltaTimeSeconds) {

	projectionMatrix = glm::perspective(RADIANS(game->GetFOV()), window->props.aspectRatio, 0.01f, 1000.0f);
	viewMatrix = game->GetCamera()->GetViewMatrix();

	game->Update(deltaTimeSeconds);

	lightDatas = game->GetLightDatas();

	for (auto object : game->GetObjectsToRender())
		for (auto model : object->GetModels())
			RenderSimpleMesh(object, meshes[model]);

}

void Tema3::FrameEnd() {

	glm::vec2 scaleVec = glm::vec2(currResolution) / glm::vec2(initialResolution);
	float scale = (scaleVec.x + scaleVec.y) / 2;

	for (auto& textData : game->GetTextsToRender())
		RenderText(textData, scale);

	if (game->IsPaused()) {

		textRenderer->RenderText("PAUSED", TEXT_PAUSED_RES_FACTOR_X * currResolution.x,
			TEXT_PAUSED_RES_FACTOR_Y * currResolution.y, scale * TEXT_STATUS_SCALE);

	} else if (game->IsEnded()) {

		textRenderer->RenderText("GAME OVER", TEXT_GAMEOVER_RES_FACTOR_X * currResolution.x,
			TEXT_GAMEOVER_RES_FACTOR_Y * currResolution.y, scale * TEXT_STATUS_SCALE);

	} else if (game->IsStarting()) {

		float startDelta = game->GetStartDelta();
		int startCount = ceil(startDelta);
		float startCountScale = 1.5f - (startCount - startDelta) / 2;

		float displacement = TEXT_COUNTDOWN_DISPLACEMENT_FACTOR * (startCount - startDelta);

		std::string timer = std::to_string(startCount);
		textRenderer->RenderText(timer, (TEXT_COUTNDOWN_RES_FACTOR_X + displacement) * currResolution.x,
			TEXT_COUNTDOWN_RES_FACTOR_Y * currResolution.y, startCountScale * TEXT_STATUS_SCALE);

	} else if (game->IsPlaying()) {

		float startDelta = game->GetStartDelta();

		if (startDelta >= -1) {
			int startCount = ceil(startDelta);
			float startCountScale = 1.5f - (startCount - startDelta) / 2;

			float displacement = TEXT_START_DISPLACEMENT_FACTOR * (startCount - startDelta);

			textRenderer->RenderText("START", (TEXT_START_RES_FACTOR_X + displacement) * currResolution.x,
				TEXT_START_RES_FACTOR_Y * currResolution.y, startCountScale * TEXT_STATUS_SCALE);
		}

	}

}

void Tema3::RenderText(std::pair<std::string, glm::vec3>& textData, float scale) {

	std::string text = textData.first;
	glm::vec3 position = textData.second;

	auto hudToResX = MathUtils::MapLinear(-1, 1, 0, currResolution.x);
	auto hudToResY = MathUtils::MapLinear(-1, 1, 0, currResolution.y);

	textRenderer->RenderText(text, hudToResX(position.x), currResolution.y - hudToResY(position.y), scale);

}

void Tema3::RenderSimpleMesh(BaseObject* object, Mesh* mesh) {

	Shader* shader = shaders["Tema3"];

	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// Bind transformation matrices
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "Model"), 1, GL_FALSE, glm::value_ptr(object->GetModelMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "View"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(shader->program, "Projection"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// Bind object details
	glUniform1i(glGetUniformLocation(shader->program, "is_hud_element"), object->IsHudElement());

	// Bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[object->GetTexture()]->GetTextureID());
	glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);

	// Bind material constants
	glUniform1i(glGetUniformLocation(shader->program, "material_shininess"), object->GetMaterialShininess());
	glUniform1f(glGetUniformLocation(shader->program, "material_kd"), object->GetMaterialKd());
	glUniform1f(glGetUniformLocation(shader->program, "material_ks"), object->GetMaterialKs());

	// Bind light sources
	std::vector<glm::vec3> lightPositions;
	std::vector<glm::vec3> lightDirections;
	std::vector<glm::vec3> lightColors;
	std::vector<float> lightCutoffs;
	std::vector<float> lightIntensities;
	std::vector<int> lightTypes;

	for (auto& lightData : lightDatas) {
		lightPositions.push_back(lightData.GetLightPosition());
		lightDirections.push_back(lightData.GetLightDirection());
		lightColors.push_back(lightData.GetLightColor());
		lightCutoffs.push_back(lightData.GetLightCutoff());
		lightIntensities.push_back(lightData.GetLightIntensity());
		lightTypes.push_back(lightData.GetLightType());
	}

	//printf("first light pos: %f %f %f\n", lightPositions[0].x, lightPositions[0].y, lightPositions[0].z);
	glUniform3fv(glGetUniformLocation(shader->program, "light_positions"), lightPositions.size(), reinterpret_cast<GLfloat*>(lightPositions.data()));
	glUniform3fv(glGetUniformLocation(shader->program, "light_directions"), lightDirections.size(), reinterpret_cast<GLfloat*>(lightDirections.data()));
	glUniform3fv(glGetUniformLocation(shader->program, "light_colors"), lightColors.size(), reinterpret_cast<GLfloat*>(lightColors.data()));
	glUniform1fv(glGetUniformLocation(shader->program, "light_cutoffs"), lightCutoffs.size(), reinterpret_cast<GLfloat*>(lightCutoffs.data()));
	glUniform1fv(glGetUniformLocation(shader->program, "light_intensities"), lightIntensities.size(), reinterpret_cast<GLfloat*>(lightIntensities.data()));
	glUniform1iv(glGetUniformLocation(shader->program, "light_types"), lightTypes.size(), reinterpret_cast<GLint*>(lightTypes.data()));
	glUniform1i(glGetUniformLocation(shader->program, "light_source_count"), lightPositions.size());

	// Bind elements related to light-computing
	glm::vec3 eyePosition = game->GetCamera()->GetPosition();
	glUniform3f(glGetUniformLocation(shader->program, "eye_position"), eyePosition.x, eyePosition.y, eyePosition.z);

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}

void Tema3::OnInputUpdate(float deltaTime, int mods) {
	game->OnInputUpdate(window, deltaTime, mods);
}

void Tema3::OnKeyPress(int key, int mods) {
	game->OnKeyPress(key, mods);
}

void Tema3::OnKeyRelease(int key, int mods) {}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
	game->OnMouseMove(window, mouseX, mouseY, deltaX, deltaY);
}

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}

void Tema3::OnWindowResize(int width, int height) {}