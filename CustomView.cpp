#include "CustomView.h"
#include <QDebug>
#include <QMouseEvent>

CustomView::CustomView(QWidget *parent):QGraphicsView(parent)
{
    this->setStyleSheet(tr("background: transparent;border:0px;"));
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
 
void CustomView::mousePressEvent(QMouseEvent *event)
{
    //qDebug() << "CustomView::mousePressEvent";
    QGraphicsView::mousePressEvent(event);
}
 
void CustomView::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug() << "CustomView::mouseMoveEvent";
    QGraphicsView::mouseMoveEvent(event);
    update();
}
 
void CustomView::mouseReleaseEvent(QMouseEvent *event)
{
    //qDebug() << "CustomView::mouseReleaseEvent";
    QGraphicsView::mouseReleaseEvent(event);
}
 
void CustomView::paintEvent(QPaintEvent *event)
{
    //qDebug() << "CustomView::paintEvent";
    QGraphicsView::paintEvent(event);
}
 
void CustomView::dragEnterEvent(QDragEnterEvent *event)
{
    //qDebug() << "CustomView::dragEnterEvent";
    QGraphicsView::dragEnterEvent(event);
}
 
void CustomView::dragLeaveEvent(QDragLeaveEvent *event)
{
    //qDebug() << "CustomView::dragLeaveEvent";
    QGraphicsView::dragLeaveEvent(event);
}
 
void CustomView::dragMoveEvent(QDragMoveEvent *event)
{
    //setCursor(Qt::CrossCursor);
    //qDebug() << "CustomView::dragMoveEvent";
    QGraphicsView::dragMoveEvent(event);
}
 
void CustomView::dropEvent(QDropEvent *event)
{
    //qDebug() << "CustomView::dropEvent";
    QGraphicsView::dropEvent(event);
}

void CustomView::wheelEvent(QWheelEvent *event)
{
    return;
}
