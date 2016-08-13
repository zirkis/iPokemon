#ifndef TILE_H
#define TILE_H
#include <QtWidgets>

class Tile
{
public:
    Tile(const bool& crossable,QImage& imagePath);
    bool getCrossable() const;
    QImage getLook() const;
private:
    bool m_crossable;
    QImage m_look;
};
#endif // TILE_H
