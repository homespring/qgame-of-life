#ifndef LIFE_LIKE_COLOR_RULE_H
#define LIFE_LIKE_COLOR_RULE_H

#include <qnamespace.h>
#include <map>
#include <vector>

namespace LifeLike
{
    class ColorRule
    {
    public:
        ColorRule(const std::vector<Qt::GlobalColor>& colors = { Qt::white });

        const std::vector<Qt::GlobalColor> colors() const { return colors_; }

        Qt::GlobalColor new_cell_color(const std::vector<Qt::GlobalColor>& neighbor_colors) const;

    private:
        std::vector<Qt::GlobalColor> colors_; // available colors for living cells

        Qt::GlobalColor find_most_frequent_color(std::map<Qt::GlobalColor, size_t> counters) const;
        Qt::GlobalColor random_color() const;
    };
}

#endif // LIFE_LIKE_COLOR_RULE_H
