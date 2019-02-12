#include "ObjReader.h"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <map>

std::vector <std::string> split(const std::string &input, char delimiter) {
	bool delimiterFound = false;
	int pos = 0, pPos = 0;
	std::vector <std::string> result;
	while (true) {
		pos = (int)input.find(delimiter, pPos);
		if (pos != std::string::npos) {
			result.push_back(input.substr(pPos, pos - pPos));
			delimiterFound = true;
		}
		else {
			if (pPos < input.length() && delimiterFound)
				result.push_back(input.substr(pPos, input.length() - pPos));
			break;
		}
		pPos = pos + 1;
	}
	return result;
}

ObjReader::ObjReader(const std::string& filename)
{
	std::ifstream filestream;
	filestream.open("data/models/" + filename);

	std::string line;
	while (std::getline(filestream, line))
	{
		auto tokens = split(line, ' ');

		if (tokens[0] == "v") {
			vertices.push_back({ std::stof(tokens[1]) ,std::stof(tokens[2]) ,std::stof(tokens[3]) });
		}
		if (tokens[0] == "vt")
		{
			texCoords.push_back({ std::stof(tokens[1]), std::stof(tokens[2]) });
		}
		if (tokens[0] == "vn")
		{
			normals.push_back({ std::stof(tokens[1]) ,std::stof(tokens[2]) ,std::stof(tokens[3]) });

		}
		if (tokens[0] == "f") {
			for (int i = 0; i < tokens.size() - 3; i++)
			{
				indices.push_back(ParseObjIndex(tokens[1].c_str()));
				indices.push_back(ParseObjIndex(tokens[2 + i].c_str()));
				indices.push_back(ParseObjIndex(tokens[3 + i].c_str()));
			}
		}
	}
}

IndexedModel ObjReader::ToIndexModel()
{
	auto result = IndexedModel();
	auto normalModel = IndexedModel();
	auto resultIndexMap = std::map<ObjIndex, int>();
	auto normalIndexMap = std::map<int, int>();

	auto indexMap = std::map<int, int>();

	for (size_t i = 0; i < indices.size(); i++)
	{
		auto currentIndex = indices[i];
		auto currentPosition = vertices[currentIndex.VertexIndex];

		glm::vec2 currentTexCoord;
		if (m_hasTexCoords)
			currentTexCoord = texCoords[currentIndex.TexCoordIndex];
		else
			currentTexCoord = glm::vec2(0);

		Vec3f currentNormal;
		if (m_hasNormals)
			currentNormal = normals[currentIndex.NormalIndex];
		else
			currentNormal = Vec3f(0);

		int modelVertexIndex = 0;
		auto data = resultIndexMap.find(currentIndex);
		if (data == resultIndexMap.end())
		{
			modelVertexIndex = result.positions.size();
			resultIndexMap.emplace(currentIndex, modelVertexIndex);

			result.positions.push_back(currentPosition);
			result.texCoords.push_back(currentTexCoord);
			if (m_hasNormals)
				result.normals.push_back(currentNormal);
		}
		else
		{
			modelVertexIndex = data->second;
		}

		int normalModelVertexIndex = 0;
		auto normalData = normalIndexMap.find(currentIndex.VertexIndex);
		if (normalData == normalIndexMap.end())
		{
			normalModelVertexIndex = normalModel.positions.size();
			normalIndexMap.emplace(currentIndex.VertexIndex, normalModelVertexIndex);

			normalModel.positions.push_back(currentPosition);
			normalModel.texCoords.push_back(currentTexCoord);
			normalModel.normals.push_back(currentNormal);
		}
		else
		{
			normalModelVertexIndex = normalData->second;
		}

		result.indices.push_back(modelVertexIndex);
		normalModel.indices.push_back(normalModelVertexIndex);

		if (indexMap.find(modelVertexIndex) == indexMap.end())
		{
			indexMap.emplace(modelVertexIndex, normalModelVertexIndex);
		}
		else {
			indexMap[modelVertexIndex] = normalModelVertexIndex;
		}
	}

	for (size_t i = 0; i < result.positions.size(); i++)
	{
		auto indexMapData = indexMap.find(i);
		result.normals.push_back(normalModel.normals.at(indexMapData->second));

		result.texCoords[i] = { result.texCoords[i].x, -result.texCoords[i].y };
	}

	return result;
}



ObjIndex ObjReader::ParseObjIndex(const char* token)
{
	auto values = split(token, '/');
	auto result = ObjIndex();
	result.VertexIndex = std::stoi(values[0]) - 1;

	if (values.size() <= 1) return result;
	m_hasTexCoords = true;
	result.TexCoordIndex = std::stoi(values[1]) - 1;
	if (values.size() <= 1) return result;
	m_hasNormals = true;
	result.NormalIndex = std::stoi(values[2]) - 1;
	return result;
}


