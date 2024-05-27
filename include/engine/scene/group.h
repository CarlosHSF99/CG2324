#ifndef CG2324_GROUP_H
#define CG2324_GROUP_H


#include <vector>
#include <memory>
#include "transform.h"
#include "engine/scene/model/model.h"
#include "deps/tinyxml2.h"

class Group
{
private:
    std::vector<std::unique_ptr<Transform>> transforms;
    std::vector<Model> models;
    std::vector<Group> subgroups;

public:
    Group() = default;

    Group(std::vector<std::unique_ptr<Transform>> transforms, std::vector<Model> models, std::vector<Group> subgroups)
            : transforms(std::move(transforms)), models(std::move(models)), subgroups(std::move(subgroups)) {}

    explicit Group(tinyxml2::XMLElement *groupElement);

    void draw(float time) const;
};


#endif //CG2324_GROUP_H
