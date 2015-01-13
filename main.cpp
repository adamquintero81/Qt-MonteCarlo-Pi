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
