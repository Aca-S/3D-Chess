//
// Created by aca on 1.2.21..
//

#ifndef RG_3D_SAH_MODEL_H
#define RG_3D_SAH_MODEL_H

#include <string>
#include <vector>
#include <map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Texture2D.h"
#include "Shader.h"
#include "Mesh.h"

class Model {
    std::string directory;
    void loadModel(const std::string &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    void loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::vector<Texture2D> &textures);
public:
    std::map<std::string, Texture2D> loadedTextures;
    std::vector<Mesh> meshes;
    Model(const std::string &path);
    void draw(Shader &shader);
};


#endif //RG_3D_SAH_MODEL_H
