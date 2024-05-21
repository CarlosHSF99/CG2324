#include <cmath>
#include <array>
#include <fstream>
#include <iostream>
#include "generator/patch_model.h"

using std::array, std::pair, std::vector;

std::pair<array<double, 4>, array<double, 4>> getVectors(double t);

Vertex
generateVertex(const vector<Point3> &patchControlPoints, array<double, 4> um, array<double, 4> vm, array<double, 4> ud,
               array<double, 4> vd, double u, double v);

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
        double x, y, z;
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
        vector<pair<array<double, 4>, array<double, 4>>> vectors;
        for (int i = 0; i <= tessellationLevel; i++) {
            double t = (double) i / tessellationLevel;
            vectors.push_back(getVectors(t));
        }

        // generate vertices
        vector<Vertex> patchVertices;
        for (int i = 0; i <= tessellationLevel; i++) {
            for (int j = 0; j <= tessellationLevel; j++) {
                auto [uv, udv] = vectors[i];
                auto [vv, vdv] = vectors[j];
                double u = (double) i / tessellationLevel;
                double v = (double) j / tessellationLevel;
                patchVertices.emplace_back(generateVertex(patchControlPoints, uv, vv, udv, vdv, u, v));
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
generateVertex(const vector<Point3> &patchControlPoints, array<double, 4> um, array<double, 4> vm, array<double, 4> ud,
               array<double, 4> vd, double u, double v)
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

    return {pointUV, normalV.cross(normalU).normalize(), Vector2(1 - v, 1 - u)};
}

pair<array<double, 4>, array<double, 4>> getVectors(double t)
{
    // bezier matrix
    static const double m[4][4] = {
            {-1.0, +3.0, -3.0, +1.0},
            {+3.0, -6.0, +3.0, +0.0},
            {-3.0, +3.0, +0.0, +0.0},
            {+1.0, +0.0, +0.0, +0.0}
    };

    double tv[]{pow(t, 3), pow(t, 2), t, 1};
    double tdv[]{3 * pow(t, 2), 2 * t, 1, 0};

    array<double, 4> res1{};
    array<double, 4> res2{};

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
