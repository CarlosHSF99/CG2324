#ifndef CG2324_PATCH_MODEL_H
#define CG2324_PATCH_MODEL_H


#include <vector>
#include "utils/point3.h"
#include "utils/model.h"

class PatchModel : public Model
{
public:
    PatchModel(int tesselationLevel, const std::vector<std::vector<int>>& indicesList, std::vector<Point3> controlPoints);

    PatchModel(const std::string &filename, int tessellationLevel);
};


#endif //CG2324_PATCH_MODEL_H
