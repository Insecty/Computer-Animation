#include "widget.h"
#include <QMessageBox>
#include <qmessagebox.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // 初始化指针
    paint = NULL;
    vbox = NULL;
    hbox = NULL;
    tenhbox = NULL;
    grahbox = NULL;
    lower = NULL;
    setlayout = NULL;
    var = NULL;
    tension = NULL;
    grain = NULL;
    speedlabel = NULL;
    tensionnum = NULL;
    grainnum = NULL;
    drawbutton = NULL;
    clearbutton = NULL;
    playbutton = NULL;
    playbutton2 = NULL;
    empty= NULL;
    empty1=NULL;
    empty2= NULL;
    showpointbutton = NULL;
    pSlider = NULL;
    draw2 = NULL;

    // 窗口布局
    Layout();
    // 按键设置为不可用状态
    disable(showpointbutton);
    disable(playbutton);
    disable(playbutton2);
}

Widget::~Widget()
{

}

void Widget::Layout()
{
    paint = new PaintWidget();
    vbox = new QVBoxLayout();
    hbox = new QHBoxLayout();
    tenhbox = new QHBoxLayout();
    grahbox = new QHBoxLayout();
    lower = new QHBoxLayout();
    setlayout = new QVBoxLayout();
    var = new QVBoxLayout();
    buttonlayout = new QVBoxLayout();
    empty = new QVBoxLayout();

    tension = new QLabel("    Tension  [0,1]         ");
    grain = new QLabel("    Grain  [10,50]         ");
    speedlabel = new QLabel("    Speed    [1,5]         ");
    empty1 = new QLabel("           ");
    empty2 = new QLabel("           ");
    tensionnum = new QDoubleSpinBox();
    tensionnum->setMinimum(0);
    tensionnum->setMaximum(1);
    tensionnum->setSingleStep(0.01);
    grainnum = new QSpinBox();
    grainnum->setMinimum(10);
    grainnum->setMaximum(50);
    grainnum->setSingleStep(1);
    drawbutton = new QPushButton("     Draw Spline     ");
    drawbutton->setFixedSize(QSize(200,25));
    drawbutton->setStyleSheet("QPushButton{color:white;background-color:#5B677A;border:1px white;border-radius:3px}"
                              "QPushButton:hover{color:black;background-color:#CDC9C9;border:1px #F0F8FF}");
    draw2 = new QPushButton(" Draw Spline With ALP ");
    draw2->setFixedSize(QSize(200,25));
    draw2->setStyleSheet("QPushButton{color:white;background-color:#5B677A;border:1px white;border-radius:3px}"
                              "QPushButton:hover{color:black;background-color:#CDC9C9;border:1px #F0F8FF}");

    clearbutton = new QPushButton("     Clear Screen     ");
    clearbutton->setFixedSize(QSize(200,25));
    clearbutton->setStyleSheet("QPushButton{color:white;background-color:#5B677A;border:1px white;border-radius:3px}"
                              "QPushButton:hover{color:black;background-color:#CDC9C9;border:1px #F0F8FF}");

    showpointbutton = new QPushButton("     Show Spline Points     ");
    showpointbutton->setFixedSize(QSize(200,25));
    playbutton = new QPushButton("    Play1   ");
    playbutton->setFixedSize(QSize(120,25));
    playbutton2 = new QPushButton("    Play2   ");
    playbutton2->setFixedSize(QSize(120,25));
    pSlider = new QSlider();
    pSlider->setOrientation(Qt::Horizontal);
    pSlider->setStyleSheet(" QSlider::add-page:Horizontal{background-color: rgb(87, 97, 106);height:4px;}"
                           "QSlider::sub-page:Horizontal{background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(231,80,229, 255), stop:1 rgba(7,208,255, 255));height:4px;}"
                           "QSlider::groove:Horizontal{background:transparent;height:6px;}"
                           "QSlider::handle:Horizontal{height:20px;width:20px;border-image: url(./slider.png);margin: -8 0px;}  ");
    pSlider->setMinimum(1);
    pSlider->setMaximum(5);
    pSlider->setSingleStep(1);

    QPalette p = paint->palette();
    p.setColor(QPalette::Foreground,Qt::white);

    // 信号槽
    connect(drawbutton,SIGNAL(clicked(bool)),this,SLOT(draw()));
    connect(draw2,SIGNAL(clicked(bool)),this,SLOT(drawALP()));
    connect(clearbutton,SIGNAL(clicked(bool)),this,SLOT(clear()));
    connect(showpointbutton,SIGNAL(clicked(bool)),this,SLOT(showpoints()));
    connect(playbutton,SIGNAL(clicked(bool)),this,SLOT(play()));
    connect(playbutton2,SIGNAL(clicked(bool)),this,SLOT(play2()));

    // 布局
    vbox->addWidget(paint);
    vbox->addLayout(lower);
    setlayout->addWidget(tension);
    setlayout->addWidget(grain);
    setlayout->addWidget(speedlabel);

    var->addLayout(tenhbox);
    tenhbox->addWidget(tensionnum);
    tenhbox->addWidget(playbutton);
    var->addLayout(grahbox);
    grahbox->addWidget(grainnum);
    grahbox->addWidget(playbutton2);
    hbox->addWidget(pSlider);
    hbox->addWidget(draw2);
    var->addLayout(hbox);

    buttonlayout->addWidget(drawbutton);
    buttonlayout->addWidget(clearbutton);
    buttonlayout->addWidget(showpointbutton);

    empty->addWidget(empty1);
    empty->addWidget(empty2);
    empty->addWidget(empty1);

    lower->addLayout(setlayout);
    lower->addLayout(var);
    lower->addLayout(empty);
    lower->addLayout(buttonlayout);
    lower->addLayout(empty);
    lower->setMargin(5);
    lower->setSpacing(10);
    resize(900,600);
    setLayout(vbox);
}

