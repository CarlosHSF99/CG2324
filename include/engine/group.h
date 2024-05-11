#ifndef CG2324_GROUP_H
#define CG2324_GROUP_H


#include <vector>
#include <memory>
#include "engine/transform.h"
#include "engine/model.h"
#include "deps/tinyxml2.h"

class Group
{
private:
    std::vector<std::unique_ptr<transform::Transform>> transforms;
    std::vector<Model> models;
    std::vector<Group> subgroups;

public:
    Group() = default;

    Group(std::vector<std::unique_ptr<transform::Transform>> transforms, std::vector<Model> models, std::vector<Group> subgroups)
            : transforms(std::move(transforms)), models(std::move(models)), subgroups(std::move(subgroups)) {}

    explicit Group(tinyxml2::XMLElement *groupElement);

    void draw(float time) const;
};


#endif //CG2324_GROUP_H
