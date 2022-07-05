#ifndef CUSTOM_AXIS_ITEM_H
#define CUSTOM_AXIS_ITEM_H
 
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

 
class CustomAxisItem : public QGraphicsItem
{
public:
    CustomAxisItem();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    QRectF boundingRect() const Q_DECL_OVERRIDE;

    void  setItemWidth(qreal total_width);
    void  setScenePositionRange(qreal minX, qreal maxX);

protected:
    //鼠标事件
    void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    //拖拽事件
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QGraphicsSceneDragDropEvent *event) Q_DECL_OVERRIDE;

private:

    QColor color;

    qreal   m_width = 40.0;
    qreal   m_height = 10.0;
    qreal   m_triAngleLen = 12.0;

    qreal   m_len = .0;
    qreal   m_minX = .0;
    qreal   m_maxX = 400;


    QPolygonF  m_leftTri        ;
    QPolygonF  m_rightTri       ;
    QPolygonF  m_centralLeftTri ;
    QPolygonF  m_centralRightTri;
    QPolygonF  m_centralRect    ;
};
 
#endif // CUSTOM_AXIS_ITEM_H
