#include "chemistryframecomponent.h"
#include "mainwindow.h"
#include "tmcirclecomponent.h"
#include "tmfreehandcomponent.h"
#include "tmlinecomponent.h"
#include "tmpixmapcomponent.h"
#include "tmrectanglecomponent.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QScreen>
#include<QMap>
#include <QFileDialog>
#include <QMainWindow>
#include <QJsonDocument>
#include <QLinkedList>
#include <QJsonArray>
#include <QJsonObject>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
QMainWindow::showFullScreen();
QScreen *screen=QGuiApplication::primaryScreen();
QRect screenGeometry=screen->geometry();
screenHeight=screenGeometry.height();
screenWidth=screenGeometry.width();
qDebug()<<screenHeight;
qDebug()<<screenWidth;
//setting components according to fullsize screen (START)
this->ui->toolFrame->setGeometry(screenWidth-170,80,screenWidth-1780,screenHeight-114);
this->ui->toolTitleFrame->setGeometry(screenWidth-170,20,screenWidth-1780,screenHeight-926);
this->ui->tableViewFrame->setGeometry(10,20,screenWidth-1780,(screenHeight-210)+(screenHeight-926));
this->ui->pageTabFrame->setGeometry(10+screenWidth-1780+40,70,screenWidth-1880,(screenHeight-910)+(screenHeight-906));
this->ui->chemistryFrame->setGeometry(screenWidth-495,screenHeight-540,screenWidth-1600,screenHeight-780);
this->ui->chemistryFrame2->setGeometry(screenWidth-495,screenHeight-581,screenWidth-1600,screenHeight-1039);
this->ui->elementDetailFrame->setGeometry(screenWidth-737,screenHeight-521,screenWidth-1709,screenHeight-959);
this->ui->functionalGroupFrame->setGeometry(screenWidth-495,screenHeight-540,screenWidth-1600,screenHeight-780);
this->ui->functionalGroupFrame2->setGeometry(screenWidth-495,screenHeight-581,screenWidth-1600,screenHeight-1039);
this->ui->labInstrumentFrame->setGeometry(screenWidth-495,screenHeight-540,screenWidth-1600,screenHeight-680);
this->ui->labInstrumentFrame2->setGeometry(screenWidth-495,screenHeight-581,screenWidth-1600,screenHeight-1039);
this->ui->applicationTitleLabel->setGeometry(10+screenWidth-1780+118,10,screenWidth-560,(screenHeight-1026));
this->ui->changeComponentNameFrame->setGeometry((screenWidth/2)-90,screenHeight-620,screenWidth-1689,screenHeight-959);

this->ui->chemistryFrame->setVisible(false);
this->ui->chemistryFrame2->setVisible(false);
this->ui->elementDetailFrame->setVisible(false);
this->ui->functionalGroupFrame->setVisible(false);
this->ui->functionalGroupFrame2->setVisible(false);
this->ui->labInstrumentFrame->setVisible(false);
this->ui->labInstrumentFrame2->setVisible(false);
this->ui->changeComponentNameFrame->setVisible(false);
this->ui->widthSlider->setRange(2,50);
this->ui->pageLineMarginSlider->setRange(20,100);
//setting components according to fullsize screen (END)

setButtonIcon();
setPageTabVisibility();
initializeTMViewObject();
tableDesign();
}

MainWindow::~MainWindow()
{
    delete ui;
}
int flag=0;
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //drawing board (START)
    painter.drawPixmap(screenWidth-1780+118,80,screenWidth-540,(screenHeight-240)+(screenHeight-1026),QPixmap(":/Images/frame.png"));
    painter.fillRect(QRect(10+screenWidth-1780+118,90,screenWidth-560,(screenHeight-260)+(screenHeight-1026)),QColor(Qt::white));
    painter.setClipRegion(QRegion(10+screenWidth-1780+118,100,screenWidth-560,(screenHeight-270)+(screenHeight-1026)));
    if(plainBoardButtonClicked==1)
    {

    painter.fillRect(QRect(10+screenWidth-1780+118,90,screenWidth-560,(screenHeight-260)+(screenHeight-1026)),QColor(Qt::white));
    painter.setClipRegion(QRegion(10+screenWidth-1780+118,100,screenWidth-560,(screenHeight-270)+(screenHeight-1026)));
    }
    if(gridButtonClicked==1)
    {
        painter.fillRect(QRect(10+screenWidth-1780+118,90,screenWidth-560,(screenHeight-260)+(screenHeight-1026)),QColor(Qt::white));
        painter.setClipRegion(QRegion(10+screenWidth-1780+118,100,screenWidth-560,(screenHeight-270)+(screenHeight-1026)));
        for (int i=pageLineMarginSlider;i<(screenHeight-260)+(screenHeight-1026);i=i+pageLineMarginSlider)
        {
            painter.setPen(Qt::black);
         painter.drawLine(10+screenWidth-1780+118,100+i,screenWidth-300,100+i);
         painter.drawLine(10+screenWidth-1780+118+i,120,10+screenWidth-1780+118+i,(screenHeight-120));
        }
        for (int i=pageLineMarginSlider;i<screenWidth-300;i=i+pageLineMarginSlider)
        {
            painter.setPen(Qt::black);
         painter.drawLine(10+screenWidth-1780+118+i,100,10+screenWidth-1780+118+i,(screenHeight-120));
        }
    }

    if(lineBoardButtonClicked==1)
    {
        painter.fillRect(QRect(10+screenWidth-1780+118,90,screenWidth-560,(screenHeight-260)+(screenHeight-1026)),QColor(Qt::white));
        painter.setClipRegion(QRegion(10+screenWidth-1780+118,100,screenWidth-560,(screenHeight-270)+(screenHeight-1026)));
        for (int i=pageLineMarginSlider;i<(screenHeight-260)+(screenHeight-1026);i=i+pageLineMarginSlider)
        {
            painter.setPen(Qt::black);
         painter.drawLine(10+screenWidth-1780+118,100+i,screenWidth-300,100+i);
        }
    }
    //drawing board (END)

    //drawing line (START)
    if(lineButtonClicked==1)
    {
        painter.setPen(QPen(QColor(color),2));
        painter.drawLine(oldX,oldY,currentX,currentY);
        if(lineButtonRelease==1)
        {
            int i=0;
            for (i=0;i<newPageRadioButtonListSize;i++)
            {
             if(newPageRadioButtonList.at(i)->isChecked()==true) break;
            }
          TMLineComponent *tmLineComponent=new TMLineComponent();
          tmLineComponent->setX1(oldX);
          tmLineComponent->setY1(oldY);
          tmLineComponent->setX2(currentX);
          tmLineComponent->setY2(currentY);
          tmLineComponent->setColor(color);
          tmLineComponent->setWidth(ComponentWidth);
          tmViewObjectList.at(i)->add(tmLineComponent);
          addComponentIntoTable();
          lineButtonRelease=0;
        }
    }
    //drawing line (END)

    //drawing circle (START)
        if(circleButtonClicked==1)
        {

            int w=currentX-oldX;
            int h=currentY-oldY;
            painter.setPen(QPen(QColor(color),2));
            painter.drawEllipse(oldX,oldY,w,h);
            if(circleButtonRelease==1)
            {
                int i=0;
                for (i=0;i<newPageRadioButtonListSize;i++)
                {
                 if(newPageRadioButtonList.at(i)->isChecked()==true) break;
                }
                tmCircleComponent=new TMCircleComponent();
                tmCircleComponent->setX(oldX);
                tmCircleComponent->setY(oldY);
                tmCircleComponent->setW(w);
                tmCircleComponent->setH(h);
                tmCircleComponent->setColor(color);
                tmCircleComponent->setWidth(ComponentWidth);
                tmViewObjectList.at(i)->add(tmCircleComponent);
                addComponentIntoTable();
                circleButtonRelease=0;
            }

        }
    //drawing circle (END)

    //drawing rectangle (START)
            if(rectangleButtonClicked==1)
            {

                int w=currentX-oldX;
                int h=currentY-oldY;
                painter.setPen(QPen(QColor(color),2));
                painter.drawRect(oldX,oldY,w,h);
                 if(rectangleButtonRelease==1)
                 {
                     int i=0;
                     for (i=0;i<newPageRadioButtonListSize;i++)
                     {
                      if(newPageRadioButtonList.at(i)->isChecked()==true) break;
                     }
                     TMRectangleComponent *tmRectangleComponent=new TMRectangleComponent();
                     tmRectangleComponent->setX(oldX);
                     tmRectangleComponent->setY(oldY);
                     tmRectangleComponent->setW(w);
                     tmRectangleComponent->setH(h);
                     tmRectangleComponent->setColor(color);
                     tmRectangleComponent->setWidth(ComponentWidth);
                     tmViewObjectList.at(i)->add(tmRectangleComponent);
                     addComponentIntoTable();
                     rectangleButtonRelease=0;
                 }

            }
