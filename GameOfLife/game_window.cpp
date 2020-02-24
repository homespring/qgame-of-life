#include "game_window.h"
#include "ui_game_window.h"
#include <QApplication>
#include <QScreen>
#include "version.h"
#include <QLabel>
#include <QBrush>
#include <QDebug>

const qreal CELL_SIZE = 50.0;

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    init_window();
    init_connections();
    init_scene();

    update_generation_counter();
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::on_bt_generate_biome_clicked()
{
    const size_t w = static_cast<size_t>(ui->sb_grid_width->value());
    const size_t h = static_cast<size_t>(ui->sb_grid_height->value());
    const float fill_factor = ui->sb_fill_factor->value() / 100.0f;

    if(game_.width() != w || game_.height() != h)
    {
        game_ = LifeLike::Game(w, h);
        game_.initialize_randomly(fill_factor);

        game_scene_.clear();
        game_items_.clear();
        game_items_.reserve(w * h);

        for(size_t y = 0; y < h; ++y)
        {
            for(size_t x = 0; x < w; ++x)
            {
                const qreal x_pos = x * CELL_SIZE;
                const qreal y_pos = y * CELL_SIZE;

                QGraphicsRectItem* item = game_scene_.addRect(x_pos,
                                                              y_pos,
                                                              CELL_SIZE,
                                                              CELL_SIZE,
                                                              QPen(),
                                                              QBrush(game_.current_biome().cell_at(x, y).color()));

                game_items_.push_back(item);
            }
        }
    }
    else
    {
        // rozmiar gry sie nie zmienil

        game_.initialize_randomly(fill_factor);
        update_generation_counter();
        update_game_cells_colors();
    }

    ui->game_view->fitInView(0, 0, game_scene_.width(), game_scene_.height());
}

void GameWindow::on_bt_sim_start_stop_clicked()
{
    ui->gb_grid->setEnabled(tim_game.isActive());
    ui->gb_rules->setEnabled(tim_game.isActive());
    ui->gb_colors->setEnabled(tim_game.isActive());

    if(!tim_game.isActive())
    {
        // start the game

        if(!game_.current_biome().has_living_cell())
            on_bt_generate_biome_clicked();

        ui->bt_sim_start_stop->setText("Stop");

        tim_game.start(ui->sb_time_step->value());
    }
    else
    {
        // stop the game

        tim_game.stop();

        ui->bt_sim_start_stop->setText("Start");
    }
}

void GameWindow::tick_game()
{
    game_.produce_next_generation();
    update_generation_counter();
    update_game_cells_colors();

    if(!game_.current_biome().has_living_cell() && tim_game.isActive())
    {
        // game over
        on_bt_sim_start_stop_clicked();
    }
}

void GameWindow::conways_rules_toggled(bool checked)
{
    if(!checked)
        return;
}

void GameWindow::init_window()
{
    this->setWindowTitle("Game of Life " + QString(VERSION_STR));
    this->resize(1024, 768);

    // window centering
    const auto cntr = QGuiApplication::screens().first()->geometry().center() - this->rect().center();
    this->move(cntr.x(), cntr.y());
}

void GameWindow::init_connections()
{
    connect(&tim_game, &QTimer::timeout, this, &GameWindow::tick_game);
}

void GameWindow::init_scene()
{
    game_scene_.setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    ui->game_view->setScene(&game_scene_);
}

void GameWindow::update_generation_counter()
{
    ui->status_bar->showMessage("Generation: " + QString::number(game_.generation_number()));
}

void GameWindow::update_game_cells_colors()
{
    for(size_t y = 0; y < game_.height(); ++y)
    {
        for(size_t x = 0; x < game_.width(); ++x)
        {
            const size_t pos = x + y * game_.width();
            game_items_[pos]->setBrush(QBrush(game_.current_biome().cell_at(x, y).color()));
        }
    }
}

void GameWindow::on_bt_single_step_clicked()
{
    if(game_.current_biome().has_living_cell())
        tick_game();
}
