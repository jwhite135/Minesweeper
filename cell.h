#ifndef CELL_H
#define CELL_H
#include <QPushButton>
#include <QIcon>
#include <QResizeEvent>

class board;

class Cell : public QPushButton {
public:
    Cell(QWidget *parent, board& board, int row, int col, int rows, int cols);
    ~Cell() = default;
    bool isMine();
    bool isRevealed();
    bool isFlagged();
    void setMine();
    void reveal();
    void calibrateAdjacentMines();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    board& _board;
    void flag();
    bool mine;
    bool revealed;
    bool flagged;
    int adjacentMines;
    int _row;
    int _col;
    int _rows;
    int _cols;
};

#endif // CELL_H
