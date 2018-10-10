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

#include <iostream>

using namespace std;

class SceneArea : public QGraphicsScene
{
  Q_OBJECT  

  public:
    SceneArea( qreal x, qreal y, qreal width, qreal height, QObject * parent);
    QPen getPen();
    ~SceneArea();
  public slots:
    void setCurrentTool(int);
    int getCurrentTool();
    void setCurrentPen(int tool);
    int getCurrentPen();
    void setCurrentWidth(int tool);
    int getCurrentWidth();
    void setCurrentColorP(int tool);
    int getCurrentColorP();
    void setCurrentColorB(int tool);
    int getCurrentColorB();
    void setCurrentFillBrush(int tool);
    int getCurrentFillBrush();
  protected :
    void mousePressEvent(QGraphicsSceneMouseEvent*);
    void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
  private :
    int _currentTool;
    int _currentToolPen;
    int _currentToolWidth;
    int _currentPColor;
    int _currentBColor;
    int _currentFillBrush;

    QPointF  _startPoint, _endPoint, _offset;
    QGraphicsItem * _item;
    QGraphicsTextItem * _text;
    QPolygon _polygon;
    QString _text_input;
    QPen _pen;
    QBrush _brush;
    // These two variables are used for freehand action
    QPointF previous;
    QGraphicsPathItem *path;
    // These variables are used for pylogon action
    int state;
    QPointF point1, point2, point3, point4;

    void startFreehandPath(QGraphicsSceneMouseEvent* evt);
};
#endif

