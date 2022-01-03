#pragma once

#include "ModelData.h"

class BaseModel {
public:
	virtual ModelData GetModelData() = 0;
};