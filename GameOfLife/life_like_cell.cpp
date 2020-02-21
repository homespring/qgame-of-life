#include "life_like_cell.h"

using namespace LifeLike;

Cell::Cell(bool alive)
    : alive_(alive) {}

bool Cell::should_be_alive(const Rule &rule, int living_neighbors)
{
    if(!alive_)
        return should_be_born(rule, living_neighbors);
    else
        return should_survive(rule, living_neighbors);
}

bool Cell::should_be_born(const Rule &rule, int living_neighbors)
{
    return rule.birth_rule() & Rule::neighbor_count_to_enum(living_neighbors);
}

bool Cell::should_survive(const Rule &rule, int living_neighbors)
{
    return rule.survival_rule() & Rule::neighbor_count_to_enum(living_neighbors);
}
