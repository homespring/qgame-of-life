#include "life_like_biome.h"
#include <ctime>
#include <sstream>

using namespace LifeLike;

Biome::Biome() {}

Biome::Biome(size_t width, size_t height)
    : width_(width), height_(height)
{
    if(width * height > 0)
        cells_.resize(width * height);

    srand(static_cast<unsigned>(time(nullptr)));
}

Cell &Biome::cell_at(size_t x, size_t y)
{
    return cells_[x + width_ * y];
}

const Cell &Biome::cell_at(size_t x, size_t y) const
{
    return cells_.at(x + width_ * y);
}

uint64_t Biome::living_cells_count() const
{
    uint64_t cnt = 0;

    for(const auto& cell : cells_)
        if(cell.is_alive())
            ++cnt;

    return cnt;
}

void Biome::initialize_randomly(float fill_factor)
{
    if(cells_.size() == 0)
        return;

    if(fill_factor >= 1.0f)
    {
        for(auto& cell : cells_)
            cell.be_born();

        return;
    }

    for(auto& cell : cells_)
        cell.kill();

    if(fill_factor <= 0.0f)
        return;

    const uint64_t cells_to_be_born = static_cast<uint64_t>(fill_factor * cells_.size());

    for(size_t i = 0; i < cells_to_be_born; ++i)
    {
        size_t id;

        do
        {
            id = static_cast<size_t>(rand()) % cells_.size();
        } while(cells_.at(id).is_alive());

        cells_[id].be_born();
    }
}

std::vector<Qt::GlobalColor> Biome::neighbors_colors(size_t x, size_t y) const
{
    std::vector<Qt::GlobalColor> ret;

    append_top_left_neighbor_color(x, y, ret);
    append_top_neighbor_color(x, y, ret);
    append_top_right_neighbor_color(x, y, ret);
    append_left_neighbor_color(x, y, ret);
    append_right_neighbor_color(x, y, ret);
    append_bottom_left_neighbor_color(x, y, ret);
    append_bottom_neighbor_color(x, y, ret);
    append_bottom_right_neighbor_color(x, y, ret);

    return ret;
}

bool Biome::operator==(const Biome &other) const
{
    if(width_ != other.width_ || height_ != other.height_)
        return false;

    for(size_t i = 0; i < cells_.size(); ++i)
        if(cells_.at(i).is_alive() != other.cells_.at(i).is_alive())
            return false;

    return true;
}

bool Biome::operator!=(const Biome &other) const
{
    return !(*this == other);
}

std::string Biome::to_string() const
{
    std::stringstream ss;

    for(size_t y = 0; y < height_; ++y)
    {
        for(size_t x = 0; x < width_; ++x)
        {
            ss << (cell_at(x, y).is_alive() ? "1" : "0");

            if(x < (width_ - 1))
                ss << " ";
        }

        ss << std::endl;
    }

    return ss.str();
}

void Biome::append_top_left_neighbor_color(size_t x, size_t y, std::vector<Qt::GlobalColor> &out) const
{
    if(x == 0 || y == 0)
        return;

    const Qt::GlobalColor col = cell_at(--x, --y).color();

    if(col != Qt::transparent)
        out.push_back(col);
}

void Biome::append_top_neighbor_color(size_t x, size_t y, std::vector<Qt::GlobalColor> &out) const
{
    if(y == 0)
        return;

    const Qt::GlobalColor col = cell_at(x, --y).color();

    if(col != Qt::transparent)
        out.push_back(col);
}

void Biome::append_top_right_neighbor_color(size_t x, size_t y, std::vector<Qt::GlobalColor> &out) const
{
    if(x == (width_ - 1) || y == 0)
        return;

    const Qt::GlobalColor col = cell_at(++x, --y).color();

    if(col != Qt::transparent)
        out.push_back(col);
}

void Biome::append_left_neighbor_color(size_t x, size_t y, std::vector<Qt::GlobalColor> &out) const
{
    if(x == 0)
        return;

    const Qt::GlobalColor col = cell_at(--x, y).color();

    if(col != Qt::transparent)
        out.push_back(col);
}

void Biome::append_right_neighbor_color(size_t x, size_t y, std::vector<Qt::GlobalColor> &out) const
{
    if(x == (width_ - 1))
        return;

    const Qt::GlobalColor col = cell_at(++x, y).color();

    if(col != Qt::transparent)
        out.push_back(col);
}

void Biome::append_bottom_left_neighbor_color(size_t x, size_t y, std::vector<Qt::GlobalColor> &out) const
{
    if(x == 0 || y == (height_ - 1))
        return;

    const Qt::GlobalColor col = cell_at(--x, ++y).color();

    if(col != Qt::transparent)
        out.push_back(col);
}

void Biome::append_bottom_neighbor_color(size_t x, size_t y, std::vector<Qt::GlobalColor> &out) const
{
    if(y == (height_ - 1))
        return;

    const Qt::GlobalColor col = cell_at(x, ++y).color();

    if(col != Qt::transparent)
        out.push_back(col);
}

void Biome::append_bottom_right_neighbor_color(size_t x, size_t y, std::vector<Qt::GlobalColor> &out) const
{
    if(x == (width_ - 1) || y == (height_ - 1))
        return;

    const Qt::GlobalColor col = cell_at(++x, ++y).color();

    if(col != Qt::transparent)
        out.push_back(col);
}
