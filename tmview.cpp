#include "tmfreehandcomponent.h"
#include "tmrectanglecomponent.h"
#include "tmview.h"

#include <QDebug>
#include <QMainWindow>

TMView::TMView()
{

}

void TMView::add(DrawableComponent *drawableComponent)
{
    this->viewList.push_back(drawableComponent);
    undo();
    redo();
    populateMap();
}
void TMView::draw(QPainter *painter)
{
    for(int i=0;i<this->viewList.size();i++)
    {
        viewList.at(i)->draw(painter);
        if(viewList.at(i)->getIsSelected()==true)
        {
        for(int j=0;j<listOfGropingComponent.size();j++)
        {
         QSet<DrawableComponent *> groupingComponentSet=listOfGropingComponent.at(j);
         int flag=0;
         for(QSet<DrawableComponent *>::iterator itr=groupingComponentSet.begin();itr!=groupingComponentSet.end();itr++)
         {
             DrawableComponent *drObject=*itr;
             if(drObject==viewList.at(i)) flag=1;

         }
         if(flag==1)
         {
        for(QSet<DrawableComponent *>::iterator itr=groupingComponentSet.begin();itr!=groupingComponentSet.end();itr++)
        {
          DrawableComponent *drObject=*itr;
          drObject->setIsSelected(true);
          drObject->draw(painter);
          populateMap();
        }
        }
        }
        }
        QMainWindow mw;
        mw.update();
    }
}

void TMView::populateMap()
{
    componentMap.clear();
    int j=0;
    for(int i=viewList.size()-1;i>=0;i--)
    {
        if(viewList.at(i)->toString()=="freehand")
        {
            TMFreeHandComponent *tmFreehandComponent=(TMFreeHandComponent *)viewList.at(i);
            while(tmFreehandComponent->getFirst()!=1&&i>=0&&viewList.at(i)->toString()=="freehand")
            {
                i--;
                if(i>=0)
                tmFreehandComponent=(TMFreeHandComponent *)viewList.at(i);
            }
        }
        componentMap.insert(j,viewList.at(i));
        j++;
    }
}

QMap<int, DrawableComponent *>* TMView::getComponentMap()
{
    return &componentMap;
}

void TMView::setSelection(int x, int y)
{
    for(int i=0;i<this->viewList.size();i++)
    {
        viewList.at(i)->setSelection(x,y);
        populateMap();
    }
}

void TMView::groupingComponent(QPainter *painter)
{
    for(int i=viewList.size()-1;i>=0;i--)
    {
        if(viewList.at(i)->getIsSelected()==true)
        {
            setForGroupingComponent.insert(viewList.at(i));
            if(setForGroupingComponent.size()!=0)
            {
            for(QSet<DrawableComponent *>::iterator itr=setForGroupingComponent.begin();itr!=setForGroupingComponent.end();itr++)
            {
              DrawableComponent *drObject=*itr;
              drObject->setIsSelected(true);
              drObject->draw(painter);
            }
            }

        }
    }
}

void TMView::insertGroupingComponentIntoList()
{
    QSet<DrawableComponent *> groupingComponentSet;
    for(QSet<DrawableComponent *>::iterator itr=setForGroupingComponent.begin();itr!=setForGroupingComponent.end();itr++)
    {
      DrawableComponent *drObject=*itr;
      groupingComponentSet.insert(drObject);
    }
    listOfGropingComponent.push_back(groupingComponentSet);
    setForGroupingComponent.clear();
    populateMap();

}

void TMView::ungroupingComponent()
{
    for(int j=0;j<listOfGropingComponent.size();j++)
    {
     QSet<DrawableComponent *> groupingComponentSet=listOfGropingComponent.at(j);
     int flag=0;
     for(QSet<DrawableComponent *>::iterator itr=groupingComponentSet.begin();itr!=groupingComponentSet.end();itr++)
     {
         DrawableComponent *drObject=*itr;
         if(drObject->getIsSelected()==true)
         {
             flag=1;
             break;
         }
     }
     if(flag==1) listOfGropingComponent.removeAt(j);
     QMainWindow mw;
     mw.update();
    }
    undo();
    redo();
}

void TMView::deleteComponent()
{

    for(int i=0;i<viewList.size();i++)
    {
        qDebug()<<viewList.at(i)->getIsSelected();
        if(viewList.at(i)->getIsSelected()==true)
        {
            undo();
            redo();
            viewList.removeAt(i);

            QMainWindow mw;
            mw.update();

        }
        populateMap();
    }


}

void TMView::undo()
{
 undoList.clear();
 for(int i=0;i<viewList.size()-1;i++)
 {
    undoList.push_back(viewList.at(i)) ;
 }
}

void TMView::redo()
{
    redoList.clear();
    for(int i=0;i<viewList.size();i++)
    {
       redoList.push_back(viewList.at(i)) ;
    }
}

QList<DrawableComponent *>* TMView::getUndoList()
{
    return &undoList;
}

QList<DrawableComponent *> *TMView::getRedoList()
{
    return &redoList;
}

QList<DrawableComponent *> *TMView::getViewList()
{
    return &viewList;
}



