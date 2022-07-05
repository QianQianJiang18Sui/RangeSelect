#ifndef CUSTOMVIEW_H
#define CUSTOMVIEW_H
 
#include <QGraphicsView>
 
class CustomView : public QGraphicsView
{
    Q_OBJECT
public:
    CustomView(QWidget *parent = 0);
protected:

    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void dragEnterEvent(QDragEnterEvent *event) Q_DECL_OVERRIDE;
    void dragLeaveEvent(QDragLeaveEvent *event) Q_DECL_OVERRIDE;
    void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
    void dropEvent(QDropEvent *event) Q_DECL_OVERRIDE;

    void wheelEvent(QWheelEvent *event) override;
};
 
#endif // CUSTOMVIEW_H
