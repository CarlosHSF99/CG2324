#ifndef CG2324_MODEL_H
#define CG2324_MODEL_H


#include <string>
#include <vector>
#include <ostream>
#include "utils/point3.h"
#include "utils/vector3.h"

class Model
{
protected:
    std::vector<Point3> vertices;

protected:
    Model() = default;

public:

    explicit Model(const std::vector<Point3> &vertices);

    explicit Model(const std::vector<Model> &models);

    explicit Model(const std::string &filename);

    void draw() const;

    void writeToFile(const std::string &filename) const;

    void translate(const Vector3 &vector);

    void rotate(const Vector3 &vector, float angle);

    void scale(const std::tuple<float, float, float> &factors);

    Model operator+(const Model &model) const;

    friend std::istream &operator>>(std::istream &is, Model &model);

    friend std::ostream &operator<<(std::ostream &os, const Model &model);
};


#endif //CG2324_MODEL_H