//Drawing rectangle (END)


//drawing freehand (END)
//freehand draw mouse ki metod me se hi kiya hai
//drawing freehand (END)

 //selction of component (START)
   if(selectedButtonClicked==1)
   {
       if(moveable==1)
       {
          moveable=0;
       }
       else
       {
            tmViewObjectList.at(currentIndexOfSelectedPage)->setSelection(oldX,oldY);
            addComponentIntoTable();
       }
   }

   if(selectedButtonClicked==1&&ctrlKeyPressed==1)
   {
       if(flag==0) tmViewObjectList.at(currentIndexOfSelectedPage)->setForGroupingComponent.clear();
       tmViewObjectList.at(currentIndexOfSelectedPage)->groupingComponent(&painter);
       flag=1;
   }
    //selection of component (END)
   //grouping component method call (START)
   if(groupButtonClicked==1)
   {
    tmViewObjectList.at(currentIndexOfSelectedPage)->insertGroupingComponentIntoList();
    groupButtonClicked=0;
   }
   //grouping component method call (END)

   //ungrouping component method call (START)
   if(ungroupButtonClicked==1)
   {
       tmViewObjectList.at(currentIndexOfSelectedPage)->ungroupingComponent();
       ungroupButtonClicked=0;
   }
   //ungrouping component method call (END)

 //retrieving list of tmView (START)
    for (int i=0;i<newPageRadioButtonListSize;i++)
     {
        if(newPageRadioButtonList.at(i)->isChecked()==true)
         {
            tmViewObjectList.at(i)->draw(&painter);
            break;
         }
      }
 //retrieving list of tmView (END)
}

//setting button icon (START)
void MainWindow::setButtonIcon()
{
    this->ui->circleButton->setIcon(QIcon(QPixmap(":/Images/circleButtonIcon.png")));
    this->ui->circleButton->setIconSize(QSize(25,25));
    this->ui->circleButton->setToolTip("Circle");
    this->ui->lineButton->setIcon(QIcon(QPixmap(":/Images/lineButtonIcon.png")));
    this->ui->lineButton->setIconSize(QSize(25,25));
    this->ui->lineButton->setToolTip("Line");
    this->ui->rectangleButton->setIcon(QIcon(QPixmap(":/Images/rectangleButtonIcon.png")));
    this->ui->rectangleButton->setIconSize(QSize(25,25));
    this->ui->rectangleButton->setToolTip("Rectangle");
    this->ui->freehandButton->setIcon(QIcon(QPixmap(":/Images/penButtonIcon.png")));
    this->ui->freehandButton->setIconSize(QSize(25,25));
    this->ui->freehandButton->setToolTip("Freehand");
    this->ui->exitButton->setIcon(QIcon(QPixmap(":/Images/exitIcon.png")));
    this->ui->exitButton->setIconSize(QSize(30,30));
    this->ui->exitButton->setToolTip("Exit");
    this->ui->openFileButton->setIcon(QIcon(QPixmap(":/Images/openFileButtonIcon.png")));
    this->ui->openFileButton->setIconSize(QSize(25,25));
    this->ui->openFileButton->setToolTip("Open");
    this->ui->saveButton->setIcon(QIcon(QPixmap(":/Images/saveButtonIcon.png")));
    this->ui->saveButton->setIconSize(QSize(25,25));
    this->ui->saveButton->setToolTip("Save");
    this->ui->groupButton->setIcon(QIcon(QPixmap(":/Images/groupButtonIcon.png")));
    this->ui->groupButton->setIconSize(QSize(25,25));
    this->ui->groupButton->setToolTip("Group");
    this->ui->ungroupButton->setIcon(QIcon(QPixmap(":/Images/ungroupButtonIcon.png")));
    this->ui->ungroupButton->setIconSize(QSize(25,25));
    this->ui->ungroupButton->setToolTip("Ungroup");
    this->ui->undoButton->setIcon(QIcon(QPixmap(":/Images/undoButtonIcon.png")));
    this->ui->undoButton->setIconSize(QSize(25,25));
    this->ui->undoButton->setToolTip("Undo");
    this->ui->redoButton->setIcon(QIcon(QPixmap(":/Images/redoButtonIcon.png")));
    this->ui->redoButton->setIconSize(QSize(25,25));
    this->ui->redoButton->setToolTip("Redo");
    this->ui->selectButton->setIcon(QIcon(QPixmap(":/Images/handButtonIcon.png")));
    this->ui->selectButton->setIconSize(QSize(25,25));
    this->ui->selectButton->setToolTip("Select");
    this->ui->newPageButton->setIcon(QIcon(QPixmap(":/Images/newPage.png")));
    this->ui->newPageButton->setIconSize(QSize(25,25));
    this->ui->newPageButton->setToolTip("New page");
    this->ui->resizeButton->setIcon(QIcon(QPixmap(":/Images/resizeIcon.png")));
    this->ui->resizeButton->setIconSize(QSize(25,25));
    this->ui->resizeButton->setToolTip("Resize");
    this->ui->imageUploadButton->setIcon(QIcon(QPixmap(":/Images/imageButtonIcon.png")));
    this->ui->imageUploadButton->setIconSize(QSize(25,25));
    this->ui->imageUploadButton->setToolTip("Upload image");
    this->ui->chemistryButton->setIcon(QIcon(QPixmap(":/Images/chemistryIcon.png")));
    this->ui->chemistryButton->setIconSize(QSize(25,25));
    this->ui->chemistryButton->setToolTip("Chemistry Tools");
    this->ui->deleteButton->setIcon(QIcon(QPixmap(":/Images/deleteIcon.png")));
    this->ui->deleteButton->setIconSize(QSize(25,25));
    this->ui->deleteButton->setToolTip("Delete");
    this->ui->clearBoardButton->setIcon(QIcon(QPixmap(":/Images/clearBoard.png")));
    this->ui->clearBoardButton->setIconSize(QSize(35,35));
    this->ui->clearBoardButton->setToolTip("Clear Board");
    this->ui->benzeneButton->setIcon(QIcon(QPixmap(":/Images/benzene.png")));
    this->ui->benzeneButton->setIconSize(QSize(35,35));
    this->ui->benzeneButton->setToolTip("Benzene");
    this->ui->functionGroupGoBackButton->setIcon(QIcon(QPixmap(":/Images/goBackIcon.png")));
    this->ui->functionGroupGoBackButton->setIconSize(QSize(22,22));
    this->ui->functionGroupGoBackButton->setToolTip("Go Back");
    this->ui->gridButton->setIcon(QIcon(QPixmap(":/Images/gridIcon.png")));
    this->ui->gridButton->setIconSize(QSize(22,22));
    this->ui->gridButton->setToolTip("Grid Page");
    this->ui->plainBoardButton->setIcon(QIcon(QPixmap(":/Images/plainIcon.png")));
    this->ui->plainBoardButton->setIconSize(QSize(22,22));
    this->ui->plainBoardButton->setToolTip("Plain Page");
    this->ui->lineBoardButton->setIcon(QIcon(QPixmap(":/Images/linePage.png")));
    this->ui->lineBoardButton->setIconSize(QSize(22,22));
    this->ui->lineBoardButton->setToolTip("Plain Page");

//Lab instrument icon setting (START)
    this->ui->emptyTestTube->setIcon(QIcon(QPixmap(":/Images/emptyTestTube.PNG")));
    this->ui->emptyTestTube->setIconSize(QSize(85,75));
    this->ui->redTestTube->setIcon(QIcon(QPixmap(":/Images/redTestTube.PNG")));
    this->ui->redTestTube->setIconSize(QSize(85,75));
    this->ui->orangeTestTube->setIcon(QIcon(QPixmap(":/Images/orangeTestTube.PNG")));
    this->ui->orangeTestTube->setIconSize(QSize(85,75));
    this->ui->blueTestTube->setIcon(QIcon(QPixmap(":/Images/blueTestTube.PNG")));
    this->ui->blueTestTube->setIconSize(QSize(85,75));
    this->ui->emptyFlask->setIcon(QIcon(QPixmap(":/Images/emptyFlask.PNG")));
    this->ui->emptyFlask->setIconSize(QSize(85,75));
    this->ui->redFlask->setIcon(QIcon(QPixmap(":/Images/redFlask.PNG")));
    this->ui->redFlask->setIconSize(QSize(85,75));
    this->ui->orangeFlask->setIcon(QIcon(QPixmap(":/Images/orangeFlask.PNG")));
    this->ui->orangeFlask->setIconSize(QSize(85,75));
    this->ui->blueFlask->setIcon(QIcon(QPixmap(":/Images/blueFlask.PNG")));
    this->ui->blueFlask->setIconSize(QSize(85,75));
    this->ui->burner->setIcon(QIcon(QPixmap(":/Images/burner.PNG")));
    this->ui->burner->setIconSize(QSize(85,75));
    this->ui->funnel->setIcon(QIcon(QPixmap(":/Images/funnel.PNG")));
    this->ui->funnel->setIconSize(QSize(85,75));
    this->ui->labStand->setIcon(QIcon(QPixmap(":/Images/labStand.PNG")));
    this->ui->labStand->setIconSize(QSize(85,75));
    this->ui->labInstrumentGoBackButton->setIcon(QIcon(QPixmap(":/Images/goBackIcon.png")));
    this->ui->labInstrumentGoBackButton->setIconSize(QSize(22,22));
    this->ui->labInstrumentGoBackButton->setToolTip("Go Back");
    this->ui->emptyBeaker->setIcon(QIcon(QPixmap(":/Images/emptyBeaker.PNG")));
    this->ui->emptyBeaker->setIconSize(QSize(85,75));
    this->ui->blueBeaker->setIcon(QIcon(QPixmap(":/Images/blueBeaker.PNG")));
    this->ui->blueBeaker->setIconSize(QSize(85,75));
    this->ui->measuringCylinder->setIcon(QIcon(QPixmap(":/Images/measuringCylinder.PNG")));
    this->ui->measuringCylinder->setIconSize(QSize(85,75));
    this->ui->dropper->setIcon(QIcon(QPixmap(":/Images/dropper.PNG")));
    this->ui->dropper->setIconSize(QSize(85,75));
//Lab instrument icon setting (START)
}
//setting button icon (END)

