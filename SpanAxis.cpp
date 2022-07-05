#include "SpanAxis.h"
#include <QHBoxLayout>
#include <QStyleOption>

SpanAxis::SpanAxis(QWidget *parent)
    :QWidget(parent)
{
    auto style = QString("background: #152640;");
    setStyleSheet(style);
    this->setFixedHeight(13);
    this->setWindowFlags(Qt::FramelessWindowHint);

    auto lay = new QHBoxLayout();
    lay->setContentsMargins(0, 0, 0, 0);

    m_pView = new CustomView;
    m_pScene = new CustomScene;
    m_pView->setScene(m_pScene);

    lay->addWidget(m_pView);
    this->setLayout(lay);

    connect(m_pScene, &CustomScene::sigMouseMoveEnd, this, &SpanAxis::sltGraphicChangedSpan);
}

SpanAxis::~SpanAxis()
{

}

void SpanAxis::sltTotalRangeChanged(double start, double end)
{
    m_totalRangeStart = start;
    m_totalRangeEnd = end;
    drawAxis();
}

void SpanAxis::sltShowRangeChanged(double start, double end)
{
    m_showRangeStart = start;
    m_showRangeEnd = end;
    drawAxis();
}

void SpanAxis::resizeEvent(QResizeEvent *event)
{
    if (this->width() != 0 && this->height() != 0)
    {
        auto size = m_pView->size();
        m_pScene->setSceneRect(QRectF(0, 0, size.width() - 2, size.height() -2));
        drawAxis();
    }
    QWidget::resizeEvent(event);
}

void SpanAxis::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QWidget::paintEvent(event);
}

void SpanAxis::sltGraphicChangedSpan()
{
    if (m_pAxisItem == nullptr)
    {
        return;
    }

    auto pos = m_pAxisItem->pos();
    auto rect = m_pAxisItem->boundingRect();
    auto show_pixel = rect.width() - 0.5 * 2; //扣除adjust调整增加的宽度
    //一个像素代表的时间长度
    auto units = m_totalRange / 1.0f / m_totalWidthPixel;
    auto new_start = (units * pos.x());
    auto new_end = new_start + (show_pixel * units);
    emit sigShowRangeChange(new_start, new_end);

    m_showRangeStart = new_start;
    m_showRangeEnd = new_end;
    m_showRange = new_end - new_start;
}

double SpanAxis::spanTime() const
{
    return m_showRange;
}

void SpanAxis::setSpanTime(double spanTime)
{
    m_showRange = spanTime;
}

void SpanAxis::drawAxis()
{
    m_totalWidthPixel = m_pScene->sceneRect().width();
    if (m_totalWidthPixel == 0.0)
    {
        return;
    }
    m_totalRange =  m_totalRangeEnd - m_totalRangeStart;
    m_showRange = m_showRangeEnd - m_showRangeStart;

    if (m_pAxisItem == nullptr)
    {
        m_pAxisItem = new CustomAxisItem;
        m_pScene->addItem(m_pAxisItem);
    }
    //宽度
    auto item_width = (m_showRange * m_totalWidthPixel / m_totalRange);
    m_pAxisItem->setItemWidth(item_width);
    m_pAxisItem->setScenePositionRange(.0, m_totalWidthPixel);
    //位置
    auto x = m_showRangeStart * (m_totalWidthPixel / 1.0 / m_totalRange);
    auto y = 6.0;
    m_pAxisItem->setPos(x, y);

    update();
}
