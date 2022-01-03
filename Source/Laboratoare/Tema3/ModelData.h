#pragma once

#include "ModelDataPart.h"

class ModelData {
private:
	std::vector<ModelDataPart> models;

public:
	ModelData(std::vector<ModelDataPart> models_)
		: models(models_) {

	}

	std::vector<ModelDataPart> GetModels() {
		return models;
	}
};