void Widget::draw(){ // 处理点击绘制按钮
    // 获取用户输入的grain、tension
    int grain = grainnum->value();
    float tension = tensionnum->value();
    if(tension == 0){ // tension为0时提示
        QMessageBox::critical(NULL, "critical", "Tension must be larger than zero!",
                              QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    paint->drawfinishflag = 1; // 不可再继续绘制
    paint->ALPflag = 0;
    paint->flag = 1;           // 绘制曲线
    paint->grain = grain;
    paint->tension = tension;
    // 生成Cardinal曲线
    paint->mCSpline[paint->m] = new CSpline(paint->px, paint->py, paint->n, grain, tension);
    paint->m += 1;   // 没有clear前点击draw就会根据参数不同多次绘制
    enable(showpointbutton);
    enable(playbutton);
    enable(playbutton2);
    disable(draw2);
    update();
}

void Widget::drawALP(){
    // 获取用户输入的grain、tension
    int grain = grainnum->value();
    float tension = tensionnum->value();
    if(tension == 0){ // tension为0时提示
        QMessageBox::critical(NULL, "critical", "Tension must be larger than zero!",
                              QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    paint->drawfinishflag = 1; // 不可再继续绘制
    paint->ALPflag = 1;
    paint->flag = 1;           // 绘制曲线
    paint->grain = grain;
    paint->tension = tension;
    // 生成Cardinal曲线
    paint->line[paint->m] = new CSplineWithALP(paint->px, paint->py, paint->n, grain, tension);
    paint->m += 1;   // 没有clear前点击draw就会根据参数不同多次绘制
    enable(showpointbutton);
    enable(playbutton);
    enable(playbutton2);
    disable(drawbutton);
    update();
}

void Widget::clear(){ // 处理点击绘制按钮
    paint->flag = 0;  // 各变量清零
    paint->n = 0;
    paint->grain = 0;
    paint->tension = 0;
    paint->drawfinishflag = 0;
    paint->ALPflag = 0;
    paint->m = 0;

    playbutton->setText("    Play1   ");
    playbutton2->setText("    Play2   ");

    disable(showpointbutton);
    enable(drawbutton);
    disable(playbutton);
    disable(playbutton2);
    enable(draw2);
    paint->carflag = 0;
    update();
}

void Widget::showpoints(){ // 处理点击显示插值点按钮
    paint->flag = 2;
    update();
}

void Widget::play(){
    if(paint->m == 1){ // 只有一条曲线在界面上显示时可以运动
        playbutton->setText("  Replay1  ");
        disable(drawbutton);
        disable(draw2);
        disable(showpointbutton);
        paint->getAllpoints();
        paint->carflag = 1;
        paint->speed = pSlider->value(); // 设置速度即每个timer间隔运动几个点
        // 设置动画
        paint->startMove();
    }else {
        QMessageBox::critical(NULL, "critical",
                              "You can only move the car when just one spline",
                              QMessageBox::Yes, QMessageBox::Yes);
    }
}

void Widget::play2(){
    if(paint->m == 1){ // 只有一条曲线在界面上显示时可以运动
        playbutton2->setText("  Replay2  ");
        disable(drawbutton);
        disable(draw2);
        disable(showpointbutton);
        paint->getAllpoints();
        paint->carflag = 2;
        paint->speed = pSlider->value(); // 设置速度即每个timer间隔运动几个点
        // 设置动画
        paint->startMove();
    }else {
        QMessageBox::critical(NULL, "critical",
                              "You can only move the car when just one spline",
                              QMessageBox::Yes, QMessageBox::Yes);
    }
}

void Widget::disable(QPushButton *button){
    button->setEnabled(false);
    button->setStyleSheet("QPushButton{color:#CDC9C9;background-color:#EEE9E9;border:1px white;border-radius:3px}");
}

void Widget::enable(QPushButton *button){
    button->setEnabled(true);
    button->setStyleSheet("QPushButton{color:white;background-color:#5B677A;border:1px white;border-radius:3px}"
                              "QPushButton:hover{color:black;background-color:#CDC9C9;border:1px #F0F8FF}");
}


