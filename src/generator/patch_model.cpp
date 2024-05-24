#include <cmath>
#include <array>
#include <fstream>
#include <iostream>
#include "generator/patch_model.h"

using std::array, std::pair, std::vector;

std::pair<array<double, 4>, array<double, 4>> getVectors(double t);

Vertex
generateVertex(const vector<Point3> &P, array<double, 4> UM, array<double, 4> VM, array<double, 4> dUM,
               array<double, 4> dVM, double u, double v);

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
    // generate vectors
    vector<pair<array<double, 4>, array<double, 4>>> vectors;
    for (int i = 0; i <= tessellationLevel; i++) {
        vectors.push_back(getVectors((double) i / tessellationLevel));
    }

    // for each patch
    for (auto &indices: indicesList) {
        // collect control points
        vector<Point3> P;
        for (const auto &index: indices) {
            P.push_back(controlPoints[index]);
        }

        // generate vertices
        vector<Vertex> patchVertices;
        for (int i = 0; i <= tessellationLevel; i++) {
            for (int j = 0; j <= tessellationLevel; j++) {
                auto [UM, dUM] = vectors[i];
                auto [VM, dVM] = vectors[j];
                double u = (double) j / tessellationLevel;
                double v = (double) i / tessellationLevel;
                patchVertices.emplace_back(generateVertex(P, UM, VM, dUM, dVM, u, v));
            }
        }

        // add patch vertices to model vertices per triangle
        for (int i = 0; i < tessellationLevel; i++) {
            for (int j = 0; j < tessellationLevel; j++) {
                int bottomLeft = i * (tessellationLevel + 1) + j;
                int bottomRight = bottomLeft + 1;
                int topLeft = bottomLeft + tessellationLevel + 1;
                int topRight = topLeft + 1;

                // triangle 1
                vertices.emplace_back(patchVertices[bottomLeft]);
                vertices.emplace_back(patchVertices[bottomRight]);
                vertices.emplace_back(patchVertices[topLeft]);

                // triangle 2
                vertices.emplace_back(patchVertices[topLeft]);
                vertices.emplace_back(patchVertices[bottomRight]);
                vertices.emplace_back(patchVertices[topRight]);
            }
        }
    }
}

Vertex
generateVertex(const vector<Point3> &P, array<double, 4> UM, array<double, 4> VM, array<double, 4> dUM,
               array<double, 4> dVM, double u, double v)
{
    Point3 pointUV;
    Vector3 tangentU;
    Vector3 tangentV;

    for (int i = 0; i < 4; i++) {
        Vector3 UMP;
        Vector3 dUMP;
        for (int j = 0; j < 4; j++) {
            UMP += Vector3(P[j * 4 + i]) * UM[j];
            dUMP += Vector3(P[j * 4 + i]) * dUM[j];
        }
        pointUV = pointUV + UMP * VM[i];
        tangentU = tangentU + dUMP * VM[i];
        tangentV = tangentV + UMP * dVM[i];
    }

    return {pointUV, tangentV.cross(tangentU).normalize(), Vector2(1 - u, 1 - v)};
}

pair<array<double, 4>, array<double, 4>> getVectors(double t)
{
    // bezier matrix
    static const double M[4][4] = {
            {-1.0, +3.0, -3.0, +1.0},
            {+3.0, -6.0, +3.0, +0.0},
            {-3.0, +3.0, +0.0, +0.0},
            {+1.0, +0.0, +0.0, +0.0}
    };

    double T[]{pow(t, 3), pow(t, 2), t, 1};
    double Td[]{3 * pow(t, 2), 2 * t, 1, 0};

    array<double, 4> TM{};
    array<double, 4> dTM{};

    for (int i = 0; i < 4; i++) {
        TM[i] = 0;
        dTM[i] = 0;
        for (int j = 0; j < 4; j++) {
            TM[i] += T[j] * M[i][j];
            dTM[i] += Td[j] * M[i][j];
        }
    }

    return {TM, dTM};
}
