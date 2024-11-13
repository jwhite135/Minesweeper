#ifndef BOARD_H
#define BOARD_H
#include<vector>

class Cell;

class board {
public:
    board();
    void setMinefield(std::vector<std::vector<Cell*>>, int row, int col);
    ~board() = default;
    void startGame();
    void resetGame();
    int remainingMines();
    void gameOverMan();
    bool isGameOver();
    std::vector<std::vector<Cell*>> _minefield;
    void generateMines(int mines);
private:
    int rows;
    int cols;
    bool gameOver;
};

#endif // BOARD_H
