#pragma once

#include "BaseModel.h"

#define CYLINDER_MODEL_NAME			("model.cylinder")
#define CYLINDER_MODEL_TOP_NAME		("model.cylinder.top")
#define CYLINDER_MODEL_BOT_NAME		("model.cylinder.bot")
#define CYLINDER_MODEL_SIDE_NAME	("model.cylinder.side")

#define CYLINDER_BASE_TRIANGLE_COUNT (40)

class CylinderModel : public BaseModel {
public:
	ModelData GetModelData() override {
		float r = 1.f;
		float h = 1.f;
		float rText = 0.25f;

		std::vector<ModelDataPart> parts;

		std::vector<glm::vec3> verticesTop = { {0,  h, 0} };
		std::vector<glm::vec3> verticesBot = { {0, -h, 0} };

		std::vector<glm::vec2> textureCoordsTop = { {0.25f, 0.25f} };
		std::vector<glm::vec2> textureCoordsBot = { {0.25f, 0.75f} };

		for (int i = 0; i <= CYLINDER_BASE_TRIANGLE_COUNT; i++) {
			float t = (float)i / CYLINDER_BASE_TRIANGLE_COUNT * 2 * (float)M_PI;

			float x = r * cos(t);
			float z = r * sin(t);

			verticesTop.push_back({ x,  h, z });
			verticesBot.push_back({ x, -h, z });

			float xText = rText * cos(t);
			float yText = rText * sin(t);

			textureCoordsTop.push_back({ 0.25f + xText, 0.25f + yText });
			textureCoordsBot.push_back({ 0.25f + xText, 0.75f + yText });
		}

		std::vector<unsigned short> indicesBase;
		for (int i = 0; i < verticesTop.size(); i++)
			indicesBase.push_back(i);

		// top
		{
			std::vector<glm::vec3> normals;
			for (auto& vertex : verticesTop)
				normals.push_back(glm::normalize(vertex));

			std::string name = CYLINDER_MODEL_TOP_NAME;
			int primitive = GL_TRIANGLE_FAN;

			parts.push_back(ModelDataPart(verticesTop, normals, textureCoordsTop, indicesBase, name, primitive));
		}

		// bot
		{
			std::vector<glm::vec3> normals;
			for (auto& vertex : verticesBot)
				normals.push_back(glm::normalize(vertex));

			std::string name = CYLINDER_MODEL_BOT_NAME;
			int primitive = GL_TRIANGLE_FAN;

			parts.push_back(ModelDataPart(verticesBot, normals, textureCoordsBot, indicesBase, name, primitive));
		}

		// side
		{
			std::vector<glm::vec3> vertices;
			std::vector<glm::vec2> textureCoords;

			float textureStripLength = 1.f / (verticesTop.size() - 1.f);

			for (size_t i = 1; i < verticesTop.size() - 1 && i < 50; i++) {
				glm::vec3 top = verticesTop[i];
				glm::vec3 bot = verticesBot[i];

				glm::vec3 topNext = verticesTop[i + 1];
				glm::vec3 botNext = verticesBot[i + 1];

				vertices.push_back(top);
				vertices.push_back(topNext);
				vertices.push_back(botNext);

				vertices.push_back(top);
				vertices.push_back(botNext);
				vertices.push_back(bot);

				float startTexture = textureStripLength * (i - 1);
				float endTexture = startTexture + textureStripLength;

				//printf("texts: %f %f\n", startTexture, endTexture);

				textureCoords.push_back({ 1.0f, startTexture });
				textureCoords.push_back({ 1.0f, endTexture });
				textureCoords.push_back({ 0.5f, endTexture });

				textureCoords.push_back({ 1.0f, startTexture });
				textureCoords.push_back({ 0.5f, endTexture });
				textureCoords.push_back({ 0.5f, startTexture });
			}

			std::vector<glm::vec3> normals;
			for (auto& vertex : vertices)
				normals.push_back(glm::normalize(vertex));

			std::vector<unsigned short> indices;
			for (int i = 0; i < vertices.size(); i++)
				indices.push_back(i);

			std::string name = CYLINDER_MODEL_SIDE_NAME;
			int primitive = GL_TRIANGLES;

			parts.push_back(ModelDataPart(vertices, normals, textureCoords, indices, name, primitive));
		}

		return ModelData(parts);
	}
};