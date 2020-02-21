#include <QtTest>
#include "../../GameOfLife/life_like_biome.h"
#include <QDebug>

using namespace LifeLike;

class LifeLikeBiomeTest : public QObject
{
    Q_OBJECT

public:
    LifeLikeBiomeTest();
    ~LifeLikeBiomeTest();

private slots:
    void has_zero_width_by_default();
    void has_zero_height_by_default();
    void can_be_created_with_size();
    void gives_read_write_access_to_cells();
    void is_initialised_with_dead_cells();
};

LifeLikeBiomeTest::LifeLikeBiomeTest() {}

LifeLikeBiomeTest::~LifeLikeBiomeTest() {}

void LifeLikeBiomeTest::has_zero_width_by_default()
{
    Biome b;
    QCOMPARE(b.width(), size_t(0));
}

void LifeLikeBiomeTest::has_zero_height_by_default()
{
    Biome b;
    QCOMPARE(b.height(), size_t(0));
}

void LifeLikeBiomeTest::can_be_created_with_size()
{
    Biome b(1, 2);
    QCOMPARE(b.width(), size_t(1));
    QCOMPARE(b.height(), size_t(2));
}

void LifeLikeBiomeTest::gives_read_write_access_to_cells()
{
    Biome b(3, 3);

    QVERIFY(!b.cell_at(2, 1).is_alive());

    b.cell_at(2, 1).be_born();

    QVERIFY(b.cell_at(2, 1).is_alive());
    QVERIFY(!b.cell_at(0, 0).is_alive());

    b.cell_at(0, 0).be_born();

    QVERIFY(b.cell_at(0, 0).is_alive());
}

void LifeLikeBiomeTest::is_initialised_with_dead_cells()
{
    Biome b(1, 2);

    for(size_t y = 0; y < b.height(); ++y)
        for(size_t x = 0; x < b.width(); ++x)
            QVERIFY(!b.cell_at(x, y).is_alive());
}

QTEST_APPLESS_MAIN(LifeLikeBiomeTest)

#include "tst_lifelikebiometest.moc"
