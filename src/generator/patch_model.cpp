#include <cmath>
#include <array>
#include <fstream>
#include <iostream>
#include "generator/patch_model.h"

using std::array, std::pair, std::vector;

std::pair<array<float, 4>, array<float, 4>> getVectors(float t);

Vertex
generateVertex(const vector<Point3> &patchControlPoints, array<float, 4> um, array<float, 4> vm, array<float, 4> ud,
               array<float, 4> vd);

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

PatchModel::PatchModel(int tessellationLevel, const vector<array<int, 16>> &indicesList, vector<Point3> controlPoints)
{
    // for each patch
    for (auto &indices: indicesList) {
        // collect control points
        vector<Point3> patchControlPoints;
        for (const auto &index: indices) {
            patchControlPoints.push_back(controlPoints[index]);
        }

        // generate vectors
        vector<pair<array<float, 4>, array<float, 4>>> vectors;
        for (int i = 0; i <= tessellationLevel; i++) {
            float t = (float) i / (float) tessellationLevel;
            vectors.push_back(getVectors(t));
        }

        // generate vertices
        vector<Vertex> patchVertices;
        for (int i = 0; i <= tessellationLevel; i++) {
            for (int j = 0; j <= tessellationLevel; j++) {
                auto [uv, udv] = vectors[i];
                auto [vv, vdv] = vectors[j];
                patchVertices.emplace_back(generateVertex(patchControlPoints, uv, vv, udv, vdv));
            }
        }

        // add patch vertices to model vertices per triangle
        for (int i = 0; i < tessellationLevel; i++) {
            for (int j = 0; j < tessellationLevel; j++) {
                int a = i * (tessellationLevel + 1) + j;
                int b = a + tessellationLevel + 1;

                // triangle 1
                vertices.emplace_back(patchVertices[a]);
                vertices.emplace_back(patchVertices[a + 1]);
                vertices.emplace_back(patchVertices[b]);

                // triangle 2
                vertices.emplace_back(patchVertices[b]);
                vertices.emplace_back(patchVertices[a + 1]);
                vertices.emplace_back(patchVertices[b + 1]);
            }
        }
    }
}

Vertex
generateVertex(const vector<Point3> &patchControlPoints, array<float, 4> um, array<float, 4> vm, array<float, 4> ud,
               array<float, 4> vd)
{
    Point3 pointUV;
    Vector3 normalU;
    Vector3 normalV;

    for (int i = 0; i < 4; i++) {
        Vector3 ump;
        Vector3 udp;
        for (int j = 0; j < 4; j++) {
            ump += Vector3(patchControlPoints[j * 4 + i]) * um[j];
            udp += Vector3(patchControlPoints[j * 4 + i]) * ud[j];
        }
        pointUV = pointUV + ump * vm[i];
        normalU = normalU + udp * vm[i];
        normalV = normalV + ump * vd[i];
    }

    return {pointUV, normalV.cross(normalU).normalize()};
}

pair<array<float, 4>, array<float, 4>> getVectors(float t)
{
    // bezier matrix
    static const float m[4][4] = {
            {-1.0f, +3.0f, -3.0f, +1.0f},
            {+3.0f, -6.0f, +3.0f, +0.0f},
            {-3.0f, +3.0f, +0.0f, +0.0f},
            {+1.0f, +0.0f, +0.0f, +0.0f}
    };

    float tv[]{powf(t, 3), powf(t, 2), t, 1};
    float tdv[]{3 * powf(t, 2), 2 * t, 1, 0};

    array<float, 4> res1{};
    array<float, 4> res2{};

    for (int i = 0; i < 4; i++) {
        res1[i] = 0;
        res2[i] = 0;
        for (int j = 0; j < 4; j++) {
            res1[i] += tv[j] * m[i][j];
            res2[i] += tdv[j] * m[i][j];
        }
    }

    return {res1, res2};
}