//Button clicked related programming(START)
void MainWindow::on_exitButton_clicked()
{
    exit(0);
}
//Button clicked related programming(END)


//color selection button (START)

void MainWindow::on_blackColorButton_clicked()
{
    color="#141414";
    this->ui->selectedColorIndicatorButton->setStyleSheet(QString("background-color: rgb(20, 20, 20);border:1px solid white;"));
}
void MainWindow::on_redColorButton_clicked()
{
    color="#ff0606";
    this->ui->selectedColorIndicatorButton->setStyleSheet(QString("background-color: rgb(255, 6, 6);border:1px solid white;"));
}
void MainWindow::on_blueColorButton_clicked()
{
    color="#3943ff";
    this->ui->selectedColorIndicatorButton->setStyleSheet(QString("background-color:rgb(57, 67, 255);border:1px solid white;"));
}
void MainWindow::on_greenColorButton_clicked()
{
    color="#21c11f";
    this->ui->selectedColorIndicatorButton->setStyleSheet(QString("background-color:rgb(33, 193, 31);border:1px solid white;"));
}
void MainWindow::on_orangeColorButton_clicked()
{
    color="#ff6d0b";
    this->ui->selectedColorIndicatorButton->setStyleSheet(QString("background-color:rgb(255, 109, 11);border:1px solid white;"));
}
void MainWindow::on_pinkColorButton_clicked()
{
    color="#ffb9e7";
    this->ui->selectedColorIndicatorButton->setStyleSheet(QString("background-color:rgb(255, 185, 231);border:1px solid white;"));
}
void MainWindow::on_skyblueColorButton_clicked()
{
    color="#70b5ff";
    this->ui->selectedColorIndicatorButton->setStyleSheet(QString("background-color:rgb(112, 181, 255);border:1px solid white;"));
}
void MainWindow::on_purpleColorButton_clicked()
{
    color="#866fce";
    this->ui->selectedColorIndicatorButton->setStyleSheet(QString("background-color:rgb(134, 111, 206);border:1px solid white;"));
}
void MainWindow::on_brownColorButton_clicked()
{
    color="#753a23";
    this->ui->selectedColorIndicatorButton->setStyleSheet(QString("background-color:rgb(117, 58, 35);border:1px solid white;"));
}

//color selection button (END)

//setting page tab visibility (START)
void MainWindow::setPageTabVisibility()
{
    newPageRadioButtonList.push_back(this->ui->page1);
    newPageRadioButtonList.push_back(this->ui->page2);
    newPageRadioButtonList.push_back(this->ui->page3);
    newPageRadioButtonList.push_back(this->ui->page4);
    newPageRadioButtonList.push_back(this->ui->page5);
    newPageRadioButtonList.push_back(this->ui->page6);
    newPageRadioButtonList.push_back(this->ui->page7);
    newPageRadioButtonList.push_back(this->ui->page8);
    newPageRadioButtonList.push_back(this->ui->page9);
    newPageRadioButtonList.push_back(this->ui->page10);
    this->ui->page1->setVisible(true);
    this->ui->page1->setChecked(true);
    for (int i=1;i<newPageRadioButtonListSize;i++)
    {
     newPageRadioButtonList.at(i)->setVisible(false);
     newPageRadioButtonList.at(i)->setChecked(false);
    }
}
//setting page tab visibility (END)

//tools button (START)

void MainWindow::on_lineButton_clicked()
{
 lineButtonClicked=1;
 freehandButtonClicked=0;
 circleButtonClicked=0;
 rectangleButtonClicked=0;
 selectedButtonClicked=0;
 resizeButtonClicked=0;
 imageUploadButtonClicked=0;
}
void MainWindow::on_freehandButton_clicked()
{
 freehandButtonClicked=1;
 lineButtonClicked=0;
 circleButtonClicked=0;
 rectangleButtonClicked=0;
 selectedButtonClicked=0;
 resizeButtonClicked=0;
 imageUploadButtonClicked=0;
}
void MainWindow::on_circleButton_clicked()
{
    circleButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    selectedButtonClicked=0;
    resizeButtonClicked=0;
    imageUploadButtonClicked=0;
}
void MainWindow::on_rectangleButton_clicked()
{
    rectangleButtonClicked=1;
    circleButtonClicked=0;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    selectedButtonClicked=0;
    resizeButtonClicked=0;
    imageUploadButtonClicked=0;
}
void MainWindow::on_newPageButton_clicked()
{
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    selectedButtonClicked=0;
    resizeButtonClicked=0;
    imageUploadButtonClicked=0;
    numberOfPages++;
    if(numberOfPages>newPageRadioButtonListSize)
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Max limit of pages is reached");
        messageBox.setFixedSize(500,200);
    }
    if(numberOfPages<newPageRadioButtonListSize+1)
    {
    for (int i=0;i<numberOfPages;i++)
    {
     newPageRadioButtonList.at(i)->setVisible(true);
     newPageRadioButtonList.at(i)->setChecked(true);
     currentIndexOfSelectedPage=i;
    }
    }
    this->ui->componentListTable->clear();
    addComponentIntoTable();
update();
}

void MainWindow::on_pageLineMarginSlider_valueChanged(int value)
{
    pageLineMarginSlider=value;
    update();
}

void MainWindow::on_widthSlider_valueChanged(int value)
{
    ComponentWidth=value;
    update();
}

void MainWindow::on_selectButton_clicked()
{
 selectedButtonClicked=1;
 rectangleButtonClicked=0;
 circleButtonClicked=0;
 freehandButtonClicked=0;
 lineButtonClicked=0;
 resizeButtonClicked=0;
 imageUploadButtonClicked=0;

}

void MainWindow::on_groupButton_clicked()
{
 groupButtonClicked=1;
 selectedButtonClicked=1;
 rectangleButtonClicked=0;
 circleButtonClicked=0;
 freehandButtonClicked=0;
 lineButtonClicked=0;
 ctrlKeyPressed=0;
 resizeButtonClicked=0;
 imageUploadButtonClicked=0;
 update();
}

void MainWindow::on_ungroupButton_clicked()
{
    ungroupButtonClicked=1;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    resizeButtonClicked=0;
    imageUploadButtonClicked=0;
    update();
}

