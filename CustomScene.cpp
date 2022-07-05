#include "CustomScene.h"
#include <QDebug>
#include <QGraphicsItem>
#include <QtMath>
 
CustomScene::CustomScene(QObject *parent):QGraphicsScene(parent)
{
}
 
void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "CustomScene::mousePressEvent";
    if (event->buttons() == Qt::LeftButton)
    {
        emit sigSceneClick(event->scenePos());
    }
    QGraphicsScene::mousePressEvent(event);
}
 
void CustomScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    auto pos = event->buttonDownScreenPos(Qt::LeftButton);
    auto pos2 = event->screenPos();
    if (qSqrt((pos.x() - pos2.x())* (pos.x() - pos2.x()) + (pos.y() - pos2.y()) * (pos.y() - pos2.y())) >= 2)
    {
        emit sigMouseMoveEnd();
    }
    QGraphicsScene::mouseReleaseEvent(event);
}
 
void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "CustomScene::mouseMoveEvent";
    QGraphicsScene::mouseMoveEvent(event);
}
 
void CustomScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    //qDebug() << "CustomScene::dragEnterEvent";
    QGraphicsScene::dragEnterEvent(event);
}
 
void CustomScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    //qDebug() << "CustomScene::dragLeaveEvent";
    QGraphicsScene::dragLeaveEvent(event);
}
 
void CustomScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    //qDebug() << "CustomScene::dragMoveEvent";
    QGraphicsScene::dragMoveEvent(event);
}
 
void CustomScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    //qDebug() << "CustomScene::dropEvent";
    QGraphicsScene::dropEvent(event);
}
