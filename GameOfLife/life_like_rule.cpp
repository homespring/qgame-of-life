#include "life_like_rule.h"
#include <cctype>

using namespace LifeLike;

Rule::Rule(RuleName name)
    : name_(name)
{
    birth_rule_ = birth_rule(name_);
    survival_rule_ = survival_rule(name_);
}

Rule::Rule(const std::string &rule_str)
{
    if(parse_rle_rule_string(rule_str))
    {
        name_ = CUSTOM;
    }
    else if(parse_mcell_rule_string(rule_str))
    {
        name_ = CUSTOM;
    }
    else
    {
        name_ = INVALID_RULE;
        birth_rule_ = 0;
        survival_rule_ = 0;
    }
}

std::string Rule::name_string(Rule::RuleName name)
{
    switch(name)
    {
    case LIFE:
        return "Life";
    case REPLICATOR:
        return "Replicator";
    case SEEDS:
        return "Seeds";
    case LIFE_WITHOUT_DEATH:
        return "Life w/o death";
    case LIFE_34:
        return "34 Life";
    case DIAMOEBA:
        return "Diamoeba";
    case TWO_BY_TWO:
        return "2x2";
    case HIGH_LIFE:
        return "High Life";
    case DAY_AND_NIGHT:
        return "Day and Night";
    case MORLEY:
        return "Morley";
    case ANNEAL:
        return "Anneal";
    case CUSTOM:
        return "custom";
    default:
        return "invalid";
    }
}

std::string Rule::name_string() const
{
    return name_string(name_);
}

uint16_t Rule::birth_rule(Rule::RuleName name)
{
    switch(name)
    {
    case LIFE:
        return WITH_3_CELLS;
    case REPLICATOR:
        return WITH_1_CELL | WITH_3_CELLS | WITH_5_CELLS | WITH_7_CELLS;
    case SEEDS:
        return WITH_2_CELLS;
    case LIFE_WITHOUT_DEATH:
        return WITH_3_CELLS;
    case LIFE_34:
        return WITH_3_CELLS | WITH_4_CELLS;
    case DIAMOEBA:
        return WITH_3_CELLS | WITH_5_CELLS | WITH_6_CELLS | WITH_7_CELLS | WITH_8_CELLS;
    case TWO_BY_TWO:
        return WITH_3_CELLS | WITH_6_CELLS;
    case HIGH_LIFE:
        return WITH_3_CELLS | WITH_6_CELLS;
    case DAY_AND_NIGHT:
        return WITH_3_CELLS | WITH_6_CELLS | WITH_7_CELLS | WITH_8_CELLS;
    case MORLEY:
        return WITH_3_CELLS | WITH_6_CELLS | WITH_8_CELLS;
    case ANNEAL:
        return WITH_4_CELLS | WITH_6_CELLS | WITH_7_CELLS | WITH_8_CELLS;
    default:
        return 0;
    }
}

std::string Rule::birth_rule_string(Rule::RuleName name)
{
    return flags_to_string_internal(birth_rule(name));
}

std::string Rule::birth_rule_string() const
{
    return flags_to_string_internal(birth_rule_);
}

uint16_t Rule::survival_rule(Rule::RuleName name)
{
    switch(name)
    {
    case LIFE:
    case HIGH_LIFE:
        return WITH_2_CELLS | WITH_3_CELLS;
    case REPLICATOR:
        return WITH_1_CELL | WITH_3_CELLS | WITH_5_CELLS | WITH_7_CELLS;
    case SEEDS:
        return 0;
    case LIFE_WITHOUT_DEATH:
        return WITH_ALL_CELLS;
    case LIFE_34:
        return WITH_3_CELLS | WITH_4_CELLS;
    case DIAMOEBA:
        return WITH_5_CELLS | WITH_6_CELLS | WITH_7_CELLS | WITH_8_CELLS;
    case TWO_BY_TWO:
        return WITH_1_CELL | WITH_2_CELLS | WITH_5_CELLS;
    case DAY_AND_NIGHT:
        return WITH_3_CELLS | WITH_4_CELLS | WITH_6_CELLS | WITH_7_CELLS | WITH_8_CELLS;
    case MORLEY:
        return WITH_2_CELLS | WITH_4_CELLS | WITH_5_CELLS;
    case ANNEAL:
        return WITH_3_CELLS | WITH_5_CELLS | WITH_6_CELLS | WITH_7_CELLS | WITH_8_CELLS;
    default:
        return 0;
    }

}

std::string Rule::survival_rule_string(Rule::RuleName name)
{
    return flags_to_string_internal(survival_rule(name));
}

std::string Rule::survival_rule_string() const
{
    return flags_to_string_internal(survival_rule_);
}

std::string Rule::to_mcell_notation(Rule::RuleName name)
{
    return to_mcell_notation_internal(birth_rule_string(name), survival_rule_string(name));
}

