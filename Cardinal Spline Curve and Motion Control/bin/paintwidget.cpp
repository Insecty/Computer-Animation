#include "paintwidget.h"
#include <QPalette>
#include <QtDebug>

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent)
{
    // 控制点下标
    n = 0;
    for(int i = 0; i < 100; i++){
        px[i] = 0;
        py[i] = 0;
    }
    ALPflag = 0;
    flag = 0;
    m = 0;
    drawfinishflag = 0;

    // 设置对象与图片
    picture.load("car.png");
    ticks = 0;
    speed = 0;
    carflag = 0;
    downflag = 0;
    index = 0;

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(changeState()));

    resize(900,400);
}

PaintWidget::~PaintWidget(){

}

void PaintWidget::changeState(){
    int position = ticks*speed; // 小车此刻所在点位置

    if(position < index){ // 还未到达终点
        x_position = ppx[position];
        y_position = ppy[position];
        if(ticks != 0){   // 计算小车的旋转角度即运动路径位移
            int lastposition = (ticks-1)*speed;
            ratio = (ppy[position]-ppy[lastposition])/(ppx[position]-ppx[lastposition]);
            if(ppx[position] > ppx[lastposition])
                downflag = 1;
            else
                downflag = 0;
        }
        ticks++;
        update();
    }else{ // 已经到达终点
        x_position = ppx[index];
        y_position = ppy[index];
        int lastposition = (ticks-1)*speed;
        ratio = (ppy[index]-ppy[lastposition])/(ppx[index]-ppx[lastposition]);
        if(ppx[index] > ppx[lastposition])
            downflag = 1;
        else
            downflag = 0;
        update();
        timer->stop();
        ticks = 0;
        return;
    }
   // ticks++;

   // update();
}

void PaintWidget::startMove(){
    ticks = 0;
    timer->start(100); //fps:10
}

void PaintWidget::getAllpoints(){ // 只有有一条曲线的时候才可以play 才会调用次函数
    // n个控制点 grain*(n-1)个插值点
    index = 0;
    for(int i = 0; i < n-1; i++){
        ppx[index] = px[i];
        ppy[index++] = py[i];
        if(ALPflag == 0){
            for(int j = grain*i; j < grain*(i+1); j++){
                ppx[index] = mCSpline[0]->Spline[j].x;
                ppy[index++] = mCSpline[0]->Spline[j].y;
            }
        }else if(ALPflag == 1){
            for(int j = grain*i; j < grain*(i+1); j++){
                ppx[index] = line[0]->SplineWithALP[j].x;
                ppy[index++] = line[0]->SplineWithALP[j].y;
            }
        }
    }
    ppx[index] = px[n-1];
    ppy[index] = py[n-1];
}

