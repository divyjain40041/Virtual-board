#ifndef DRAWABLECOMPONENT_H
#define DRAWABLECOMPONENT_H

#include <QPainter>



class DrawableComponent
{
public:
     QString componentName;
     bool isSelected=false;
public:
    DrawableComponent();
    virtual void draw(QPainter *painter)=0;
    virtual QString toString();
    virtual QString getComponentName() const;
    virtual void setComponentName(const QString &value);
    virtual void setSelection(int x,int y);
    virtual bool getIsSelected() const;
    virtual void setIsSelected(bool value);
    virtual void changePosition(int x,int y);
    virtual void resizeComponent(int x,int y);
};

#endif // DRAWABLECOMPONENT_H
