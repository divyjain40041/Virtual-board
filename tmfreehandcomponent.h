#ifndef TMFREEHANDCOMPONENT_H
#define TMFREEHANDCOMPONENT_H

#include "drawablecomponent.h"

#include <QString>



class TMFreeHandComponent:public DrawableComponent
{
public:
    TMFreeHandComponent();
public:
    int x1;
    int x2;
    int y1;
    int y2;
    int width;
    QString color;    
    QString componentName="Freehand";
    int first=0;
    int last=0;
    bool isSelected=false;
public:
    int getX1() const;
    void setX1(int value);
    int getX2() const;
    void setX2(int value);
    int getY1() const;
    void setY1(int value);
    int getY2() const;
    void setY2(int value);
    int getWidth() const;
    void setWidth(int value);
    QString getColor() const;
    void setColor(const QString &value);
     void draw(QPainter *painter) override;
     QString toString() override;
     QString getComponentName() const override;
     void setComponentName(const QString &value) override;
     int getFirst() const;
     void setFirst(int value);
     int getLast() const;
     void setLast(int value);
};

#endif // TMFREEHANDCOMPONENT_H
