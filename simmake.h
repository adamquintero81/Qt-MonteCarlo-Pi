#ifndef SIMMAKE_H
#define SIMMAKE_H

#include <QObject>
#include <QPointF>
#include <QDateTime>
#include <cmath>

//#include <QDebug>

class simMake : public QObject
{
  Q_OBJECT
public:
  explicit simMake(int high = 500, int low = 0, int threadID = 1);

signals:
  void innerDot(QPointF,int);
  void outerDot(QPointF,int);

public slots:
  void makeDot(int iterations,int,int,int,int);
  void clean();
  void init(int,int);

private:
  void maker(int iterations);
  QList<QPointF> inDots, outDots;
  int h, l, thread;
};

#endif // SIMMAKE_H
