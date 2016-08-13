#include "tile.h"

Tile::Tile(const bool &crossable, QImage &imagePath)
{
    m_crossable = crossable;
    m_look = imagePath;
}
bool Tile::getCrossable()const{
    return m_crossable;
}
QImage Tile::getLook()const{
    return m_look;
}

