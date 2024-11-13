#include "board.h"
#include "cell.h"


board::board() : _minefield() {
    srand((unsigned) time(NULL));
    this->gameOver = false;
}
void board::setMinefield(std::vector<std::vector<Cell*>> mines, int row, int col) {
    _minefield = mines;
    rows = row;
    cols = col;
    gameOver = false;
}
void board::generateMines(int mines) {
    for(int i = 0; i < mines; i++) {
        while(true) {
            int idx = rand() % (rows*cols);
            int x = idx / cols;
            int y = idx % cols;
            if(!_minefield[x][y]->isMine()) {
                _minefield[x][y]->setMine();
                break;
            }
        }
    }//Populating board with mines
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            _minefield[i][j]->calibrateAdjacentMines();
        }
    }//Initializing adjacent mine values for each cell
}
void board::gameOverMan() {
    gameOver = true;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            if(_minefield[i][j]->isMine())
                _minefield[i][j]->reveal();
        }
    }
}// When a mine is clicked, reveal all the mines
bool board::isGameOver() {
    return gameOver;
}
