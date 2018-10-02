#include "scene_area.h"

SceneArea::SceneArea(qreal x, qreal y, qreal width, qreal height, QObject * parent = 0) : QGraphicsScene(x, y, width, height, parent) {
  qDebug() << "Scene::Scene(void)";

  _startPoint = _endPoint = _offset = QPointF(0,0);

  addRect(QRectF(150,150,200,400));

  state = 0;

  QPolygonF _polygon;
  _polygon << QPointF(10, 10) << QPointF(100, 55) <<  QPointF(100, 100) << QPointF(10, 100);
  addPolygon(_polygon);

  _item = NULL;
}

void SceneArea::mousePressEvent(QGraphicsSceneMouseEvent* evt) {
  qDebug() << "Scene::mousePressEvent(void)";
  /*qDebug() <<  "evt->pos() : " << evt->pos(); 
  qDebug() <<  "evt->scenePos() : " <<  evt->scenePos();*/

  for (int i = 0; i<items().size(); i++) {
    items().value(i)->show();
    /*qDebug() << "item number : " << i;
    qDebug() << "items().value(i)->scenePos() : " << items().value(i)->scenePos();
    qDebug() << "items().value(i)->pos()  : " << items().value(i)->mapToScene(items().value(i)->pos());*/
  }

  _startPoint = _endPoint = evt->scenePos();
  _item = itemAt(_startPoint);
  if (_item) {
    QList<QGraphicsItem *> items = collidingItems(_item);
    for (int i =0; i < items.size(); i++) {
      qDebug() << "colliding item number : " << i;
      items.value(i)->hide();
    }
    _offset =  _startPoint - _item->pos();
//    _item->setPos(_startPoint - _offset );
//    _item->setPos( _item->pos());
    _item->grabMouse();
  } else if (_currentTool == TOOLS_MENU_ID_FREEHAND - 4) {
    startFreehandPath(evt);
  } else if (_currentTool == TOOLS_MENU_ID_POLYGON -4) {
    switch (state) {
      case 0:
        point1 = QPointF(_startPoint.x(), _startPoint.y());
        break;
      case 1:
        point2 = QPointF(_startPoint.x(), _startPoint.y());
        break;
      case 2:
        point3 = QPointF(_startPoint.x(), _startPoint.y());
        break;
      case 3:
        point4 = QPointF(_startPoint.x(), _startPoint.y());
        QPolygonF _polygon;
        _polygon << point1 << point2 << point3 << point4;
        QGraphicsPolygonItem * polygon = addPolygon(_polygon);
        polygon->setFlag(QGraphicsItem::ItemIsMovable);
        break;
    }
    // Increment state or reset it
    state = state+1 > 3 ? 0 : state+1;
  }
}

void SceneArea::mouseMoveEvent(QGraphicsSceneMouseEvent* evt) {
//  qDebug() << "Scene::mouseMoveEvent(void)";
  if (_item) {
     _item->setPos(evt->scenePos() - _offset);
  }
  _endPoint = evt->scenePos(); 

  if ((_currentTool == TOOLS_MENU_ID_FREEHAND - 4) && path) {
    QPainterPath p = path->path();
    previous = evt->scenePos();
    p.lineTo(previous);
    path->setPath(p);
  }
}

void SceneArea::mouseReleaseEvent(QGraphicsSceneMouseEvent* evt) {
  qDebug() << "Scene::mouseReleaseEvent(void)";
  if (_item) {
    _item->setPos(evt->scenePos() - _offset);
    _item->ungrabMouse();
    _item = NULL;
  }
  else if (_startPoint != _endPoint) {
    qDebug() << "Current tool: " << _currentTool;
    switch(_currentTool) {
      case TOOLS_ID_FREEHAND: {
        // Create a freehand object
        qDebug() << "Freehand";
        path = NULL;
        break;
      } case TOOLS_ID_LINE: {
        // Create a new line
        qDebug() << "Line";
        QGraphicsLineItem *line = addLine(_startPoint.x(), _startPoint.y(), _endPoint.x(), _endPoint.y());
        line->setFlag(QGraphicsItem::ItemIsMovable);
        break;
      } case TOOLS_ID_RECTANGLE: {
        // Create a new rectangle
        qDebug() << "Rectangle";
        QGraphicsRectItem *rect = addRect(_startPoint.x(), _startPoint.y(), _endPoint.x() - _startPoint.x(), _endPoint.y() - _startPoint.y());
        rect->setFlag(QGraphicsItem::ItemIsMovable);
        break;
      } case TOOLS_ID_CIRCLE: {
        // Create a new circle
        qDebug() << "Circle/Ellipse";
        QGraphicsEllipseItem *ellipse = addEllipse(_startPoint.x(), _startPoint.y(), _endPoint.x() - _startPoint.x(), _endPoint.y() - _startPoint.y());
        ellipse->setFlag(QGraphicsItem::ItemIsMovable);
        break;
      } case TOOLS_ID_POLYGON: {
        // Create a new polygon
        qDebug() << "Polygon" << state;
        break;
      } case TOOLS_ID_TEXT: {
        // Create a text zone
        qDebug() << "Text";
        break;
      } default:
        // Nothing to do
        qDebug() << "Nothing to do";
        break;
    }
  }
  _endPoint = evt->scenePos();
  qDebug() << items().size();
}

void SceneArea::startFreehandPath(QGraphicsSceneMouseEvent* evt) {
  path = new QGraphicsPathItem();
  previous = evt->scenePos();
  QPainterPath p;
  p.moveTo(previous);
  path->setPath(p);
  addItem(path);
}

void SceneArea::setCurrentTool(int tool) {
  qDebug() << "Scene::setCurrentTool(int tool)";
  _currentTool = tool;
  qDebug () << _currentTool;
}

void SceneArea::setCurrentStyle(int style) {
  qDebug() << "Scene::setCurrentStyle(int style)";
  _currentStyle = style;
  qDebug () << _currentStyle;
}

