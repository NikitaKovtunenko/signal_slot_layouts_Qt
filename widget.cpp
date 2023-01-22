#include "widget.h"
#include <QPushButton>
#include <QLayout>
#include <QComboBox>
//#include <QVBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QLineEdit>
#include <QStyleFactory>
#include <QApplication>
#include <QFile>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QComboBox *box = new QComboBox;
    QStringList lay_names;
    lay_names.push_back(QString("Horizontal layout"));
    lay_names.push_back(QString("Vertical layout"));
    lay_names.push_back(QString("Grid layout"));
    box->addItems(lay_names);
    QPushButton *butn_ex = new QPushButton("Exit",this);
    QObject::connect(butn_ex,"2clicked()",this,"1close()");
    button_dis = new QPushButton("Disamble",this);
    this->connect(button_dis,SIGNAL(clicked(bool)),SLOT(disWindow()));
    button_st = new QPushButton("Fusion style",this);
    frame = new QFrame(this);
    frame->setFrameStyle(1);
    slide = new QSlider(Qt::Horizontal,frame);
    slide->setRange(0,50);
    slide->setTickPosition(QSlider::TicksBelow);
    slide->setTickInterval(5);

    line = new QLineEdit(frame);

    QIntValidator* valid = new QIntValidator(0,50,line);
    line->setValidator(valid);
    spin  = new QSpinBox(frame);
    spin->setFixedSize(spin->sizeHint());
    spin->setMinimum(0);
    spin->setMaximum(50);
    spin->setValue(0);
    label = new QLabel("Not set",frame);
    label->setFrameStyle(QFrame::Panel | QFrame::Plain);
    label->setMinimumWidth(50);
    label->setMaximumHeight(20);

    this->connect(spin,"2valueChanged(int)",slide,"1setValue(int)");
    this->connect(slide,"2valueChanged(int)",spin,"1setValue(int)");
    this->connect(spin,SIGNAL(textChanged(QString)),label,SLOT(setText(QString)));
    this->connect(box,SIGNAL(activated(int)),this,SLOT(slotChangeLayout(int)));
    this->connect(spin,SIGNAL(textChanged(QString)),line,SLOT(setText(QString)));
    this->connect(line,"2textChanged(QString)",this,"1myslot(QString)");
    this->connect(this,"2mysignal(int)",spin,"1setValue(int)");

    this->connect(button_st,SIGNAL(clicked(bool)),this,SLOT(setStyle()));
    slide->setValue(20); // устанавливаем начальное значение, автоматически
    //инициируются сигналы к остальным элементам управления

    QHBoxLayout *main_layout = new QHBoxLayout(this);
    QVBoxLayout *butn_layout = new QVBoxLayout;
    butn_layout->addWidget(box);
    butn_layout->addWidget(butn_ex);
    butn_layout->addWidget(button_dis);
    butn_layout->addWidget(button_st);
    createGridlayout();
    main_layout->addWidget(frame);
    main_layout->addLayout(butn_layout);
    this->dumpObjectTree();

    qDebug()<<QStyleFactory::keys();

     QFile file("style.qss");
     qDebug()<< file.open(QFile::ReadOnly);
     QString stylesheet = file.readAll();
     this->setStyleSheet(stylesheet);

}

QLayout* Widget:: createHBoxlayout()
{
     QHBoxLayout *hlayout = new QHBoxLayout(frame);
     hlayout->addWidget(spin);
     hlayout->addWidget(slide);
     slide->setRange(0,50);
     slide->setTickPosition(QSlider::TicksBelow);
     slide->setTickInterval(5);
     hlayout->addWidget(line);
     hlayout->addWidget(label);
     return hlayout;
}



QLayout* Widget:: createVBoxlayout()
{
    QVBoxLayout * vlayout = new QVBoxLayout(frame);
    vlayout->addWidget(spin,Qt::AlignHCenter | Qt::AlignVCenter);
    vlayout->addWidget(slide);
    slide->setRange(0,50);
    slide->setTickPosition(QSlider::TicksAbove);
    slide->setTickInterval(5);
    vlayout->addWidget(line,Qt::AlignHCenter | Qt::AlignVCenter);
    line->setMaximumWidth(30);
    vlayout->addWidget(label,Qt::AlignHCenter | Qt::AlignVCenter);
    label->setMaximumWidth(30);
    return vlayout;

}

QLayout* Widget::createGridlayout()
{
    QGridLayout* glayout = new QGridLayout(frame);
    glayout->addWidget(spin,1,1,Qt::AlignCenter);
    glayout->addWidget(slide,1,2);
    glayout->addWidget(line,2,2,Qt::AlignCenter);
    line->setMaximumWidth(30);
    glayout->addWidget(label,2,1);
    return glayout;

}

void Widget::slotChangeLayout(int index)
{
    delete frame->layout();

    switch (index) {
    case 0:
        createHBoxlayout();
        break;
    case 1:
        createVBoxlayout();
        break;
    case 2:
        createGridlayout();
        break;
    default:
        break;
    }
}

void Widget::disWindow()
{
    if(frame->isEnabled())
    {
    button_dis->setText("Enable");
    frame->setEnabled(false);
    } else
    {
        frame->setEnabled(true);
        button_dis->setText("Disable");
    }
}

void Widget::setStyle()
{
    if(button_st->text()=="Fusion")
    {
        QApplication::setStyle(QStyleFactory::create("Fusion"));
        button_st->setText("Windows");
    }else
    {
        QApplication::setStyle(QStyleFactory::create("windowsvista"));
        button_st->setText("Fusion");
    }

}


Widget::~Widget()
{
}

