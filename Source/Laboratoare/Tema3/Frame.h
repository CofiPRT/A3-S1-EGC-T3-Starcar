#pragma once

#include "BaseHUDObject.h"
#include "TrapezoidModel.h"

#define FRAME_WIDTH (2.f)
#define FRAME_HEIGHT (0.2f)
#define FRAME_LENGTH (1.f)

#define FRAME_POS_X (0.f)
#define FRAME_POS_Y (-1.f + FRAME_HEIGHT / 2)
#define FRAME_POS_Z (1.f)

#define FRAME_TEXTURE ("texture.frame")
#define FRAME_MODEL (TRAPEZOID_MODEL_NAME)

class Frame : public BaseHUDObject {

public:
	Frame();
	~Frame();

	std::vector<std::string> GetModels() override;
	std::string GetTexture() override;

};