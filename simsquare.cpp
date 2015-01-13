#include "simsquare.h"

simSquare::simSquare(qreal size)
{
  s = size;
}

QRectF simSquare::boundingRect() const
{
  return QRectF(qreal(0), qreal(0), s, s);
}

void simSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  QPen simPen(QColor(Qt::yellow), qreal(0));
  painter->setPen(simPen);
  painter->drawRect(QRectF(qreal(0), qreal(0), s, s));
}
