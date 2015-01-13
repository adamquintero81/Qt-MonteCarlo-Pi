#include "simthread.h"

simThread::simThread(QObject *parent) :
  QThread(parent)
{
}

void simThread::run()
{
  exec();
}
