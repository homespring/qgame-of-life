#include <QtTest>
#include "../../GameOfLife/life_like_rule.h"

class LifeLikeRuleTest : public QObject
{
    Q_OBJECT

public:
    LifeLikeRuleTest();
    ~LifeLikeRuleTest();

private slots:
    void returns_conways_name_when_default_constructed();
    void returns_conways_name_string_when_default_constructed();
    void returns_birth_rule_as_int();
    void returns_birth_rule_as_string();
    void returns_survival_rule_as_int();
    void returns_survival_rule_as_string();
    void returns_rules_in_mirek_cellebration_notation();
    void returns_rules_in_golly_rle_notation();
    void can_be_constructed_with_non_conways_name();
    void knows_replicator_rule();
    void knows_seeds_rule();
    void knows_life_without_death_rule();
    void knows_life_34_rule();
    void knows_diamoeba_rule();
    void knows_two_by_two_rule();
    void knows_high_life_rule();
    void knows_day_and_night_rule();
    void knows_morley_rule();
    void knows_anneal_rule();
    void can_be_constructed_from_rle_notation_string();
};

LifeLikeRuleTest::LifeLikeRuleTest() {}

LifeLikeRuleTest::~LifeLikeRuleTest() {}

void LifeLikeRuleTest::returns_conways_name_when_default_constructed()
{
    LifeLikeRule r;
    QCOMPARE(r.name(), LifeLikeRule::LIFE);
}

void LifeLikeRuleTest::returns_conways_name_string_when_default_constructed()
{
    const std::string expected_name("Life");
    LifeLikeRule r;
    QCOMPARE(r.name_string(), expected_name);
}

void LifeLikeRuleTest::returns_birth_rule_as_int()
{
    const uint16_t expected_birth_rule = LifeLikeRule::WITH_3_CELLS; // Conway's birth rules
    LifeLikeRule r;

    QCOMPARE(r.birth_rule(), expected_birth_rule);
}

void LifeLikeRuleTest::returns_birth_rule_as_string()
{
    const std::string expected_birth_rule("3"); // Conway's birth rules
    LifeLikeRule r;

    QCOMPARE(r.birth_rule_string(), expected_birth_rule);
}

void LifeLikeRuleTest::returns_survival_rule_as_int()
{
    const uint16_t expected_survival_rule = LifeLikeRule::WITH_2_CELLS | LifeLikeRule::WITH_3_CELLS; // Conway's survival rules
    LifeLikeRule r;

    QCOMPARE(r.survival_rule(), expected_survival_rule);
}

void LifeLikeRuleTest::returns_survival_rule_as_string()
{
    const std::string expected_survival_rule("23"); // Conway's survival rules
    LifeLikeRule r;

    QCOMPARE(r.survival_rule_string(), expected_survival_rule);
}

void LifeLikeRuleTest::returns_rules_in_mirek_cellebration_notation()
{
    const std::string expected_rule_string("23/3"); // Conway's rules in MCell notation
    LifeLikeRule r;

    QCOMPARE(r.to_mcell_notation(), expected_rule_string);
}

void LifeLikeRuleTest::returns_rules_in_golly_rle_notation()
{
    const std::string expected_rule_string("B3/S23"); // Conway's rules in Golly/RLE notation
    LifeLikeRule r;

    QCOMPARE(r.to_rle_notation(), expected_rule_string);
}

void LifeLikeRuleTest::can_be_constructed_with_non_conways_name()
{
    LifeLikeRule r(LifeLikeRule::REPLICATOR);
    QCOMPARE(r.name(), LifeLikeRule::REPLICATOR);
}

void LifeLikeRuleTest::knows_replicator_rule()
{
    const std::string expected_rule_string("B1357/S1357");
    const std::string expected_name("Replicator");
    LifeLikeRule r(LifeLikeRule::REPLICATOR);

    QCOMPARE(r.to_rle_notation(), expected_rule_string);
    QCOMPARE(r.name_string(), expected_name);
}