void MainWindow::on_resizeButton_clicked()
{
    resizeButtonClicked=1;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    imageUploadButtonClicked=0;
}

void MainWindow::on_imageUploadButton_clicked()
{
    imageUploadButtonClicked=1;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=0;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    QString fileName=QFileDialog::getOpenFileName(this,"Open the file","c://");
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName(fileName.trimmed());
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    imageUploadButtonClicked=0;
}

void MainWindow::on_chemistryButton_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=0;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    this->ui->chemistryFrame->setVisible(true);
    this->ui->chemistryFrame2->setVisible(true);
}

void MainWindow::on_chemistryFrameCrossButton_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=0;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    this->ui->chemistryFrame->setVisible(false);
    this->ui->chemistryFrame2->setVisible(false);
    this->ui->elementDetailFrame->setVisible(false);
}

void MainWindow::on_clearBoardButton_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=0;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.clear();
    tmViewObjectList.at(currentIndexOfSelectedPage)->componentMap.clear();
    //this->ui->elementDetailFrame->setVisible();
    addComponentIntoTable();
    update();
}

void MainWindow::on_elementButton_clicked()
{
    ChemistryFrameComponent chemistryFrameComponent;
    chemistryFrameComponent.populateElementInList();
    QList<QString> elementList=chemistryFrameComponent.searchElementOfPeriodicTable(this->ui->elementNamelineEdit->text().trimmed());
    if(elementList.size()==0)
    {
        this->ui->elementNamelineEdit->setText(this->ui->elementNamelineEdit->text());
        this->ui->elementNamelineEdit->setStyleSheet(QString("color:red;"));
    }
    else
    {
           this->ui->elementDetailFrame->setVisible(true);
           if((elementList.at(2)).toInt()%2==0)
           {
               this->ui->elementDetailFrame->setStyleSheet("background-color: rgb(99, 255, 117);");
           }
           else
           {
               this->ui->elementDetailFrame->setStyleSheet("background-color: rgb(255, 249, 61);");
           }
           this->ui->elementNameLabel->setText(elementList.at(0));
           this->ui->elementSymbolLabel->setText(elementList.at(1));
           this->ui->atomicNumberLabel->setText(elementList.at(2));
           this->ui->atomicMassLabel->setText(elementList.at(3));
    }
}

void MainWindow::on_elementNamelineEdit_textChanged(const QString &elementName)
{
    this->ui->elementNamelineEdit->setStyleSheet(QString("color:black;"));
}

void MainWindow::on_periodicTableButton_clicked()
{
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName(":/Images/periodicTable.png");
    tmPixmapComponent->setX(10+screenWidth-1680+118);
    tmPixmapComponent->setY(120);
    tmPixmapComponent->setW(screenWidth-760);
    tmPixmapComponent->setH((screenHeight-370)+(screenHeight-1026));
    tmPixmapComponent->setComponentName("Periodic Table");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_phScaleButton_clicked()
{
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName(":/Images/pHScale.png");
    tmPixmapComponent->setX(10+screenWidth-1680+118);
    tmPixmapComponent->setY(120);
    tmPixmapComponent->setW(screenWidth-760);
    tmPixmapComponent->setH(screenHeight-1720);
    tmPixmapComponent->setComponentName("phScale");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}


void MainWindow::on_metricButton_clicked()
{
    QString metric1=this->ui->metric1ComboBox->currentText();
    QString metric2=this->ui->metric2ComboBox->currentText();
    double numberToConvert=this->ui->metricLineEdit->text().toDouble();

    if(metric1=="gram"&&metric2=="gram")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert)+" g");
    }

    if(metric1=="gram"&&metric2=="kilogram")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert*0.0001)+" kg");
    }

    if(metric1=="gram"&&metric2=="liter")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert*0.001)+" l");
    }

    if(metric1=="gram"&&metric2=="milliliter")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert)+" ml");
    }

    if(metric1=="gram"&&metric2=="cubic meter")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert*0.000001)+" cubic meter");
    }

    if(metric1=="gram"&&metric2=="degree celcius")
    {
        this->ui->metricResultLabel->setText("Result: Conversion not possible");
    }

    if(metric1=="gram"&&metric2=="kelvin")
    {
        this->ui->metricResultLabel->setText("Result: Conversion not possible");
    }

    if(metric1=="kilogram"&&metric2=="gram")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert*1000)+" g");
    }

    if(metric1=="kilogram"&&metric2=="kilogram")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert)+" kg");
    }

    if(metric1=="kilogram"&&metric2=="liter")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert)+" l");
    }

    if(metric1=="kilogram"&&metric2=="milliliter")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert*1000)+" ml");
    }

    if(metric1=="kilogram"&&metric2=="cubic meter")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert*0.001)+" cubic meter");
    }

    if(metric1=="kilogram"&&metric2=="degree celcius")
    {
        this->ui->metricResultLabel->setText("Result: Conversion not possible");
    }

    if(metric1=="kilogram"&&metric2=="kelvin")
    {
        this->ui->metricResultLabel->setText("Result: Conversion not possible");
    }

    if(metric1=="liter"&&metric2=="gram")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert*1000)+" g");
    }

    if(metric1=="liter"&&metric2=="kilogram")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert)+" kg");
    }

    if(metric1=="liter"&&metric2=="liter")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert)+" l");
    }

    if(metric1=="liter"&&metric2=="milliliter")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert*1000)+" ml");
    }

    if(metric1=="liter"&&metric2=="cubic meter")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert*0.001)+" cubic meter");
    }

    if(metric1=="liter"&&metric2=="degree celcius")
    {
        this->ui->metricResultLabel->setText("Result: Conversion not possible");
    }

    if(metric1=="liter"&&metric2=="kelvin")
    {
        this->ui->metricResultLabel->setText("Result: Conversion not possible");
    }

    if(metric1=="milliliter"&&metric2=="gram")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert)+" g");
    }

    if(metric1=="milliliter"&&metric2=="kilogram")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert*0.001)+" kg");
    }

    if(metric1=="milliliter"&&metric2=="liter")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert*0.001)+" l");
    }

    if(metric1=="milliliter"&&metric2=="milliliter")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert)+" ml");
    }

    if(metric1=="milliliter"&&metric2=="cubic meter")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert*0.000001)+" cubic meter");
    }

    if(metric1=="milliliter"&&metric2=="degree celcius")
    {
        this->ui->metricResultLabel->setText("Result: Conversion not possible");
    }

    if(metric1=="milliliter"&&metric2=="kelvin")
    {
        this->ui->metricResultLabel->setText("Result: Conversion not possible");
    }

    if(metric1=="liter"&&metric2=="gram")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert*1000)+" g");
    }

    if(metric1=="liter"&&metric2=="kilogram")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert)+" kg");
    }

    if(metric1=="liter"&&metric2=="liter")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert)+" l");
    }

    if(metric1=="liter"&&metric2=="milliliter")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert*1000)+" ml");
    }

    if(metric1=="liter"&&metric2=="cubic meter")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert*0.001)+" cubic meter");
    }

    if(metric1=="liter"&&metric2=="degree celcius")
    {
        this->ui->metricResultLabel->setText("Result: Conversion not possible");
    }

    if(metric1=="liter"&&metric2=="kelvin")
    {
        this->ui->metricResultLabel->setText("Result: Conversion not possible");
    }

    if(metric1=="cubic meter"&&metric2=="gram")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert*1000000)+" g");
    }

    if(metric1=="cubic meter"&&metric2=="kilogram")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert*1000)+" kg");
    }

    if(metric1=="cubic meter"&&metric2=="liter")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert*1000)+" l");
    }

    if(metric1=="cubic meter"&&metric2=="milliliter")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert*1000000)+" ml");
    }

    if(metric1=="cubic meter"&&metric2=="cubic meter")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert)+" cubic meter");
    }

    if(metric1=="cubic meter"&&metric2=="degree celcius")
    {
        this->ui->metricResultLabel->setText("Result: Conversion not possible");
    }

    if(metric1=="cubic meter"&&metric2=="kelvin")
    {
        this->ui->metricResultLabel->setText("Result: Conversion not possible");
    }

    if(metric1=="degree celcius"&&metric2=="gram")
    {
        this->ui->metricResultLabel->setText("Result: Conversion not possible");
    }

    if(metric1=="degree celcius"&&metric2=="kilogram")
    {
        this->ui->metricResultLabel->setText("Result: Conversion not possible");
    }

    if(metric1=="degree celcius"&&metric2=="liter")
    {
        this->ui->metricResultLabel->setText("Result: Conversion not possible");
    }

    if(metric1=="degree celcius"&&metric2=="milliliter")
    {
        this->ui->metricResultLabel->setText("Result: Conversion not possible");
    }

    if(metric1=="degree celcius"&&metric2=="cubic meter")
    {
        this->ui->metricResultLabel->setText("Result: Conversion not possible");
    }

    if(metric1=="degree celcius"&&metric2=="degree celcius")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert)+" degree celcius");
    }

    if(metric1=="degree celcius"&&metric2=="kelvin")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert+273.15)+" kelvin");
    }

    //kelvin conversion
    if(metric1=="kelvin"&&metric2=="gram")
    {
        this->ui->metricResultLabel->setText("Result: Conversion not possible");
    }

    if(metric1=="kelvin"&&metric2=="kilogram")
    {
        this->ui->metricResultLabel->setText("Result: Conversion not possible");
    }

    if(metric1=="kelvin"&&metric2=="liter")
    {
        this->ui->metricResultLabel->setText("Result: Conversion not possible");
    }

    if(metric1=="kelvin"&&metric2=="milliliter")
    {
        this->ui->metricResultLabel->setText("Result: Conversion not possible");
    }

    if(metric1=="kelvin"&&metric2=="cubic meter")
    {
        this->ui->metricResultLabel->setText("Result: Conversion not possible");
    }

    if(metric1=="kelvin"&&metric2=="degree celcius")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert-273.15)+" degree celcius");
    }

    if(metric1=="kelvin"&&metric2=="kelvin")
    {
        this->ui->metricResultLabel->setText("Result: "+QString::number(numberToConvert)+" kelvin");
    }
}

