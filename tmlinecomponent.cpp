#include "tmlinecomponent.h"
#include<QtMath>
TMLineComponent::TMLineComponent()
{

}

bool TMLineComponent::getIsSelected() const
{
    return isSelected;
}

void TMLineComponent::setIsSelected(bool value)
{
    isSelected = value;
}

void TMLineComponent::changePosition(int x, int y)
{
    //int changeX=x-getX1();
    //int changeY=y-getY1();
    setX1(getX1()+x);
    setY1(getY1()+y);
    setX2(getX2()+x);
    setY2(getY2()+y);
}

void TMLineComponent::resizeComponent(int x, int y)
{
    setX1(getX1());
    setY1(getY1());
    setX2(getX2()+x);
    setY2(getY2()+y);
}

QString TMLineComponent::getComponentName() const
{
    return componentName;
}

void TMLineComponent::setComponentName(const QString &value)
{
    componentName = value;
    if(value=="") componentName="Line";
}

void TMLineComponent::setSelection(int x, int y)
{
    int fullDistance=sqrt(qPow(getX2()-getX1(),2)+qPow(getY2()-getY1(),2));
    int firstHalf=sqrt(qPow(x-getX1(),2)+qPow(y-getY1(),2));
    int secondHalf=sqrt(qPow(getX2()-x,2)+qPow(getY2()-y,2));
    int flag=0;
    if(isSelected==true)
    {
     flag=0;
    }
    else
    {
    if(fullDistance==firstHalf+secondHalf)
    {
        flag=1;
        isSelected=true;
    }
    }
    if(flag==0) isSelected=false;

}

QString TMLineComponent::getColor() const
{
    return color;
}

void TMLineComponent::setColor(const QString &value)
{
    color = value;
}

int TMLineComponent::getWidth() const
{
    return width;
}

void TMLineComponent::setWidth(int value)
{
    width = value;
}

int TMLineComponent::getY2() const
{
    return y2;
}

void TMLineComponent::setY2(int value)
{
    y2 = value;
}

int TMLineComponent::getY1() const
{
    return y1;
}

void TMLineComponent::setY1(int value)
{
    y1 = value;
}

int TMLineComponent::getX2() const
{
    return x2;
}

void TMLineComponent::setX2(int value)
{
    x2 = value;
}

int TMLineComponent::getX1() const
{
    return x1;
}

void TMLineComponent::setX1(int value)
{
    x1 = value;
}

void TMLineComponent::draw(QPainter *painter)
{
   painter->setPen(QPen(QColor(getColor()),getWidth()));
   painter->drawLine(getX1(),getY1(),getX2(),getY2());
   if(isSelected==true)
   {
       painter->setPen(QPen(QColor("blue"),8));
       painter->drawPoint(getX1(),getY1());
       painter->drawPoint(getX2(),getY2());
       painter->setPen(QPen(QColor("blue"),1,Qt::DashLine));
       painter->drawLine(getX1(),getY1(),getX2(),getY2());
   }
}

QString TMLineComponent::toString()
{
    return "line";
}
