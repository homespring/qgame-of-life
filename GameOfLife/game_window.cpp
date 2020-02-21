#include "game_window.h"
#include "ui_game_window.h"
#include <QApplication>
#include <QScreen>
#include "version.h"
#include <QLabel>
#include <QBrush>

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

}

void GameWindow::on_bt_sim_start_stop_clicked()
{
    ui->gb_grid->setEnabled(tim_game.isActive());
    ui->gb_rules->setEnabled(tim_game.isActive());
    ui->gb_colors->setEnabled(tim_game.isActive());

    if(!tim_game.isActive())
    {
        // start the game

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
    biome_scene_.setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    ui->biome_display->setScene(&biome_scene_);
}

void GameWindow::update_generation_counter()
{
    ui->status_bar->showMessage("Generation: " + QString::number(game_.generation_number()));
}
