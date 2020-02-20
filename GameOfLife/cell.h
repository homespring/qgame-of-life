#ifndef CELL_H
#define CELL_H


class Cell
{
public:
    Cell(bool alive = false);

    bool is_alive() const { return alive_; }

private:
    bool alive_;
};

#endif // CELL_H
