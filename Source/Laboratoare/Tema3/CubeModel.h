#pragma once

#include "BaseModel.h"
#include "Globals.h"

#define CUBE_MODEL_NAME	("model.cube")

class CubeModel : public BaseModel {
public:
	ModelData GetModelData() override {
		std::vector<ModelDataPart> parts;

		// the cube
		{
			float l = 1.f;

			std::vector<glm::vec3> vertices = {
				// TOP
				{  l,  l,  l },
				{ -l,  l,  l },
				{ -l,  l, -l },
				{  l,  l, -l },

				// BACK
				{  l, -l,  l },
				{ -l, -l,  l },
				{ -l,  l,  l },
				{  l,  l,  l },

				// FRONT
				{  l,  l, -l },
				{ -l,  l, -l },
				{ -l, -l, -l },
				{  l, -l, -l },

				// LEFT
				{  l, -l,  l },
				{  l,  l,  l },
				{  l,  l, -l },
				{  l, -l, -l },

				// RIGHT
				{ -l,  l,  l },
				{ -l, -l,  l },
				{ -l, -l, -l },
				{ -l,  l, -l },

				// BOTTOM
				{ -l, -l,  l },
				{  l, -l,  l },
				{  l, -l, -l },
				{ -l, -l, -l }
			};

			std::vector<glm::vec3> normalsBase = {
				 AXIS_OY,
				 AXIS_OZ,
				-AXIS_OZ,
				 AXIS_OX,
				-AXIS_OX,
				-AXIS_OY,
			};

			std::vector<glm::vec3> normals;
			for (auto normal : normalsBase)
				for (int i = 1; i <= 4; i++)
					normals.push_back(normal);

			std::vector<glm::vec2> textureCoords = {
				// TOP
				{ 0.25f, 0.25f },
				{ 0.50f, 0.25f },
				{ 0.50f, 0.50f },
				{ 0.25f, 0.50f },

				// BACK
				{ 0.25f, 0.00f },
				{ 0.50f, 0.00f },
				{ 0.50f, 0.25f },
				{ 0.25f, 0.25f },

				// FRONT
				{ 0.25f, 0.50f },
				{ 0.50f, 0.50f },
				{ 0.50f, 0.75f },
				{ 0.25f, 0.75f },

				// LEFT
				{ 0.00f, 0.25f },
				{ 0.25f, 0.25f },
				{ 0.25f, 0.50f },
				{ 0.00f, 0.50f },

				// RIGHT
				{ 0.50f, 0.25f },
				{ 0.75f, 0.25f },
				{ 0.75f, 0.50f },
				{ 0.50f, 0.50f },

				// BOTTOM
				{ 0.25f, 0.75f },
				{ 0.50f, 0.75f },
				{ 0.50f, 1.00f },
				{ 0.25f, 1.00f }
			};

			std::vector<unsigned short> indices = {
				// TOP
				0, 1, 2,
				0, 2, 3,

				// BACK
				4, 5, 6,
				4, 6, 7,

				// FRONT
				8, 9, 10,
				8, 10, 11,

				// LEFT
				12, 13, 14,
				12, 14, 15,

				// RIGHT
				16, 17, 18,
				16, 18, 19,

				// BOTTOM
				20, 21, 22,
				20, 22, 23
			};

			std::string name = CUBE_MODEL_NAME;
			int primitive = GL_TRIANGLES;

			parts.push_back(ModelDataPart(vertices, normals, textureCoords, indices, name, primitive));
		}

		return ModelData(parts);
	}
};