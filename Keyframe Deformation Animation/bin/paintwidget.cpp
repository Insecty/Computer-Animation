#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent)
{
    drawflag = 1;
    beginn = 0;
    endn = 0;
    flag = 0;
    mInter = NULL;

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(changeState()));
    resize(1000,400);
}

void PaintWidget::createInter(int __polnum){
    polnum = __polnum;
    mInter = new Interpol(polnum, beginn, beginx, beginy, endx, endy);
}

void PaintWidget::normalInter(int speed){
    mInter->linear(); // 生成插值图形
    startMove(speed); // 开始运动
}

void PaintWidget::vecInter(int speed){
    mInter->veclinear(); // 矢量线性插值
    startMove(speed); // 开始运动
}

void PaintWidget::vecclockInter(int speed){
    mInter->vecclocklinear(); // 顺时针矢量线性插值
    startMove(speed); // 开始运动
}

void PaintWidget::veccounterclockInter(int speed){
    mInter->veccounterclocklinear();
    startMove(speed);
}

void PaintWidget::startMove(int speed){
    ticks = 0;
    timer->start(speed);
}

void PaintWidget::changeState(){
    if(flag == 10 || flag == 11){
        //cspline
        if(ticks < polnum){
            flag = 11;
            for(int i = 0; i < endn; i++){
                currenthandx[i] = mInter->inter[ticks][i].x;
                currenthandy[i] = mInter->inter[ticks][i].y;
            }
            ticks++;
            update();
        }else if(ticks == polnum){
            flag = 10;
            ticks = 0;
            timer->stop();
            update();
        }

    }else{
        if(ticks < polnum){
            flag = 5;
            for(int i = 0; i < endn; i++){
                current[i].x = mInter->inter[ticks][i].x;
                current[i].y = mInter->inter[ticks][i].y;
            }
            ticks++;
            update();
        }else if(ticks == polnum){
            flag = 4;
            ticks = 0;
            timer->stop();
            update();
        }

    }
}

