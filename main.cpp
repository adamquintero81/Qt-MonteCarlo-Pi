//Copyright 2015 Adam Quintero
//This program is distributed under the terms of the GNU General Public License.

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  //qRegisterMetaType< QList<QPointF> >("QList<QPointF>");
  MainWindow w;
  w.show();

  return a.exec();
}
