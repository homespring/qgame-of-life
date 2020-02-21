#ifndef LIFE_LIKE_COLOR_RULE_H
#define LIFE_LIKE_COLOR_RULE_H

#include <qnamespace.h>
#include <vector>

namespace LifeLike
{
    class ColorRule
    {
    public:
        ColorRule(const std::vector<Qt::GlobalColor>& colors = { Qt::white });

        const std::vector<Qt::GlobalColor> colors() const { return colors_; }

    private:
        std::vector<Qt::GlobalColor> colors_; // available colors for living cells
    };
}

#endif // LIFE_LIKE_COLOR_RULE_H
