#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  _createActions();
  _createMenus();
  _createToolbars();
  _connectActions();

  QGraphicsView *view = new QGraphicsView();
  _area= new SceneArea (0, 0, 600, 800, this);
  _area->setCurrentTool(TOOLS_ID_FREEHAND);
  _area->setCurrentStyle(STYLE_MENU_ID_PEN);
  QGraphicsTextItem * text = _area->addText("Tu peux me deplacer !");
  text->setPos(100, 100);
  text->setVisible(true);
  view->setScene(_area);
  setCentralWidget(view);
  statusBar()->showMessage(tr("Ready"));

  _signalMapperTool = new QSignalMapper(this);
  _signalMapperTool->setMapping(_freehandAct,  TOOLS_ID_FREEHAND);
  _signalMapperTool->setMapping(_lineAct,      TOOLS_ID_LINE);
  _signalMapperTool->setMapping(_rectangleAct, TOOLS_ID_RECTANGLE);
  _signalMapperTool->setMapping(_ellipseAct,   TOOLS_ID_CIRCLE);
  _signalMapperTool->setMapping(_polygonAct,   TOOLS_ID_POLYGON); 
  _signalMapperTool->setMapping(_textAct,      TOOLS_ID_TEXT);

  _signalMapperStyle = new QSignalMapper(this);
  _signalMapperStyle->setMapping(_penAction,   STYLE_MENU_ID_PEN);
  _signalMapperStyle->setMapping(_brushAction, STYLE_MENU_ID_BRUSH);

  _connectSignals();
}

void MainWindow::_createMenus(void) {
  QMenuBar* menubar = menuBar();
  // File menu
  _fileMenu  = menubar->addMenu(tr("&File"));
  // Tools menu
  _toolsMenu = menubar->addMenu(tr("&Tools"));
  // Style menu
  _styleMenu = menubar->addMenu(tr("&Style"));
  _penMenu   = _styleMenu->addMenu(tr("Pen"));
  _brushMenu = _styleMenu->addMenu(tr("Brush"));
  // Help menu
  _helpMenu  = menubar->addMenu(tr("&Help"));
}

void MainWindow::_createToolbars(void) {
  _toolBar = addToolBar(tr("File"));
}

// ---------------- ACTIONS ----------------
void MainWindow::_createActions(void) {
  // File actions
  this->_createFileActions();
  // Tools actions
  this->_createToolsActions();
  // Style actions
  this->_createStyleActions();
  // Help actions
  this->_createHelpActions();
}

void MainWindow::_createFileActions(void) {
  _newAction = new QAction(QIcon(":/Images/new.png"), tr("&New..."), this);
  _newAction->setShortcut(tr("Ctrl+N"));
  _newAction->setToolTip(tr("New Tooltip"));
  _newAction->setStatusTip(tr("New Status"));
  _newAction->setData(QVariant("New data to process"));

  _openAction = new QAction(QIcon(":/Images/open.png"), tr("&Open..."), this);
  _openAction->setShortcut(tr("Ctrl+O"));

  _saveAction = new QAction(QIcon(":/Images/save.png"), tr("&Save..."), this);
  _saveAction->setShortcut(tr("Ctrl+S"));

  _saveAsAction = new QAction(tr("&Save As..."), this);
  _saveAsAction->setShortcut(tr("Ctrl+Shift+S"));

  _exitAction = new QAction(tr("&Exit"), this);
  _exitAction->setShortcut(tr("Ctrl+E"));
}

void MainWindow::_createToolsActions(void) {
  _toolsQag = new QActionGroup(this);

  // Free hand
  _freehandAct = new QAction(tr("&Freehand"),  this);
  _freehandAct->setCheckable(true);
  _freehandAct->setChecked(true);
  // Line
  _lineAct = new QAction(tr("&Line"), this);
  _lineAct->setCheckable(true);
  // Rectangle
  _rectangleAct = new QAction(tr("&Rectangle"), this);
  _rectangleAct->setCheckable(true);
  // Ellipse
  _ellipseAct = new QAction(tr("&Ellipse"), this);
  _ellipseAct->setCheckable(true);
  // Polygon
  _polygonAct = new QAction(tr("&Polygon"), this);
  _polygonAct->setCheckable(true);
  // Text
  _textAct = new QAction(tr("&Text"), this);
  _textAct->setCheckable(true);
}

