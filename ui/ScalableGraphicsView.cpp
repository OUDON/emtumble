#include "ScalableGraphicsView.h"

ScalableGraphicsView::ScalableGraphicsView(QWidget *parent) : QGraphicsView(parent)
{
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setDragMode(QGraphicsView::DragMode::ScrollHandDrag);
    setInteractive(true);
}

void ScalableGraphicsView::wheelEvent(QWheelEvent *event)
{
    int deg = event->delta() / 8;
    int steps = deg / 15; // See: https://doc-snapshots.qt.io/qt5-dev/qwheelevent.html#QWheelEvent

    scale_factor_int += steps;
    scale_factor_int = std::min(scale_factor_int, 1000);
    scale_factor_int = std::max(scale_factor_int, 10);
    do_scale();
}

void ScalableGraphicsView::do_scale()
{
    qreal factor = 1.0 * qreal(scale_factor_int) / 100.0;
    resetMatrix();
    scale(factor, factor);
}

void ScalableGraphicsView::wrap_content_height()
{
    QRectF scene_rect = sceneRect();
    scale_factor_int = height() / scene_rect.height() * 100;
    do_scale();
}
