#ifndef CELL_H
#define CELL_H

#include <qnamespace.h>
#include "life_like_rule.h"

namespace LifeLike
{
    class Cell
    {
    public:
        Cell(bool alive = false, Qt::GlobalColor alive_color = Qt::white);

        bool is_alive() const { return alive_; }

        void kill() { alive_ = false; }
        void be_born() { alive_ = true; }
        void be_born(Qt::GlobalColor color);

        Qt::GlobalColor color() const { return alive_ ? alive_color_ : Qt::transparent; }

        bool should_be_alive(const Rule& rule, size_t living_neighbors) const;

    private:
        bool alive_;
        Qt::GlobalColor alive_color_;

        bool should_be_born(const Rule& rule, size_t living_neighbors) const;
        bool should_survive(const Rule& rule, size_t living_neighbors) const;
    };
}

#endif // CELL_H
