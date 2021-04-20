#include "tmfreehandcomponent.h"

#include <QDebug>
#include<QtMath>
TMFreeHandComponent::TMFreeHandComponent()
{

}

int TMFreeHandComponent::getLast() const
{
    return last;
}

void TMFreeHandComponent::setLast(int value)
{
    last = value;
}

int TMFreeHandComponent::getFirst() const
{
    return first;
}

void TMFreeHandComponent::setFirst(int value)
{
    first = value;
}


QString TMFreeHandComponent::getComponentName() const
{
    return componentName;
}

void TMFreeHandComponent::setComponentName(const QString &value)
{
    componentName = value;
    if(value=="") componentName="Freehand";
}

QString TMFreeHandComponent::getColor() const
{
    return color;
}

void TMFreeHandComponent::setColor(const QString &value)
{
    color = value;
}

int TMFreeHandComponent::getWidth() const
{
    return width;
}

void TMFreeHandComponent::setWidth(int value)
{
    width = value;
}

int TMFreeHandComponent::getY2() const
{
    return y2;
}

void TMFreeHandComponent::setY2(int value)
{
    y2 = value;
}

int TMFreeHandComponent::getY1() const
{
    return y1;
}

void TMFreeHandComponent::setY1(int value)
{
    y1 = value;
}

int TMFreeHandComponent::getX2() const
{
    return x2;
}

void TMFreeHandComponent::setX2(int value)
{
    x2 = value;
}

int TMFreeHandComponent::getX1() const
{
    return x1;
}

void TMFreeHandComponent::setX1(int value)
{
    x1 = value;
}
void TMFreeHandComponent::draw(QPainter *painter)
{
    painter->setPen(QPen(QColor(getColor()),getWidth()));
    painter->drawLine(getX1(),getY1(),getX2(),getY2());
}
QString TMFreeHandComponent::toString()
{
    return "freehand";
}
