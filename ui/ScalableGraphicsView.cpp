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

    qreal factor = 1.0 * qreal(scale_factor_int) / 100.0;
    resetMatrix();
    scale(factor, factor);
    std::cerr << "scale_factor: " << factor << std::endl;
}
