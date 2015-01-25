//Copyright 2015 Adam Quintero
//This program is distributed under the terms of the GNU General Public License.

#include "simcircle.h"

simCircle::simCircle(qreal size)
{
  s = size;
}

QRectF simCircle::boundingRect() const
{
  return QRectF(qreal(0), qreal(0), s, s);
}

void simCircle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  QPen simPen(QColor(Qt::yellow), qreal(0));
  painter->setPen(simPen);
  painter->drawEllipse(QRectF(qreal(0), qreal(0), s, s));
}
