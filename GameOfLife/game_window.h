#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include "life_like_game.h"
#include <QGraphicsRectItem>

namespace Ui {
class GameWindow;
}

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private slots:
    void on_bt_generate_biome_clicked();

    void on_bt_sim_start_stop_clicked();

    void tick_game();

    void game_rules_toggled(bool checked);

    void on_bt_single_step_clicked();

    void selected_rule_index_changed(const QString& rule_name);

    void on_sb_time_step_valueChanged(int arg1);

    void on_bt_jump_clicked();

private:
    Ui::GameWindow *ui;

    QGraphicsScene game_scene_;
    LifeLike::Game game_;
    QTimer tim_game;
    std::vector<QGraphicsRectItem*> game_items_;

    void init_window();
    void init_connections();
    void init_scene();
    void init_rules_combobox();

    void update_generation_counter();
    void update_game_cells_colors();

    LifeLike::Rule selected_rule() const;
    LifeLike::Rule::RuleName selected_rule_name() const;

    LifeLike::ColorRule selected_color_rule() const;
};

#endif // GAME_WINDOW_H
