#ifndef TMLINECOMPONENT_H
#define TMLINECOMPONENT_H

#include "drawablecomponent.h"



class TMLineComponent : public DrawableComponent
{
public:
    TMLineComponent();
public:
    int x1;
    int x2;
    int y1;
    int y2;
    int width;
    QString color;
    QString componentName="Line";
    bool isSelected=false;
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
    void setSelection(int x,int y) override;
    bool getIsSelected() const override;
    void setIsSelected(bool value) override;
    void changePosition(int x, int y) override;
    void resizeComponent(int x, int y) override;
};

#endif // TMLINECOMPONENT_H
