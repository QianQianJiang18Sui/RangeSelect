#include "CustomAxisItem.h"
#include <QDebug>
#include <QPainter>
#include <QCursor>
#include <QPen>
#include <QtMath>
 
CustomAxisItem::CustomAxisItem()
{
    color = Qt::red;
    setFlag(QGraphicsItem::ItemIsFocusable);
    //设置图元为可移动的
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptDrops(true);

    m_len = qTan(qDegreesToRadians(60.0)) * (m_triAngleLen / 2.0);
}
 
void CustomAxisItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    //qDebug() << "CustomAxisItem::paint";
    if(hasFocus())
    {
        painter->setPen(QPen(Qt::yellow));
        painter->setBrush(QBrush(Qt::yellow));
    }
    else
    {
        painter->setPen(QPen(Qt::white));
        painter->setBrush(QBrush(Qt::white));
    }


    //painter->setBrush(QBrush(Qt::white));
    //painter->drawRect(QRect(-5, -5, 10, 10));
//    if (m_width == 0)
//    {
//        return;
//    }

    auto y1 = m_triAngleLen / 2.0;
    auto y2 = 0 - m_triAngleLen / 2.0;
    auto x1 = qTan(qDegreesToRadians(60.0)) * y1;
    auto x2 = x1 + m_width;
    auto x2_mid = x1 + m_width / 2.0;
    auto x3 = x2 + x1;

    m_leftTri.clear();
    m_leftTri.append(QPointF(.0, .0));
    m_leftTri.append(QPointF(x1, y1));
    m_leftTri.append(QPointF(x1, y2));
    painter->drawPolygon(m_leftTri);

    painter->save();
    painter->setPen(QPen(QColor(52,84,189)));
    painter->setBrush(QBrush(QColor(52,84,189)));
    m_centralRect.clear();
    m_centralRect.append(QPointF(x1, m_height / 2.0));
    m_centralRect.append(QPointF(x2, m_height / 2.0));
    m_centralRect.append(QPointF(x2, 0 - m_height / 2.0));
    m_centralRect.append(QPointF(x1, 0 - m_height / 2.0));
    painter->drawPolygon(m_centralRect);

    painter->restore();
    m_centralLeftTri.clear();
    m_centralLeftTri.append(QPointF(x2_mid - x1,  0));
    m_centralLeftTri.append(QPointF(x2_mid, y1));
    m_centralLeftTri.append(QPointF(x2_mid, y2));
    painter->drawPolygon(m_centralLeftTri);

    m_centralRightTri.clear();
    m_centralRightTri.append(QPointF(x2_mid + x1, 0));
    m_centralRightTri.append(QPointF(x2_mid, y2));
    m_centralRightTri.append(QPointF(x2_mid, y1));
    painter->drawPolygon(m_centralRightTri);

    m_rightTri.clear();
    m_rightTri.append(QPointF(x3, .0));
    m_rightTri.append(QPointF(x2, y2));
    m_rightTri.append(QPointF(x2, y1));
    painter->drawPolygon(m_rightTri);

}
 
QRectF CustomAxisItem::boundingRect() const
{
    qreal adjust = 0.5;
    auto len = qTan(qDegreesToRadians(60.0)) * (m_triAngleLen / 2.0);

    return QRectF(0 - adjust, 0 - m_triAngleLen / 2.0, len * 2 + m_width + adjust * 2, m_triAngleLen + adjust * 2);
}

void CustomAxisItem::setItemWidth(qreal total_width)
{
    if (total_width < m_len * 4)
    {
        total_width = m_len * 4;
    }
    m_width = total_width - 2 * m_len;
}

void CustomAxisItem::setScenePositionRange(qreal minX, qreal maxX)
{
    m_minX = minX;
    m_maxX = maxX;
}
 
void CustomAxisItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //Q_UNUSED(event);
    //qDebug() << "CustomAxisItem::mousePressEvent: " << event->pos;
    //setCursor(Qt::OpenHandCursor);
    QGraphicsItem::mousePressEvent(event);
}
 
void CustomAxisItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    auto pos = this->pos();
    //判断是点击在哪个三角形上
    auto pressPos = event->lastPos();
    //设置y为0，一直在x轴上移动，业务需要
    pressPos.setY(0);
    auto x1 = event->lastScenePos().x();
    auto x2 = event->scenePos().x();
    auto offset_x = x2 - x1;

    if (m_leftTri.containsPoint(pressPos, Qt::FillRule::OddEvenFill))
    {
        //左托width最大
        auto width_max = m_width + pos.x() - m_minX;
        //左侧拉长三角
        auto newwidth = m_width - offset_x;
        if (newwidth <= m_len * 2)
        {
            newwidth = m_len * 2;
        }

        if (newwidth >=width_max)
        {
            newwidth = width_max;
        }

        offset_x = m_width - newwidth;
        m_width = newwidth;
        pos.setX(pos.x() + offset_x);
    }
    else if (m_rightTri.containsPoint(pressPos, Qt::OddEvenFill))
    {
        //右托width最大
        auto width_max = m_maxX - pos.x() - 2 * m_len;

        //右侧拉长三角
        auto new_width = m_width += offset_x;
        if (new_width <= m_len * 2)
        {
            new_width = m_len * 2;
        }

        if (new_width >=width_max)
        {
            new_width = width_max;
        }
        m_width = new_width;
    }
    else
    {
        //中间移动
        auto new_x = pos.x() + offset_x;
        if (new_x <= m_minX)
        {
            new_x = m_minX;
        }
        else if (new_x >= m_maxX - (m_len * 2 + m_width))
        {
            new_x = m_maxX - (m_len * 2 + m_width);
        }
        pos.setX(new_x);
    }
    this->update();
    this->setPos(pos);
}
 
void CustomAxisItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}
 
void CustomAxisItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    //setCursor(Qt::CrossCursor);
    //qDebug() << "CustomAxisItem::dragEnterEvent";
    QGraphicsItem::dragEnterEvent(event);
}
 
void CustomAxisItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    //setCursor(Qt::ForbiddenCursor);
    //qDebug() << "CustomAxisItem::dragLeaveEvent";
    QGraphicsItem::dragLeaveEvent(event);
}
 
void CustomAxisItem::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    qDebug() << "22222";
    QGraphicsItem::dragMoveEvent(event);
}
 
void CustomAxisItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    //setCursor(Qt::WaitCursor);
    //qDebug() << "CustomAxisItem::dropEvent";
    QGraphicsItem::dropEvent(event);
}
