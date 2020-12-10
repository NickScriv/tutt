#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Texture.h"

class Model
{
public:
	Model();

	void LoadModel(const std::string& fileName);
	void RenderModel();
	void ClearModel();
	~Model();

private:
	// each node stores a reference of where a mesh is
	void LoadNode(aiNode * node, const aiScene *scene);
	void LoadMesh(aiMesh * mesh, const aiScene *scene);
	void LoadMaterials(const aiScene * scene);
	std::vector<Texture*> textureList;
	std::vector<Mesh*> meshList;
	std::vector<unsigned int> meshToTex;
};

