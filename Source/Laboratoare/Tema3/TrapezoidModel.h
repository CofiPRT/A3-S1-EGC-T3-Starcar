#pragma once

#include "BaseModel.h"

#define TRAPEZOID_MODEL_NAME	("model.trapezoid")

class TrapezoidModel : public BaseModel {
public:
	ModelData GetModelData() override {
		std::vector<ModelDataPart> parts;

		// the trapezoid
		{
			float l = 1.f;

			std::vector<glm::vec3> vertices = {
				{  l / 2,  l, -l},
				{ -l / 2,  l, -l},
				{ -l,     -l, -l},
				{  l,     -l, -l}
			};

			std::vector<glm::vec3> normalsBase = {
				-AXIS_OZ
			};
			
			std::vector<glm::vec3> normals;
			for (auto& normal : normalsBase)
				for (int i = 1; i <= 4; i++)
					normals.push_back(normal);

			std::vector<glm::vec2> textureCoords = {
				{0.f, 0.f},
				{1.f, 0.f},
				{1.f, 1.f},
				{0.f, 1.f}
			};

			std::vector<unsigned short> indices = {
				0, 1, 2,
				0, 2, 3
			};

			std::string name = TRAPEZOID_MODEL_NAME;
			int primitive = GL_TRIANGLES;

			parts.push_back(ModelDataPart(vertices, normals, textureCoords, indices, name, primitive));
		}

		return ModelData(parts);
	}
};