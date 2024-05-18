#ifndef CG2324_MODEL_H
#define CG2324_MODEL_H


#include <vector>
#include "utils/vertex.h"

class Model
{
protected:
    std::vector<Vertex> vertices;

protected:
    Model() = default;

public:
    void writeToFile(const std::string &filename) const;
};


#endif //CG2324_MODEL_H
