//Copyright 2015 Adam Quintero
//This program is distributed under the terms of the GNU General Public License.

#include "simthread.h"

simThread::simThread(QObject *parent) :
  QThread(parent)
{
}

void simThread::run()
{
  exec();
}