void MainWindow::on_benzeneButton_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName(":/Images/benzene.png");
    tmPixmapComponent->setX(10+screenWidth-1680+118);
    tmPixmapComponent->setY(120);
    tmPixmapComponent->setW(100);
    tmPixmapComponent->setH(100);
    tmPixmapComponent->setComponentName("Benzene");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();

}

void MainWindow::on_deleteButton_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    tmViewObjectList.at(currentIndexOfSelectedPage)->deleteComponent();
    addComponentIntoTable();
    update();
}

void MainWindow::on_functionalGroupButton_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    this->ui->functionalGroupFrame->setVisible(true);
    this->ui->functionalGroupFrame2->setVisible(true);
}

void MainWindow::on_functionGroupGoBackButton_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    this->ui->chemistryFrame->setVisible(true);
    this->ui->chemistryFrame2->setVisible(true);
    this->ui->functionalGroupFrame->setVisible(false);
    this->ui->functionalGroupFrame2->setVisible(false);
}

void MainWindow::on_labInstrumentButton_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    this->ui->labInstrumentFrame->setVisible(true);
    this->ui->labInstrumentFrame2->setVisible(true);
}

void MainWindow::on_labInstrumentGoBackButton_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    this->ui->chemistryFrame->setVisible(true);
    this->ui->chemistryFrame2->setVisible(true);
    this->ui->labInstrumentFrame->setVisible(false);
    this->ui->labInstrumentFrame2->setVisible(false);
}

void MainWindow::on_changeComponentNameFrameCrossButton_clicked()
{
    for (int i=0;i<tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.size();i++)
    {
     tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.at(i)->setIsSelected(false);
     this->ui->changeComponentNameFrame->setVisible(false);
     this->ui->componentNameChangelineEdit->setText("");
    }
}

void MainWindow::on_setComponentNameButton_clicked()
{
    for (int i=0;i<tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.size();i++)
    {
     if(tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.at(i)->getIsSelected()==true)
     {
     tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.at(i)->setComponentName(this->ui->componentNameChangelineEdit->text().trimmed());
     this->ui->changeComponentNameFrame->setVisible(false);
     this->ui->componentNameChangelineEdit->setText("");
     addComponentIntoTable();
     }
    }
    selectedButtonClicked=1;
    update();
}

void MainWindow::on_gridButton_clicked()
{
 gridButtonClicked=1;
 lineBoardButtonClicked=0;
 plainBoardButtonClicked=0;
 update();
}

void MainWindow::on_lineBoardButton_clicked()
{
    lineBoardButtonClicked=1;
    gridButtonClicked=0;
    plainBoardButtonClicked=0;
    update();
}

void MainWindow::on_plainBoardButton_clicked()
{
 plainBoardButtonClicked=1;
 lineBoardButtonClicked=0;
 gridButtonClicked=0;
 update();
}
//tools button (END)

//mouse related code (START)

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x=event->pos().x();
    int y=event->pos().y();
    if(x>=screenWidth-1650&&y>=100&&x<=screenWidth-300&&y<=screenHeight-120)
    {

        if(rectangleButtonClicked==1||circleButtonClicked==1||lineButtonClicked==1)
        {
            setCursor(Qt::CrossCursor);
        }
        if(selectedButtonClicked==1) setCursor(Qt::PointingHandCursor);

    this->ui->elementDetailFrame->setVisible(false);
    rectangleButtonRelease=0;
    circleButtonRelease=0;
    lineButtonRelease=0;
    freehandButtonRelease=0;




  oldX=event->pos().x();
  oldY=event->pos().y();
  oldStartX=event->pos().x();
  oldStartY=event->pos().y();
  //drwaing freehand (START)
  if(freehandButtonClicked==1)
  {
      tmFreehandComponent=new TMFreeHandComponent();
      tmFreehandComponent->setX1(oldX);
      tmFreehandComponent->setY1(oldY);
      tmFreehandComponent->setFirst(1);
      tmFreehandComponent->setLast(0);
  }
  }
  else
  {
    setCursor(Qt::ArrowCursor);
  }

}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    int x=event->pos().x();
    int y=event->pos().y();
    if(x>=screenWidth-1650&&y>=100&&x<=screenWidth-300&&y<=screenHeight-120)
    {

        if(rectangleButtonClicked==1||circleButtonClicked==1||lineButtonClicked==1)
        {
            setCursor(Qt::CrossCursor);
        }
        if(selectedButtonClicked==1) setCursor(Qt::PointingHandCursor);
 currentX=event->pos().x();
 currentY=event->pos().y();
 if(resizeButtonClicked==1)
 {
     if(shiftKeyPress==0)
     {
     resizeComponent(currentX-oldStartX,currentY-oldStartY);
     oldStartX=currentX;
     oldStartY=currentY;
     }
     if(shiftKeyPress==1)
     {
         resizeComponent(currentY-oldStartY,currentY-oldStartY);
         oldStartX=currentX;
         oldStartY=currentY;
     }
 }
 if(selectedButtonClicked==1)
 {
     changePosition(currentX-oldStartX,currentY-oldStartY);
     oldStartX=currentX;
     oldStartY=currentY;
 }
 if(freehandButtonClicked==1)
 {
     int i=0;
     for (i=0;i<newPageRadioButtonListSize;i++)
     {
      if(newPageRadioButtonList.at(i)->isChecked()==true)
      {
          currentIndexOfSelectedPage=i;
          break;
      }
     }
     tmFreehandComponent->setX2(currentX);
     tmFreehandComponent->setY2(currentY);
     tmFreehandComponent->setColor(color);
     tmFreehandComponent->setWidth(ComponentWidth);
     tmViewObjectList.at(i)->add(tmFreehandComponent);
     update();
     tmFreehandComponent=new TMFreeHandComponent();
     oldX=event->pos().x();
     oldY=event->pos().y();
     tmFreehandComponent->setX1(oldX);
     tmFreehandComponent->setY1(oldY);
     tmFreehandComponent->setFirst(0);
     tmFreehandComponent->setLast(0);
 }
 if(circleButtonClicked==1) update();
 if(rectangleButtonClicked==1) update();
 if(lineButtonClicked==1) update();
 }
 else
 {
   setCursor(Qt::ArrowCursor);
  }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{


 currentX=event->pos().x();
 currentY=event->pos().y();
 if(lineButtonClicked==1) lineButtonRelease=1;
 if(freehandButtonClicked==1)
 {
     if(tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.size()==0) return;
       if(tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.last()->toString()=="freehand")
       {
               TMFreeHandComponent *freehand=(TMFreeHandComponent *)tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.last();
               freehand->setLast(1);
               tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
               addComponentIntoTable();

       }
 }
 if(circleButtonClicked==1) circleButtonRelease=1;
 if(rectangleButtonClicked==1) rectangleButtonRelease=1;
 int x=event->pos().x();
 int y=event->pos().y();
setCursor(Qt::ArrowCursor);
 update();

}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{

    for (int i=0;i<tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.size();i++) {
       if(tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.at(i)->getIsSelected()==true)
       {
           this->ui->changeComponentNameFrame->setVisible(true);
           tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.at(i)->setIsSelected(true);
           selectedButtonClicked=0;
           update();
       }
    }

}
//mouse related code (END)

