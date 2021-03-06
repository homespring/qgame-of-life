#include "life_like_cell.h"

using namespace LifeLike;

Cell::Cell(bool alive, Qt::GlobalColor alive_color)
    : alive_(alive), alive_color_(alive_color) {}

void Cell::be_born(Qt::GlobalColor color)
{
    alive_ = true;
    alive_color_ = color;
}

bool Cell::should_be_alive(const Rule &rule, size_t living_neighbors) const
{
    if(!alive_)
        return should_be_born(rule, living_neighbors);
    else
        return should_survive(rule, living_neighbors);
}

bool Cell::should_be_born(const Rule &rule, size_t living_neighbors) const
{
    return rule.birth_rule() & Rule::neighbor_count_to_enum(living_neighbors);
}

bool Cell::should_survive(const Rule &rule, size_t living_neighbors) const
{
    return rule.survival_rule() & Rule::neighbor_count_to_enum(living_neighbors);
}
