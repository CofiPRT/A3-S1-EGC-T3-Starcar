#pragma once

#include "BaseModel.h"
#include "Globals.h"

#define LAMPPOST_MODEL_NAME					("model.lamppost")
#define LAMPPOST_MODEL_BASE_NAME			("model.lamppost.base")
#define LAMPPOST_MODEL_VERTICAL_ROD_NAME	("model.lamppost.vertical_rod")
#define LAMPPOST_MODEL_HORIZONTAL_ROD_NAME	("model.lamppost.horizontal_rod")
#define LAMPPOST_MODEL_LIGHTBULB_NAME		("model.lamppost.lightbulb")

#define LAMPPOST_MODEL_LIGHTBULB_POSITION	(glm::vec3(3.625, 5.25, 0))

class LampPostModel : public BaseModel {
public:
	ModelData GetModelData() override {
		std::vector<ModelDataPart> parts;

		// the base
		{
			float l = 1.f;

			std::vector<glm::vec3> vertices = {
				// TOP
				{  l,  0,  l },
				{ -l,  0,  l },
				{ -l,  0, -l },
				{  l,  0, -l },

				// BACK
				{  l, -l / 2,  l },
				{ -l, -l / 2,  l },
				{ -l,  0,      l },
				{  l,  0,      l },

				// FRONT
				{  l,  0,     -l },
				{ -l,  0,     -l },
				{ -l, -l / 2, -l },
				{  l, -l / 2, -l },

				// LEFT
				{  l, -l / 2,  l },
				{  l,  0,      l },
				{  l,  0,     -l },
				{  l, -l / 2, -l },

				// RIGHT
				{ -l,  0,      l },
				{ -l, -l / 2,  l },
				{ -l, -l / 2, -l },
				{ -l,  0,     -l },

				// BOTTOM
				{ -l, -l / 2,  l },
				{  l, -l / 2,  l },
				{  l, -l / 2, -l },
				{ -l, -l / 2, -l }
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
				{ 0.00f, 0.00f },
				{ 0.50f, 0.00f },
				{ 0.50f, 0.50f },
				{ 0.00f, 0.50f },

				// BACK
				{ 0.00f, 0.00f },
				{ 0.50f, 0.00f },
				{ 0.50f, 0.50f },
				{ 0.00f, 0.50f },

				// FRONT
				{ 0.00f, 0.00f },
				{ 0.50f, 0.00f },
				{ 0.50f, 0.50f },
				{ 0.00f, 0.50f },

				// LEFT
				{ 0.00f, 0.00f },
				{ 0.50f, 0.00f },
				{ 0.50f, 0.50f },
				{ 0.00f, 0.50f },

				// RIGHT
				{ 0.00f, 0.00f },
				{ 0.50f, 0.00f },
				{ 0.50f, 0.50f },
				{ 0.00f, 0.50f },

				// BOTTOM
				{ 0.00f, 0.00f },
				{ 0.50f, 0.00f },
				{ 0.50f, 0.50f },
				{ 0.00f, 0.50f }
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

			std::string name = LAMPPOST_MODEL_BASE_NAME;
			int primitive = GL_TRIANGLES;

			parts.push_back(ModelDataPart(vertices, normals, textureCoords, indices, name, primitive));
		};

		// the vertical rod
		{
			float l = 0.5f;
			float h = 6.f;

			std::vector<glm::vec3> vertices = {
				// TOP
				{  l,  h,  l },
				{ -l,  h,  l },
				{ -l,  h, -l },
				{  l,  h, -l },

				// BACK
				{  l,  0,  l },
				{ -l,  0,  l },
				{ -l,  h,  l },
				{  l,  h,  l },

				// FRONT
				{  l,  h, -l },
				{ -l,  h, -l },
				{ -l,  0, -l },
				{  l,  0, -l },

				// LEFT
				{  l,  0,  l },
				{  l,  h,  l },
				{  l,  h, -l },
				{  l,  0, -l },

				// RIGHT
				{ -l,  h,  l },
				{ -l,  0,  l },
				{ -l,  0, -l },
				{ -l,  h, -l },

				// BOTTOM
				{ -l,  0,  l },
				{  l,  0,  l },
				{  l,  0, -l },
				{ -l,  0, -l }
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
				{ 0.50f, 0.00f },
				{ 1.00f, 0.00f },
				{ 1.00f, 0.50f },
				{ 0.50f, 0.50f },

				// BACK
				{ 0.50f, 0.00f },
				{ 1.00f, 0.00f },
				{ 1.00f, 0.50f },
				{ 0.50f, 0.50f },

				// FRONT
				{ 0.50f, 0.00f },
				{ 1.00f, 0.00f },
				{ 1.00f, 0.50f },
				{ 0.50f, 0.50f },

				// LEFT
				{ 0.50f, 0.00f },
				{ 1.00f, 0.00f },
				{ 1.00f, 0.50f },
				{ 0.50f, 0.50f },

				// RIGHT
				{ 0.50f, 0.00f },
				{ 1.00f, 0.00f },
				{ 1.00f, 0.50f },
				{ 0.50f, 0.50f },

				// BOTTOM
				{ 0.50f, 0.00f },
				{ 1.00f, 0.00f },
				{ 1.00f, 0.50f },
				{ 0.50f, 0.50f },
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

			std::string name = LAMPPOST_MODEL_VERTICAL_ROD_NAME;
			int primitive = GL_TRIANGLES;

			parts.push_back(ModelDataPart(vertices, normals, textureCoords, indices, name, primitive));
		};

		// the horizontal rod
		{
			float w = 0.5f;
			float h = 6.f;
			float l = 4.f;

			std::vector<glm::vec3> vertices = {
				// TOP
				{  l,  h,  w },
				{  w,  h,  w },
				{  w,  h, -w },
				{  l,  h, -w },

				// BACK
				{  l,  h - w,  w },
				{  w,  h - w,  w },
				{  w,  h,      w },
				{  l,  h,      w },

				// FRONT
				{  l,  h,     -w },
				{  w,  h,     -w },
				{  w,  h - w, -w },
				{  l,  h - w, -w },

				// LEFT
				{  l,  h - w,  w },
				{  l,  h,      w },
				{  l,  h,     -w },
				{  l,  h - w, -w },

				// RIGHT
				{  w,  h,      w },
				{  w,  h - w,  w },
				{  w,  h - w, -w },
				{  w,  h,     -w },

				// BOTTOM
				{  w,  h - w,  w },
				{  l,  h - w,  w },
				{  l,  h - w, -w },
				{  w,  h - w, -w }
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
				{ 0.00f, 0.50f },
				{ 0.50f, 0.50f },
				{ 0.50f, 1.00f },
				{ 0.00f, 1.00f },

				// BACK
				{ 0.00f, 0.50f },
				{ 0.50f, 0.50f },
				{ 0.50f, 1.00f },
				{ 0.00f, 1.00f },

				// FRONT
				{ 0.00f, 0.50f },
				{ 0.50f, 0.50f },
				{ 0.50f, 1.00f },
				{ 0.00f, 1.00f },

				// LEFT
				{ 0.00f, 0.50f },
				{ 0.50f, 0.50f },
				{ 0.50f, 1.00f },
				{ 0.00f, 1.00f },

				// RIGHT
				{ 0.00f, 0.50f },
				{ 0.50f, 0.50f },
				{ 0.50f, 1.00f },
				{ 0.00f, 1.00f },

				// BOTTOM
				{ 0.00f, 0.50f },
				{ 0.50f, 0.50f },
				{ 0.50f, 1.00f },
				{ 0.00f, 1.00f }
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

			std::string name = LAMPPOST_MODEL_HORIZONTAL_ROD_NAME;
			int primitive = GL_TRIANGLES;

			parts.push_back(ModelDataPart(vertices, normals, textureCoords, indices, name, primitive));
		};

		// the lightbulb
		{
			float o = 3.75f;
			float l = 0.25f;
			float H = 5.5f;
			float h = 5.f;

			std::vector<glm::vec3> vertices = {
				// TOP
				{  o,      H,  l },
				{  o - l,  H,  l },
				{  o - l,  H, -l },
				{  o,      H, -l },

				// BACK
				{  o,      h,  l },
				{  o - l,  h,  l },
				{  o - l,  H,  l },
				{  o,      H,  l },

				// FRONT
				{  o,      H, -l },
				{  o - l,  H, -l },
				{  o - l,  h, -l },
				{  o,      h, -l },

				// LEFT
				{  o,  h,  l },
				{  o,  H,  l },
				{  o,  H, -l },
				{  o,  h, -l },

				// RIGHT
				{  o - l,  H,  l },
				{  o - l,  h,  l },
				{  o - l,  h, -l },
				{  o - l,  H, -l },

				// BOTTOM
				{  o - l,  h,  l },
				{  o,      h,  l },
				{  o,      h, -l },
				{  o - l,  h, -l }
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
				{ 0.50f, 0.50f },
				{ 1.00f, 0.50f },
				{ 1.00f, 1.00f },
				{ 0.50f, 1.00f },

				// BACK
				{ 0.50f, 0.50f },
				{ 1.00f, 0.50f },
				{ 1.00f, 1.00f },
				{ 0.50f, 1.00f },

				// FRONT
				{ 0.50f, 0.50f },
				{ 1.00f, 0.50f },
				{ 1.00f, 1.00f },
				{ 0.50f, 1.00f },

				// LEFT
				{ 0.50f, 0.50f },
				{ 1.00f, 0.50f },
				{ 1.00f, 1.00f },
				{ 0.50f, 1.00f },

				// RIGHT
				{ 0.50f, 0.50f },
				{ 1.00f, 0.50f },
				{ 1.00f, 1.00f },
				{ 0.50f, 1.00f },

				// BOTTOM
				{ 0.50f, 0.50f },
				{ 1.00f, 0.50f },
				{ 1.00f, 1.00f },
				{ 0.50f, 1.00f }
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

			std::string name = LAMPPOST_MODEL_LIGHTBULB_NAME;
			int primitive = GL_TRIANGLES;

			parts.push_back(ModelDataPart(vertices, normals, textureCoords, indices, name, primitive));
		};

		return ModelData(parts);
	}
};