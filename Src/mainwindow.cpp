#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  _createActions();
  _createMenus();
  _createToolbars();
  _connectActions();

  QGraphicsView *view = new QGraphicsView();
  _area = new SceneArea (0, 0, 600, 800, this);
  _area->setCurrentTool(TOOLS_ID_FREEHAND);

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

  _lineMapper = new QSignalMapper(this);
  _lineMapper->setMapping(_SolidLine, SOLIDLINE_ID);
  _lineMapper->setMapping(_DashLine,  DASHLINE_ID);
  _lineMapper->setMapping(_DotLine,   DOTLINE_ID);

  _widthMapper = new QSignalMapper(this);
  _widthMapper->setMapping(_ThickWidth,   THICKWIDTH_ID);
  _widthMapper->setMapping(_NormalWidth,  NORMALWIDTH_ID);
  _widthMapper->setMapping(_LargeWidth,   LARGEWIDTH_ID);

  _colorPMapper = new QSignalMapper(this);
  _colorPMapper->setMapping(_penColorBlue,    PENBLUE_ID);
  _colorPMapper->setMapping(_penColorRed,     PENRED_ID);
  _colorPMapper->setMapping(_penColorGreen,   PENGREEN_ID);
  _colorPMapper->setMapping(_penColorBlack,   PENBLACK_ID);
  _colorPMapper->setMapping(_penColorYellow,  PENYELLOW_ID);
  
  _colorBMapper = new QSignalMapper(this);
  _colorBMapper->setMapping(_brushColorBlue,    BRUSHBLUE_ID);
  _colorBMapper->setMapping(_brushColorRed,     BRUSHRED_ID);
  _colorBMapper->setMapping(_brushColorGreen,   BRUSHGREEN_ID);
  _colorBMapper->setMapping(_brushColorBlack,   BRUSHBLACK_ID);
  _colorBMapper->setMapping(_brushColorYellow,  BRUSHYELLOW_ID);

  _fillbrushMapper = new QSignalMapper(this);
  _fillbrushMapper->setMapping(_fillbrush1, FILLBRUSH1_ID);
  _fillbrushMapper->setMapping(_fillbrush2, FILLBRUSH2_ID);
  _fillbrushMapper->setMapping(_fillbrush3, FILLBRUSH3_ID);
  _fillbrushMapper->setMapping(_fillbrush4, FILLBRUSH4_ID);

  _connectSignals();
}

MainWindow::~MainWindow() {
  cout << "~MainWindow()" << endl;
  delete _area;
  delete _fileMenu;
  cout << "here" << endl;
  delete _toolsMenu;
  
  delete _helpMenu;
  delete _toolBar;
  delete _newAction; 
  delete _openAction; 
  delete _saveAction; 
  delete _saveAsAction;
  delete _exitAction;
  cout << "here 1" << endl;
  // Tools menu actions
  delete _freehandAct; delete _lineAct; delete _rectangleAct; delete _ellipseAct; delete _polygonAct; delete _textAct;
  cout << "here 1.0" << endl;
  // Style menu actions and submenus
  delete _penMenu; // -> FIXME: segfault at this line
  cout << "here 1.1" << endl;
  
  delete _penAction; delete _penColorAction; delete _penLineAction; delete _penWidthAction;
  delete _brushMenu;
  cout << "here 1.1.0" << endl;
  delete _brushAction; delete _brushColorAction; delete _brushFillAction;
  cout << "here 1.1.1" << endl;
  delete _fontAction;
  
  delete _styleMenu;
  // Help menu actions
  delete _aboutAction; delete _aboutQtAction;

  delete _toolsQag;
  delete _signalMapperTool;
}