void PaintWidget::paintEvent(QPaintEvent *){
    QPainter paint(this);
    // 设置背景色
    paint.setPen(Qt::NoPen);
    paint.setBrush(Qt::white);
    paint.drawRect(rect());
    // 设置笔刷
    paint.setPen(QPen(QColor(3,3,255),1,Qt::SolidLine,Qt::RoundCap));
    paint.setRenderHint(QPainter::Antialiasing,true);

    switch(flag){
    case 1:
        for(int i = 0; i < beginn; i++){
            paint.setPen(Qt::red);
            paint.setBrush(Qt::red);
            paint.drawEllipse(beginx[i],beginy[i],4,4);
        }
        break;
    case 2:
        for(int i = 0; i < beginn; i++){
            paint.setPen(Qt::red);
            paint.setBrush(Qt::red);
            paint.drawEllipse(beginx[i],beginy[i],4,4);
            if(i < beginn-1){
                paint.setPen(QPen(QColor(0,0,0),1,Qt::SolidLine,Qt::RoundCap));
                paint.drawLine(beginx[i],beginy[i],beginx[i+1],beginy[i+1]);
            }else{
                paint.setPen(QPen(QColor(0,0,0),1,Qt::SolidLine,Qt::RoundCap));
                paint.drawLine(beginx[i],beginy[i],beginx[0],beginy[0]);
            }
        }
        break;
    case 3:
        for(int i = 0; i < beginn; i++){
            paint.setPen(Qt::red);
            paint.setBrush(Qt::red);
            paint.drawEllipse(beginx[i],beginy[i],4,4);
            if(i < beginn-1){
                paint.setPen(QPen(QColor(0,0,0),1,Qt::SolidLine,Qt::RoundCap));
                paint.drawLine(beginx[i],beginy[i],beginx[i+1],beginy[i+1]);
            }else{
                paint.setPen(QPen(QColor(0,0,0),1,Qt::SolidLine,Qt::RoundCap));
                paint.drawLine(beginx[i],beginy[i],beginx[0],beginy[0]);
            }
        }
        for(int i = 0; i < endn; i++){
            paint.setPen(Qt::red);
            paint.setBrush(Qt::red);
            paint.drawEllipse(endx[i],endy[i],4,4);
        }
        break;
    case 4:
        if(endn != beginn){
            flag = 0;
            beginn = endn = 0;
            drawflag = 1;
            QMessageBox::critical(NULL, "critical", "图形控制点对应出错！请清除屏幕重新绘制！",
                                          QMessageBox::Yes, QMessageBox::Yes);
            return;
        }
        for(int i = 0; i < beginn; i++){
            paint.setPen(Qt::red);
            paint.setBrush(Qt::red);
            paint.drawEllipse(beginx[i],beginy[i],4,4);
            if(i < beginn-1){
                paint.setPen(QPen(QColor(0,0,0),1,Qt::SolidLine,Qt::RoundCap));
                paint.drawLine(beginx[i],beginy[i],beginx[i+1],beginy[i+1]);
            }else{
                paint.setPen(QPen(QColor(0,0,0),1,Qt::SolidLine,Qt::RoundCap));
                paint.drawLine(beginx[i],beginy[i],beginx[0],beginy[0]);
            }
        }
        for(int i = 0; i < endn; i++){
            paint.setPen(Qt::red);
            paint.setBrush(Qt::red);
            paint.drawEllipse(endx[i],endy[i],4,4);
            if(i < endn-1){
                paint.setPen(QPen(QColor(0,0,0),1,Qt::SolidLine,Qt::RoundCap));
                paint.drawLine(endx[i],endy[i],endx[i+1],endy[i+1]);
            }else{
                paint.setPen(QPen(QColor(0,0,0),1,Qt::SolidLine,Qt::RoundCap));
                paint.drawLine(endx[i],endy[i],endx[0],endy[0]);
            }
        }
        break;
    case 5:
        for(int i = 0; i < endn; i++){
            paint.setPen(Qt::red);
            paint.setBrush(Qt::red);
            paint.drawEllipse(current[i].x,current[i].y,4,4);
            if(i < endn-1){
                paint.setPen(QPen(QColor(0,0,0),1,Qt::SolidLine,Qt::RoundCap));
                paint.drawLine(current[i].x,current[i].y,current[i+1].x,current[i+1].y);
            }else{
                paint.setPen(QPen(QColor(0,0,0),1,Qt::SolidLine,Qt::RoundCap));
                paint.drawLine(current[i].x,current[i].y,current[0].x,current[0].y);
            }
        }
        break;
    case 10:{// cspline手臂位置显示
        // 起始图形插值曲线 两点之间插值20个点 tension = 0.6
        CSpline *mbegin = new CSpline(beginx,beginy,beginn,20,0.4);
        CSpline *mend = new CSpline(endx,endy,endn,20,0.4);
        for(int i = 0; i < beginn-1; i++){
            paint.setPen(Qt::red);
            paint.setBrush(Qt::red);
//            paint.drawEllipse(endx[i],endy[i],4,4);
            int g = 20;
            paint.drawLine(beginx[i],beginy[i],mbegin->Spline[i*g].x,mbegin->Spline[i*g].y);
            paint.drawLine(endx[i],endy[i],mend->Spline[i*g].x,mend->Spline[i*g].y);
            for(int j = i*g ; j < (i+1)*g-1; j++){
                QPoint a,b;
                a.setX(mbegin->Spline[j].x);
                a.setY(mbegin->Spline[j].y);
                b.setX(mbegin->Spline[j+1].x);
                b.setY(mbegin->Spline[j+1].y);
                paint.drawLine(a,b);
                a.setX(mend->Spline[j].x);
                a.setY(mend->Spline[j].y);
                b.setX(mend->Spline[j+1].x);
                b.setY(mend->Spline[j+1].y);
                paint.drawLine(a,b);
            }
            paint.drawLine(mbegin->Spline[(i+1)*g-1].x,mbegin->Spline[(i+1)*g-1].y,beginx[i+1],beginy[i+1]);
            paint.drawLine(mend->Spline[(i+1)*g-1].x,mend->Spline[(i+1)*g-1].y,endx[i+1],endy[i+1]);
        }
        free(mbegin);
        free(mend);
        break;
    }
    case 11:{// cspline手臂运动
        CSpline *mcurrent = new CSpline(currenthandx,currenthandy,beginn,20,0.4);
        for(int i = 0; i < beginn-1; i++){
            paint.setPen(Qt::red);
            paint.setBrush(Qt::red);
            int g = 20;
            paint.drawLine(currenthandx[i],currenthandy[i],mcurrent->Spline[i*g].x,mcurrent->Spline[i*g].y);
            for(int j = i*g ; j < (i+1)*g-1; j++){
                QPoint a,b;
                a.setX(mcurrent->Spline[j].x);
                a.setY(mcurrent->Spline[j].y);
                b.setX(mcurrent->Spline[j+1].x);
                b.setY(mcurrent->Spline[j+1].y);
                paint.drawLine(a,b);
            }
            paint.drawLine(mcurrent->Spline[(i+1)*g-1].x,mcurrent->Spline[(i+1)*g-1].y,currenthandx[i+1],currenthandy[i+1]);
        }
        free(mcurrent);
        break;
    }
    default:
        break;
    }
}

void PaintWidget::mousePressEvent(QMouseEvent *event){
    if(drawflag == 1){
        flag = 1;
        double x = event->pos().x();
        double y = event->pos().y();
        beginx[beginn] = x;
        beginy[beginn++] = y;

        update();
    }else if(drawflag == 2){
        flag = 3;
        double x = event->pos().x();
        double y = event->pos().y();
        endx[endn] = x;
        endy[endn++] = y;

        update();
    }
}

PaintWidget::~PaintWidget(){

}
