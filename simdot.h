#ifndef SIMDOT_H
#define SIMDOT_H

#include <QGraphicsItem>
#include <QPainter>

class simDot : public QGraphicsItem
{
public:
  simDot(QPointF dot, int color);
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
  QPointF pDot;
  int pColor;
  qreal s;
};

#endif // SIMDOT_H
