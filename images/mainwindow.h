#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "tmcirclecomponent.h"
#include "tmfreehandcomponent.h"
#include "tmlinecomponent.h"
#include "tmview.h"

#include <QMainWindow>
#include <QPainter>
#include <QRadioButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public:
    int screenHeight;
    int screenWidth;
    QString color="black";
    TMView *tmView;
    int oldX;
    int oldY;
    int currentX;
    int currentY;
    //QPainter painter;
    int lineButtonClicked=0;
    int lineButtonRelease=0;
    int freehandButtonClicked=0;
    int freehandButtonRelease=0;
    int circleButtonClicked=0;
    int circleButtonRelease=0;
    int rectangleButtonClicked=0;
    int rectangleButtonRelease=0;
    int imageUploadButtonClicked=0;
    int selectedButtonClicked=0;
    int numberOfPages=1;
    int tmViewObjectListSize=10;
    int newPageRadioButtonListSize=10;
    int currentIndexOfSelectedPage=0;
    int moveable=0;
    int ctrlKeyPressed=-1;
    int groupButtonClicked=0;
    int ungroupButtonClicked=0;
    int resizeButtonClicked=0;
    int oldStartX=0;
    int oldStartY=0;
    int shiftKeyPress=0;
    int periodicTableButtonClicked=0;
    int phScaleButtonClicked=0;
    int ComponentWidth=2;
    int gridButtonClicked=0;
    int lineBoardButtonClicked=0;
    int plainBoardButtonClicked=0;
    int pageLineMarginSlider=20;
    TMFreeHandComponent *tmFreehandComponent=NULL;
    TMCircleComponent *tmCircleComponent;
    QList<QRadioButton *> newPageRadioButtonList;
    QList<TMView *> tmViewObjectList;
public:
    void setButtonIcon();
    void paintEvent(QPaintEvent *event);
    void setPageTabVisibility();
    void initializeTMViewObject();
    void tableDesign();
    void addComponentIntoTable();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void changePosition(int x,int y);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void moveGrouping(int x, int y);
    void resizeComponent(int x,int y);
    void mouseDoubleClickEvent(QMouseEvent *event);
private slots:
    void on_exitButton_clicked();

    void on_blackColorButton_clicked();

    void on_redColorButton_clicked();

    void on_blueColorButton_clicked();

    void on_greenColorButton_clicked();

    void on_orangeColorButton_clicked();

    void on_pinkColorButton_clicked();

    void on_skyblueColorButton_clicked();

    void on_purpleColorButton_clicked();

    void on_brownColorButton_clicked();

    void on_lineButton_clicked();

    void on_freehandButton_clicked();

    void on_circleButton_clicked();

    void on_rectangleButton_clicked();

    void on_newPageButton_clicked();

    void on_page1_clicked();

    void on_page2_clicked();

    void on_page3_clicked();

    void on_page4_clicked();

    void on_page5_clicked();

    void on_page6_clicked();

    void on_page7_clicked();

    void on_page8_clicked();

    void on_page9_clicked();

    void on_page10_clicked();

    void on_selectButton_clicked();

    void on_componentListTable_cellClicked(int row, int column);

    void on_groupButton_clicked();

    void on_ungroupButton_clicked();

    void on_resizeButton_clicked();

    void on_imageUploadButton_clicked();

    void on_chemistryButton_clicked();

    void on_chemistryFrameCrossButton_clicked();

    void on_clearBoardButton_clicked();

    void on_elementButton_clicked();

    void on_elementNamelineEdit_textChanged(const QString &arg1);

    void on_periodicTableButton_clicked();

    void on_phScaleButton_clicked();

    void on_metricButton_clicked();

    void on_benzeneButton_clicked();

    void on_deleteButton_clicked();

    void on_functionalGroupButton_clicked();

    void on_alkane_clicked();

    void on_alkene_clicked();

    void on_alkyne_clicked();

    void on_alcohol_clicked();

    void on_epoxide_clicked();

    void on_haloalkane_clicked();

    void on_ether_clicked();

    void on_aldehyde_clicked();

    void on_ketone_clicked();

    void on_ester_clicked();

    void on_amide_clicked();

    void on_acylHalide_clicked();

    void on_amine_clicked();

    void on_nitrile_clicked();

    void on_imine_clicked();

    void on_isocynate_clicked();

    void on_arene_clicked();

    void on_thiol_clicked();

    void on_functionGroupGoBackButton_clicked();

    void on_labInstrumentButton_clicked();

    void on_labInstrumentGoBackButton_clicked();


    void on_emptyFlask_clicked();

    void on_blueFlask_clicked();

    void on_redFlask_clicked();

    void on_orangeFlask_clicked();

    void on_emptyTestTube_clicked();

    void on_blueTestTube_clicked();

    void on_redTestTube_clicked();

    void on_orangeTestTube_clicked();

    void on_burner_clicked();

    void on_funnel_clicked();

    void on_labStand_clicked();

    void on_emptyBeaker_clicked();

    void on_blueBeaker_clicked();

    void on_measuringCylinder_clicked();

    void on_dropper_clicked();

    void on_undoButton_clicked();

    void on_redoButton_clicked();

    void on_saveButton_clicked();

    void on_openFileButton_clicked();

    void on_changeComponentNameFrameCrossButton_clicked();

    void on_setComponentNameButton_clicked();

    void on_gridButton_clicked();

    void on_lineBoardButton_clicked();

    void on_plainBoardButton_clicked();

    void on_pageLineMarginSlider_valueChanged(int value);

    void on_widthSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
