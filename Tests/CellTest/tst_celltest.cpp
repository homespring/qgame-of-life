#include <QtTest>
#include "../../GameOfLife/life_like_cell.h"

using namespace LifeLike;

class CellTest : public QObject
{
    Q_OBJECT

public:
    CellTest();
    ~CellTest();

private slots:
    void is_dead_by_default();
    void can_be_constructed_alive();
    void can_be_constructed_dead();
    void has_white_color_when_alive();
    void has_transparent_color_when_dead();
    void dead_cell_tells_if_should_be_born();
    void dead_cell_tells_if_shouldnt_be_born();
    void live_cell_tells_if_should_die_of_loneliness();
    void live_cell_tells_if_should_survive();
    void live_cell_tells_if_should_die_of_overpopulation();
};

CellTest::CellTest() {}

CellTest::~CellTest() {}

void CellTest::is_dead_by_default()
{
    Cell c;
    QVERIFY(!c.is_alive());
}

void CellTest::can_be_constructed_alive()
{
    Cell c(true);
    QVERIFY(c.is_alive());
}

void CellTest::can_be_constructed_dead()
{
    Cell c(false);
    QVERIFY(!c.is_alive());
}

void CellTest::has_white_color_when_alive()
{
    Cell c(true);
    QCOMPARE(c.color(), Qt::white);
}

void CellTest::has_transparent_color_when_dead()
{
    Cell c(false);
    QCOMPARE(c.color(), Qt::transparent);
}

void CellTest::dead_cell_tells_if_should_be_born()
{
    const Rule rule; // Life rule - cell is born when it has exactly 3 living neighbors
    const int living_neighbors = 3;
    Cell c(false);

    QVERIFY(c.should_be_alive(rule, living_neighbors));
}

void CellTest::dead_cell_tells_if_shouldnt_be_born()
{
    const Rule rule; // Life rule - cell is born when it has exactly 3 living neighbors
    const int living_neighbors = 6;
    Cell c(false);

    QVERIFY(!c.should_be_alive(rule, living_neighbors));
}

void CellTest::live_cell_tells_if_should_die_of_loneliness()
{
    const Rule rule; // Life rule - cell survives when it has 2 or 3 living neighbors
    const int living_neighbors = 1;
    Cell c(true);

    QVERIFY(!c.should_be_alive(rule, living_neighbors));
}

void CellTest::live_cell_tells_if_should_survive()
{
    const Rule rule; // Life rule - cell survives when it has 2 or 3 living neighbors
    const int living_neighbors = 2;
    Cell c(true);

    QVERIFY(c.should_be_alive(rule, living_neighbors));
}

void CellTest::live_cell_tells_if_should_die_of_overpopulation()
{
    const Rule rule; // Life rule - cell survives when it has 2 or 3 living neighbors
    const int living_neighbors = 7;
    Cell c(true);

    QVERIFY(!c.should_be_alive(rule, living_neighbors));
}

QTEST_APPLESS_MAIN(CellTest)

#include "tst_celltest.moc"
