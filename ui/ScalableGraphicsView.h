#ifndef SCALABLE_GRAPHICS_VIEW_H
#define SCALABLE_GRAPHICS_VIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QWidget>
#include <QTimeLine>

#include <iostream>
#include <algorithm>

class ScalableGraphicsView : public QGraphicsView {
public:
    ScalableGraphicsView(QWidget *parent);

protected:
  virtual void wheelEvent(QWheelEvent *event);

private:

  int scale_factor_int = 100; // %
};

#endif
