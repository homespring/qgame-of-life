#include "life_like_rule.h"

LifeLikeRule::LifeLikeRule(RuleName name)
    : name_(name)
{
    birth_rule_ = birth_rule(name_);
    survival_rule_ = survival_rule(name_);
}

LifeLikeRule::LifeLikeRule(const std::string &rle_notation_rule)
{
    (void)rle_notation_rule;
}

std::string LifeLikeRule::name_string(LifeLikeRule::RuleName name)
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
    }

    return "";
}

std::string LifeLikeRule::name_string() const
{
    return name_string(name_);
}

uint16_t LifeLikeRule::birth_rule(LifeLikeRule::RuleName name)
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

std::string LifeLikeRule::birth_rule_string(LifeLikeRule::RuleName name)
{
    return flags_to_string_internal(birth_rule(name));
}

std::string LifeLikeRule::birth_rule_string() const
{
    return flags_to_string_internal(birth_rule_);
}

uint16_t LifeLikeRule::survival_rule(LifeLikeRule::RuleName name)
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

std::string LifeLikeRule::survival_rule_string(LifeLikeRule::RuleName name)
{
    return flags_to_string_internal(survival_rule(name));
}

std::string LifeLikeRule::survival_rule_string() const
{
    return flags_to_string_internal(survival_rule_);
}

std::string LifeLikeRule::to_mcell_notation(LifeLikeRule::RuleName name)
{
    return to_mcell_notation_internal(birth_rule_string(name), survival_rule_string(name));
}

std::string LifeLikeRule::to_mcell_notation() const
{
    return to_mcell_notation_internal(birth_rule_string(), survival_rule_string());
}

std::string LifeLikeRule::to_rle_notation(LifeLikeRule::RuleName name)
{
    return to_rle_notation_internal(birth_rule_string(name), survival_rule_string(name));
}

std::string LifeLikeRule::to_rle_notation() const
{
    return to_rle_notation_internal(birth_rule_string(), survival_rule_string());
}

std::string LifeLikeRule::flags_to_string_internal(uint16_t flags)
{
    std::string ret;

    for(int neighbors = 0; neighbors <= 8; ++neighbors)
    {
        if(flags & (1 << neighbors))
            ret.append(std::to_string(neighbors));
    }

    return ret;
}

std::string LifeLikeRule::to_mcell_notation_internal(const std::string &birth_rule_str, const std::string &survival_rule_str)
{
    return survival_rule_str + "/" + birth_rule_str;
}

std::string LifeLikeRule::to_rle_notation_internal(const std::string &birth_rule_str, const std::string &survival_rule_str)
{
    return "B" + birth_rule_str + "/S" + survival_rule_str;
}
