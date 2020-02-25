#ifndef LIFE_LIKE_GAME_H
#define LIFE_LIKE_GAME_H

#include "life_like_rule.h"
#include "life_like_biome.h"
#include "life_like_color_rule.h"

namespace LifeLike
{
    class Game
    {
    public:
        Game();
        Game(size_t width, size_t height);
        Game(size_t width, size_t height, const Rule& rule);

        size_t width() const { return width_; }
        size_t height() const { return height_; }

        const Rule& rule() const { return rule_; }
        void set_rule(const Rule& rule) { rule_ = rule; }

        const ColorRule& color_rule() { return color_rule_; }
        void set_color_rule(const ColorRule& color_rule) { color_rule_ = color_rule; }

        uint64_t generation_number() const { return generation_number_; }
        void produce_next_generation();

        void initialize_randomly(float fill_factor);

        uint64_t living_cells_count() const;

        const Biome& current_biome() const;

        void reset();

    protected:
        size_t width_ = 0;
        size_t height_ = 0;

        Rule rule_;
        ColorRule color_rule_;

        uint64_t generation_number_ = 1;

        Biome biome_0, biome_1;

        void reinitialize_biomes();
        Biome& output_biome();
        Biome& current_biome_internal();
    };
}

#endif // LIFE_LIKE_GAME_H
