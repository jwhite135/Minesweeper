#include "cell.h"
#include "board.h"

Cell::Cell(QWidget *parent, board& board, int row, int col, int rows, int cols) : _board(board), QPushButton(parent) {
    this->setIcon(QIcon(":/images/unrevealedCell.png"));
    this->flagged = false;
    this->revealed = false;
    this->mine = false;
    this->adjacentMines = 0;
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setMinimumSize(0, 0);
    _row = row;
    _col = col;
    _rows = rows;
    _cols = cols;
}
bool Cell::isMine() {
    return mine;
}
bool Cell::isRevealed() {
    return revealed;
}
bool Cell::isFlagged() {
    return flagged;
}
void Cell::flag() {
    if(!revealed) {
        QPixmap pixmap;
        flagged = !flagged;
        if(flagged) {
            pixmap.load(":/images/flaggedCell.png");
        }
        else {
            pixmap.load(":/images/unrevealedCell.png");
        }
        this->setIcon(QIcon(pixmap));
    }
}//Calls on right click, flags the cell to denote it as a potential mine, or unflags it.
void Cell::reveal() {
    QPixmap pixmap;
    if(revealed) {
        return;
    }
    revealed = true;
    if(mine) {
        if(_board.isGameOver()) {
            pixmap.load(":/images/revealedMine.png");
            this->setIcon(QIcon(pixmap));
        }
        else {
            pixmap.load(":/images/triggeredMine.png");
            this->setIcon(QIcon(pixmap));
            _board.gameOverMan();
        }
        return;
    }
    if(!_board.isGameOver() && !flagged) {
        switch(adjacentMines) {
        case 1:
            pixmap.load(":/images/oneAdj.png");
            break;
        case 2:
            pixmap.load(":/images/twoAdj.png");
            break;
        case 3:
            pixmap.load(":/images/threeAdj.png");
            break;
        case 4:
            pixmap.load(":/images/fourAdj.png");
            break;
        case 5:
            pixmap.load(":/images/fiveAdj.png");
            break;
        case 6:
            pixmap.load(":/images/sixAdj.png");
            break;
        case 7:
            pixmap.load(":/images/sevenAdj.png");
            break;
        case 8:
            pixmap.load(":/images/eightAdj.png");
            break;
        default:
            pixmap.load(":/images/revealedCell.png");
            int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
            int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};
            for(int i = 0; i < 8; i++) {
                if(_col-dx[i] >= 0 && _col-dx[i] < _cols && _row-dy[i] >= 0 && _row-dy[i] < _rows) {
                    _board._minefield[_row-dy[i]][_col-dx[i]]->reveal();
                }
            }//Reveals valid adjacent spots as if there are 0 mines it should reveal all surrounding tiles
            break;
        }
        this->setIcon(QIcon(pixmap));
    }
}//Changes the image when a cell is clicked, either triggering game over and revealing a mine if a mine is clicked, or displaying the amount of adjacent mines otherwise
void Cell::setMine() {
    mine = true;
}
void Cell::calibrateAdjacentMines() {
    if(mine) {
        return;
    }
    adjacentMines = 0;
    int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    for(int i = 0; i < 8; i++) {
        if(_col+dx[i] >= 0 && _col+dx[i] < _cols && _row+dy[i] >= 0 && _row+dy[i] < _rows) {
            if(_board._minefield[_row+dy[i]][_col+dx[i]]->isMine()) {
                adjacentMines++;
            }
        }
    }
}//Checks through the board and gives each cell the amount of mines adjacent to it (for the correct picture to show up on reveal)

void Cell::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton)
        reveal();
    if(event->button() == Qt::RightButton)
        flag();
}//Calls reveal on left click and flag on right click
void Cell::resizeEvent(QResizeEvent *event) {
    int sideLength = qMin(event->size().width(), event->size().height());
    this->setIconSize(QSize(sideLength-10, sideLength-10));
}//Ensures even and proper sizing
