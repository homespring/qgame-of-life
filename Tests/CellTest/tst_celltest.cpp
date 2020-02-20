#include <QtTest>
#include "../../GameOfLife/cell.h"

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

QTEST_APPLESS_MAIN(CellTest)

#include "tst_celltest.moc"
