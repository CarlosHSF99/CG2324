#include <cmath>
#include <fstream>
#include <GL/glut.h>
#include <iostream>
#include <iterator>
#include "utils/vector3.h"
#include "utils/model.h"

using std::string, std::cerr, std::endl, std::istream, std::fstream, std::ifstream, std::ofstream, std::cos, std::sin, std::ios, std::ostream, std::tuple, std::vector;

Model::Model(const string &filename)
{
    // fstream file(filename, ios::in | ios::binary);
    ifstream file(filename, ios::binary);

    if (!file.is_open()) {
        cerr << "Error opening file " << filename << endl;
        return;
    }

    // std::vector<Point3> tmp((std::istream_iterator<Point3>(file)), std::istream_iterator<Point3>());
    // vertices = std::move(tmp);

    float x, y, z;
    while (file.read(reinterpret_cast<char *>(&x), sizeof(x)) &&
           file.read(reinterpret_cast<char *>(&y), sizeof(y)) &&
           file.read(reinterpret_cast<char *>(&z), sizeof(z))) {
        vertices.emplace_back(x, y, z);
    }
}

Model::Model(const std::vector<Point3> &vertices) : vertices(vertices) {}

Model::Model(const std::vector<Model> &models)
{
    for (const auto &model: models) {
        for (const auto &vertex: model.vertices) {
            vertices.push_back(vertex);
        }
    }
}

void Model::draw() const
{
    glBegin(GL_TRIANGLES);
    for (const auto &[x, y, z]: vertices)
        glVertex3f(x, y, z);
    glEnd();
}

void Model::translate(const Vector3 &v)
{
    vector<Point3> translatedVertices;
    for (const auto &vertex: vertices) {
        translatedVertices.push_back(vertex + v);
    }
    vertices = std::move(translatedVertices);
}

Model Model::translateImmutable(const Vector3 &v) const
{
    vector<Point3> translatedVertices;
    for (const auto &vertex: vertices) {
        translatedVertices.push_back(vertex + v);
    }
    return Model(translatedVertices);
}

void Model::rotate(const Vector3 &v, float angle)
{
    float cosA = cos(angle);
    float sinA = sin(angle);
    float cosComp = 1 - cosA;

    vector<Point3> rotateVertices;
    for (const auto &[x, y, z]: vertices) {
        rotateVertices.emplace_back(
                x * (cosA + cosComp * v.x * v.x) +
                y * (cosComp * v.x * v.y - sinA * v.z) +
                z * (cosComp * v.x * v.z + sinA * v.y),
                x * (cosComp * y + sinA * v.z) +
                y * (cosA + cosComp * v.y * v.y) +
                z * (cosComp * v.y * v.z - sinA * v.x),
                x * (cosComp * v.x * v.z - sinA * v.y) +
                y * (cosComp * v.y * v.z + sinA * v.x) +
                z * (cosA + cosComp * v.z * v.z)
        );
    }
    vertices = std::move(rotateVertices);
}

Model Model::rotateImmutable(const Vector3 &v, float angle)
{
    float cosA = cos(angle);
    float sinA = sin(angle);
    float cosComp = 1 - cosA;

    vector<Point3> rotatedVertices;
    for (const auto &[x, y, z]: vertices) {
        rotatedVertices.emplace_back(
                x * (cosA + cosComp * v.x * v.x) +
                y * (cosComp * v.x * v.y - sinA * v.z) +
                z * (cosComp * v.x * v.z + sinA * v.y),
                x * (cosComp * y + sinA * v.z) +
                y * (cosA + cosComp * v.y * v.y) +
                z * (cosComp * v.y * v.z - sinA * v.x),
                x * (cosComp * v.x * v.z - sinA * v.y) +
                y * (cosComp * v.y * v.z + sinA * v.x) +
                z * (cosA + cosComp * v.z * v.z)
        );
    }

    return Model(rotatedVertices);
}

void Model::scale(const std::tuple<float, float, float> &factors)
{
    auto [sx, sy, sz] = factors;
    vector<Point3> scaledVertices;
    for (const auto &[x, y, z]: vertices) {
        scaledVertices.emplace_back(x * sx, y * sy, z * sz);
    }
    vertices = std::move(scaledVertices);
}

Model Model::scaleImmutable(const std::tuple<float, float, float> &factors)
{
    auto [sx, sy, sz] = factors;
    vector<Point3> scaledVertices;
    for (const auto &[x, y, z]: vertices) {
        scaledVertices.emplace_back(x * sx, y * sy, z * sz);
    }
    return Model(scaledVertices);
}

void Model::writeToFile(const string &filename) const
{
    ofstream file(filename, ios::binary);

    if (!file.is_open()) {
        cerr << "Error opening file " << filename << endl;
        return;
    }

    file.write(reinterpret_cast<const char *>(vertices.data()),
               static_cast<std::streamsize>(vertices.size() * sizeof(Point3)));
}

Model Model::operator+(const Model &model) const
{
    return Model({*this, model});
}

istream &operator>>(istream &is, Model &model)
{
    float x, y, z;
    while (is >> x >> y >> z) {
        model.vertices.emplace_back(x, y, z);
    }
    return is;
}

ostream &operator<<(ostream &os, const Model &model)
{
    for (const auto &vertex: model.vertices) {
        os << vertex << '\n';
    }
    return os;
}
