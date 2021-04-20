#ifndef CHEMISTRYFRAMECOMPONENT_H
#define CHEMISTRYFRAMECOMPONENT_H

#include <QList>



class ChemistryFrameComponent
{
public:
    QList<QString> atomicNumberList;
    QList<QString> atomicMassList;
    QList<QString> elementNameList;
    QList<QString> elementSymbolList;
public:
    ChemistryFrameComponent();
public:
    void populateElementInList();
    QList<QString> searchElementOfPeriodicTable(QString elementName);
};

#endif // CHEMISTRYFRAMECOMPONENT_H