void MainWindow::_createStyleActions(void) {
  _styleQag = new QActionGroup(this);
  // Pen menu
  _penAction      = new QAction(tr("Pen"), this);
  _penAction->setCheckable(true);
  _penAction->setChecked(true);
  _penColorAction = new QAction(tr("Color"), this);
  _penLineAction  = new QAction(tr("Line"), this);
  _penWidthAction = new QAction(tr("Width"), this);
  // Brush menu
  _brushAction      = new QAction(tr("Brush"), this);
  _brushAction->setCheckable(true);
  _brushColorAction = new QAction(tr("Color"), this);
  _brushFillAction  = new QAction(tr("Fill"), this);
}

void MainWindow::_createHelpActions(void) {
  // About us
  _aboutAction = new QAction(tr("About"), this);
  _aboutAction->setShortcut(tr("Ctrl+A"));
  _aboutAction->setStatusTip(tr("It' a beautiful work"));
  // About Qt
  _aboutQtAction = new QAction(tr("About Qt"), this);
  _aboutQtAction->setShortcut(tr("Ctrl+Q"));
  _aboutQtAction->setStatusTip(tr("Thank's a lot, you're so cute !"));
}

void MainWindow::_connectActions(void) {
  // File Menu
  _fileMenu->addAction(_newAction);
  _fileMenu->addAction(_openAction);
  _fileMenu->addAction(_saveAction);
  _fileMenu->addAction(_saveAsAction);
  _fileMenu->addAction(_exitAction);

  // Tools menu
  _toolsMenu->addAction(_freehandAct);
  _toolsMenu->addAction(_lineAct);
  _toolsMenu->addAction(_rectangleAct);
  _toolsMenu->addAction(_ellipseAct);
  _toolsMenu->addAction(_polygonAct);
  _toolsMenu->addAction(_textAct);

  _toolsQag->addAction(_freehandAct);
  _toolsQag->addAction(_lineAct);
  _toolsQag->addAction(_rectangleAct);
  _toolsQag->addAction(_ellipseAct);
  _toolsQag->addAction(_polygonAct);
  _toolsQag->addAction(_textAct);

  // Tools actions
  // Pen menu
  _penMenu->addAction(_penAction);
  _penMenu->addAction(_penColorAction);
  _penMenu->addAction(_penLineAction);
  _penMenu->addAction(_penWidthAction);
  // Brush menu
  _brushMenu->addAction(_brushAction);
  _brushMenu->addAction(_brushColorAction);
  _brushMenu->addAction(_brushFillAction);

  _styleQag->addAction(_penAction);
  _styleQag->addAction(_brushAction);

  // Help Menu
  _helpMenu->addAction(_aboutAction);
  _helpMenu->addAction(_aboutQtAction);

  _toolBar->addAction(_newAction);
  _toolBar->addAction(_openAction);
  _toolBar->addAction(_saveAction);
}

