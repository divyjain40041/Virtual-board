#include "tmrectanglecomponent.h"

#include <QDebug>

TMRectangleComponent::TMRectangleComponent()
{

}

bool TMRectangleComponent::getIsSelected() const
{
    return isSelected;
}

void TMRectangleComponent::setIsSelected(bool value)
{
    isSelected = value;
}

void TMRectangleComponent::changePosition(int x, int y)
{
    setX(getX()+x);
    setY(getY()+y);
    setW(getW());
    setH(getH());
}

void TMRectangleComponent::resizeComponent(int x, int y)
{
    setX(getX());
    setY(getY());
    setW(getW()+x);
    setH(getH()+y);
}

void TMRectangleComponent::setComponentName(const QString &value)
{
    componentName = value;
    if(value=="") componentName="Rectangle";
}

void TMRectangleComponent::setSelection(int x, int y)
{
    int flag=0;
    int x2=this->x+this->w;
    int y2=this->y+this->h;
    if(isSelected==true)
    {
        flag=0;
    }
    else
    {
    if(this->w>0&&this->h>0)
    {
        if((x>this->x)&&(x<x2)&&(y>this->y)&&(y<y2))
        {
            flag=1;
            isSelected=true;
        }

    }
    if(this->w>0&&this->h<0)
    {
            if((x>this->x)&&(x<x2)&&(y<this->y)&&(y>y2))
            {
                flag=1;
                isSelected=true;
            }
    }
    if(this->w<0&&this->h<0)
    {
            if((x<this->x)&&(x>x2)&&(y<this->y)&&(y>y2))
            {
                flag=1;
                isSelected=true;
            }
    }
    if(this->w<0&&this->h>0)
    {
            if((x<this->x)&&(x>x2)&&(y>this->y)&&(y<y2))
            {
                flag=1;
                isSelected=true;
            }
    }
    }
    if(flag==0) this->isSelected=false;
}

QString TMRectangleComponent::getColor() const
{
    return color;
}

void TMRectangleComponent::setColor(const QString &value)
{
    color = value;
}

int TMRectangleComponent::getWidth() const
{
    return width;
}

void TMRectangleComponent::setWidth(int value)
{
    width = value;
}

int TMRectangleComponent::getH() const
{
    return h;
}

void TMRectangleComponent::setH(int value)
{
    h = value;
}

int TMRectangleComponent::getW() const
{
    return w;
}

void TMRectangleComponent::setW(int value)
{
    w = value;
}

int TMRectangleComponent::getY() const
{
    return y;
}

void TMRectangleComponent::setY(int value)
{
    y = value;
}

int TMRectangleComponent::getX() const
{
    return x;
}

void TMRectangleComponent::setX(int value)
{
    x = value;
}
void TMRectangleComponent::draw(QPainter *painter)
{
    painter->setPen(QPen(QColor(getColor()),getWidth()));
    painter->drawRect(getX(),getY(),getW(),getH());
    if(isSelected==true)
    {
        painter->setPen(QPen(QColor("blue"),8));
        painter->drawPoint(getX(),getY());
        painter->drawPoint(getX()+getW(),getY());
        painter->drawPoint(getX(),(getY()+getH()));
        painter->drawPoint(getX()+getW(),getH()+getY());
        painter->setPen(QPen(QColor("blue"),1,Qt::DashDotLine));
         painter->drawRect(x,y,w,h);
    }

}

QString TMRectangleComponent::toString()
{
    return "rectangle";
}

QString TMRectangleComponent::getComponentName() const
{
    return componentName;
}
