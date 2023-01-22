#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
class QLayout;
class QFrame;
class QSlider;
class QLineEdit;
class QSpinBox;
class QLabel;
class QPushButton;
class Widget : public QWidget
{
    Q_OBJECT

   QFrame* frame;
   QSlider* slide;
   QLineEdit* line;
   QSpinBox* spin;
   QLabel* label;
   QPushButton *button_dis;
   QPushButton *button_st;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
   QLayout* createHBoxlayout();
   QLayout* createVBoxlayout();
   QLayout* createGridlayout();

signals:
    void mysignal(int a );

public slots:
   void myslot(QString str)
   {
       int num = str.toInt();

       emit mysignal(num);
   }

   void slotChangeLayout(int index);
   void disWindow();
   void setStyle();

};
#endif // WIDGET_H
