#include "tmpixmapcomponent.h"

TMPixmapComponent::TMPixmapComponent()
{

}

QString TMPixmapComponent::getComponentName() const
{
    return componentName;
}

void TMPixmapComponent::setComponentName(const QString &value)
{
    componentName = value;
    if(value=="") componentName="Pixmap";
}

void TMPixmapComponent::changePosition(int x, int y)
{
    setX(getX()+x);
    setY(getY()+y);
    setW(getW());
    setH(getH());
}

void TMPixmapComponent::resizeComponent(int x, int y)
{
    setX(getX());
    setY(getY());
    setW(getW()+x);
    setH(getH()+y);
}

bool TMPixmapComponent::getIsSelected() const
{
    return isSelected;
}

void TMPixmapComponent::setIsSelected(bool value)
{
    isSelected = value;
}

void TMPixmapComponent::setSelection(int x, int y)
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

int TMPixmapComponent::getH() const
{
    return h;
}

void TMPixmapComponent::setH(int value)
{
    h = value;
}

int TMPixmapComponent::getW() const
{
    return w;
}

void TMPixmapComponent::setW(int value)
{
    w = value;
}

int TMPixmapComponent::getY() const
{
    return y;
}

void TMPixmapComponent::setY(int value)
{
    y = value;
}

void TMPixmapComponent::draw(QPainter *painter)
{
    painter->drawPixmap(getX(),getY(),getW(),getH(),QPixmap(getFileName().trimmed()));
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

QString TMPixmapComponent::toString()
{
    return "pixmap";
}

int TMPixmapComponent::getX() const
{
    return x;
}

void TMPixmapComponent::setX(int value)
{
    x = value;
}

QString TMPixmapComponent::getFileName() const
{
    return fileName;
}

void TMPixmapComponent::setFileName(const QString &value)
{
    fileName = value;
}
