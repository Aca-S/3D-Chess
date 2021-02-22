//
// Created by aca on 22.2.21..
//

#ifndef RG_3D_SAH_RAWMESH_H
#define RG_3D_SAH_RAWMESH_H

#include "materials.h"

class RawMesh {
    float *vertices;
    int numOfVertices;
    int sizeOfVertices;
    unsigned *indices;
    int numOfIndices;
    unsigned VBO, VAO, EBO;
    Material &material;
public:
    RawMesh(float *vertices, int numOfVertices, int sizeOfVertices, unsigned *indices, int numOfIndices, MaterialTexture &material);
    RawMesh(float *vertices, int numOfVertices, int sizeOfVertices, unsigned *indices, int numOfIndices, MaterialColor &material);
    RawMesh(float *vertices, int numOfVertices, int sizeOfVertices, MaterialTexture &material);
    RawMesh(float *vertices, int numOfVertices, int sizeOfVertices, MaterialColor &material);
    void draw(Shader &shader);
};


#endif //RG_3D_SAH_RAWMESH_H
