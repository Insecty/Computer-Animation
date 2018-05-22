#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QPixmap>
#include <QSlider>
#include "cspline.h"
#include "paintwidget.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    PaintWidget *paint;
    QVBoxLayout *vbox;
    QHBoxLayout *lower;
    QHBoxLayout *hbox;
    QHBoxLayout *tenhbox;
    QHBoxLayout *grahbox;
    QVBoxLayout *setlayout;
    QVBoxLayout *var;
    QVBoxLayout *empty;
    QVBoxLayout *buttonlayout;
    QLabel *tension;
    QLabel *grain;
    QLabel *speedlabel;
    QLabel *empty1;
    QLabel *empty2;
    QDoubleSpinBox *tensionnum;
    QSpinBox *grainnum;
    QPushButton *drawbutton;
    QPushButton *clearbutton;
    QPushButton *showpointbutton;
    QPushButton *playbutton;
    QPushButton *playbutton2;
    QPushButton *draw2;
    QSlider *pSlider;
    void Layout();
private slots:
    void draw();
    void drawALP();
    void clear();
    void showpoints();
    void play();
    void play2();
private:
    void disable(QPushButton *button);
    void enable(QPushButton *button);
};

#endif // WIDGET_H
