#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"
#include "shader.h"

unsigned int TextureFromFile(const char* path, const std::string &directory, bool gamma = false);

class Model
{
public:
    // model data
    std::vector<Texture> textures_loaded; // stores all the textures loaded so far, optimization
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorrection;

    // constructor, expects a filepath to a 3D model
    Model(char* path, bool gamma = false) : gammaCorrection(gamma)
    {
        loadModel(path);
    }
    void Draw(Shader& shader);
private:
    // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector
    void loadModel(std::string const &path);
    // processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};


#endif // MODEL_H