#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // 初始化指针
    paint = NULL;
    totallayout = NULL;
    vectorlayout = NULL;
    normallayout = NULL;
    paramlayout = NULL;
    indexlayout = NULL;
    numlayout = NULL;
    speedlayout = NULL;
    numlabel = NULL;
    speedlabel = NULL;
    emptylabel = NULL;
    speedspinbox = NULL;
    numspinbox = NULL;
    drawbutton = NULL;
    clearbutton = NULL;
    playbutton = NULL;
    vecbutton = NULL;
    vecclockbutton = NULL;
    veccounterbutton = NULL;
    lowerlayout = NULL;
    checkgroup = NULL;
    handcheckbox = NULL;
    carcheckbox = NULL;
    emptybox = NULL;
    applebox = NULL;
    handlinearbox = NULL;
    add = NULL;
    add2 = NULL;
    // 窗口布局
    Layout();
    // 按键设置为不可用状态
    disable(playbutton);
    disable(vecbutton);
    disable(vecclockbutton);
    disable(veccounterbutton);
}

Widget::~Widget()
{

}

void Widget::Layout(){
    paint = new PaintWidget;
    totallayout = new QVBoxLayout;
    vectorlayout = new QVBoxLayout;
    normallayout = new QVBoxLayout;
    paramlayout = new QVBoxLayout;
    indexlayout = new QVBoxLayout;
    numlayout = new QHBoxLayout;
    speedlayout = new QHBoxLayout;
    lowerlayout = new QHBoxLayout;
    numlabel = new QLabel("插值图形个数[10,100]    ");
    speedlabel = new QLabel("屏幕刷新速率[100,1000ms]");
    emptylabel = new QLabel("        ");
    speedspinbox = new QSpinBox();
    speedspinbox->setMinimum(50);
    speedspinbox->setMaximum(500);
    speedspinbox->setSingleStep(50);
    numspinbox= new QSpinBox();
    numspinbox->setMinimum(10);
    numspinbox->setMaximum(100);
    numspinbox->setSingleStep(10);
    drawbutton = new QPushButton("生成图形(起)");
    drawbutton->setFixedSize(QSize(200,25));
    drawbutton->setStyleSheet("QPushButton{color:white;background-color:#5B677A;border:1px white;border-radius:3px}"
                                  "QPushButton:hover{color:black;background-color:#CDC9C9;border:1px #F0F8FF}");
    clearbutton = new QPushButton("清除屏幕");
    clearbutton->setFixedSize(QSize(200,25));
    clearbutton->setStyleSheet("QPushButton{color:white;background-color:#5B677A;border:1px white;border-radius:3px}"
                                  "QPushButton:hover{color:black;background-color:#CDC9C9;border:1px #F0F8FF}");
    playbutton = new QPushButton("线性插值运动");
    playbutton->setFixedSize(QSize(200,25));
    playbutton->setStyleSheet("QPushButton{color:white;background-color:#5B677A;border:1px white;border-radius:3px}"
                                  "QPushButton:hover{color:black;background-color:#CDC9C9;border:1px #F0F8FF}");
    vecbutton = new QPushButton("矢量线性插值运动");
    vecbutton->setFixedSize(QSize(200,25));
    vecbutton->setStyleSheet("QPushButton{color:white;background-color:#5B677A;border:1px white;border-radius:3px}"
                                  "QPushButton:hover{color:black;background-color:#CDC9C9;border:1px #F0F8FF}");
    vecclockbutton = new QPushButton("矢量线性插值(顺时针)运动");
    vecclockbutton->setFixedSize(QSize(200,25));
    vecclockbutton->setStyleSheet("QPushButton{color:white;background-color:#5B677A;border:1px white;border-radius:3px}"
                                  "QPushButton:hover{color:black;background-color:#CDC9C9;border:1px #F0F8FF}");
    veccounterbutton = new QPushButton("矢量线性插值(逆时针)运动");
    veccounterbutton->setFixedSize(QSize(200,25));
    veccounterbutton->setStyleSheet("QPushButton{color:white;background-color:#5B677A;border:1px white;border-radius:3px}"
                                  "QPushButton:hover{color:black;background-color:#CDC9C9;border:1px #F0F8FF}");

    // 单选框
    checkgroup = new QButtonGroup();
    handcheckbox = new QRadioButton("手臂",this);
    handcheckbox->setIcon(QIcon("./hand.png"));
    handlinearbox = new QRadioButton("手臂(cspline插值)",this);
    handlinearbox->setIcon(QIcon("./hand.png"));
    carcheckbox = new QRadioButton("小车",this);
    carcheckbox->setIcon(QIcon("./car.png"));
    emptybox = new QRadioButton("自定义           ",this);
    emptybox->setIcon(QIcon("./draw.png"));
    applebox = new QRadioButton("苹果",this);
    applebox->setIcon(QIcon("./apple.png"));
    add = new QHBoxLayout();
    add2 = new QHBoxLayout();

    checkgroup->addButton(handcheckbox,1);
    checkgroup->addButton(carcheckbox,2);
    checkgroup->addButton(emptybox,3);
    checkgroup->addButton(applebox,4);
    checkgroup->addButton(handlinearbox,5);
    emptybox->setChecked(true);


    QPalette p = paint->palette();
    p.setColor(QPalette::Foreground,Qt::white);

    // 信号槽
    connect(drawbutton,SIGNAL(clicked(bool)),this,SLOT(draw()));
    connect(clearbutton,SIGNAL(clicked(bool)),this,SLOT(clear()));
    connect(playbutton,SIGNAL(clicked(bool)),this,SLOT(play()));
    connect(vecbutton,SIGNAL(clicked(bool)),this,SLOT(vecplay()));
    connect(vecclockbutton,SIGNAL(clicked(bool)),this,SLOT(vecclockplay()));
    connect(veccounterbutton,SIGNAL(clicked(bool)),this,SLOT(veccounterclockplay()));

    connect(checkgroup,SIGNAL(buttonToggled(int,bool)),this,SLOT(operatingModeButtonsToggled(int,bool)));
    connect(checkgroup,SIGNAL(buttonClicked(int)),this,SLOT(operatingModeButtonsClicked(int)));


    // 布局
    totallayout->addWidget(paint);
    totallayout->addLayout(lowerlayout);
    lowerlayout->addLayout(paramlayout);
    lowerlayout->addLayout(indexlayout);
    lowerlayout->addLayout(normallayout);
    lowerlayout->addLayout(vectorlayout);

    paramlayout->addLayout(numlayout);
    paramlayout->addLayout(speedlayout);
//    paramlayout->addWidget(emptybox);
    paramlayout->setMargin(10);

    numlayout->addWidget(numlabel);
    numlayout->addWidget(numspinbox);
    speedlayout->addWidget(speedlabel);
    speedlayout->addWidget(speedspinbox);

    add->addWidget(handcheckbox);
    add->addWidget(handlinearbox);
    add2->addWidget(carcheckbox);
    add2->addWidget(emptybox);
    indexlayout->addLayout(add);
    indexlayout->addLayout(add2);
    indexlayout->addWidget(applebox);
    indexlayout->setMargin(10);

    normallayout->addWidget(drawbutton);
    normallayout->addWidget(playbutton);
    normallayout->addWidget(clearbutton);
    normallayout->setMargin(10);

    vectorlayout->addWidget(vecbutton);
    vectorlayout->addWidget(vecclockbutton);
    vectorlayout->addWidget(veccounterbutton);
    vectorlayout->setMargin(10);

    resize(1000,800);
    setLayout(totallayout);
}

