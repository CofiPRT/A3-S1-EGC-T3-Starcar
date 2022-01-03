#pragma once

#include "BaseModel.h"
#include "Globals.h"

#define SQUARE_PYRAMID_MODEL_NAME	("model.square_pyramid")

class SquarePyramidModel : public BaseModel {
public:
	ModelData GetModelData() override {
		std::vector<ModelDataPart> parts;

		// the square pyramid
		{
			float l = 1.f;
			float h = l / sqrt(2.f);

			std::vector<glm::vec3> vertices = {
				// FRONT
				{  0, h,  0 },
				{ -l, 0, -l },
				{  l, 0, -l },

				// RIGHT
				{  0, h,  0 },
				{ -l, 0,  l },
				{ -l, 0, -l },

				// BACK
				{  0, h,  0 },
				{  l, 0,  l },
				{ -l, 0,  l },

				// LEFT
				{  0, h,  0 },
				{  l, 0, -l },
				{  l, 0,  l },

				// BASE
				{  l, 0,  l },
				{ -l, 0,  l },
				{ -l, 0, -l },
				{  l, 0, -l }
			};

			float dihedralAngle = atan(sqrt(2.f));
			float sinC = sin(dihedralAngle);
			float cosC = cos(dihedralAngle);

			std::vector<glm::vec3> normalsBase = {
				{ 0,     sinC, -cosC },
				{ -cosC, sinC, 0     },
				{ 0,     sinC, cosC  },
				{ cosC,  sinC, 0     },
				-AXIS_OY
			};

			std::vector<glm::vec3> normals;
			for (int i = 0; i < normalsBase.size(); i++)
				for (int j = 1; j <= (i == normalsBase.size() - 1 ? 4 : 3); j++)
					normals.push_back(normalsBase[i]);

			std::vector<glm::vec2> textureCoords = {
				/// FRONT
				{ 0.01f, 0.01f },
				{ 0.50f, 0.17f },
				{ 0.17f, 0.50f },

				// RIGHT
				{ 0.99f, 0.01f },
				{ 0.83f, 0.50f },
				{ 0.50f, 0.17f },

				// BACK
				{ 0.99f, 0.99f },
				{ 0.50f, 0.83f },
				{ 0.83f, 0.50f },

				// LEFT
				{ 0.01f, 0.99f },
				{ 0.17f, 0.50f },
				{ 0.50f, 0.83f },

				// BASE
				{ 0.50f, 0.83f },
				{ 0.83f, 0.50f },
				{ 0.50f, 0.17f },
				{ 0.17f, 0.50f }
			};

			std::vector<unsigned short> indices = {
				// FRONT
				0, 1, 2,

				// RIGHT
				3, 4, 5,

				// BACK
				6, 7, 8,

				// LEFT
				9, 10, 11,

				// BASE
				12, 13, 14,
				12, 14, 15
			};

			std::string name = SQUARE_PYRAMID_MODEL_NAME;
			int primitive = GL_TRIANGLES;

			parts.push_back(ModelDataPart(vertices, normals, textureCoords, indices, name, primitive));
		}

		return ModelData(parts);
	}
};