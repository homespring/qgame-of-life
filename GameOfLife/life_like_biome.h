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
        const Cell& cell_at(size_t x, size_t y) const;

        uint64_t living_cells_count() const;

        void initialize_randomly(float fill_factor, const std::vector<Qt::GlobalColor>& colors = { Qt::white });

        std::vector<Qt::GlobalColor> neighbors_colors(size_t x, size_t y) const;

        bool operator==(const Biome& other) const;
        bool operator!=(const Biome& other) const;

        std::string to_string() const;

        bool has_living_cell() const;

    private:
        size_t width_ = 0;
        size_t height_ = 0;

        std::vector<Cell> cells_;

        void append_top_left_neighbor_color(size_t x, size_t y, std::vector<Qt::GlobalColor>& out) const;
        void append_top_neighbor_color(size_t x, size_t y, std::vector<Qt::GlobalColor>& out) const;
        void append_top_right_neighbor_color(size_t x, size_t y, std::vector<Qt::GlobalColor>& out) const;
        void append_left_neighbor_color(size_t x, size_t y, std::vector<Qt::GlobalColor>& out) const;
        void append_right_neighbor_color(size_t x, size_t y, std::vector<Qt::GlobalColor>& out) const;
        void append_bottom_left_neighbor_color(size_t x, size_t y, std::vector<Qt::GlobalColor>& out) const;
        void append_bottom_neighbor_color(size_t x, size_t y, std::vector<Qt::GlobalColor>& out) const;
        void append_bottom_right_neighbor_color(size_t x, size_t y, std::vector<Qt::GlobalColor>& out) const;
    };
}

#endif // LIFE_LIKE_BIOME_H
