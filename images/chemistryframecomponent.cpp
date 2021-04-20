#include "chemistryframecomponent.h"

#include <QFile>
#include <QList>
#include<QDebug>

ChemistryFrameComponent::ChemistryFrameComponent()
{

}

void ChemistryFrameComponent::populateElementInList()
{
    QFile atomicNumberFile(":/txtFiles/atomicNumber.txt");
    QFile atomicMassFile(":/txtFiles/atomicMass.txt");
    QFile elementNameFile(":/txtFiles/elementName.txt");
    QFile elementSymbolFile(":/txtFiles/elementSymbol.txt");
    if(!atomicNumberFile.open(QFile::ReadOnly | QFile::Text)||!atomicMassFile.open(QFile::ReadOnly | QFile::Text)||!elementNameFile.open(QFile::ReadOnly | QFile::Text)||!elementSymbolFile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << " Could not open the file for reading";
        return;
    }
    QTextStream atomicNumber(&atomicNumberFile);
    QTextStream atomicMass(&atomicMassFile);
    QTextStream elementName(&elementNameFile);
    QTextStream elementSymbol(&elementSymbolFile);

    while (!atomicNumber.atEnd()) {
          QString line = atomicNumber.readLine();
          atomicNumberList.push_back(line);
    }
    atomicNumberFile.close();

    while (!atomicMass.atEnd()) {
          QString line = atomicMass.readLine();
          atomicMassList.push_back(line);
    }
    atomicMassFile.close();

    while (!elementName.atEnd()) {
          QString line = elementName.readLine();
          elementNameList.push_back(line);
    }
    elementNameFile.close();

    while (!elementSymbol.atEnd()) {
          QString line = elementSymbol.readLine();
          elementSymbolList.push_back(line);
    }
    elementSymbolFile.close();
}

QList<QString> ChemistryFrameComponent::searchElementOfPeriodicTable(QString elementName)
{
    int found=-1;
    QList<QString> returnList;
    for(int i=0;i<elementNameList.size();i++)
    {
        if(elementName.toUpper()==elementNameList.at(i).toUpper())
        {
            found=i;
            break;
        }
    }
    if(found==-1)
    {
     returnList.clear();
     return returnList;
    }
    returnList.push_back(elementNameList.at(found));
    returnList.push_back(elementSymbolList.at(found));
    returnList.push_back(atomicNumberList.at(found));
    returnList.push_back(atomicMassList.at(found));
return returnList;
}