void MainWindow::_createMenus(void) {
  qDebug() << "_createMenus()";
  QMenuBar* menubar = menuBar();
  _fileMenu = menubar->addMenu(tr("&File"));
  _toolsMenu = menubar->addMenu(tr("&Tools"));
  _styleMenu = menubar->addMenu(tr("&Style"));
  _helpMenu = menubar->addMenu(tr("&Help"));
  _penMenu = _styleMenu->addMenu(tr("&Pen"));
  _lineMenu = _penMenu->addMenu(tr("&Line"));
  _widthMenu = _penMenu->addMenu(tr("&Width"));
  _brushMenu = _styleMenu->addMenu(tr("&Brush"));
  _fillbrushMenu = _brushMenu->addMenu(tr("&Fill"));
  _colorPMenu = _penMenu->addMenu(tr("&Color"));
  _colorBMenu = _brushMenu->addMenu(tr("&Color"));
}

void MainWindow::_createToolbars(void) {
  qDebug() << "_createToolbars()";
  _toolBar = addToolBar(tr("File"));
}

// ---------------- ACTIONS ----------------
void MainWindow::_createActions(void) {
  qDebug() << "_createActions()";
  // File actions
  _createFileActions();
  // Tools actions
  _createToolsActions();
  // Style actions
  _createStyleActions();
  // Help actions
  _createHelpActions();
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

  _toolsLine = new QActionGroup(this);
  _SolidLine = new QAction(tr("&SolidLine"),this);
  _DashLine = new QAction(tr("&DashLine"),this);
  _DotLine = new QAction(tr("&DotLine"),this);

  _SolidLine->setCheckable(true);
  _DashLine->setCheckable(true);
  _DotLine->setCheckable(true);
  
  _toolsWidth =new QActionGroup(this);
  _ThickWidth =new QAction(tr("&Thick"),this);
  _NormalWidth=new QAction(tr("&Normal"),this);
  _LargeWidth=new QAction(tr("&Large"),this);

  _ThickWidth->setCheckable(true);
  _NormalWidth->setCheckable(true);
  _LargeWidth->setCheckable(true);
}

