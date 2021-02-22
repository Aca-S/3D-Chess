//
// Created by aca on 19.2.21..
//

#ifndef RG_3D_SAH_SCENE_H
#define RG_3D_SAH_SCENE_H

#include <vector>
#include <tuple>
#include <map>
#include "Camera.h"
#include "Model.h"
#include "RawMesh.h"
#include "Shader.h"
#include "lights.h"

class Scene {
    Camera &camera;
    std::map<Shader *, std::vector<Light *>> lights;
    std::map<Shader *, std::vector<std::pair<Model *, glm::mat4 *>>> models;
    std::map<Shader *, std::vector<std::pair<RawMesh *, glm::mat4 *>>> meshes;
public:
    Scene(Camera &camera);
    void addModel(Model *model, Shader *shader, glm::mat4 *transformation);
    void addRawMesh(RawMesh *mesh, Shader *shader, glm::mat4 *transformation);
    void addLight(Light *light, Shader *shader);
    void render();
    // void clean();
};


#endif //RG_3D_SAH_SCENE_H
