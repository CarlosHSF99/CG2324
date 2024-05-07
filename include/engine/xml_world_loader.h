#ifndef CG2324_XML_WORLD_LOADER_H
#define CG2324_XML_WORLD_LOADER_H


#include "engine/world.h"

namespace XMLWorldLoader
{
    Window loadWindow(char *filename);

    World loadWorld(char *filename);
}


#endif //CG2324_XML_WORLD_LOADER_H