void MainWindow::_connectSignals(void) {
  // File actions
  connect(_newAction, SIGNAL(triggered()), this, SLOT(_newFile()));
  connect(_openAction, SIGNAL(triggered()), this, SLOT(_open()));
  connect(_saveAction, SIGNAL(triggered()), this, SLOT(_save()));
  connect(_saveAsAction, SIGNAL(triggered()), this, SLOT(_saveAs()));
  connect(_exitAction, SIGNAL(triggered()), this, SLOT(_exit()));

  // Tools actions
  connect(_freehandAct, SIGNAL(activated()), _signalMapperTool, SLOT(map()));
  connect(_lineAct, SIGNAL(activated()), _signalMapperTool, SLOT(map()));
  connect(_rectangleAct, SIGNAL(activated()), _signalMapperTool, SLOT(map()));
  connect(_ellipseAct, SIGNAL(activated()), _signalMapperTool, SLOT(map()));
  connect(_polygonAct, SIGNAL(activated()), _signalMapperTool, SLOT(map()));
  connect(_textAct, SIGNAL(activated()), _signalMapperTool, SLOT(map()));

  // Style actions
  connect(_penColorAction, SIGNAL(triggered()), this, SLOT(_penColor()));
  connect(_penLineAction, SIGNAL(triggered()), this, SLOT(_penLine()));
  connect(_penWidthAction, SIGNAL(triggered()), this, SLOT(_penWidth()));
  connect(_brushColorAction, SIGNAL(triggered()), this, SLOT(_brushColor()));
  connect(_brushFillAction, SIGNAL(triggered()), this, SLOT(_brushFill()));

  connect(_penAction, SIGNAL(activated()), _signalMapperStyle, SLOT(map()));
  connect(_brushAction, SIGNAL(activated()), _signalMapperStyle, SLOT(map()));

  // Help actions
  connect(_aboutAction, SIGNAL(triggered()), this, SLOT(_about()));
  connect(_aboutQtAction, SIGNAL(triggered()), this, SLOT(_aboutQt()));

  connect(_signalMapperTool, SIGNAL(mapped(int)), this, SIGNAL(toolMapped(int)));
  connect(this, SIGNAL(toolMapped(int)), _area, SLOT(setCurrentTool(int)));

  connect(_signalMapperStyle, SIGNAL(mapped(int)), this, SIGNAL(styleMapped(int)));
  connect(this, SIGNAL(styleMapped(int)), _area, SLOT(setCurrentStyle(int)));
}

// FILE METHODS
void MainWindow::_newFile(void) {
  qDebug() << "MainWindow::newFile(void)";
  qDebug() << "Date : " << QDate::currentDate();
  QString str = _newAction->data().toString();
  qDebug() << str ;
  statusBar()->showMessage(str);

  for (int i =0; i< _area->items().size();i++) { 
    qDebug() <<  "scene.items() :" <<_area->items().value(i)->type();
    qDebug() << _area->items().value(i)->x();
    qDebug() << _area->items().value(i)->pos();
    qDebug() << _area->items().value(i)->scenePos();
//     qDebug() << _area->mapToScene(_area->items().value(i)->pos());
  }
}

void MainWindow::_open() {
  qDebug() << "MainWindow::_open(void)";
}

void MainWindow::_save() {
  qDebug() << "MainWindow::_save(void)";
}

void MainWindow::_saveAs() {
  qDebug() << "MainWindow::_saveAs(void)";
}

void MainWindow::_exit(void) {
  qDebug() << "MainWindow::_exit(void)";
  exit(0);
}

// STYLE METHODS
void MainWindow::_penColor() {
  qDebug() << "MainWindow::_penColor(void)";
}

void MainWindow::_penLine() {
  qDebug() << "MainWindow::_penLine(void)";
}

void MainWindow::_penWidth() {
  qDebug() << "MainWindow::_penWidth(void)";
}

void MainWindow::_brushColor() {
  qDebug() << "MainWindow::_brushColor(void)";
}

void MainWindow::_brushFill() {
  qDebug() << "MainWindow::_brushFill(void)";
}

// HELP METHODS
void MainWindow::_about() {
  qDebug() << "MainWindow::_aboutUs()" ;
  QMessageBox::information(this,
                           "Editeur graphique Version 0.1",
                           "ENIB module CAI, Copyright Automne 2018 : \n Lamsiah - Landuré",
                           "Go back to work !");
}

void MainWindow::_aboutQt() {
  qDebug() << "MainWindow::_aboutQt()" ;
  QMessageBox::aboutQt(this, "A propos de Qt");
}

