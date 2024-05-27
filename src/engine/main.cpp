#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <IL/il.h>
#include "engine/scene/window.h"
#include "engine/scene/world.h"
#include "deps/tinyxml2.h"

using namespace tinyxml2;

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <xml_file>" << std::endl;
        return 1;
    }

    XMLDocument doc;
    if (doc.LoadFile(argv[1]) != XML_SUCCESS) {
        std::cerr << "Failed to load file." << std::endl;
        return 1;
    }

    XMLElement *worldElement = doc.FirstChildElement("world");
    if (!worldElement) {
        return 1;
    }

    XMLElement *windowElement = worldElement->FirstChildElement("window");
    if (!windowElement) {
        return 1;
    }

    Window window(windowElement);

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(window.x, window.y);
    glutInitWindowSize(window.width, window.height);
    glutCreateWindow(argv[1]);

    glewInit();

    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

    static World world(worldElement);

    // callback registry
    glutDisplayFunc([]() { world.renderScene(); });
    glutReshapeFunc([](int w, int h) { world.changeSize(w, h); });
    glutIdleFunc([]() { world.renderScene(); });
    glutKeyboardFunc([](unsigned char key, int xx, int yy) { world.processNormalKeys(key, xx, yy); });

    // OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_RESCALE_NORMAL);

    // controls global ambient light
    float amb[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glutMainLoop();

    return 1;
}