void Widget::draw(){
    if(paint->beginn == 0){
        QMessageBox::critical(NULL, "critical", "请绘制点！",
                                      QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    if(paint->drawflag == 1){ // 画完起始图形
        paint->flag = 2;
        paint->drawflag = 2;
        drawbutton->setText("生成图形(终)");
    }else if(paint->drawflag == 2){ // 画完结束图形
        paint->flag = 4;
        paint->drawflag = 0; // 不能继续绘制
        drawbutton->setText("生成图形(始)");
        disable(drawbutton);
        enable(playbutton);
        enable(vecbutton);
        enable(vecclockbutton);
        enable(veccounterbutton);
    }
    update();
}

void Widget::clear(){
    paint->drawflag = 1;
    paint->flag = 0;
    paint->endn = paint->beginn = 0;
    free(paint->mInter);
    paint->mInter = NULL;
    enable(drawbutton);
    disable(playbutton);
    disable(vecbutton);
    disable(vecclockbutton);
    disable(veccounterbutton);

    update();
}

void Widget::play(){
    paint->createInter(numspinbox->value());
    paint->normalInter(speedspinbox->value());
    free(paint->mInter);
}

void Widget::vecplay(){
    paint->createInter(numspinbox->value());
    paint->vecInter(speedspinbox->value());
    free(paint->mInter);
}

void Widget::vecclockplay(){
    paint->createInter(numspinbox->value());
    paint->vecclockInter(speedspinbox->value());
    free(paint->mInter);
}

void Widget::veccounterclockplay(){
    paint->createInter(numspinbox->value());
    paint->veccounterclockInter(speedspinbox->value());
    free(paint->mInter);
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

 void Widget::operatingModeButtonsToggled(int i,bool flag){
     int tmp = checkgroup->checkedId();
     QString str = checkgroup->checkedButton()->text();
     QByteArray byteArray = str.toLocal8Bit();
     qDebug("flag = %d, status = %d, tmp = %d, checked = %s", i, flag, tmp, byteArray.data());
 }

 void Widget::operatingModeButtonsClicked(int i){
     switch(i){
     case 1:
         paint->drawflag = 0;
         disable(drawbutton);
         enable(playbutton);
         enable(vecbutton);
         enable(vecclockbutton);
         enable(veccounterbutton);
         paint->beginn = paint->endn = 23;
         for(int i = 0; i < 23; i++){
             paint->beginx[i] = paint->handx[i];
             paint->beginy[i] = paint->handy[i];
             paint->endx[i] = paint->endhandx[i];
             paint->endy[i] = paint->endhandy[i];
         }
         paint->flag = 4;
         free(paint->mInter);
         paint->mInter = NULL;

         update();
         break;
     case 2:
         paint->drawflag = 0;
         disable(drawbutton);
         enable(playbutton);
         enable(vecbutton);
         enable(vecclockbutton);
         enable(veccounterbutton);
         paint->beginn = paint->endn = 23;
         for(int i = 0; i < 23; i++){
             paint->beginx[22-i] = paint->carx[i];
             paint->beginy[22-i] = paint->cary[i];
             paint->endx[22-i] = paint->endcarx[i];
             paint->endy[22-i] = paint->endcary[i];
         }
         paint->flag = 4;
         free(paint->mInter);
         paint->mInter = NULL;

         update();
         break;
     case 3: // 充当clear作用
         paint->drawflag = 1;
         paint->flag = 0;
         paint->endn = paint->beginn = 0;
         free(paint->mInter);
         paint->mInter = NULL;
         enable(drawbutton);
         disable(playbutton);
         disable(vecbutton);
         disable(vecclockbutton);
         disable(veccounterbutton);

         update();
         break;
     case 4:
         paint->drawflag = 0;
         disable(drawbutton);
         enable(playbutton);
         enable(vecbutton);
         enable(vecclockbutton);
         enable(veccounterbutton);
         paint->beginn = paint->endn = 37;
         for(int i = 0; i < 37; i++){
             paint->beginx[i] = paint->applex[i];
             paint->beginy[i] = paint->appley[i];
             paint->endx[i] = paint->endapplex[i];
             paint->endy[i] = paint->endappley[i];
         }
         paint->flag = 4;
         free(paint->mInter);
         paint->mInter = NULL;

         update();
         break;
     case 5:
         paint->drawflag = 0;
         disable(drawbutton);
         enable(playbutton);
         enable(vecbutton);
         enable(vecclockbutton);
         enable(veccounterbutton);
         paint->beginn = paint->endn = 23;
         for(int i = 0; i < 23; i++){
             paint->beginx[i] = paint->handx[i];
             paint->beginy[i] = paint->handy[i];
             paint->endx[i] = paint->endhandx[i];
             paint->endy[i] = paint->endhandy[i];
         }
         paint->flag = 10;
         free(paint->mInter);
         paint->mInter = NULL;

         update();
         break;
     }
 }