void LifeLikeRuleTest::knows_seeds_rule()
{
    const std::string expected_rule_string("B2/S");
    const std::string expected_name("Seeds");
    LifeLikeRule r(LifeLikeRule::SEEDS);

    QCOMPARE(r.to_rle_notation(), expected_rule_string);
    QCOMPARE(r.name_string(), expected_name);
}

void LifeLikeRuleTest::knows_life_without_death_rule()
{
    const std::string expected_rule_string("B3/S012345678");
    const std::string expected_name("Life w/o death");
    LifeLikeRule r(LifeLikeRule::LIFE_WITHOUT_DEATH);

    QCOMPARE(r.to_rle_notation(), expected_rule_string);
    QCOMPARE(r.name_string(), expected_name);
}

void LifeLikeRuleTest::knows_life_34_rule()
{
    const std::string expected_rule_string("B34/S34");
    const std::string expected_name("34 Life");
    LifeLikeRule r(LifeLikeRule::LIFE_34);

    QCOMPARE(r.to_rle_notation(), expected_rule_string);
    QCOMPARE(r.name_string(), expected_name);
}

void LifeLikeRuleTest::knows_diamoeba_rule()
{
    const std::string expected_rule_string("B35678/S5678");
    const std::string expected_name("Diamoeba");
    LifeLikeRule r(LifeLikeRule::DIAMOEBA);

    QCOMPARE(r.to_rle_notation(), expected_rule_string);
    QCOMPARE(r.name_string(), expected_name);
}

void LifeLikeRuleTest::knows_two_by_two_rule()
{
    const std::string expected_rule_string("B36/S125");
    const std::string expected_name("2x2");
    LifeLikeRule r(LifeLikeRule::TWO_BY_TWO);

    QCOMPARE(r.to_rle_notation(), expected_rule_string);
    QCOMPARE(r.name_string(), expected_name);
}

void LifeLikeRuleTest::knows_high_life_rule()
{
    const std::string expected_rule_string("B36/S23");
    const std::string expected_name("High Life");
    LifeLikeRule r(LifeLikeRule::HIGH_LIFE);

    QCOMPARE(r.to_rle_notation(), expected_rule_string);
    QCOMPARE(r.name_string(), expected_name);
}

void LifeLikeRuleTest::knows_day_and_night_rule()
{
    const std::string expected_rule_string("B3678/S34678");
    const std::string expected_name("Day and Night");
    LifeLikeRule r(LifeLikeRule::DAY_AND_NIGHT);

    QCOMPARE(r.to_rle_notation(), expected_rule_string);
    QCOMPARE(r.name_string(), expected_name);
}

void LifeLikeRuleTest::knows_morley_rule()
{
    const std::string expected_rule_string("B368/S245");
    const std::string expected_name("Morley");
    LifeLikeRule r(LifeLikeRule::MORLEY);

    QCOMPARE(r.to_rle_notation(), expected_rule_string);
    QCOMPARE(r.name_string(), expected_name);
}

void LifeLikeRuleTest::knows_anneal_rule()
{
    const std::string expected_rule_string("B4678/S35678");
    const std::string expected_name("Anneal");
    LifeLikeRule r(LifeLikeRule::ANNEAL);

    QCOMPARE(r.to_rle_notation(), expected_rule_string);
    QCOMPARE(r.name_string(), expected_name);
}

void LifeLikeRuleTest::can_be_constructed_from_rle_notation_string()
{
    const std::string expected_rule_string("B123/S456");
    const std::string expected_name("custom");
    LifeLikeRule r(expected_rule_string);

    QCOMPARE(r.name(), LifeLikeRule::CUSTOM);
    QCOMPARE(r.to_rle_notation(), expected_rule_string);
    QCOMPARE(r.name_string(), expected_name);
}

QTEST_APPLESS_MAIN(LifeLikeRuleTest)

#include "tst_lifelikeruletest.moc"
