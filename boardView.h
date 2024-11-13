#ifndef BOARDVIEW_H
#define BOARDVIEW_H
#include <QGroupBox>
class boardView : public QGroupBox {
public:
    boardView(QWidget *parent = nullptr);
    ~boardView() = default;
protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // BOARDVIEW_H
