#include "simdot.h"

simDot::simDot(QPointF dot, int color)
{
  pDot = dot;
  pColor = color;
}

QRectF simDot::boundingRect() const
{
  return QRectF(pDot.x(), pDot.y(), qreal(1), qreal(1));
}

void simDot::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  if(pColor == 0)
    {
      QPen simPen(QColor(Qt::red), qreal(0));
      painter->setPen(simPen);
      painter->drawEllipse(QRectF(pDot.x(), pDot.y(), qreal(1), qreal(1)));
    }
  else
    if(pColor == 1)
      {
        QPen simPen(QColor(Qt::blue), qreal(0));
        painter->setPen(simPen);
        painter->drawEllipse(QRectF(pDot.x(), pDot.y(), qreal(1), qreal(1)));
      }
}
