#ifndef TMCIRCLECOMPONENT_H
#define TMCIRCLECOMPONENT_H

#include "drawablecomponent.h"



class TMCircleComponent : public DrawableComponent
{
public:
    TMCircleComponent();
public:
    int x;
    int y;
    int w;
    int h;
    int width;
    QString color;
    QString componentName="Circle";
    bool isSelected=false;
    int getX() const;
    void setX(int value);
    int getY() const;
    void setY(int value);
    int getW() const;
    void setW(int value);
    int getH() const;
    void setH(int value);
    int getWidth() const;
    void setWidth(int value);
    QString getColor() const;
    void setColor(const QString &value);
    void draw(QPainter *painter) override;
    QString toString() override;
    QString getComponentName() const override;
    void setComponentName(const QString &value) override;
    void setSelection(int x,int y) override;
    bool getIsSelected() const override;
    void setIsSelected(bool value) override;
    void changePosition(int x, int y) override;
    void resizeComponent(int x, int y) override;
};

#endif // TMCIRCLECOMPONENT_H