void MainWindow::_createStyleActions(void) {
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

  _fillbrushgroup =new QActionGroup(this);
  _fillbrush1 =new QAction(tr("&Solid"),this);
  _fillbrush2=new QAction(tr("&Vertical"),this);
  _fillbrush3=new QAction(tr("&Horizontal"),this);
  _fillbrush4=new QAction(tr("&Empty"),this);

  _fillbrush1->setCheckable(true);
  _fillbrush2->setCheckable(true);
  _fillbrush3->setCheckable(true);
  _fillbrush4->setCheckable(true);

  _penColor =new QActionGroup(this);
  _penColorBlue =new QAction(tr("&Blue"),this);
  _penColorRed=new QAction(tr("&Red"),this);
  _penColorGreen=new QAction(tr("&Green"),this);
  _penColorBlack=new QAction(tr("&Black"),this);
  _penColorYellow=new QAction(tr("&Yellow"),this);

  _penColorBlue->setCheckable(true);
  _penColorRed->setCheckable(true);
  _penColorGreen->setCheckable(true);
  _penColorBlack->setCheckable(true);
  _penColorYellow->setCheckable(true);

  _brushColor =new QActionGroup(this);
  _brushColorBlue =new QAction(tr("&Blue"),this);
  _brushColorRed=new QAction(tr("&Red"),this);
  _brushColorGreen=new QAction(tr("&Green"),this);
  _brushColorBlack=new QAction(tr("&Black"),this);
  _brushColorYellow=new QAction(tr("&Yellow"),this);

  _brushColorBlue->setCheckable(true);
  _brushColorRed->setCheckable(true);
  _brushColorGreen->setCheckable(true);
  _brushColorBlack->setCheckable(true);
  _brushColorYellow->setCheckable(true);
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
  qDebug() << "_connectActions()";
  // File Menu
  _fileMenu->addAction(_newAction);
  _fileMenu->addAction(_openAction);
  _fileMenu->addAction(_saveAction);
  _fileMenu->addAction(_saveAsAction);
  _fileMenu->addAction(_exitAction);

  qDebug() << "OK";

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

  qDebug() << "OK2";

  // Help Menu
  _helpMenu->addAction(_aboutAction);
  _helpMenu->addAction(_aboutQtAction);

  _toolBar->addAction(_newAction);
  _toolBar->addAction(_openAction);
  _toolBar->addAction(_saveAction);

  _toolsLine->addAction(_SolidLine);
  _toolsLine->addAction(_DashLine);
  _toolsLine->addAction(_DotLine);

  _lineMenu->addAction(_SolidLine);
  _lineMenu->addAction(_DashLine);
  _lineMenu->addAction(_DotLine);

  _toolsWidth->addAction(_ThickWidth);
  _toolsWidth->addAction(_NormalWidth);
  _toolsWidth->addAction(_LargeWidth);

  _widthMenu->addAction(_ThickWidth);
  _widthMenu->addAction(_NormalWidth);
  _widthMenu->addAction(_LargeWidth);

  _colorPMenu->addAction(_penColorBlue);
  _colorPMenu->addAction(_penColorRed);
  _colorPMenu->addAction(_penColorGreen);
  _colorPMenu->addAction(_penColorBlack);
  _colorPMenu->addAction(_penColorYellow);

  _penColor->addAction(_penColorBlue);
  _penColor->addAction(_penColorRed);
  _penColor->addAction(_penColorGreen);
  _penColor->addAction(_penColorBlack);
  _penColor->addAction(_penColorYellow);

  _colorBMenu->addAction(_brushColorBlue);
  _colorBMenu->addAction(_brushColorRed);
  _colorBMenu->addAction(_brushColorGreen);
  _colorBMenu->addAction(_brushColorBlack);
  _colorBMenu->addAction(_brushColorYellow);

  _brushColor->addAction(_brushColorBlue);
  _brushColor->addAction(_brushColorRed);
  _brushColor->addAction(_brushColorGreen);
  _brushColor->addAction(_brushColorBlack);
  _brushColor->addAction(_brushColorYellow);

  _fillbrushMenu->addAction(_fillbrush1);
  _fillbrushMenu->addAction(_fillbrush2);
  _fillbrushMenu->addAction(_fillbrush3);
  _fillbrushMenu->addAction(_fillbrush4);

  _fillbrushgroup->addAction(_fillbrush1);
  _fillbrushgroup->addAction(_fillbrush2);
  _fillbrushgroup->addAction(_fillbrush3);
  _fillbrushgroup->addAction(_fillbrush4);
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

  // Help actions
  connect(_aboutAction, SIGNAL(triggered()), this, SLOT(_about()));
  connect(_aboutQtAction, SIGNAL(triggered()), this, SLOT(_aboutQt()));

  connect(_signalMapperTool, SIGNAL(mapped(int)), this, SIGNAL(toolMapped(int)));
  connect(this, SIGNAL(toolMapped(int)), _area, SLOT(setCurrentTool(int)));

  connect(_SolidLine,SIGNAL(activated()),_lineMapper, SLOT(map()));
  connect(_DashLine,SIGNAL(activated()),_lineMapper, SLOT(map()));
  connect(_DotLine,SIGNAL(activated()),_lineMapper, SLOT(map()));

  connect(_lineMapper,SIGNAL(mapped(int)), this, SIGNAL(toolPenMapped(int)));
  connect(this, SIGNAL(toolPenMapped(int)), _area, SLOT(setCurrentPen(int)) ); 

  connect(_ThickWidth,SIGNAL(activated()),_widthMapper, SLOT(map()));
  connect(_NormalWidth,SIGNAL(activated()),_widthMapper, SLOT(map()));
  connect(_LargeWidth,SIGNAL(activated()),_widthMapper, SLOT(map()));

  connect(_widthMapper,SIGNAL(mapped(int)), this, SIGNAL(toolWidthMapped(int)));
  connect(this, SIGNAL(toolWidthMapped(int)), _area, SLOT(setCurrentWidth(int)) );

  connect(_penColorBlue,SIGNAL(activated()),_colorPMapper, SLOT(map()));
  connect(_penColorRed,SIGNAL(activated()),_colorPMapper, SLOT(map()));
  connect(_penColorGreen,SIGNAL(activated()),_colorPMapper, SLOT(map()));
  connect(_penColorBlack,SIGNAL(activated()),_colorPMapper, SLOT(map()));
  connect(_penColorYellow,SIGNAL(activated()),_colorPMapper, SLOT(map()));  

  connect(_colorPMapper,SIGNAL(mapped(int)), this, SIGNAL(toolColorPMapped(int)));
  connect(this, SIGNAL(toolColorPMapped(int)), _area, SLOT(setCurrentColorP(int)) ); 

  connect(_brushColorBlue,SIGNAL(activated()),_colorBMapper, SLOT(map()));
  connect(_brushColorRed,SIGNAL(activated()),_colorBMapper, SLOT(map()));
  connect(_brushColorGreen,SIGNAL(activated()),_colorBMapper, SLOT(map()));
  connect(_brushColorBlack,SIGNAL(activated()),_colorBMapper, SLOT(map()));
  connect(_brushColorYellow,SIGNAL(activated()),_colorBMapper, SLOT(map()));  

  connect(_colorBMapper,SIGNAL(mapped(int)), this, SIGNAL(toolColorBMapped(int)));
  connect(this, SIGNAL(toolColorBMapped(int)), _area, SLOT(setCurrentColorB(int)) ); 

  connect(_fillbrush1,SIGNAL(activated()),_fillbrushMapper, SLOT(map()));
  connect(_fillbrush2,SIGNAL(activated()),_fillbrushMapper, SLOT(map()));
  connect(_fillbrush3,SIGNAL(activated()),_fillbrushMapper, SLOT(map()));
  connect(_fillbrush4,SIGNAL(activated()),_fillbrushMapper, SLOT(map()));

  connect(_fillbrushMapper,SIGNAL(mapped(int)), this, SIGNAL(stylefillbrushMapped(int)));
  connect(this, SIGNAL(stylefillbrushMapped(int)), _area, SLOT(setCurrentFillBrush(int)) ); 
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
  }    

  int response = QMessageBox::warning(this, tr("Warning !"),
                                tr("The document has been modified. If you do not save your data first, they will be lost.\n"
                                "Do you want to create a new file ?"),
                                QMessageBox::Yes | QMessageBox::No);
  
  if (response == 16384) _area->clear();
}