void PaintWidget::paintEvent(QPaintEvent *){ // 处理绘制事件
    QPainter paint(this);
    // 设置背景色
    paint.setPen(Qt::NoPen);
    paint.setBrush(Qt::white);
    paint.drawRect(rect());
    // 设置笔刷
    paint.setPen(QPen(QColor(3,3,255),1,Qt::SolidLine,Qt::RoundCap));
    paint.setRenderHint(QPainter::Antialiasing,true);

    if(flag == 0){// 绘制控制点及连接控制点的折线
        if(n == 1){
            paint.setPen(Qt::red);
            paint.setBrush(Qt::red);
            paint.drawEllipse(px[0],py[0],3,3);
        }else if(n != 0){
            for(int i = 0; i < n-1; i++){
                paint.drawLine(px[i],py[i],px[i+1],py[i+1]);
            }
            for(int i = 0; i < n; i++){
                paint.setPen(Qt::red);
                paint.setBrush(Qt::red);
                paint.drawEllipse(px[i]-2,py[i]-2,4,4);}
        }
    }
    else if(flag == 1){// 绘制样条曲线
        // 支持改变参数多次绘制
        for(int k = 0; k < m; k++){
            for(int i = 0; i < n-1; i++){
                switch(k){ // 设置绘制曲线的颜色
                case 0:
                    paint.setPen(QPen(QColor(255,106,106),1,Qt::SolidLine,Qt::RoundCap));
                    break;
                case 1:
                    paint.setPen(QPen(QColor(255,127,36),1,Qt::SolidLine,Qt::RoundCap));
                    break;
                case 2:
                    paint.setPen(QPen(QColor(255,215,0),1,Qt::SolidLine,Qt::RoundCap));
                    break;
                case 3:
                    paint.setPen(QPen(QColor(144,238,144),1,Qt::SolidLine,Qt::RoundCap));
                    break;
                case 4:
                    paint.setPen(QPen(QColor(64,224,208),1,Qt::SolidLine,Qt::RoundCap));
                    break;
                case 5:
                    paint.setPen(QPen(QColor(0,191,255),1,Qt::SolidLine,Qt::RoundCap));
                    break;
                case 6:
                    paint.setPen(QPen(QColor(132,112,255),1,Qt::SolidLine,Qt::RoundCap));
                    break;
                case 7:
                    paint.setPen(QPen(QColor(25,25,112),1,Qt::SolidLine,Qt::RoundCap));
                    break;
                case 8:
                    paint.setPen(QPen(QColor(240,128,128),1,Qt::SolidLine,Qt::RoundCap));
                    break;
                case 9:
                    paint.setPen(QPen(QColor(255,110,180),1,Qt::SolidLine,Qt::RoundCap));
                    break;
                }
                if(ALPflag == 0){
                    int g = mCSpline[k]->grain;
                    paint.drawLine(px[i],py[i],mCSpline[k]->Spline[i*g].x,mCSpline[k]->Spline[i*g].y);
                    for(int j = i*g ; j < (i+1)*g-1; j++){
                        QPoint a,b;
                        a.setX(mCSpline[k]->Spline[j].x);
                        a.setY(mCSpline[k]->Spline[j].y);
                        b.setX(mCSpline[k]->Spline[j+1].x);
                        b.setY(mCSpline[k]->Spline[j+1].y);
                        paint.drawLine(a,b);
                    }
                    paint.drawLine(mCSpline[k]->Spline[(i+1)*g-1].x,mCSpline[k]->Spline[(i+1)*g-1].y,px[i+1],py[i+1]);
                }else if(ALPflag == 1){
                    int g = line[k]->grain;
                    paint.drawLine(px[i],py[i],line[k]->SplineWithALP[i*g].x,line[k]->SplineWithALP[i*g].y);
                    for(int j = i*g ; j < (i+1)*g-1; j++){
                        QPoint a,b;
                        a.setX(line[k]->SplineWithALP[j].x);
                        a.setY(line[k]->SplineWithALP[j].y);
                        b.setX(line[k]->SplineWithALP[j+1].x);
                        b.setY(line[k]->SplineWithALP[j+1].y);
                        paint.drawLine(a,b);
                    }
                    paint.drawLine(line[k]->SplineWithALP[(i+1)*g-1].x,line[k]->SplineWithALP[(i+1)*g-1].y,px[i+1],py[i+1]);
                }
            }
        }
        // 单独绘制控制点
        for(int j = 0; j < n; j++){
            paint.setPen(Qt::red);
            paint.setBrush(Qt::red);
            paint.drawEllipse(px[j]-2,py[j]-2,4,4);
        }
    }
    else if(flag == 2){// 显示最后一次生成的曲线的插值点
        for(int k = 0; k < m; k++){ // 绘制样条曲线
            for(int i = 0; i < n-1; i++){
                switch(k){ // 设置样条曲线颜色
                case 0:
                    paint.setPen(QPen(QColor(255,106,106),1,Qt::SolidLine,Qt::RoundCap));
                    break;
                case 1:
                    paint.setPen(QPen(QColor(255,127,36),1,Qt::SolidLine,Qt::RoundCap));
                    break;
                case 2:
                    paint.setPen(QPen(QColor(255,215,0),1,Qt::SolidLine,Qt::RoundCap));
                    break;
                case 3:
                    paint.setPen(QPen(QColor(144,238,144),1,Qt::SolidLine,Qt::RoundCap));
                    break;
                case 4:
                    paint.setPen(QPen(QColor(64,224,208),1,Qt::SolidLine,Qt::RoundCap));
                    break;
                case 5:
                    paint.setPen(QPen(QColor(0,191,255),1,Qt::SolidLine,Qt::RoundCap));
                    break;
                case 6:
                    paint.setPen(QPen(QColor(132,112,255),1,Qt::SolidLine,Qt::RoundCap));
                    break;
                case 7:
                    paint.setPen(QPen(QColor(25,25,112),1,Qt::SolidLine,Qt::RoundCap));
                    break;
                case 8:
                    paint.setPen(QPen(QColor(240,128,128),1,Qt::SolidLine,Qt::RoundCap));
                    break;
                case 9:
                    paint.setPen(QPen(QColor(255,110,180),1,Qt::SolidLine,Qt::RoundCap));
                    break;
                }
                if(ALPflag == 0){
                    int g = mCSpline[k]->grain;
                    paint.drawLine(px[i],py[i],mCSpline[k]->Spline[i*g].x,mCSpline[k]->Spline[i*g].y);
                    for(int j = i*g ; j < (i+1)*g-1; j++){
                        QPoint a,b;
                        a.setX(mCSpline[k]->Spline[j].x);
                        a.setY(mCSpline[k]->Spline[j].y);
                        b.setX(mCSpline[k]->Spline[j+1].x);
                        b.setY(mCSpline[k]->Spline[j+1].y);
                        paint.drawLine(a,b);
                    }
                    paint.drawLine(mCSpline[k]->Spline[(i+1)*g-1].x,mCSpline[k]->Spline[(i+1)*g-1].y,px[i+1],py[i+1]);
                }else if(ALPflag == 1){
                    int g = line[k]->grain;
                    paint.drawLine(px[i],py[i],line[k]->SplineWithALP[i*g].x,line[k]->SplineWithALP[i*g].y);
                    for(int j = i*g ; j < (i+1)*g-1; j++){
                        QPoint a,b;
                        a.setX(line[k]->SplineWithALP[j].x);
                        a.setY(line[k]->SplineWithALP[j].y);
                        b.setX(line[k]->SplineWithALP[j+1].x);
                        b.setY(line[k]->SplineWithALP[j+1].y);
                        paint.drawLine(a,b);
                    }
                    paint.drawLine(line[k]->SplineWithALP[(i+1)*g-1].x,line[k]->SplineWithALP[(i+1)*g-1].y,px[i+1],py[i+1]);
                }
            }
        }
        for(int j = 0; j < n; j++){ // 绘制控制点
            paint.setPen(Qt::red);
            paint.setBrush(Qt::red);
            paint.drawEllipse(px[j]-2,py[j]-2,4,4);
        }
        // 绘制最后一条生成的曲线的插值点
        if(ALPflag == 0){
            int g = mCSpline[m-1]->grain;
            for(int j = 0; j < g*(n-1); j++){
                paint.setPen(Qt::blue);
                paint.setBrush(Qt::blue);
                paint.drawEllipse(mCSpline[m-1]->Spline[j].x-1,mCSpline[m-1]->Spline[j].y-1,2,2);
            }
        }else if(ALPflag == 1){
            int g = line[m-1]->grain;
            for(int j = 0; j < g*(n-1); j++){
                paint.setPen(Qt::blue);
                paint.setBrush(Qt::blue);
                paint.drawEllipse(line[m-1]->SplineWithALP[j].x-1,line[m-1]->SplineWithALP[j].y-1,2,2);
            }
        }
    }

    // 绘制小车
    if(carflag != 0){
        if(carflag == 1){ // 普通绘制
            QPixmap picture2 = picture.scaled(picture.width()*0.2,
                                              picture.height()*0.2,Qt::KeepAspectRatio);
            paint.drawPixmap(x_position-20,y_position-60,picture2);
        }
        else if(carflag == 2){  // 小车形状改变（斜率）绘制
            const float pi = 3.14159;
            QPixmap picture2 = picture.scaled(picture.width()*0.2,
                                              picture.height()*0.2,Qt::KeepAspectRatio);
            paint.translate(x_position,y_position);   // 让图片中心作为旋转中心
            paint.rotate(atan(ratio)/(2*pi)*360);
            if(downflag == 0){
                paint.rotate(-180);
            }
            paint.translate(-x_position,-y_position); // 使原点复原
            paint.drawPixmap(x_position-20,y_position-60,picture2);
        }
    }
}

void PaintWidget::mousePressEvent(QMouseEvent *e){
    if(drawfinishflag == 0){
        double x = e->pos().x();
        double y = e->pos().y();
        px[n] = x;
        py[n++] = y;

        update();
    }
}
