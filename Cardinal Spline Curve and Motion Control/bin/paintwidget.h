#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include "cspline.h"
#include "csplinewithalp.h"
#include <QLabel>
#include <QImage>
#include <QTimer>
#include <QPropertyAnimation>

class PaintWidget : public QWidget
{
    Q_OBJECT
public:
    PaintWidget(QWidget *parent = 0);
    ~PaintWidget();
public:
    CSpline *mCSpline[20]; // 绘制的曲线数组
    CSplineWithALP *line[20]; // 绘制的曲线数组
    int m; // 绘制的曲线数目
    double px[100];        // 从画布上获取的控制点坐标
    double py[100];
    int n; // 控制点个数
    int grain;
    double tension;

    int ALPflag; // 是否曲线参数化
    int flag;    // 显示模式
    int drawfinishflag; // 是否完成绘制（点击生成按钮后就默认完成）
    int downflag; // 是否下坡

    int speed;   // 小车运动速度
    int carflag; // 是否绘制小车及小车运动方式

    double ppx[512]; // 算上控制点和插值点的所有点坐标
    double ppy[512];
    int index;
    double x_position; // 小车位置
    double y_position;
    double ratio;      // 小车斜率

    QTimer *timer;
    int ticks;
    QPixmap picture;   // 小车形状

public:
    void startMove();
    void getAllpoints();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);

private slots:
    void changeState();
};

#endif // PAINTWIDGET_H