//changing component position (START)
void MainWindow::changePosition(int x, int y)
{

    for(int i=0;i<tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.size();i++)
    {
        if(tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.at(i)->getIsSelected()==true)
        {
            tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.at(i)->changePosition(x,y);
            moveable=1;
        }
        update();
    }

}
//changing component position (END)

//intialize TMView Object List (START)
void MainWindow::initializeTMViewObject()
{
    for (int i=0;i<tmViewObjectListSize;i++)
    {
        tmView=new TMView();
        tmViewObjectList.push_back(tmView);
    }
}
//intialize TMView Object List (END)


// page radio button related  code(END)
void MainWindow::on_page1_clicked()
{
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    freehandButtonClicked=0;
    currentIndexOfSelectedPage=0;
    for (int i=0;i<newPageRadioButtonListSize;i++)
    {
     if(i!=0) newPageRadioButtonList.at(i)->setChecked(false);
    }
    addComponentIntoTable();
update();
}

void MainWindow::on_page2_clicked()
{
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    freehandButtonClicked=0;
    currentIndexOfSelectedPage=1;
    for (int i=0;i<newPageRadioButtonListSize;i++)
    {
     if(i!=1) newPageRadioButtonList.at(i)->setChecked(false);
    }
    addComponentIntoTable();
update();
}

void MainWindow::on_page3_clicked()
{
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    freehandButtonClicked=0;
    currentIndexOfSelectedPage=2;
    for (int i=0;i<newPageRadioButtonListSize;i++)
    {
     if(i!=2) newPageRadioButtonList.at(i)->setChecked(false);
    }
    update();
}

void MainWindow::on_page4_clicked()
{
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    freehandButtonClicked=0;
    currentIndexOfSelectedPage=3;
    for (int i=0;i<newPageRadioButtonListSize;i++)
    {
     if(i!=3) newPageRadioButtonList.at(i)->setChecked(false);
    }
    update();
}


void MainWindow::on_page5_clicked()
{
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    freehandButtonClicked=0;
    currentIndexOfSelectedPage=4;
    for (int i=0;i<newPageRadioButtonListSize;i++)
    {
     if(i!=4) newPageRadioButtonList.at(i)->setChecked(false);
    }
    update();
}

void MainWindow::on_page6_clicked()
{
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    freehandButtonClicked=0;
    currentIndexOfSelectedPage=5;
    for (int i=0;i<newPageRadioButtonListSize;i++)
    {
     if(i!=5) newPageRadioButtonList.at(i)->setChecked(false);
    }
    update();
}


void MainWindow::on_page7_clicked()
{
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    freehandButtonClicked=0;
    currentIndexOfSelectedPage=6;
    for (int i=0;i<newPageRadioButtonListSize;i++)
    {
     if(i!=6) newPageRadioButtonList.at(i)->setChecked(false);
    }
    update();
}

void MainWindow::on_page8_clicked()
{
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    freehandButtonClicked=0;
    currentIndexOfSelectedPage=7;
    for (int i=0;i<newPageRadioButtonListSize;i++)
    {
     if(i!=7) newPageRadioButtonList.at(i)->setChecked(false);
    }
    update();
}

void MainWindow::on_page9_clicked()
{
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    freehandButtonClicked=0;
    currentIndexOfSelectedPage=8;
    for (int i=0;i<newPageRadioButtonListSize;i++)
    {
     if(i!=8) newPageRadioButtonList.at(i)->setChecked(false);
    }
    update();
}

void MainWindow::on_page10_clicked()
{
lineButtonClicked=0;
rectangleButtonClicked=0;
circleButtonClicked=0;
freehandButtonClicked=0;
currentIndexOfSelectedPage=9;
    for (int i=0;i<newPageRadioButtonListSize;i++)
    {
     if(i!=9) newPageRadioButtonList.at(i)->setChecked(false);
    }
    update();
}
// page radio button related  code(END)


//designing table(START)
void MainWindow::tableDesign()
{
    this->ui->componentListTable->setSelectionMode(QAbstractItemView::MultiSelection);
    this->ui->componentListTable->verticalHeader()->hide();
    this->ui->componentListTable->setColumnCount(1);
    this->ui->componentListTable->horizontalHeader()->hide();
}

void MainWindow::addComponentIntoTable()
{
    this->ui->componentListTable->clear();
    this->ui->componentListTable->setSelectionMode(QAbstractItemView::MultiSelection);
    this->ui->componentListTable->verticalHeader()->hide();
    this->ui->componentListTable->setColumnCount(1);
    this->ui->componentListTable->horizontalHeader()->hide();
    this->ui->componentListTable->setColumnWidth(0,screenWidth-1789);
QMap<int,DrawableComponent *> *componentMap=tmViewObjectList.at(currentIndexOfSelectedPage)->getComponentMap();
this->ui->componentListTable->setRowCount(componentMap->size());
int j=0;
int i=0;
for (i=0;i<componentMap->size();i++)
{

        QLabel *componentNameLabel=new QLabel(componentMap->value(i)->getComponentName().trimmed());
        componentNameLabel->setAlignment(Qt::AlignCenter);
        if(componentMap->value(i)->getIsSelected()==true)
        {
         this->ui->componentListTable->selectRow(j);
         componentNameLabel->setFont(QFont("Comic Sans MS",12,QFont::Bold));
         componentNameLabel->setStyleSheet("color:red;");
        }
         this->ui->componentListTable->setCellWidget(j,0,componentNameLabel);
        j++;
}

}

//desiogning table(END)


//select component from table (START)
void MainWindow::on_componentListTable_cellClicked(int row, int column)
{
 QMap<int,DrawableComponent *> *componentMap=tmViewObjectList.at(currentIndexOfSelectedPage)->getComponentMap();
 if(componentMap->value(row)->getIsSelected()==true)
 {
    componentMap->value(row)->setIsSelected(false);
    tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.at(componentMap->size()-1-row)->setIsSelected(false);
 }
 else
 {
    componentMap->value(row)->setIsSelected(true);
    tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.at(componentMap->size()-1-row)->setIsSelected(true);
 }

 addComponentIntoTable();
 update();
}
//select component from table (END)

//ctrl key pressed and release related programming (START)
void MainWindow::keyPressEvent(QKeyEvent *event)
{
 if(event->key()==Qt::Key_Control)
 {
     rectangleButtonClicked=0;
     lineButtonClicked=0;
     circleButtonClicked=0;
     freehandButtonClicked=0;
     selectedButtonClicked=1;
     ctrlKeyPressed=1;
 }
 if(event->key()==Qt::Key_Shift)
 {
     shiftKeyPress=1;
     qDebug()<<"press";
 }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Control)
    {
        rectangleButtonClicked=0;
        lineButtonClicked=0;
        circleButtonClicked=0;
        freehandButtonClicked=0;
        selectedButtonClicked=1;
        ctrlKeyPressed=0;
        flag=0;
    }
    if(event->key()==Qt::Key_Shift)
    {
        shiftKeyPress=0;
        qDebug()<<"release";
    }
}


//ctrl key pressed and release related programming (END)

//resizing component (START)
void MainWindow::resizeComponent(int x, int y)
{
    for(int i=0;i<tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.size();i++)
    {
        if(tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.at(i)->getIsSelected()==true)
        {
            tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.at(i)->resizeComponent(x,y);
        }
        update();
    }
}
//resizing component (END)

//functional group button (START)
void MainWindow::on_alkane_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName(":/Images/alkane.png");
    tmPixmapComponent->setX(10+screenWidth-1680+118);
    tmPixmapComponent->setY(120);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Alkane");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();

}

