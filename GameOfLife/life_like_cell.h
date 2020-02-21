#ifndef CELL_H
#define CELL_H

#include <QColor>
#include "life_like_rule.h"

namespace LifeLike
{
    class Cell
    {
    public:
        Cell(bool alive = false);

        bool is_alive() const { return alive_; }

        Qt::GlobalColor color() const { return alive_ ? Qt::white : Qt::transparent; }

        bool should_be_alive(const Rule& rule, int living_neighbors);

    private:
        bool alive_;

        bool should_be_born(const Rule& rule, int living_neighbors);
        bool should_survive(const Rule& rule, int living_neighbors);
    };
}

#endif // CELL_H
