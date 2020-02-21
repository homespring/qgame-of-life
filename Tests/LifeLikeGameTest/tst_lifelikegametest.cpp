#include <QtTest>
#include "../../GameOfLife/life_like_game.h"

using namespace LifeLike;

class LifeLikeGameTest : public QObject
{
    Q_OBJECT

public:
    LifeLikeGameTest();
    ~LifeLikeGameTest();

private slots:
    void has_zero_width_by_default();
    void has_zero_height_by_default();
    void can_be_created_with_size();
    void has_life_rule_by_default();
    void can_be_constructed_with_size_and_rule();
    void can_set_rule();
    void counts_generations();
};

LifeLikeGameTest::LifeLikeGameTest() {}

LifeLikeGameTest::~LifeLikeGameTest() {}

void LifeLikeGameTest::has_zero_width_by_default()
{
    Game g;
    QCOMPARE(g.width(), 0);
}

void LifeLikeGameTest::has_zero_height_by_default()
{
    Game g;
    QCOMPARE(g.height(), 0);
}

void LifeLikeGameTest::can_be_created_with_size()
{
    Game g(1, 2);
    QCOMPARE(g.width(), 1);
    QCOMPARE(g.height(), 2);
}

void LifeLikeGameTest::has_life_rule_by_default()
{
    Game g;
    QCOMPARE(g.rule().name(), Rule::LIFE);
}

void LifeLikeGameTest::can_be_constructed_with_size_and_rule()
{
    Game g(1, 2, Rule(Rule::SEEDS));
    QCOMPARE(g.rule().name(), Rule::SEEDS);
}

void LifeLikeGameTest::can_set_rule()
{
    Game g;

    QCOMPARE(g.rule().name(), Rule::LIFE);

    g.set_rule(Rule(Rule::ANNEAL));

    QCOMPARE(g.rule().name(), Rule::ANNEAL);
}

void LifeLikeGameTest::counts_generations()
{
    Game g;

    QCOMPARE(g.generation_number(), uint64_t(1));

    g.produce_next_generation();

    QCOMPARE(g.generation_number(), uint64_t(2));
}

QTEST_APPLESS_MAIN(LifeLikeGameTest)

#include "tst_lifelikegametest.moc"
