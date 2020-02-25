#include "life_like_color_rule.h"
#include <ctime>

using namespace LifeLike;

ColorRule::ColorRule(const std::vector<Qt::GlobalColor>& colors)
    : colors_(colors)
{
    srand(static_cast<unsigned>(time(nullptr)));
}

Qt::GlobalColor ColorRule::new_cell_color(const std::vector<Qt::GlobalColor> &neighbor_colors) const
{
    if(neighbor_colors.empty())
        return random_color();

    std::map<Qt::GlobalColor, size_t> counters;

    for(auto& color : neighbor_colors)
        ++counters[color];

    std::vector<Qt::GlobalColor> neighbors_unique_colors;

    for(const auto& col : neighbor_colors)
        if(std::find(neighbors_unique_colors.begin(),
                     neighbors_unique_colors.end(),
                     col) == neighbors_unique_colors.end())
            neighbors_unique_colors.push_back(col);

    if(neighbors_unique_colors.size() == 1)
        return neighbors_unique_colors.front();

    const size_t expected_freq = counters.at(neighbor_colors.front());

    for(auto i = std::begin(counters); i != std::end(counters); ++i)
        if(i->second != expected_freq)
            return find_most_frequent_color(counters);

    // here we know that every color occurs in the same frequency

    if(neighbors_unique_colors.size() == colors_.size())
    {
        // every color used, same frequency -> return random
        return random_color();
    }
    else
    {
        // not every color used, rest have same frequency -> return not used color

        for(const auto& col : colors_)
            if(std::find(neighbors_unique_colors.begin(),
                         neighbors_unique_colors.end(),
                         col) == neighbors_unique_colors.end())
                return col;
    }

    return find_most_frequent_color(counters);
}

Qt::GlobalColor ColorRule::find_most_frequent_color(std::map<Qt::GlobalColor, size_t> counters) const
{
    using pair_type = decltype(counters)::value_type;

    const auto res = std::max_element(
                std::begin(counters), std::end(counters),
                [](const pair_type& p1, const pair_type& p2)
                    {
                        return p1.second < p2.second;
                    }
                );

    return res->first;
}

Qt::GlobalColor ColorRule::random_color() const
{
    return colors_.at(static_cast<size_t>(rand()) % colors_.size());
}
