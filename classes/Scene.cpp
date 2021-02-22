//
// Created by aca on 19.2.21..
//

#include "Scene.h"

Scene::Scene(Camera &camera)
    : camera{camera} { }

void Scene::addLight(Light *light, Shader *shader) {
    lights[shader].push_back(light);
}

void Scene::addRawMesh(RawMesh *mesh, Shader *shader, glm::mat4 *transformation) {
    meshes[shader].push_back(std::make_pair(mesh, transformation));
}

void Scene::render() {
    for(auto it : lights)
    {
        it.first->use();
        for(auto light : it.second)
        {
            it.first->setUniform3fv("viewPosition", camera.Position);
            light->activate(*it.first);
        }
    }
    glm::mat4 view = glm::lookAt(camera.Position, camera.Position + camera.Front, camera.Up);
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)800 / 600, 0.1f, 100.0f);
    for(auto it : models)
    {
        it.first->use();
        it.first->setUniformMatrix4fv("view", view);
        it.first->setUniformMatrix4fv("projection", projection);
        for(auto model : it.second)
        {
            it.first->setUniformMatrix4fv("model", *model.second);
            model.first->draw(*it.first);
        }
    }
    for(auto it : meshes)
    {
        it.first->use();
        it.first->setUniformMatrix4fv("view", view);
        it.first->setUniformMatrix4fv("projection", projection);
        for(auto mesh : it.second)
        {
            it.first->setUniformMatrix4fv("model", *mesh.second);
            mesh.first->draw(*it.first);
        }
    }
}