#ifndef SCENE_H
#define SCENE_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsEffect>
#include <QGraphicsSceneMouseEvent>

#include <QDebug>
#include <QPolygonF>

#include "enums.h"

class SceneArea : public QGraphicsScene
{
  Q_OBJECT  

  public:
    SceneArea( qreal x, qreal y, qreal width, qreal height, QObject * parent);
//   PaintArea(QWidget *parent = 0);
  public slots:
    void setCurrentTool(int);
    void setCurrentStyle(int);
  protected :
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
  private :
    int _currentTool, _currentStyle;
    QPointF  _startPoint,_endPoint, _offset;
    QGraphicsItem * _item;
    QPolygon _polygon;
    // These two variables are used for freehand action
    QPointF previous;
    QGraphicsPathItem *path;
    // These variables are used for pylogon action
    int state;
    QPointF point1, point2, point3, point4;

    void startFreehandPath(QGraphicsSceneMouseEvent* evt);
};
#endif