void MainWindow::_open(void) {
  qDebug()<< "MainWindow::_open(void)" ;
  QString fileReadName(QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("XML (*.xml)")));
  QFileInfo info(fileReadName);
  this->setWindowTitle(info.fileName());
  qDebug() << this->windowTitle();
  QFile fileRead(fileReadName);
  if (fileRead.open(QIODevice::ReadOnly))
  {
    _area->clear();
  }
  QXmlStreamReader xmlReader;
  QFile fileread(fileReadName);
  qDebug() << "read";
  if (!fileread.open(QFile::ReadOnly | QFile::Text)) { 
    qDebug() << "Error: Cannot read file ";
  }
  xmlReader.setDevice(&fileread);
  while (!xmlReader.atEnd()) {
    if(xmlReader.isStartElement()) {
      if ( xmlReader.name()== "GraphicsItem") {
        qDebug() << "graphics";
        qDebug() << xmlReader.attributes().value("type").toString().toInt();
        int number = xmlReader.attributes().value("type").toString().toInt();
        int color = xmlReader.attributes().value("color").toString().toInt();
        _area->setCurrentColorP(color);
        QPen pen = _area->getPen();
        switch (number) {
          case 3:  {
            int x=xmlReader.attributes().value("x").toString().toInt();
            int y=xmlReader.attributes().value("y").toString().toInt();
            int w=xmlReader.attributes().value("w").toString().toInt();
            int h=xmlReader.attributes().value("h").toString().toInt();
            int style=xmlReader.attributes().value("style").toString().toInt();
            
            QGraphicsRectItem *rectangle = _area->addRect(x,y,w,h, pen);
            if (style == 0) {
              rectangle->pen().setStyle(Qt::DashDotDotLine);
            }
            break;
          } case 4: {
            int x=xmlReader.attributes().value("x").toString().toInt();
            int y=xmlReader.attributes().value("y").toString().toInt();
            int w=xmlReader.attributes().value("w").toString().toInt();
            int h=xmlReader.attributes().value("h").toString().toInt();
            int style=xmlReader.attributes().value("style").toString().toInt();

            QGraphicsEllipseItem *circle = _area->addEllipse(x,y,w,h, pen);
            if (style == 0) {
            circle->pen().setStyle(Qt::DashDotDotLine);
            }
            break;
          } case 5: {
            QVector<QPointF> points(0);
            QPointF point;
            int nbPoints=xmlReader.attributes().value("size").toString().toInt();
            int style=xmlReader.attributes().value("style").toString().toInt();
            for(int i=0; i<nbPoints; i++){
              QString xValue = "x" + QString::number(i);
              QString yValue = "y" + QString::number(i);
              int x=xmlReader.attributes().value(xValue).toString().toInt();
              int y=xmlReader.attributes().value(yValue).toString().toInt();
              point.setX(x);
              point.setY(y);
              points.append(point);
            };
            QPolygonF qPolygonF = QPolygonF(points);
            
            QGraphicsPolygonItem *polygon = _area->addPolygon(qPolygonF, pen);
            if (style == 0) {
              polygon->pen().setStyle(Qt::DashDotDotLine);
            }
            break;
          } case 6: {
            int x=xmlReader.attributes().value("x").toString().toInt();
            int y=xmlReader.attributes().value("y").toString().toInt();
            int w=xmlReader.attributes().value("w").toString().toInt();
            int h=xmlReader.attributes().value("h").toString().toInt();
            int style=xmlReader.attributes().value("style").toString().toInt();

            QGraphicsLineItem *line = _area->addLine(x,y,w,h, pen);
            if (style == 0) {
            line->pen().setStyle(Qt::DashDotDotLine);
            } 
            break;
          } case 8 : {
            int x=xmlReader.attributes().value("x").toString().toInt();
            int y=xmlReader.attributes().value("y").toString().toInt();
            QString text=xmlReader.attributes().value("text").toString();
            
            QGraphicsTextItem *_text = _area->addText(text);
            _text->setPos(x,y);
            break;
          }
        }
      }
    }
    xmlReader.readNext();
  }
  qDebug() << "end read";
}

