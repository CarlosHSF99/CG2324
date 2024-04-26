#include "generator/patch_model.h"

#include <cmath>
#include <array>
#include <fstream>
#include <iostream>

using std::vector, std::array;

array<float, 4> multMatrixVector(const float m[4][4], const array<float, 4> &v);

Point3 generatePoint(vector<Point3> patchControlPoints, array<float, 4> um, array<float, 4> vm);

// bezier matrix
static const float M[4][4] = {
        {-1.0f, +3.0f, -3.0f, +1.0f},
        {+3.0f, -6.0f, +3.0f, +0.0f},
        {-3.0f, +3.0f, +0.0f, +0.0f},
        {+1.0f, +0.0f, +0.0f, +0.0f}
};

PatchModel::PatchModel(int tessellationLevel, const vector<array<int, 16>> &indicesList, vector<Point3> controlPoints)
{
    // for each patch
    for (auto &indices: indicesList) {
        // collect control points for current patch
        vector<Point3> patchControlPoints;
        for (const auto &index: indices) {
            patchControlPoints.push_back(controlPoints[index]);
        }

        // generate vectors for current patch
        vector<array<float, 4>> vectors;
        for (int i = 0; i <= tessellationLevel; i++) {
            float t = (float) i / (float) tessellationLevel;
            vectors.push_back(multMatrixVector(M, {powf(t, 3), powf(t, 2), t, 1}));
        }

        // generate vertices for current patch
        vector<Point3> patchVertices;
        for (int i = 0; i <= tessellationLevel; i++) {
            for (int j = 0; j <= tessellationLevel; j++) {
                patchVertices.push_back(generatePoint(patchControlPoints, vectors[i], vectors[j]));
            }
        }

        // add current patch vertices to the model per triangle
        for (int i = 0; i < tessellationLevel; i++) {
            for (int j = 0; j < tessellationLevel; j++) {
                int a = i * (tessellationLevel + 1) + j;
                int b = a + tessellationLevel + 1;

                // triangle 1
                vertices.push_back(patchVertices[a]);
                vertices.push_back(patchVertices[a + 1]);
                vertices.push_back(patchVertices[b]);

                // triangle 2
                vertices.push_back(patchVertices[b]);
                vertices.push_back(patchVertices[a + 1]);
                vertices.push_back(patchVertices[b + 1]);
            }
        }
    }
}

PatchModel::PatchModel(const std::string &filename, int tessellationLevel)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        return;
    }

    int nPatches;
    file >> nPatches;
    vector<array<int, 16>> indicesList(nPatches);

    // read vertices indices for each patch
    for (auto i = 0; i < nPatches; i++) {
        vector<int> patch;
        int index;
        for (int j = 0; j < 16; j++) {
            file >> index;
            file.ignore();
            indicesList[i][j] = index;
        }
    }

    int nControlPoints;
    file >> nControlPoints;
    vector<Point3> patchesControlPoints(nControlPoints);

    // read control points
    for (auto i = 0; i < nControlPoints; i++) {
        float x, y, z;
        char comma;
        file >> x >> comma >> y >> comma >> z;
        patchesControlPoints[i] = {x, y, z};
    }

    *this = PatchModel(tessellationLevel, indicesList, patchesControlPoints);
}

array<float, 4> multMatrixVector(const float m[4][4], const array<float, 4> &v)
{
    array<float, 4> res{};
    for (int i = 0; i < 4; i++) {
        res[i] = 0;
        for (int j = 0; j < 4; j++) {
            res[i] += v[j] * m[i][j];
        }
    }
    return res;
}

Point3 generatePoint(vector<Point3> patchControlPoints, array<float, 4> um, array<float, 4> vm)
{
    Point3 pointUV;
    for (int i = 0; i < 4; i++) {
        Vector3 ump;
        for (int j = 0; j < 4; j++) {
            ump += Vector3(patchControlPoints[j * 4 + i]) * um[j];
        }
        pointUV = pointUV + ump * vm[i];
    }
    return pointUV;
}
