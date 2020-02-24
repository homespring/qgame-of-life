#include <QtTest>
#include "../../GameOfLife/life_like_biome.h"
#include <QDebug>
#include <sstream>

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
    void returns_number_of_living_cells();
    void can_be_randomly_initialized();
    void all_cells_are_alive_when_randomly_initialized_with_fill_factor_above_1();
    void all_cells_are_dead_when_randomly_initialized_with_fill_factor_below_0();
    void biomes_with_the_same_cells_alive_are_equal();
    void biomes_with_different_alive_cells_arent_equal();
    void biomes_with_different_sizes_arent_equal();
    void returns_colors_of_living_neighbors_for_a_cell();
    void can_be_converted_to_string();
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

void LifeLikeBiomeTest::returns_number_of_living_cells()
{
    Biome b(1, 10);

    QCOMPARE(b.living_cells_count(), uint64_t(0));

    b.cell_at(0, 1).be_born();
    b.cell_at(0, 2).be_born();
    b.cell_at(0, 9).be_born();

    QCOMPARE(b.living_cells_count(), uint64_t(3));
}

void LifeLikeBiomeTest::can_be_randomly_initialized()
{
    const float fill_factor = 0.5f;
    const quint64 expected_alive_cells_count = static_cast<int>(fill_factor * 4 * 5);
    Biome b(4, 5);

    b.initialize_randomly(fill_factor);

    QCOMPARE(b.living_cells_count(), expected_alive_cells_count);
}

void LifeLikeBiomeTest::all_cells_are_alive_when_randomly_initialized_with_fill_factor_above_1()
{
    const float fill_factor = 1.5f;
    const quint64 expected_alive_cells_count = 4 * 5;
    Biome b(4, 5);

    b.initialize_randomly(fill_factor);

    QCOMPARE(b.living_cells_count(), expected_alive_cells_count);
}

void LifeLikeBiomeTest::all_cells_are_dead_when_randomly_initialized_with_fill_factor_below_0()
{
    const float fill_factor = -0.5f;
    const quint64 expected_alive_cells_count = 0;
    Biome b(4, 5);

    b.initialize_randomly(fill_factor);

    QCOMPARE(b.living_cells_count(), expected_alive_cells_count);
}

void LifeLikeBiomeTest::biomes_with_the_same_cells_alive_are_equal()
{
    Biome b0(2, 3), b1(2, 3);
    b0.cell_at(0, 1).be_born();
    b0.cell_at(1, 2).be_born();
    b1.cell_at(0, 1).be_born();
    b1.cell_at(1, 2).be_born();

    QVERIFY(b0 == b1);
}

void LifeLikeBiomeTest::biomes_with_different_alive_cells_arent_equal()
{
    Biome b0(2, 3), b1(2, 3);
    b0.cell_at(0, 1).be_born();
    b0.cell_at(1, 2).be_born();
    b1.cell_at(0, 0).be_born();
    b1.cell_at(2, 1).be_born();

    QVERIFY(b0 != b1);
}

void LifeLikeBiomeTest::biomes_with_different_sizes_arent_equal()
{
    Biome b0(3, 2), b1(2, 1);

    QVERIFY(b0 != b1);
}

void LifeLikeBiomeTest::returns_colors_of_living_neighbors_for_a_cell()
{
    // biome
    // red 0 white
    // blue 0 white
    // green 0 0

    const std::vector<Qt::GlobalColor> expected_colors_0_0 =
        { Qt::blue };

    const std::vector<Qt::GlobalColor> expected_colors_1_0 =
        { Qt::red, Qt::white, Qt::blue, Qt::white };

    const std::vector<Qt::GlobalColor> expected_colors_2_0 =
        { Qt::white };

    const std::vector<Qt::GlobalColor> expected_colors_0_1 =
        { Qt::red, Qt::green };

    const std::vector<Qt::GlobalColor> expected_colors_1_1 =
        { Qt::red, Qt::white, Qt::blue, Qt::white, Qt::green };

    const std::vector<Qt::GlobalColor> expected_colors_2_1 =
        { Qt::white };

    const std::vector<Qt::GlobalColor> expected_colors_0_2 =
        { Qt::blue };

    const std::vector<Qt::GlobalColor> expected_colors_1_2 =
        { Qt::blue, Qt::white, Qt::green };

    const std::vector<Qt::GlobalColor> expected_colors_2_2 =
        { Qt::white };

    Biome b(3, 3);
    b.cell_at(0, 0).be_born(Qt::red);
    b.cell_at(2, 0).be_born(Qt::white);
    b.cell_at(0, 1).be_born(Qt::blue);
    b.cell_at(2, 1).be_born(Qt::white);
    b.cell_at(0, 2).be_born(Qt::green);

    QCOMPARE(b.neighbors_colors(0, 0), expected_colors_0_0);
    QCOMPARE(b.neighbors_colors(1, 0), expected_colors_1_0);
    QCOMPARE(b.neighbors_colors(2, 0), expected_colors_2_0);
    QCOMPARE(b.neighbors_colors(0, 1), expected_colors_0_1);
    QCOMPARE(b.neighbors_colors(1, 1), expected_colors_1_1);
    QCOMPARE(b.neighbors_colors(2, 1), expected_colors_2_1);
    QCOMPARE(b.neighbors_colors(0, 2), expected_colors_0_2);
    QCOMPARE(b.neighbors_colors(1, 2), expected_colors_1_2);
    QCOMPARE(b.neighbors_colors(2, 2), expected_colors_2_2);
}

void LifeLikeBiomeTest::can_be_converted_to_string()
{
    // biome
    // 1 0 0
    // 0 1 1
    // 1 0 0

    Biome biome(3, 3);
    biome.cell_at(0, 0).be_born();
    biome.cell_at(1, 1).be_born();
    biome.cell_at(2, 1).be_born();
    biome.cell_at(0, 2).be_born();

    std::stringstream expected_biome_str;
    expected_biome_str << "1 0 0" << std::endl;
    expected_biome_str << "0 1 1" << std::endl;
    expected_biome_str << "1 0 0" << std::endl;

    QCOMPARE(biome.to_string(), expected_biome_str.str());
}

QTEST_APPLESS_MAIN(LifeLikeBiomeTest)

#include "tst_lifelikebiometest.moc"