void MainWindow::_save(void) {
  qDebug()<< "MainWindow::_save(void)" ;
  QFile file(this->windowTitle());
  qDebug() << this->windowTitle();
  qDebug() << file.fileName();
  QString fileName(this->windowTitle());
  if (fileName == ""){
    MainWindow::_saveAs();
  } else {
  if (file.open(QIODevice::ReadWrite|QIODevice::Text|QIODevice::Truncate)){
      QXmlStreamWriter xmlWriter(&file);
      xmlWriter.setAutoFormatting(true);
      xmlWriter.writeStartDocument();
      xmlWriter.writeStartElement("Scene");
      xmlWriter.writeAttribute("version", "v1.0");
      xmlWriter.writeStartElement("GraphicsItemList");
      qreal width, height, x, y;
      for (int i =0; i< _area->items().size();i++) { 
        xmlWriter.writeStartElement("GraphicsItem");
        int number=_area->items().value(i)->type();
        xmlWriter.writeAttribute("type", QString::number(number));
        xmlWriter.writeAttribute("color", QString::number(_area->items().value(i)->data(0).toInt()));
        switch(number) {
          case 3: {
            qDebug() << "Rectangle";
            QGraphicsRectItem *rectangle;
            rectangle = qgraphicsitem_cast<QGraphicsRectItem*>(_area->items().value(i));
            x = rectangle->rect().x();
            y = rectangle->rect().y();
            width = rectangle->rect().width();
            height = rectangle->rect().height();
            xmlWriter.writeAttribute("x", QString::number(x));
            xmlWriter.writeAttribute("y", QString::number(y));
            xmlWriter.writeAttribute("w", QString::number(width));
            xmlWriter.writeAttribute("h", QString::number(height));
            xmlWriter.writeAttribute("style", QString::number(rectangle->pen().style()));
            break;
          } case 4: {
            qDebug() << "Circle";
            QGraphicsEllipseItem *circle;
            circle = qgraphicsitem_cast<QGraphicsEllipseItem*>(_area->items().value(i));
            x = circle->rect().x();
            y = circle->rect().y();
            width = circle->rect().width();
            height = circle->rect().height();
            xmlWriter.writeAttribute("x", QString::number(x));
            xmlWriter.writeAttribute("y", QString::number(y));
            xmlWriter.writeAttribute("w", QString::number(width));
            xmlWriter.writeAttribute("h", QString::number(height));
            xmlWriter.writeAttribute("style", QString::number(circle->pen().style()));
            break;
          } case 5: {
            qDebug() << "Polygon";
            QGraphicsPolygonItem *polygon;
            polygon = qgraphicsitem_cast<QGraphicsPolygonItem*>(_area->items().value(i));
            int xTab[polygon->polygon().size()];
            int yTab[polygon->polygon().size()];
            int nbPoints = polygon->polygon().size();
            xmlWriter.writeAttribute("size", QString::number(nbPoints));
            for(int i=0; i<polygon->polygon().size(); i++){
              xTab[i] = polygon->polygon().at(i).x();
              yTab[i] = polygon->polygon().at(i).y();
            };
            for(unsigned int i=0; i<sizeof(xTab); i++){
              QString x = "x" + QString::number(i);
              xmlWriter.writeAttribute(x, QString::number(xTab[i]));
            }
            for(unsigned int i=0; i<sizeof(yTab); i++){
              QString y = "y" + QString::number(i);
              xmlWriter.writeAttribute(y, QString::number(yTab[i]));
            }
            xmlWriter.writeAttribute("style", QString::number(polygon->pen().style()));
            break;
          } case 6 : {
            qDebug() << "Line";
            QGraphicsLineItem *line;
            line = qgraphicsitem_cast<QGraphicsLineItem*>(_area->items().value(i));
            x = line->line().x1();
            y = line->line().y1();
            width = line->line().x2();
            height = line->line().y2();
            xmlWriter.writeAttribute("x", QString::number(x));
            xmlWriter.writeAttribute("y", QString::number(y));
            xmlWriter.writeAttribute("w", QString::number(width));
            xmlWriter.writeAttribute("h", QString::number(height));
            xmlWriter.writeAttribute("style", QString::number(line->pen().style()));
            break;
          } case 8 : {
            qDebug() << "Text";
            QGraphicsTextItem *text;
            text = qgraphicsitem_cast<QGraphicsTextItem*>(_area->items().value(i));
            x = text->x();
            y = text->y();
            QString textValue = text->toPlainText();
            xmlWriter.writeAttribute("x", QString::number(x));
            xmlWriter.writeAttribute("y", QString::number(y));
            xmlWriter.writeAttribute("text", textValue);
            break;
          }
          break;
        }
        xmlWriter.writeEndElement(); // GraphicsItem
      }
      xmlWriter.writeEndElement(); // GraphicsItemList
      xmlWriter.writeEndElement(); // Scene
      file.close();
    }
  }
}

