//Copyright 2015 Adam Quintero
//This program is distributed under the terms of the GNU General Public License.

#ifndef SIMSQUARE_H
#define SIMSQUARE_H

#include <QGraphicsItem>
#include <QPainter>

class simSquare : public QGraphicsItem
{
public:
  simSquare(qreal size = 100);
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
  qreal s;
};

#endif // SIMSQUARE_H
