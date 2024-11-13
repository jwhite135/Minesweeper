#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "cell.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _board()
{
    ui->setupUi(this);
    connect(ui->startBut, &QPushButton::clicked, this, &MainWindow::resetBoard);
    _board.setMinefield(createCells(5,5), 5, 5);
    _board.generateMines(4);
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::vector<std::vector<Cell*>> MainWindow::createCells(int x, int y) {
    std::vector<std::vector<Cell*>> cells(x, std::vector<Cell*>(y, nullptr));
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            Cell* newCell = new Cell(ui->cellHolder, _board, i, j, x, y);
            ui->gridLayout->addWidget(newCell, i, j);
            cells[i][j] = newCell;
        }
    }
    return cells;
}//Populates the box with however many cells, though too many will not play well with the ui

void MainWindow::resetBoard() {
    for(auto &row : _board._minefield) {
        for(auto &cell : row) {
            ui->gridLayout->removeWidget(cell);
            delete cell;
            cell = nullptr;
        }
    }//Clears out the board to make room for the new one, which is created based on which radio button is selected.
    if(ui->medBut->isChecked()) {
        _board.setMinefield(createCells(9,9),9,9);
        _board.generateMines(10);
    }
    else if(ui->hardBut->isChecked()) {
        _board.setMinefield(createCells(16,16),16,16);
        _board.generateMines(40);
    }
    else {
        _board.setMinefield(createCells(5,5),5,5);
        _board.generateMines(4);
    }
}
