#pragma once
#include <vector>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <tuple>
#include "GLCommon.h"


struct ObjIndex
{
public:
	int VertexIndex;
	int TexCoordIndex;
	int NormalIndex;


};

inline bool operator< (const ObjIndex& lhs, const ObjIndex& rhs)
{
	// std::tuple's lexicographic ordering does all the actual work for you
	// and using std::tie means no actual copies are made
	return std::tie(lhs.VertexIndex, lhs.NormalIndex, lhs.TexCoordIndex) <  std::tie(rhs.VertexIndex, rhs.NormalIndex, rhs.TexCoordIndex);
}

struct IndexedModel
{
public:
	std::vector<Vec3f> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<Vec3f> positions;
	std::vector<GLuint> indices;


};

class ObjReader
{
public:
	ObjReader(const std::string& filepath);
	IndexedModel ToIndexModel();

	std::vector<Vec3f> vertices;
	std::vector<Vec3f> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<ObjIndex> indices;
private:
	ObjIndex ParseObjIndex(const char* token);

	bool m_hasTexCoords = true;
	bool m_hasNormals;


};