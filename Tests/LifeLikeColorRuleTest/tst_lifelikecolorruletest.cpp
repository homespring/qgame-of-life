#include <QtTest>
#include "../../GameOfLife/life_like_color_rule.h"

using namespace LifeLike;

class LifeLikeColorRuleTest : public QObject
{
    Q_OBJECT

public:
    LifeLikeColorRuleTest();
    ~LifeLikeColorRuleTest();

private slots:
    void has_only_white_color_by_default();
    void can_be_constructed_with_vector_of_colors();
    void returns_new_cell_color_based_on_neighbors_major_colors();
    void returns_other_color_if_every_neighbor_has_different();
    void returns_major_color_even_when_one_color_isnt_used();
    void returns_major_color_when_only_one_exists();
    void returns_random_color_when_no_living_neighbors();
};

LifeLikeColorRuleTest::LifeLikeColorRuleTest() {}

LifeLikeColorRuleTest::~LifeLikeColorRuleTest() {}

void LifeLikeColorRuleTest::has_only_white_color_by_default()
{
    ColorRule r;
    QCOMPARE(r.colors().size(), size_t(1));
    QCOMPARE(r.colors().front(), Qt::white);
}

void LifeLikeColorRuleTest::can_be_constructed_with_vector_of_colors()
{
    const std::vector<Qt::GlobalColor> expected_colors = { Qt::red, Qt::green, Qt::blue };
    ColorRule r(expected_colors);

    QCOMPARE(r.colors(), expected_colors);
}

void LifeLikeColorRuleTest::returns_new_cell_color_based_on_neighbors_major_colors()
{
    const std::vector<Qt::GlobalColor> rule_colors = { Qt::red, Qt::blue };
    const std::vector<Qt::GlobalColor> neighbors_colors = { Qt::red, Qt::red, Qt::blue, Qt::red };
    const Qt::GlobalColor expected_color = Qt::red;
    ColorRule r(rule_colors);

    QCOMPARE(r.new_cell_color(neighbors_colors), expected_color);
}

void LifeLikeColorRuleTest::returns_other_color_if_every_neighbor_has_different()
{
    const std::vector<Qt::GlobalColor> rule_colors = { Qt::red, Qt::green, Qt::blue };
    const std::vector<Qt::GlobalColor> neighbors_colors = { Qt::red, Qt::blue };
    const Qt::GlobalColor expected_color = Qt::green;
    ColorRule r(rule_colors);

    QCOMPARE(r.new_cell_color(neighbors_colors), expected_color);
}

void LifeLikeColorRuleTest::returns_major_color_even_when_one_color_isnt_used()
{
    const std::vector<Qt::GlobalColor> rule_colors = { Qt::red, Qt::green, Qt::blue, Qt::yellow };
    const std::vector<Qt::GlobalColor> neighbors_colors = { Qt::red, Qt::blue, Qt::red, Qt::green };
    const Qt::GlobalColor expected_color = Qt::red;
    ColorRule r(rule_colors);

    QCOMPARE(r.new_cell_color(neighbors_colors), expected_color);
}

void LifeLikeColorRuleTest::returns_major_color_when_only_one_exists()
{
    const std::vector<Qt::GlobalColor> rule_colors = { Qt::red, Qt::green, Qt::blue, Qt::yellow };
    const std::vector<Qt::GlobalColor> neighbors_colors = { Qt::red, Qt::red, Qt::red };
    const Qt::GlobalColor expected_color = Qt::red;
    ColorRule r(rule_colors);

    QCOMPARE(r.new_cell_color(neighbors_colors), expected_color);
}

void LifeLikeColorRuleTest::returns_random_color_when_no_living_neighbors()
{
    const std::vector<Qt::GlobalColor> rule_colors = { Qt::red, Qt::green, Qt::blue, Qt::yellow };
    const std::vector<Qt::GlobalColor> neighbors_colors = {};
    ColorRule r(rule_colors);
    const Qt::GlobalColor actual_color = r.new_cell_color(neighbors_colors);

    QVERIFY(actual_color != Qt::transparent);
}

QTEST_APPLESS_MAIN(LifeLikeColorRuleTest)

#include "tst_lifelikecolorruletest.moc"
