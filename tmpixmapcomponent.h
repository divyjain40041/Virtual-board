#ifndef TMPIXMAPCOMPONENT_H
#define TMPIXMAPCOMPONENT_H

#include "drawablecomponent.h"

#include <QGuiApplication>
#include <QScreen>



class TMPixmapComponent : public DrawableComponent
{
public:
    TMPixmapComponent();
public:
    QScreen *screen=QGuiApplication::primaryScreen();
    QRect screenGeometry=screen->geometry();
    int y=screenGeometry.height()/3;
    int x=screenGeometry.width()/2;
    int w=200;
    int h=200;
    QString fileName="";
    QString componentName="Pixmap";
    bool isSelected=false;
    QString getFileName() const;
    void setFileName(const QString &value);
    int getX() const;
    void setX(int value);
    int getY() const;
    void setY(int value);
    void draw(QPainter *painter) override;
    QString toString() override;
    int getW() const;
    void setW(int value);
    int getH() const;
    void setH(int value);
    bool getIsSelected() const override;
    void setIsSelected(bool value) override;
    void setSelection(int x,int y) override;
    QString getComponentName() const override;
    void setComponentName(const QString &value) override;
    void changePosition(int x, int y) override;
    void resizeComponent(int x, int y) override;
};

#endif // TMPIXMAPCOMPONENT_H
