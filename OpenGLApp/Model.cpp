#include "Model.h"

Model::Model()
{

}

void Model::LoadModel(const std::string & fileName)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if (!scene)
	{
		std::cout << "Model " << fileName << " failed to load: " << importer.GetErrorString() << std::endl;
		return;
	}

	// top node of the scene
	LoadNode(scene->mRootNode, scene);

	LoadMaterials(scene);
}

void Model::RenderModel()
{
	for (size_t i = 0; i < meshList.size(); i++)
	{
		unsigned int materialIndex = meshToTex[i];

		if (materialIndex < textureList.size() && textureList[materialIndex])
		{
			textureList[materialIndex]->UseTexture();
			meshList[i]->RenderMesh();
		}
	}
}

void Model::ClearModel()
{

	for (size_t i = 0; i < meshList.size(); i++)
	{
		if (meshList[i])
		{
			delete meshList[i];
			meshList[i] = nullptr;
		}
	}

	for (size_t i = 0; i < textureList.size(); i++)
	{
		if (textureList[i])
		{
			delete textureList[i];
			textureList[i] = nullptr;
		}
	}

}

Model::~Model()
{
	ClearModel();
}

void Model::LoadNode(aiNode * node, const aiScene * scene)
{

	for (size_t i = 0; i < node->mNumMeshes; i++)
	{
		// node->mMeshes[i] holds the id of that mesh at that node
		LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	for (size_t i = 0; i < node->mNumChildren; i++)
	{
		LoadNode(node->mChildren[i], scene);
	}


}

void Model::LoadMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<GLfloat> verticies;
	std::vector<unsigned int> indicies;

	for (size_t i = 0; i < mesh->mNumVertices; i++)
	{
		verticies.insert(verticies.end(), { mesh->mVertices[i].x,mesh->mVertices[i].y, mesh->mVertices[i].z });

		// there can be multiple textures per mesh
		if (mesh->mTextureCoords[0])
		{
			verticies.insert(verticies.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
		}
		else
		{
			verticies.insert(verticies.end(), { 0.0f, 0.0f});
		}

		verticies.insert(verticies.end(), { -mesh->mNormals[i].x,-mesh->mNormals[i].y, -mesh->mNormals[i].z });

	}


	for (size_t i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; j++)
		{
			
			indicies.push_back(face.mIndices[j]);
		}
	}

	Mesh* newMesh = new Mesh();

	newMesh->CreateMesh(&verticies[0], &indicies[0], verticies.size(), indicies.size());
	meshList.push_back(newMesh);
	meshToTex.push_back(mesh->mMaterialIndex);
}

void Model::LoadMaterials(const aiScene * scene)
{
	textureList.resize(scene->mNumMaterials);
	
	for (size_t i = 0; i < scene->mNumMaterials; i++)
	{
		aiMaterial * material = scene->mMaterials[i];

		textureList[i] = nullptr;

		if (material->GetTextureCount(aiTextureType_DIFFUSE))
		{
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
			{
				// if model is exported with absolute file location
				int idx = std::string(path.data).rfind("\\");
				std::string fileName = std::string(path.data).substr(idx + 1);

				std::string texPath = std::string("Textures/") +  fileName;

				textureList[i] = new Texture(texPath.c_str());

				if (!textureList[i]->LoadTexture())
				{
					std::cout << "Failed to load texture at " << texPath << std::endl;
					delete textureList[i];
					textureList[i] = nullptr;

				}
			}
		}

		if (!textureList[i])
		{
			textureList[i] = new Texture("Textures/plain.png");
			textureList[i]->LoadTextureA();
		}

	}

	
}
