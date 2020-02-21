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

QTEST_APPLESS_MAIN(LifeLikeColorRuleTest)

#include "tst_lifelikecolorruletest.moc"
