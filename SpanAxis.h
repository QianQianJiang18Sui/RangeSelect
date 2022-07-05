#ifndef SPAN_AXIS_H
#define SPAN_AXIS_H

#include <QWidget>
#include <QtMath>

#include "CustomScene.h"
#include "CustomView.h"
#include "CustomAxisItem.h"


////////
/// \brief The SpanAxis class
/// 范围选取轴
/// ----|-----|-----
///   start  end
///可调整
/// 目前只支持水平轴
///


class SpanAxis : public QWidget
{
    Q_OBJECT

public:
    SpanAxis(QWidget *parent = nullptr);
    ~SpanAxis();

    double spanTime() const;
    void setSpanTime(double spanTime);

public slots:

    void sltTotalRangeChanged(double start, double end);
    void sltShowRangeChanged(double start, double end);

signals:

    void sigShowRangeChange(double start, double end);

protected:

    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void paintEvent(QPaintEvent *event) override;

protected slots:

    void sltGraphicChangedSpan();

private:

    CustomView*     m_pView = nullptr;
    CustomScene*    m_pScene = nullptr;
    CustomAxisItem* m_pAxisItem = nullptr;

    double        m_totalRangeStart = .0;
    double        m_totalRangeEnd = 3600;

    double        m_totalRange = .0;
    double        m_totalWidthPixel = .0;

    double        m_showRangeStart = 200;
    double        m_showRangeEnd = 1200;
    double        m_showRange = .0;

private:

    void drawAxis();

};
#endif // SPAN_AXIS_H
