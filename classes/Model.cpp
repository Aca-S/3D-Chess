//
// Created by aca on 1.2.21..
//

#include "Model.h"
#include "error.h"

Model::Model(const std::string &path) {
    loadModel(path);
}

void Model::draw(Shader &shader) {
    for(Mesh &mesh : meshes)
        mesh.draw(shader);
}

void Model::loadModel(const std::string &path) {
    Assimp::Importer importer;
    unsigned flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace;
    const aiScene *scene = importer.ReadFile(path, flags);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        CHECK_ERROR(0, "Model loading failed");
    directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    for(int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for(int i = 0; i < node->mNumChildren; i++)
        processNode(node->mChildren[i], scene);
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned> indices;
    std::vector<Texture2D> textures;

    for(int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;

        if(mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }

        if(mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;

            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.tangent = vector;

            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.bitangent = vector;
        }
        else
            vertex.texCoords = glm::vec2(0.0, 0.0);
        vertices.push_back(vertex);
    }

    for(int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
    loadMaterialTextures(material, aiTextureType_DIFFUSE, textures);
    loadMaterialTextures(material, aiTextureType_SPECULAR, textures);
    loadMaterialTextures(material, aiTextureType_NORMALS, textures);
    loadMaterialTextures(material, aiTextureType_HEIGHT, textures);

    return Mesh(vertices, indices, textures);
}

void Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::vector<Texture2D> &textures) {
    for(int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;

        auto it = loadedTextures.find(str.C_Str());
        if(it != loadedTextures.end())
        {
            textures.push_back(it->second);
            skip = true;
        }

        if(!skip)
        {
            texType t_type;
            switch(type)
            {
                case aiTextureType_DIFFUSE:
                    t_type = DIFFUSE;
                    break;
                case aiTextureType_SPECULAR:
                    t_type = SPECULAR;
                    break;
                case aiTextureType_NORMALS:
                    t_type = NORMAL;
                    break;
                case aiTextureType_HEIGHT:
                    t_type = HEIGHT;
                    break;
            }
            Texture2D tex(directory + '/' + str.C_Str(), t_type, GL_REPEAT, GL_LINEAR);
            textures.push_back(tex);
            loadedTextures.insert(std::make_pair(str.C_Str(), tex));
        }
    }
}
