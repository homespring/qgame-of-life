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
    void produces_next_generation();
    void counts_generations();
    void can_be_randomly_initialized_with_fill_factor();
    void reset_without_param_kills_all_cells();
};

LifeLikeGameTest::LifeLikeGameTest() {}

LifeLikeGameTest::~LifeLikeGameTest() {}

void LifeLikeGameTest::has_zero_width_by_default()
{
    Game g;
    QCOMPARE(g.width(), uint64_t(0));
}

void LifeLikeGameTest::has_zero_height_by_default()
{
    Game g;
    QCOMPARE(g.height(), uint64_t(0));
}

void LifeLikeGameTest::can_be_created_with_size()
{
    Game g(1, 2);
    QCOMPARE(g.width(), uint64_t(1));
    QCOMPARE(g.height(), uint64_t(2));
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

class FakeGame3x3 : public Game
{
public:
    FakeGame3x3()
    {
        rule_ = Rule(Rule::LIFE);
        width_ = 3;
        height_ = 3;

        // biome_0
        // 0 1 0
        // 0 1 0
        // 0 1 0

        biome_0 = Biome(3, 3);
        biome_0.cell_at(1, 0).be_born();
        biome_0.cell_at(1, 1).be_born();
        biome_0.cell_at(1, 2).be_born();

        biome_1 = Biome(3, 3);
    }
};

void LifeLikeGameTest::produces_next_generation()
{
    // expected biome
    // 0 0 0
    // 1 1 1
    // 0 0 0

    Biome expected_biome(3, 3);
    expected_biome.cell_at(0, 1).be_born();
    expected_biome.cell_at(1, 1).be_born();
    expected_biome.cell_at(2, 1).be_born();

    FakeGame3x3 g;

    QVERIFY(g.current_biome() != expected_biome);

    g.produce_next_generation();

    QCOMPARE(g.current_biome(), expected_biome);
}

void LifeLikeGameTest::counts_generations()
{
    Game g;

    QCOMPARE(g.generation_number(), uint64_t(1));

    g.produce_next_generation();

    QCOMPARE(g.generation_number(), uint64_t(2));
}

void LifeLikeGameTest::can_be_randomly_initialized_with_fill_factor()
{
    const float fill_factor = 0.5f;
    const quint64 expected_alive_cells_count = static_cast<int>(fill_factor * 4 * 5);
    Game g(4, 5);
    g.initialize_randomly(fill_factor);

    QCOMPARE(g.living_cells_count(), expected_alive_cells_count);
}

void LifeLikeGameTest::reset_without_param_kills_all_cells()
{
    Game g(4, 5);
    g.initialize_randomly(0.5f);
    g.produce_next_generation();
    g.produce_next_generation();

    QVERIFY(g.living_cells_count() > 0);
    QCOMPARE(g.generation_number(), uint64_t(3));

    g.reset();

    QVERIFY(g.living_cells_count() == 0);
    QCOMPARE(g.generation_number(), uint64_t(1));
}

QTEST_APPLESS_MAIN(LifeLikeGameTest)

#include "tst_lifelikegametest.moc"
