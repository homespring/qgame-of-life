#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>

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

    void conways_rules_toggled(bool checked);

private:
    Ui::GameWindow *ui;
    QGraphicsScene biome_scene_;

    QTimer tim_game;
    quint64 generation_cnt_;

    void init_window();
    void init_connections();
    void init_scene();

    void clear_generations_counter();
    void update_generation_counter();
};

#endif // GAME_WINDOW_H
