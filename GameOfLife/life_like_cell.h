#ifndef CELL_H
#define CELL_H

#include <QColor>
#include "life_like_rule.h"

namespace LifeLike
{
    class Cell
    {
    public:
        Cell(bool alive = false, Qt::GlobalColor alive_color = Qt::white);

        bool is_alive() const { return alive_; }

        void kill() { alive_ = false; }
        void born() { alive_ = true; }
        void born(Qt::GlobalColor color);

        Qt::GlobalColor color() const { return alive_ ? alive_color_ : Qt::transparent; }

        bool should_be_alive(const Rule& rule, int living_neighbors);

    private:
        bool alive_;
        Qt::GlobalColor alive_color_;

        bool should_be_born(const Rule& rule, int living_neighbors);
        bool should_survive(const Rule& rule, int living_neighbors);
    };
}

#endif // CELL_H
