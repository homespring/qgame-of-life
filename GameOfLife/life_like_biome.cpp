#include "life_like_biome.h"

using namespace LifeLike;

Biome::Biome() {}

Biome::Biome(size_t width, size_t height)
    : width_(width), height_(height)
{
    if(width * height > 0)
        cells_.resize(width * height);
}

Cell &Biome::cell_at(size_t x, size_t y)
{
    static Cell default_cell;

    return cells_[x + width_ * y];
}
