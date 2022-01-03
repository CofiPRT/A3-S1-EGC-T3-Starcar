#pragma once

#include "BaseObject.h"
#include "CubeModel.h"

#define SKYBOX_SCALE_X (1000.f)
#define SKYBOX_SCALE_Y (1000.f)
#define SKYBOX_SCALE_Z (1000.f)

#define SKYBOX_TEXTURE ("texture.skybox")
#define SKYBOX_MODEL (CUBE_MODEL_NAME)

class SkyBox : public BaseObject {

public:
	SkyBox();
	~SkyBox();

	std::vector<std::string> GetModels() override;
	std::string GetTexture() override;

};