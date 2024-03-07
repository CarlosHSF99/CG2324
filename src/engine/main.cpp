#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include "utils/model.h"
#include "deps/tinyxml2.h"

using namespace tinyxml2;

struct Transformation {
    const char* type;
    Vector3 vector;
    float angle;
};

struct Group {
    std::vector<Transformation> transformations;
    std::vector<Model> models;
    std::vector<Group> nestedGroups;
};

void renderScene();

void parseGroup(XMLElement* groupElement, Group &group, const std::vector<Transformation> &accumulatedTransformations);

void changeSize(int w, int h);

void drawAxis();

float positionX, positionY, positionZ;
float lookAtX, lookAtY, lookAtZ;
float upX, upY, upZ;
float fov, near, far;
Group rootGroup;

int main(int argc, char **argv)
{
    int width, height;

    XMLDocument doc;
    if (doc.LoadFile(argv[1]) == XML_SUCCESS) {
        XMLElement *worldElement = doc.FirstChildElement("world");
        if (worldElement) {
            XMLElement *windowElement = worldElement->FirstChildElement("window");
            if (windowElement) {
                windowElement->QueryIntAttribute("width", &width);
                windowElement->QueryIntAttribute("height", &height);
            }

            XMLElement *cameraElement = worldElement->FirstChildElement("camera");
            if (cameraElement) {
                XMLElement *positionElement = cameraElement->FirstChildElement("position");
                if (positionElement) {
                    positionElement->QueryFloatAttribute("x", &positionX);
                    positionElement->QueryFloatAttribute("y", &positionY);
                    positionElement->QueryFloatAttribute("z", &positionZ);
                }
                XMLElement *lookAtElement = cameraElement->FirstChildElement("lookAt");
                if (lookAtElement) {
                    lookAtElement->QueryFloatAttribute("x", &lookAtX);
                    lookAtElement->QueryFloatAttribute("y", &lookAtY);
                    lookAtElement->QueryFloatAttribute("z", &lookAtZ);
                }
                XMLElement *upElement = cameraElement->FirstChildElement("up");
                if (upElement) {
                    upElement->QueryFloatAttribute("x", &upX);
                    upElement->QueryFloatAttribute("y", &upY);
                    upElement->QueryFloatAttribute("z", &upZ);
                }
                XMLElement *projectionElement = cameraElement->FirstChildElement("projection");
                if (projectionElement) {
                    projectionElement->QueryFloatAttribute("fov", &fov);
                    projectionElement->QueryFloatAttribute("near", &near);
                    projectionElement->QueryFloatAttribute("far", &far);
                }
            }

            XMLElement *rootGroupElement = worldElement->FirstChildElement("group");
            if(rootGroupElement){
                parseGroup(rootGroupElement, rootGroup, {});
            }
        }
    } else {
        std::cerr << "Failed to load file." << std::endl;
    }

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - width) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - height) / 2);
    glutInitWindowSize(width, height);
    glutCreateWindow("CG@DI-UM");

    // required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glutMainLoop();

    return 1;
}

void renderGroups(const std::vector<Group> &groups){
    for (const auto &group : groups){
        for(const auto &model : group.models){
            model.draw();
        }

        renderGroups(group.nestedGroups);
    }
}

void renderScene()
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(positionX, positionY, positionZ,
              lookAtX, lookAtY, lookAtZ,
              upX, upY, upZ);

    drawAxis();
    for (const auto &model: rootGroup.models) {
        model.draw();
    }

    renderGroups(rootGroup.nestedGroups);

    glutSwapBuffers();
}

void changeSize(int w, int h)
{
    // Prevent a divide by zero, when window is too short
    // (you can't make a window of zero width).
    if (h == 0)
        h = 1;

    float ratio = (float) w / (float) h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(fov, ratio, near, far);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void drawAxis()
{
    // save current color
    float currentColor[4];
    glGetFloatv(GL_CURRENT_COLOR, currentColor);

    glBegin(GL_LINES);
    // X Axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);
    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    // Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();

    // restore previous color
    glColor4fv(currentColor);
}

void applyTransformations(const std::vector<Transformation> &transformations, Model &model){
    std::cout << "applyTransformation called\n" << std::endl;

    for(const auto& t : transformations){
        std::cout << "1 transformation applied" << std::endl;
        std::cout << "O tipo da transformação é: " << t.type << std::endl;

        if(strcmp(t.type, "translate") == 0){
            std::cout << "Os valores do translate são " << t.vector.x << " - " << t.vector.y << " - " << t.vector.z << std::endl;
            model.translate(t.vector);
        }
        else if(strcmp(t.type, "scale") == 0){
            model.scale(t.vector);
        }
        else if(strcmp(t.type, "rotate") == 0){
            model.rotate(t.vector, t.angle);
        }
    }
}

void parseTranformations(XMLElement *transformElement, std::vector<Transformation> &transformations){
    std::cout << "parseTransformations called" << std::endl;
    XMLElement *childElement = transformElement->FirstChildElement();
    while(childElement){
        float x, y, z;
        Transformation transform;
        transform.type = childElement->Value();
        if(strcmp(transform.type, "rotate") == 0){
            childElement->QueryFloatAttribute("angle", &transform.angle);
        }

        childElement->QueryFloatAttribute("x", &x);
        childElement->QueryFloatAttribute("y", &y);
        childElement->QueryFloatAttribute("z", &z);
        Vector3 vector1(x, y, z);
        transform.vector = vector1;

        transformations.emplace_back(transform);

        childElement = childElement->NextSiblingElement();
        
    }
}

void parseModels(XMLElement* modelsElement, std::vector<Model> &models, const std::vector<Transformation> &accumulatedTransformations){
    std::cout << "parseModels called" << std::endl;

    XMLElement* modelElement = modelsElement->FirstChildElement("model");
    while(modelElement){
        const char* file = modelElement->Attribute("file");
        Model model(file);
        applyTransformations(accumulatedTransformations, model);
        models.emplace_back(model);
        modelElement = modelElement->NextSiblingElement("model");
    }
}

void parseGroup(XMLElement* groupElement, Group &group, const std::vector<Transformation> &accumulatedTransformations){
    std::cout << "\nparseGroup called" << std::endl;

    XMLElement* childElement = groupElement->FirstChildElement();
    while (childElement) {
        const char* elementName = childElement->Value();
        if (strcmp(elementName, "group") == 0) {
            Group nestedGroup;
            parseGroup(childElement, nestedGroup, group.transformations);
            group.nestedGroups.emplace_back(nestedGroup);
        }
        else if(strcmp(elementName, "transform") == 0){
            std::vector<Transformation> localTransformations = accumulatedTransformations;
            parseTranformations(childElement, localTransformations);
            group.transformations = localTransformations;
        }
        else if(strcmp(elementName, "models") == 0){
            parseModels(childElement, group.models, group.transformations);
        }

        childElement = childElement->NextSiblingElement();
    }
}