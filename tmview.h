#ifndef TMVIEW_H
#define TMVIEW_H

#include "drawablecomponent.h"

#include <QList>
#include <QMap>
#include <QSet>



class TMView
{
public:
    TMView();
public:
    QList<DrawableComponent *> viewList;
    QMap<int,DrawableComponent *> componentMap;
    QSet<DrawableComponent *> setForGroupingComponent;
    QList<QSet<DrawableComponent *>> listOfGropingComponent;
    QList<DrawableComponent *> undoList;
    QList<DrawableComponent *> redoList;
    int changeX=0;
    int changeY=0;
public:
    void add(DrawableComponent *drawableComponent);
    void draw(QPainter *painter);
    void populateMap();
    QMap<int,DrawableComponent *>* getComponentMap();
     void setSelection(int x,int y);
     void groupingComponent(QPainter *painter);
     void insertGroupingComponentIntoList();
     int getChangeX() const;
     void setChangeX(int value);
     void ungroupingComponent();
     void deleteComponent();
     void undo();
     void redo();
     QList<DrawableComponent *>* getUndoList();
     QList<DrawableComponent *>* getRedoList();
     QList<DrawableComponent *>* getViewList();
};

#endif // TMVIEW_H
