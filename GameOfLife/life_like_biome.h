#ifndef LIFE_LIKE_BIOME_H
#define LIFE_LIKE_BIOME_H

#include "life_like_cell.h"
#include <vector>

namespace LifeLike
{
    class Biome
    {
    public:
        Biome();
        Biome(size_t width, size_t height);

        size_t width() const { return width_; }
        size_t height() const { return height_; }

        Cell& cell_at(size_t x, size_t y);

    private:
        size_t width_ = 0;
        size_t height_ = 0;

        std::vector<Cell> cells_;
    };
}

#endif // LIFE_LIKE_BIOME_H
