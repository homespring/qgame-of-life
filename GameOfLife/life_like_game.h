#ifndef LIFE_LIKE_GAME_H
#define LIFE_LIKE_GAME_H

#include "life_like_rule.h"

namespace LifeLike
{
    class Game
    {
    public:
        Game();
        Game(int width, int height);
        Game(int width, int height, const Rule& rule);

        int width() const { return width_; }
        int height() const { return height_; }

        const Rule& rule() const { return rule_; }
        void set_rule(const Rule& rule) { rule_ = rule; }

    private:
        int width_ = 0;
        int height_ = 0;

        Rule rule_;
    };
}

#endif // LIFE_LIKE_GAME_H