std::string Rule::to_mcell_notation() const
{
    return to_mcell_notation_internal(birth_rule_string(), survival_rule_string());
}

std::string Rule::to_rle_notation(Rule::RuleName name)
{
    return to_rle_notation_internal(birth_rule_string(name), survival_rule_string(name));
}

std::string Rule::to_rle_notation() const
{
    return to_rle_notation_internal(birth_rule_string(), survival_rule_string());
}

Rule::Neighborhood Rule::neighbor_count_to_enum(size_t neighbor_cnt)
{
    switch(neighbor_cnt)
    {
    case 0: return WITH_0_CELLS;
    case 1: return WITH_1_CELL;
    case 2: return WITH_2_CELLS;
    case 3: return WITH_3_CELLS;
    case 4: return WITH_4_CELLS;
    case 5: return WITH_5_CELLS;
    case 6: return WITH_6_CELLS;
    case 7: return WITH_7_CELLS;
    case 8: return WITH_8_CELLS;
    default: return UNKNOWN_CELL_NUMBER;
    }
}

std::string Rule::flags_to_string_internal(uint16_t flags)
{
    std::string ret;

    for(int neighbors = 0; neighbors <= 8; ++neighbors)
    {
        if(flags & (1 << neighbors))
            ret.append(std::to_string(neighbors));
    }

    return ret;
}

std::string Rule::to_mcell_notation_internal(const std::string &birth_rule_str, const std::string &survival_rule_str)
{
    return survival_rule_str + "/" + birth_rule_str;
}

std::string Rule::to_rle_notation_internal(const std::string &birth_rule_str, const std::string &survival_rule_str)
{
    return "B" + birth_rule_str + "/S" + survival_rule_str;
}

bool Rule::parse_rle_rule_string(const std::string &rule_str)
{
    // RLE format: Bx/Sy, where x,y == (0, 1, 2, ... 8)
    // x - birth rule, y - survival rule
    // minimal example: B/S
    // maximal example: B012345678/S012345678

    if(rule_str.size() < 3)
        return false;

    if(rule_str.front() != 'B')
        return false;

    size_t off;
    bool birth_rule_parsing = true;

    birth_rule_ = 0;
    survival_rule_ = 0;

    for(off = 1; off < rule_str.size(); ++off)
    {
        if(birth_rule_parsing)
        {
            if(isdigit(rule_str.at(off)))
            {
                birth_rule_ |= digit_char_to_neighborhood(rule_str.at(off));
            }
            else
            {
                if(rule_str.at(off) == '/')
                {
                    if(off + 1 < rule_str.size())
                    {
                        if(rule_str.at(++off) == 'S')
                            birth_rule_parsing = false;
                        else
                            return false; // parsing error
                    }
                }
                else
                    return false;
            }
        }
        else
        {
            // survival rule parsing

            if(isdigit(rule_str.at(off)))
            {
                survival_rule_ |= digit_char_to_neighborhood(rule_str.at(off));
            }
            else
                return false;
        }
    }

    return true;
}

bool Rule::parse_mcell_rule_string(const std::string &rule_str)
{
    // Mirek's Cellebration format: x/y, where x,y == (0, 1, 2, ... 8)
    // x - survival rule, y - birth rule
    // minimal example: /
    // maximal example: 012345678/012345678

    if(rule_str.size() < 1)
        return false;

    if(rule_str.find('/') == std::string::npos)
        return false;

    bool survival_rule_parsing = true;

    birth_rule_ = 0;
    survival_rule_ = 0;

    for(size_t off = 0; off < rule_str.size(); ++off)
    {
        if(survival_rule_parsing)
        {
            if(isdigit(rule_str.at(off)))
            {
                survival_rule_ |= digit_char_to_neighborhood(rule_str.at(off));
            }
            else if(rule_str.at(off) == '/')
            {
                survival_rule_parsing = false;
            }
            else
                return false;
        }
        else
        {
            // birth rule parsing

            if(isdigit(rule_str.at(off)))
            {
                birth_rule_ |= digit_char_to_neighborhood(rule_str.at(off));
            }
            else
                return false;
        }
    }

    return true;
}

Rule::Neighborhood Rule::digit_char_to_neighborhood(char digit) const
{
    switch(digit)
    {
    case '0': return WITH_0_CELLS;
    case '1': return WITH_1_CELL;
    case '2': return WITH_2_CELLS;
    case '3': return WITH_3_CELLS;
    case '4': return WITH_4_CELLS;
    case '5': return WITH_5_CELLS;
    case '6': return WITH_6_CELLS;
    case '7': return WITH_7_CELLS;
    case '8': return WITH_8_CELLS;
    default: return UNKNOWN_CELL_NUMBER;
    }
}
