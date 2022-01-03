#pragma once

#include "BaseHUDObject.h"
#include "Frame.h"
#include "SquareModel.h"

#define INDICATOR_WIDTH (0.25f)
#define INDICATOR_HEIGHT (0.05f)
#define INDICATOR_LENGTH (1.f)

#define INDICATOR_POS_X (FRAME_POS_X - FRAME_WIDTH / 4)
#define INDICATOR_POS_Y (FRAME_POS_Y - FRAME_HEIGHT / 3)
#define INDICATOR_POS_Z (FRAME_POS_Z)

#define FUEL_INDICATOR_MODEL (SQUARE_MODEL_NAME)

class BaseFuelIndicator : public BaseHUDObject {

public:
	BaseFuelIndicator();
	~BaseFuelIndicator();

	std::vector<std::string> GetModels() override;

};