#include "Frame.h"

Frame::Frame() {
	this->position = glm::vec3(FRAME_POS_X, FRAME_POS_Y, FRAME_POS_Z);
	this->scale = glm::vec3(FRAME_WIDTH / 2, FRAME_HEIGHT / 2, FRAME_LENGTH / 2);
}

Frame::~Frame() {

}

std::vector<std::string> Frame::GetModels() {
	return { FRAME_MODEL };
}

std::string Frame::GetTexture() {
	return FRAME_TEXTURE;
}