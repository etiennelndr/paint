#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QWidget>
#include <QMainWindow>
#include <QMenuBar>
#include <QFileDialog>
#include <QXmlStreamReader>
#include <QStatusBar>
#include <QAction>
#include <QActionGroup>
#include <QToolBar>
#include <QMessageBox>
#include <QDate>
#include <QSignalMapper>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "enums.h"
#include "scene_area.h"

class MainWindow : public QMainWindow {
Q_OBJECT
  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
  private:
    SceneArea* _area;
    // Menus
    void _createMenus(void);
    // Toolbars
    void _createToolbars(void);
    // Actions
    void _createActions(void);
    void _createFileActions(void);
    void _createToolsActions(void);
    void _createStyleActions(void);
    void _createHelpActions(void);
    void _connectActions(void);
    // Signals
    void _connectSignals(void);

    QMenu *_fileMenu, *_toolsMenu, *_styleMenu, *_helpMenu;
    QToolBar *_toolBar;

    // File menu actions
    QAction *_newAction, *_openAction, *_saveAction, *_saveAsAction, *_exitAction;
    // Tools menu actions
    QAction *_freehandAct, *_lineAct, *_rectangleAct, *_ellipseAct, *_polygonAct, *_textAct;
    // Style menu actions and submenus
    QMenu *_penMenu;
    QAction *_penAction, *_penColorAction, *_penLineAction, *_penWidthAction;
    QMenu *_brushMenu;
    QAction *_brushAction, *_brushColorAction, *_brushFillAction;
    QAction *_fontAction;

    QMenu *_colorPMenu, *_colorBMenu, *_lineMenu, *_widthMenu, *_fontMenu, *_popUpMenu, *_fillbrushMenu;

    QAction *_SolidLine, *_DashLine, *_DotLine;
    QAction *_ThickWidth, *_NormalWidth, *_LargeWidth;
    QAction *_penColorBlue, *_penColorRed, *_penColorGreen, *_penColorBlack, *_penColorYellow;
    QAction *_brushColorBlue, *_brushColorRed, *_brushColorGreen, *_brushColorBlack, *_brushColorYellow;
    QAction *_fillbrush1, *_fillbrush2, *_fillbrush3, *_fillbrush4;

    // Help menu actions
    QAction *_aboutAction, *_aboutQtAction;

    QActionGroup *_toolsQag, *_toolsLine, *_toolsWidth,*_penColor,*_brushColor ,*_fillbrushgroup;
    QSignalMapper *_signalMapperTool;
    QSignalMapper *_lineMapper,*_widthMapper,*_colorPMapper,*_colorBMapper,*_fillbrushMapper;
  private slots :
    // File menu
    void _newFile();
    void _open();
    void _save();
    void _saveAs();
    void _exit();
    // Help menu
    void _about();
    void _aboutQt();
  signals:
    void toolMapped(int digit);
    void toolPenMapped(int digit);
    void toolWidthMapped(int digit);
    void toolColorPMapped(int digit);
    void toolColorBMapped(int digit);
    void stylefillbrushMapped(int digit);
};


#endif

