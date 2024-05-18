#include "utils/vertex.h"

Vertex &Vertex::operator=(Vertex const &other) noexcept
{
    if (this != &other) {
        std::destroy_at(this);
        std::construct_at(this, other);
    }
    return *this;
}
