#include "tmcirclecomponent.h"
#include <QDebug>
#include<QtMath>
TMCircleComponent::TMCircleComponent()
{

}

bool TMCircleComponent::getIsSelected() const
{
    return isSelected;
}

void TMCircleComponent::setIsSelected(bool value)
{
    isSelected = value;
}

void TMCircleComponent::changePosition(int x, int y)
{
    setX(getX()+x);
    setY(getY()+y);
    setW(getW());
    setH(getH());
}

void TMCircleComponent::resizeComponent(int x, int y)
{
    setX(getX());
    setY(getY());
    setW(getW()+x);
    setH(getH()+y);
}

QString TMCircleComponent::getComponentName() const
{
    return componentName;
}

void TMCircleComponent::setComponentName(const QString &value)
{
    componentName = value;
    if(value=="") componentName="Circle";
}

void TMCircleComponent::setSelection(int x, int y)
{

  double h=double(getX()+getX()+getW())/2;
  double k=double(getY()+getY()+getH())/2;
  double a=double(getW())/2;
  double b=double(getH())/2;
  double positionX=double(x);
  double positionY=double(y);

  int flag=0;
  if(isSelected==true)
  {
      flag=0;
  }
  else
  {
      double result=(double(qPow(positionX-h,2)/qPow(a,2)))+(double(qPow(positionY-k,2)/qPow(b,2)));
      if(result<=1)
      {
          flag=1;
              isSelected=true;
      }
  }
  if(flag==0) isSelected=false;
}

QString TMCircleComponent::getColor() const
{
    return color;
}

void TMCircleComponent::setColor(const QString &value)
{
    color = value;
}

int TMCircleComponent::getWidth() const
{
    return width;
}

void TMCircleComponent::setWidth(int value)
{
    width = value;
}

int TMCircleComponent::getH() const
{
    return h;
}

void TMCircleComponent::setH(int value)
{
    h = value;
}

int TMCircleComponent::getW() const
{
    return w;
}

void TMCircleComponent::setW(int value)
{
    w = value;
}

int TMCircleComponent::getY() const
{
    return y;
}

void TMCircleComponent::setY(int value)
{
    y = value;
}

int TMCircleComponent::getX() const
{
    return x;
}

void TMCircleComponent::setX(int value)
{
    x = value;
}

void TMCircleComponent::draw(QPainter *painter)
{
    painter->setPen(QPen(QColor(getColor()),getWidth()));
    painter->drawEllipse(getX(),getY(),getW(),getH());
    if(isSelected==true)
    {int x1=getX();
        int y1=getH()/2+getY();
        int x2=getX()+getW();
        int y2=getH()/2+getY();
        int x3=getX()+getW()/2;
        int y3=getY();
        int x4=getX()+getW()/2;
        int y4=getH()+getY();
        painter->setPen(QPen(QColor("blue"),8));
        painter->drawPoint(x1,y1);
        painter->drawPoint(x2,y2);
        painter->drawPoint(x3,y3);
        painter->drawPoint(x4,y4);
        painter->setPen(QPen(QColor("blue"),1,Qt::DashLine));
        painter->drawEllipse(x,y,w,h);
    }
}

QString TMCircleComponent::toString()
{
    return "circle";
}