void MainWindow::on_alkene_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/alkene.png");
    tmPixmapComponent->setX(10+screenWidth-1680+118);
    tmPixmapComponent->setY(120);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Alkene");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_alkyne_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/alkyne.png");
    tmPixmapComponent->setX(10+screenWidth-1680+118);
    tmPixmapComponent->setY(120);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Alkyne");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_alcohol_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/alcohol.png");
    tmPixmapComponent->setX(10+screenWidth-1680+118);
    tmPixmapComponent->setY(120);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Alcohol");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}


void MainWindow::on_epoxide_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/expoxide.png");
    tmPixmapComponent->setX(10+screenWidth-1680+118);
    tmPixmapComponent->setY(120);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Expoxide");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_haloalkane_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/haloalkane.png");
    tmPixmapComponent->setX(10+screenWidth-1680+118);
    tmPixmapComponent->setY(120);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Haloalkane");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_ether_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/ether.png");
    tmPixmapComponent->setX(10+screenWidth-1680+118);
    tmPixmapComponent->setY(120);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Ether");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_aldehyde_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/aldehyde.png");
    tmPixmapComponent->setX(10+screenWidth-1680+118);
    tmPixmapComponent->setY(120);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Aldehyde");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}


void MainWindow::on_ketone_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/ketone.png");
    tmPixmapComponent->setX(10+screenWidth-1680+118);
    tmPixmapComponent->setY(120);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Ketone");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_ester_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/ester.png");
    tmPixmapComponent->setX(10+screenWidth-1680+118);
    tmPixmapComponent->setY(120);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Ester");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_amide_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/amide.png");
    tmPixmapComponent->setX(10+screenWidth-1680+118);
    tmPixmapComponent->setY(120);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Amide");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_acylHalide_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/acyl Halide.png");
    tmPixmapComponent->setX(10+screenWidth-1680+118);
    tmPixmapComponent->setY(120);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Acyl Halide");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_amine_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/amine.png");
    tmPixmapComponent->setX(10+screenWidth-1680+118);
    tmPixmapComponent->setY(120);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Amine");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_nitrile_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/nitrile.png");
    tmPixmapComponent->setX(10+screenWidth-1680+118);
    tmPixmapComponent->setY(120);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Nitrile");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_imine_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/imine.png");
    tmPixmapComponent->setX(10+screenWidth-1680+118);
    tmPixmapComponent->setY(120);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Imine");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_isocynate_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/isocynate.png");
    tmPixmapComponent->setX(10+screenWidth-1680+118);
    tmPixmapComponent->setY(120);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Isocynate");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_arene_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/arene.png");
    tmPixmapComponent->setX(10+screenWidth-1680+118);
    tmPixmapComponent->setY(120);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Arene");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_thiol_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/thiol.png");
    tmPixmapComponent->setX(10+screenWidth-1680+118);
    tmPixmapComponent->setY(120);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Thiol");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}
//function groups button(END)

//Lab instrument button (START)

void MainWindow::on_emptyFlask_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/emptyFlask.PNG");
    tmPixmapComponent->setX(150+screenWidth-1680+118);
    tmPixmapComponent->setY(220);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Empty Flask");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_blueFlask_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/blueFlask.PNG");
    tmPixmapComponent->setX(150+screenWidth-1680+118);
    tmPixmapComponent->setY(220);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Blue Flask");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_redFlask_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/redFlask.PNG");
    tmPixmapComponent->setX(150+screenWidth-1680+118);
    tmPixmapComponent->setY(220);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Red Flask");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_orangeFlask_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/orangeFlask.PNG");
    tmPixmapComponent->setX(150+screenWidth-1680+118);
    tmPixmapComponent->setY(220);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Orange Flask");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_emptyTestTube_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/emptyTestTube.PNG");
    tmPixmapComponent->setX(150+screenWidth-1680+118);
    tmPixmapComponent->setY(220);
    tmPixmapComponent->setW(60);
    tmPixmapComponent->setH(250);
    tmPixmapComponent->setComponentName("Empty Test Tube");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}



void MainWindow::on_blueTestTube_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/blueTestTube.PNG");
    tmPixmapComponent->setX(150+screenWidth-1680+118);
    tmPixmapComponent->setY(220);
    tmPixmapComponent->setW(60);
    tmPixmapComponent->setH(250);
    tmPixmapComponent->setComponentName("Blue Test Tube");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_redTestTube_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/redTestTube.PNG");
    tmPixmapComponent->setX(150+screenWidth-1680+118);
    tmPixmapComponent->setY(220);
    tmPixmapComponent->setW(60);
    tmPixmapComponent->setH(250);
    tmPixmapComponent->setComponentName("Red Test Tube");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_orangeTestTube_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/orangeTestTube.PNG");
    tmPixmapComponent->setX(150+screenWidth-1680+118);
    tmPixmapComponent->setY(220);
    tmPixmapComponent->setW(60);
    tmPixmapComponent->setH(250);
    tmPixmapComponent->setComponentName("Orange Test Tube");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_burner_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/burner.PNG");
    tmPixmapComponent->setX(150+screenWidth-1680+118);
    tmPixmapComponent->setY(220);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("burner");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_funnel_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/funnel.PNG");
    tmPixmapComponent->setX(150+screenWidth-1680+118);
    tmPixmapComponent->setY(220);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("funnel");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_labStand_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/labStand.PNG");
    tmPixmapComponent->setX(150+screenWidth-1680+118);
    tmPixmapComponent->setY(220);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Lab Stand");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_emptyBeaker_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/emptyBeaker.PNG");
    tmPixmapComponent->setX(150+screenWidth-1680+118);
    tmPixmapComponent->setY(220);
    tmPixmapComponent->setW(200);
    tmPixmapComponent->setH(200);
    tmPixmapComponent->setComponentName("Empty Beaker");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}


void MainWindow::on_blueBeaker_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/blueBeaker.PNG");
    tmPixmapComponent->setX(150+screenWidth-1680+118);
    tmPixmapComponent->setY(220);
    tmPixmapComponent->setW(200);
    tmPixmapComponent->setH(200);
    tmPixmapComponent->setComponentName("Blue Beaker");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_measuringCylinder_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/measuringCylinder.PNG");
    tmPixmapComponent->setX(150+screenWidth-1680+118);
    tmPixmapComponent->setY(220);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Measuring Cylinder");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

void MainWindow::on_dropper_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    TMPixmapComponent *tmPixmapComponent=new TMPixmapComponent();
    tmPixmapComponent->setFileName("/Images/dropper.PNG");
    tmPixmapComponent->setX(150+screenWidth-1680+118);
    tmPixmapComponent->setY(220);
    tmPixmapComponent->setW(150);
    tmPixmapComponent->setH(150);
    tmPixmapComponent->setComponentName("Dropper");
    tmViewObjectList.at(currentIndexOfSelectedPage)->add(tmPixmapComponent);
    tmViewObjectList.at(currentIndexOfSelectedPage)->populateMap();
    addComponentIntoTable();
    update();
}

//undo and redo button (START)
void MainWindow::on_undoButton_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    QList<DrawableComponent *> *undoList=tmViewObjectList.at(currentIndexOfSelectedPage)->getUndoList();
    tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.clear();
    for (int i=0;i<undoList->size();i++)
    {
        tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.push_back(undoList->at(i));
    }
    tmViewObjectList.at(currentIndexOfSelectedPage)->undo();
update();
}

void MainWindow::on_redoButton_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=1;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    QList<DrawableComponent *> *redoList=tmViewObjectList.at(currentIndexOfSelectedPage)->getRedoList();
    tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.clear();
    for (int i=0;i<redoList->size();i++)
    {
        tmViewObjectList.at(currentIndexOfSelectedPage)->viewList.push_back(redoList->at(i));
    }
    tmViewObjectList.at(currentIndexOfSelectedPage)->redo();
update();
}
//undo and redo button (END)

//save button (START)


