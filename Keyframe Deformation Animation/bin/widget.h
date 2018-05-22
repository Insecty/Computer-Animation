#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QSpinBox>
#include <QRadioButton>
#include <QButtonGroup>
#include "paintwidget.h"


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    PaintWidget *paint;
    QVBoxLayout *totallayout;
    QVBoxLayout *vectorlayout;
    QVBoxLayout *normallayout;
    QVBoxLayout *paramlayout;
    QVBoxLayout *indexlayout;
    QHBoxLayout *lowerlayout;
    QHBoxLayout *numlayout;
    QHBoxLayout *speedlayout;
    QLabel *numlabel;
    QLabel *speedlabel;
    QLabel *emptylabel;
    QSpinBox *numspinbox;
    QSpinBox *speedspinbox;
    QPushButton *drawbutton;
    QPushButton *clearbutton;
    QPushButton *playbutton;
    QPushButton *vecbutton;
    QPushButton *vecclockbutton;
    QPushButton *veccounterbutton;
    QButtonGroup *checkgroup;
    QRadioButton *handcheckbox;
    QRadioButton *carcheckbox;
    QRadioButton *emptybox;
    QRadioButton *applebox;
    QRadioButton *handlinearbox;
    QHBoxLayout *add;
    QHBoxLayout *add2;

    void Layout();
private slots:
    void draw();
    void clear();
    void play();
    void vecplay();
    void vecclockplay();
    void veccounterclockplay();
    void operatingModeButtonsToggled(int i,bool flag);
    void operatingModeButtonsClicked(int i);
private:
    void disable(QPushButton *button); // 设置按钮样式
    void enable(QPushButton *button);
};

#endif // WIDGET_H
