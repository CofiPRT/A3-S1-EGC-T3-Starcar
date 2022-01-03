#include "SkyBox.h"

SkyBox::SkyBox() {
	this->scale = glm::vec3(SKYBOX_SCALE_X / 2, SKYBOX_SCALE_Y / 2, SKYBOX_SCALE_Z / 2);
}

SkyBox::~SkyBox() {

}

std::vector<std::string> SkyBox::GetModels() {
	return { SKYBOX_MODEL };
}

std::string SkyBox::GetTexture() {
	return SKYBOX_TEXTURE;
}