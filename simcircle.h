#ifndef SIMCIRCLE_H
#define SIMCIRCLE_H

#include <QGraphicsItem>
#include <QPainter>

class simCircle : public QGraphicsItem
{
public:
  simCircle(qreal size);
  QRectF boundingRect() const;
  void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
  qreal s;
};

#endif // SIMCIRCLE_H
