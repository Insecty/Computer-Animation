#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QLabel>
#include <QTimer>
#include <QMessageBox>
#include <qmessagebox.h>
#include "interpol.h"
#include "cspline.h"

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    PaintWidget(QWidget *parent = 0);
    ~PaintWidget();
public:
    double beginx[50]; // 从画布上获取的起始图形控制点坐标
    double beginy[50];
    double endx[50];   // 从画布上获取的终止图形控制点坐标
    double endy[50];
    int beginn; // 控制点个数
    int endn;
    Interpol *mInter;

    CPt current[50];   // 绘制时显示的当其前图形

    int drawflag;      // 0表示在操作不能绘制 1表示绘制起始图形 2表示绘制结束图形
    int flag;          // 0表示初始化 1表示点 2表示线 3表示线点 4表示线线(绘制阶段)·

    QTimer *timer;
    int ticks;

    int polnum;

    // 预设小车
    double carx[30] =    {85 ,72 ,102,106,111,121,131,141,147,207,211,217,228,239,250,259,262,298,281,240,225,155,140};
    double cary[30] =    {465,503,503,512,519,523,523,515,503,503,511,519,525,525,520,509,503,503,465,465,414,414,465};
    double endcarx[30] = {511,473,473,464,457,453,453,461,473,473,465,457,451,451,456,467,473,473,511,511,562,562,511};
    double endcary[30] = {105 ,92 ,122,126,131,141,151,161,167,227,231,237,248,259,270,279,282,318,301,260,245,175,160};

    // 预设手臂
    double handx[50] =    {456,425,426,442,449,441,432,429,425,421,419,414,411,408,404,400,395,390,391,401,391,402,438};
    double handy[50] =    {453,460,330,305,271,270,297,237,237,283,231,230,281,235,235,285,257,258,309,327,470,497,500};
    double endhandx[50] = {458,430,275,255,221,221,240,191,192,232,185,187,226,193,193,226,201,203,251,275,386,447,475};
    double endhandy[50] = {457,468,474,457,442,447,463,466,471,476,478,484,488,495,500,500,508,513,510,501,512,502,490};

    // 预设苹果
    double applex[40] =    {184,174,163,156,156,160,171,181,198,213,225,231,236,240,241,239,230,214,206,193,192,191,195,201,209,208,198,195,193,192,192,191,192,194,193,192,192};
    double appley[40] =    {431,432,438,452,466,479,489,496,498,498,491,482,470,455,444,436,429,428,428,432,440,446,447,447,447,450,450,450,445,439,427,403,396,386,399,410,420};
    double endapplex[40] = {431,430,424,410,396,383,373,366,364,364,371,380,392,407,418,426,433,434,434,430,422,416,415,415,415,412,412,412,417,423,435,459,466,476,463,452,442};
    double endappley[40] = {184,174,163,156,156,160,171,181,198,213,225,231,236,240,241,239,230,214,206,193,192,191,195,201,209,208,198,195,193,192,192,191,192,194,193,192,192};

    double currenthandx[50]; //手臂控制点（用于手臂的曲线插值）
    double currenthandy[50];
public:
    void createInter(int __polnum);
    void normalInter(int speed);
    void vecInter(int speed);
    void vecclockInter(int speed);
    void veccounterclockInter(int speed);
    void startMove(int speed);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);

public slots:
    void changeState();
};

#endif // PAINTWIDGET_H
