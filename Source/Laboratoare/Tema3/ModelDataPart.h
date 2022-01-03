#pragma once

#include <Core/Engine.h>

#include <vector>

class ModelDataPart {
private:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textureCoords;
	std::vector<unsigned short> indices;
	std::string name;
	int primitive;

public:
	ModelDataPart(std::vector<glm::vec3> vertices_,
		std::vector<glm::vec3> normals_,
		std::vector<glm::vec2> textureCoords_,
		std::vector<unsigned short> indices_,
		std::string name_,
		int primitive_)

		: vertices(vertices_),
		normals(normals_),
		textureCoords(textureCoords_),
		indices(indices_),
		name(name_),
		primitive(primitive_) {

	}

	std::vector<glm::vec3> GetVertices() {
		return vertices;
	}

	std::vector<glm::vec3> GetNormals() {
		return normals;
	}

	std::vector<glm::vec2> GetTextureCoords() {
		return textureCoords;
	}

	std::vector<unsigned short> GetIndices() {
		return indices;
	}

	std::string GetName() {
		return name;
	}

	int GetPrimitive() {
		return primitive;
	}
};