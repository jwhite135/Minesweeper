#include "boardView.h"



boardView::boardView(QWidget *parent) : QGroupBox(parent) {

}

void boardView::resizeEvent(QResizeEvent *event)  {
    int sideLength = qMin(size().width(), size().height());
    resize(sideLength, sideLength);
}// Ensures proper resizing
