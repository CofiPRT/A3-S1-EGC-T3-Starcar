#pragma once

#include "BaseModel.h"

#define PLATFORM_MODEL_NAME	("model.platform")

class PlatformModel : public BaseModel {
public:
	ModelData GetModelData() override {
		std::vector<ModelDataPart> parts;

		// the platform
		{
			float w = 1;
			float h = 1;
			float l = 1;

			std::vector<glm::vec3> vertices = {
				// TOP
				{  w,  h,  l },
				{ -w,  h,  l },
				{ -w,  h, -l },
				{  w,  h, -l },

				// BACK
				{  w, -h,  l },
				{ -w, -h,  l },
				{ -w,  h,  l },
				{  w,  h,  l },

				// FRONT
				{  w,  h, -l },
				{ -w,  h, -l },
				{ -w, -h, -l },
				{  w, -h, -l },

				// LEFT
				{  w, -h,  l },
				{  w,  h,  l },
				{  w,  h, -l },
				{  w, -h, -l },

				// RIGHT
				{ -w,  h,  l },
				{ -w, -h,  l },
				{ -w, -h, -l },
				{ -w,  h, -l },

				// BOTTOM
				{ -w, -h,  l },
				{  w, -h,  l },
				{  w, -h, -l },
				{ -w, -h, -l }
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
				{ 0.5f, 0.f },
				{ 1.f,  0.f },
				{ 1.f,  1.f },
				{ 0.5f, 1.f },

				// BACK
				{ 0.f,  0.f },
				{ 0.5f, 0.f },
				{ 0.5f, 1.f },
				{ 0.f,  1.f },

				// FRONT
				{ 0.f,  0.f },
				{ 0.5f, 0.f },
				{ 0.5f, 1.f },
				{ 0.f,  1.f },

				// LEFT
				{ 0.f,  0.f },
				{ 0.5f, 0.f },
				{ 0.5f, 1.f },
				{ 0.f,  1.f },

				// RIGHT
				{ 0.f,  0.f },
				{ 0.5f, 0.f },
				{ 0.5f, 1.f },
				{ 0.f,  1.f },

				// BOTTOM
				{ 0.f,  0.f },
				{ 0.5f, 0.f },
				{ 0.5f, 1.f },
				{ 0.f,  1.f }
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

			std::string name = PLATFORM_MODEL_NAME;
			int primitive = GL_TRIANGLES;

			parts.push_back(ModelDataPart(vertices, normals, textureCoords, indices, name, primitive));
		}

		return ModelData(parts);
	}
};