void MainWindow::on_saveButton_clicked()
{
    imageUploadButtonClicked=0;
    resizeButtonClicked=0;
    ungroupButtonClicked=0;
    groupButtonClicked=0;
    selectedButtonClicked=0;
    freehandButtonClicked=0;
    lineButtonClicked=0;
    rectangleButtonClicked=0;
    circleButtonClicked=0;
    QString jsonFilter="CHEMBOARD(*.chbd)";
       QString fileName=QFileDialog::getSaveFileName(this,"Open the file","/","CHEMBOARD(*.chbd)",&jsonFilter,QFileDialog::DontUseNativeDialog);
       QFile output(fileName);
       if(!output.open(QIODevice::WriteOnly|QIODevice::Text))
       {
           QMessageBox::warning(this,"Warning","Cannot open File"+output.errorString());
       }
       QJsonDocument document;
       DrawableComponent *d;
       QByteArray data_json;
       QJsonArray listArray;
       qDebug()<<numberOfPages;
       for (int i=0;i<numberOfPages;i++)
       {
        QJsonObject obj1;
        QList<DrawableComponent *> *list=tmViewObjectList.at(i)->getViewList();
       for(int j=0;j<list->size();j++)
       {
           QJsonObject obj;
           d=list->at(j);
           if(d->toString().compare("rectangle")==0)
           {
              TMRectangleComponent *t=(TMRectangleComponent *)d;
              obj.insert("x",QJsonValue::fromVariant(t->getX()));
              obj.insert("y",QJsonValue::fromVariant(t->getY()));
              obj.insert("width",QJsonValue::fromVariant(t->getW()));
              obj.insert("Height",QJsonValue::fromVariant(t->getH()));
              obj.insert("toString",QJsonValue::fromVariant(t->toString()));
              obj.insert("componentName",QJsonValue::fromVariant(t->getComponentName()));
              obj.insert("componentWidth",QJsonValue::fromVariant(t->getWidth()));
              qDebug()<<t->getWidth();
              obj.insert("color",QJsonValue::fromVariant(t->getColor()));
              listArray.append(obj);
           }
           if(d->toString().compare("circle")==0)
           {
               TMCircleComponent *c=(TMCircleComponent *)d;
               obj.insert("x",QJsonValue::fromVariant(c->getX()));
               obj.insert("y",QJsonValue::fromVariant(c->getY()));
               obj.insert("width",QJsonValue::fromVariant(c->getW()));
               obj.insert("height",QJsonValue::fromVariant(c->getH()));
               obj.insert("toString",QJsonValue::fromVariant(c->toString()));
               obj.insert("componentName",QJsonValue::fromVariant(c->getComponentName()));
               obj.insert("componentWidth",QJsonValue::fromVariant(c->getWidth()));
               obj.insert("color",QJsonValue::fromVariant(c->getColor()));
               listArray.append(obj);
           }
           if(d->toString().compare("line")==0)
           {
               TMLineComponent *l=(TMLineComponent *)d;
               obj.insert("x1",QJsonValue::fromVariant(l->getX1()));
               obj.insert("y1",QJsonValue::fromVariant(l->getY1()));
               obj.insert("x2",QJsonValue::fromVariant(l->getX2()));
               obj.insert("y2",QJsonValue::fromVariant(l->getY2()));
               obj.insert("toString",QJsonValue::fromVariant(l->toString()));
               obj.insert("componentName",QJsonValue::fromVariant(l->getComponentName()));
               obj.insert("componentWidth",QJsonValue::fromVariant(l->getWidth()));
               obj.insert("color",QJsonValue::fromVariant(l->getColor()));
               listArray.append(obj);
           }

           if(d->toString().compare("pixmap")==0)
           {
               TMPixmapComponent *p=(TMPixmapComponent *)d;
               obj.insert("x",QJsonValue::fromVariant(p->getX()));
               obj.insert("y",QJsonValue::fromVariant(p->getY()));
               obj.insert("width",QJsonValue::fromVariant(p->getW()));
               obj.insert("height",QJsonValue::fromVariant(p->getH()));
               obj.insert("toString",QJsonValue::fromVariant(p->toString()));
               obj.insert("componentName",QJsonValue::fromVariant(p->getComponentName()));
               listArray.append(obj);
           }

           if(d->toString().compare("freehand")==0)
           {
               TMFreeHandComponent *f=(TMFreeHandComponent *)d;
               obj.insert("x1",QJsonValue::fromVariant(f->getX1()));
               obj.insert("y1",QJsonValue::fromVariant(f->getY1()));
               obj.insert("x2",QJsonValue::fromVariant(f->getX2()));
               obj.insert("y2",QJsonValue::fromVariant(f->getY2()));
               obj.insert("getLast",QJsonValue::fromVariant(f->getLast()));
               obj.insert("getFirst",QJsonValue::fromVariant(f->getFirst()));
               obj.insert("toString",QJsonValue::fromVariant(f->toString()));
               obj.insert("componentName",QJsonValue::fromVariant(f->getComponentName()));
               obj.insert("componentWidth",QJsonValue::fromVariant(f->getWidth()));
               obj.insert("color",QJsonValue::fromVariant(f->getColor()));
               listArray.append(obj);
           }

       }
        obj1.insert("newPage",QJsonValue::fromVariant("newPage"));
        listArray.append(obj1);
       }
       document.setArray(listArray);
       data_json=document.toJson();
       output.write(data_json);
       output.close();
}

void MainWindow::on_openFileButton_clicked()
{
    QString jsonFilter="CHEMBOARD(*.chbd)";
        QString filename=QFileDialog::getOpenFileName(this,"Open the File","/",jsonFilter,&jsonFilter,QFileDialog::DontUseNativeDialog);
        QFile input(filename);
        if(!input.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QMessageBox::warning(this,"warning","Cannot open file"+input.errorString());
        }

        QByteArray data_json=input.readAll();
        input.close();
        QJsonDocument document=document.fromJson(data_json);
        QJsonArray jsonArray=document.array();
        int i=0;
        for(QJsonValue value:jsonArray)
        {
            QJsonObject obj(value.toObject());
            if(obj.value(QString("toString")).toString().compare("rectangle")==0)
           {
                TMRectangleComponent *t=new TMRectangleComponent;
                t->setX(obj["x"].toInt());
                t->setY(obj["y"].toInt());
                t->setW(obj["width"].toInt());
                t->setH(obj["Height"].toInt());
                t->setColor(obj["color"].toString());
                t->setComponentName(obj["componentName"].toString());
                t->setWidth(obj["componentWidth"].toInt());
                tmViewObjectList.at(i)->add(t);
            }
            if(obj.value(QString("toString")).toString().compare("circle")==0)
           {
                TMCircleComponent *t=new TMCircleComponent;
                t->setX(obj["x"].toInt());
                t->setY(obj["y"].toInt());
                t->setW(obj["width"].toInt());
                t->setH(obj["height"].toInt());
                obj.insert("toString",QJsonValue::fromVariant(t->toString()));
                t->setColor(obj["color"].toString());
                t->setComponentName(obj["componentName"].toString());
                t->setWidth(obj["componentWidth"].toInt());
                tmViewObjectList.at(i)->add(t);
            }
            if(obj.value(QString("toString")).toString().compare("freehand")==0)
           {
                TMFreeHandComponent *t=new TMFreeHandComponent;
                t->setX1(obj["x1"].toInt());
                t->setY1(obj["y1"].toInt());
                t->setX2(obj["x2"].toInt());
                t->setY2(obj["y2"].toInt());
                obj.insert("toString",QJsonValue::fromVariant(t->toString()));
                t->setColor(obj["color"].toString());
                t->setComponentName(obj["componentName"].toString());
                t->setWidth(obj["componentWidth"].toInt());
                t->setLast(obj["getLast"].toInt());
                t->setFirst(obj["getFirst"].toInt());
                tmViewObjectList.at(i)->add(t);
            }
            if(obj.value(QString("toString")).toString().compare("line")==0)
           {
                TMLineComponent *t=new TMLineComponent;
                t->setX1(obj["x1"].toInt());
                t->setY1(obj["y1"].toInt());
                t->setX2(obj["x2"].toInt());
                t->setY2(obj["y2"].toInt());
                obj.insert("toString",QJsonValue::fromVariant(t->toString()));
                t->setColor(obj["color"].toString());
                t->setComponentName(obj["componentName"].toString());
                t->setWidth(obj["componentWidth"].toInt());
                qDebug()<<obj["componentWidth"].toInt();
                tmViewObjectList.at(i)->add(t);
            }
            if(obj.value(QString("toString")).toString().compare("pixmap")==0)
           {
                TMPixmapComponent *t=new TMPixmapComponent;
                t->setX(obj["x"].toInt());
                t->setY(obj["y"].toInt());
                t->setW(obj["width"].toInt());
                t->setH(obj["Height"].toInt());
                obj.insert("toString",QJsonValue::fromVariant(t->toString()));
                t->setComponentName(obj["componentName"].toString());
                tmViewObjectList.at(i)->add(t);

            }
            if(obj.value(QString("newPage")).toString().compare("newPage")==0)
            {
                on_newPageButton_clicked();
                i++;
                qDebug()<<"gaya";
            }
        }
        update();
}







