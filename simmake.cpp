//Copyright 2015 Adam Quintero
//This program is distributed under the terms of the GNU General Public License.

#include "simmake.h"

simMake::simMake(int high, int low, int threadID)
{
  h = high;
  l = low;
  thread = threadID;

}

void simMake::makeDot(int iterations, int active1, int active2, int active3, int active4)
{

  if(h > 0 && l < h && l >= 0)
    {
      if(thread == 1)
        if(active1 == 1)
          {
            maker(iterations);
          }

      if(thread == 2)
        if(active2 == 1)
          {
            maker(iterations);
          }

      if(thread == 3)
        if(active3 == 1)
          {
            maker(iterations);
          }

      if(thread == 4)
        if(active4 == 1)
          {
            maker(iterations);
          }
    }
}

void simMake::maker(int iterations)
{
  QDateTime local(QDateTime::currentDateTime());
  uint timeCount = local.toTime_t();
  uint seed = timeCount / uint(thread);
  //qDebug() << "seed =" << seed;
  //qDebug() << "thread = " << thread;
  qsrand(seed);
  //qDebug() << "random = " << qrand();

  for(int i = 0; i < iterations; i++)
    {
      int fractionX = (qrand() % ((h + 1) - l) + l) / 10000;
      int fractionY = (qrand() % ((h + 1) - l) + l) / 10000;

      int x = (qrand() % ((h + 1) - l) + l) + fractionX;
      int y = (qrand() % ((h + 1) - l) + l) + fractionY;
      int middle = h/2;
      QPointF mark(x,y);
      if( pow(x - middle, 2) + pow(y - middle, 2) < pow(middle, 2) )
        {
          inDots.append(mark);
          emit innerDot(mark,thread);
        }
      else
        {
          outDots.append(mark);
          emit outerDot(mark,thread);
        }
    }
}

void simMake::clean()
{
  inDots.clear();
  outDots.clear();
}

void simMake::init(int high, int low)
{
  h = high;
  l = low;
}