void MainWindow::_saveAs(void) {
  qDebug()<< "MainWindow::_saveAs(void)";
  QString fileName(QFileDialog::getSaveFileName(this, tr("Save File"), ".xml", tr("XML (*.xml)")));
  QFile file(fileName);
  QFileInfo info(fileName);
  this->setWindowTitle(info.fileName());
    if (file.open(QIODevice::WriteOnly)){
      QXmlStreamWriter xmlWriter(&file);
      xmlWriter.setAutoFormatting(true);
      xmlWriter.writeStartDocument();
      xmlWriter.writeStartElement("Scene");
      xmlWriter.writeAttribute("version", "v1.0");
      xmlWriter.writeStartElement("GraphicsItemList");
      qreal width, height, x, y;
      for (int i =0; i< _area->items().size();i++) { 
        xmlWriter.writeStartElement("GraphicsItem");
        int number=_area->items().value(i)->type();
        xmlWriter.writeAttribute("type", QString::number(number));
        xmlWriter.writeAttribute("color", QString::number(_area->items().value(i)->data(0).toInt()));
        switch(number) {
          case 3: {
            qDebug() << "Rectangle";
            QGraphicsRectItem *rectangle;
            rectangle = qgraphicsitem_cast<QGraphicsRectItem*>(_area->items().value(i));
            x = rectangle->rect().x();
            y = rectangle->rect().y();
            width = rectangle->rect().width();
            height = rectangle->rect().height();
            xmlWriter.writeAttribute("x", QString::number(x));
            xmlWriter.writeAttribute("y", QString::number(y));
            xmlWriter.writeAttribute("w", QString::number(width));
            xmlWriter.writeAttribute("h", QString::number(height));
            xmlWriter.writeAttribute("style", QString::number(rectangle->pen().style()));
            break;
          } case 4: {
            qDebug() << "Circle";
            QGraphicsEllipseItem *circle;
            circle = qgraphicsitem_cast<QGraphicsEllipseItem*>(_area->items().value(i));
            x = circle->rect().x();
            y = circle->rect().y();
            width = circle->rect().width();
            height = circle->rect().height();
            xmlWriter.writeAttribute("x", QString::number(x));
            xmlWriter.writeAttribute("y", QString::number(y));
            xmlWriter.writeAttribute("w", QString::number(width));
            xmlWriter.writeAttribute("h", QString::number(height));
            xmlWriter.writeAttribute("style", QString::number(circle->pen().style()));
            break;
          } case 5: {
            qDebug() << "Polygon";
            QGraphicsPolygonItem *polygon;
            polygon = qgraphicsitem_cast<QGraphicsPolygonItem*>(_area->items().value(i));
            int xTab[polygon->polygon().size()];
            int yTab[polygon->polygon().size()];
            int nbPoints = polygon->polygon().size();
            xmlWriter.writeAttribute("size", QString::number(nbPoints));
            for(int i=0; i<polygon->polygon().size(); i++){
              xTab[i] = polygon->polygon().at(i).x();
              yTab[i] = polygon->polygon().at(i).y();
            };
            for(unsigned int i=0; i<sizeof(xTab); i++){
              QString x = "x" + QString::number(i);
              xmlWriter.writeAttribute(x, QString::number(xTab[i]));
            }
            for(unsigned int i=0; i<sizeof(yTab); i++){
              QString y = "y" + QString::number(i);
              xmlWriter.writeAttribute(y, QString::number(yTab[i]));
            }
            xmlWriter.writeAttribute("style", QString::number(polygon->pen().style()));
            break;
          } case 6 : {
            qDebug() << "Line";
            QGraphicsLineItem *line;
            line = qgraphicsitem_cast<QGraphicsLineItem*>(_area->items().value(i));
            x = line->line().x1();
            y = line->line().y1();
            width = line->line().x2();
            height = line->line().y2();
            xmlWriter.writeAttribute("x", QString::number(x));
            xmlWriter.writeAttribute("y", QString::number(y));
            xmlWriter.writeAttribute("w", QString::number(width));
            xmlWriter.writeAttribute("h", QString::number(height));
            xmlWriter.writeAttribute("style", QString::number(line->pen().style()));
            break;
          } case 8 : {
            qDebug() << "Text";
            QGraphicsTextItem *text;
            text = qgraphicsitem_cast<QGraphicsTextItem*>(_area->items().value(i));
            x = text->x();
            y = text->y();
            QString textValue = text->toPlainText();
            xmlWriter.writeAttribute("x", QString::number(x));
            xmlWriter.writeAttribute("y", QString::number(y));
            xmlWriter.writeAttribute("text", textValue);
            break;
          }
          break;
        }
        xmlWriter.writeEndElement(); // GraphicsItem
      }
    xmlWriter.writeEndElement(); // GraphicsItemList
    xmlWriter.writeEndElement(); // Scene
    file.close();
    }
}

void MainWindow::_exit(void) {
  qDebug() << "MainWindow::_exit(void)";
  exit(0);
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

