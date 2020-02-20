#ifndef LIFE_LIKE_RULE_H
#define LIFE_LIKE_RULE_H

#include <stdint.h>
#include <string>

class LifeLikeRule
{
public:
    enum RuleName
    {
        LIFE,
        REPLICATOR,
        SEEDS,
        LIFE_WITHOUT_DEATH,
        LIFE_34,
        DIAMOEBA,
        TWO_BY_TWO,
        HIGH_LIFE,
        DAY_AND_NIGHT,
        MORLEY,
        ANNEAL,
        CUSTOM,
        INVALID_RULE
    };

    enum Neighborhood
    {
        UNKNOWN_CELL_NUMBER = 0,
        WITH_0_CELLS = 1,
        WITH_1_CELL  = 2,
        WITH_2_CELLS = 4,
        WITH_3_CELLS = 8,
        WITH_4_CELLS = 16,
        WITH_5_CELLS = 32,
        WITH_6_CELLS = 64,
        WITH_7_CELLS = 128,
        WITH_8_CELLS = 256,
        WITH_ALL_CELLS = 1 + 2 + 4 + 8 + 16 + 32 + 64 + 128 + 256
    };

    LifeLikeRule(RuleName name = LIFE);
    LifeLikeRule(const std::string& rule_str);

    RuleName name() const { return name_; }
    static std::string name_string(RuleName name);
    std::string name_string() const;

    static uint16_t birth_rule(RuleName name);
    uint16_t birth_rule() const { return birth_rule_; }

    static std::string birth_rule_string(RuleName name);
    std::string birth_rule_string() const;

    static uint16_t survival_rule(RuleName name);
    uint16_t survival_rule() const { return survival_rule_; }

    static std::string survival_rule_string(RuleName name);
    std::string survival_rule_string() const;

    static std::string to_mcell_notation(RuleName name);
    std::string to_mcell_notation() const;

    static std::string to_rle_notation(RuleName name);
    std::string to_rle_notation() const;

private:
    RuleName name_;
    uint16_t birth_rule_;
    uint16_t survival_rule_;

    static std::string flags_to_string_internal(uint16_t flags);
    static std::string to_mcell_notation_internal(const std::string& birth_rule_str,
                                                  const std::string &survival_rule_str);
    static std::string to_rle_notation_internal(const std::string& birth_rule_str,
                                                  const std::string &survival_rule_str);

    bool parse_rle_rule_string(const std::string& rule_str);
    bool parse_mcell_rule_string(const std::string& rule_str);
    Neighborhood digit_char_to_neighborhood(char digit) const;
};

#endif // LIFE_LIKE_RULE_H
