#ifndef CG2324_GROUP_H
#define CG2324_GROUP_H


#include <utility>
#include <vector>
#include <memory>
#include "utils/model.h"
#include "transform.h"

class Group
{
private:
    std::vector<std::unique_ptr<Transform>> transforms;
    std::vector<Model> models;
    std::vector<Group> subgroups;

public:
    Group() = default;

    void draw() const;

    Group(std::vector<std::unique_ptr<Transform>> transforms, std::vector<Model> models, std::vector<Group> subgroups)
            : transforms(std::move(transforms)), models(std::move(models)), subgroups(std::move(subgroups)) {}
};


#endif //CG2324_GROUP_H
