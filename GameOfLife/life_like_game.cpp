#include "life_like_game.h"
#include <QDebug>

using namespace LifeLike;

Game::Game() {}

Game::Game(size_t width, size_t height)
    : width_(width), height_(height)
{
    reinitialize_biomes();
}

Game::Game(size_t width, size_t height, const Rule &rule)
    : width_(width), height_(height), rule_(rule)
{
    reinitialize_biomes();
}

void Game::produce_next_generation()
{
    for(size_t y = 0; y < height(); ++y)
    {
        for(size_t x = 0; x < width(); ++x)
        {
            const auto living_neighbors_colors = current_biome().neighbors_colors(x, y);

            if(color_rule_.colors().size() > 1)
            {
                if(current_biome().cell_at(x, y).should_be_alive(rule_, living_neighbors_colors.size()))
                    output_biome().cell_at(x, y).be_born(color_rule_.new_cell_color(living_neighbors_colors));
                else
                    output_biome().cell_at(x, y).kill();
            }
            else
            {
                if(current_biome().cell_at(x, y).should_be_alive(rule_, living_neighbors_colors.size()))
                    output_biome().cell_at(x, y).be_born();
                else
                    output_biome().cell_at(x, y).kill();
            }
        }
    }

    ++generation_number_;
}

void Game::initialize_randomly(float fill_factor)
{
    generation_number_ = 1;
    current_biome_internal().initialize_randomly(fill_factor, color_rule_.colors());
}

uint64_t Game::living_cells_count() const
{
    return current_biome().living_cells_count();
}

const Biome &Game::current_biome() const
{
    if(generation_number_ % 2 == 1)
        return biome_0;
    else
        return biome_1;
}

void Game::reset()
{
    generation_number_ = 1;

    for(size_t y = 0; y < height(); ++y)
        for(size_t x = 0; x < width(); ++x)
            current_biome_internal().cell_at(x, y).kill();
}

void Game::toggle_cell_at(size_t x, size_t y)
{
    if(current_biome().cell_at(x, y).is_alive())
    {
        current_biome_internal().cell_at(x, y).kill();
        return;
    }

    const auto living_neighbors_colors = current_biome().neighbors_colors(x, y);

    if(color_rule_.colors().size() > 1)
    {
        current_biome_internal().cell_at(x, y).be_born(color_rule_.new_cell_color(living_neighbors_colors));
    }
    else
    {
        current_biome_internal().cell_at(x, y).be_born();
    }
}

void Game::reinitialize_biomes()
{
    biome_0 = Biome(width_, height_);
    biome_1 = Biome(width_, height_);
}

Biome &Game::output_biome()
{
    if(generation_number_ % 2 == 1)
        return biome_1;
    else
        return biome_0;
}

Biome &Game::current_biome_internal()
{
    if(generation_number_ % 2 == 1)
        return biome_0;
    else
        return biome_1;
}
