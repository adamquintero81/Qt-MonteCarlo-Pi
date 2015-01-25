//Copyright 2015 Adam Quintero
//This program is distributed under the terms of the GNU General Public License.

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QVariant>
#include <QList>
#include <QtAlgorithms>
#include <cmath>

#include "simdot.h"
#include "simsquare.h"
#include "simcircle.h"
#include "simthread.h"
#include "simmake.h"

//#include <QDebug>
#define M_PI 3.14159265358979323846

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
  simThread threadOne;
  simThread threadTwo;
  simThread threadThree;
  simThread threadFour;

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

signals:
  void simStart(int,int,int,int,int);
  void simInit(int,int);

public slots:
  void makeInnerDot(QPointF mark, int threadID);
  void makeOuterDot(QPointF mark, int threadID);

private slots:
  void on_runButton_pressed();
  void diamter(int);
  void iters(int);

  void on_analyzeButton_pressed();

private:
  Ui::MainWindow *ui;

  //Simulation Graphics
  void initSimView(QGraphicsView *view, QGraphicsScene *scene);
  QGraphicsScene *simScene1;
  QGraphicsScene *simScene2;
  QGraphicsScene *simScene3;
  QGraphicsScene *simScene4;
  QRectF simRect;
  int low;
  int high;
  int its;
  int firstRun;
  QList<QPointF> inDots1;
  QList<QPointF> outDots1;
  QList<QPointF> inDots2;
  QList<QPointF> outDots2;
  QList<QPointF> inDots3;
  QList<QPointF> outDots3;
  QList<QPointF> inDots4;
  QList<QPointF> outDots4;
  int gCounter;

  //simulation engine
  simMake *simulation1;
  simMake *simulation2;
  simMake *simulation3;
  simMake *simulation4;
  void initEngine();

  //estimates pi
  double estimate();
  double precision();

  //data structures
  QList<double> estimateList;
};

#endif // MAINWINDOW_H
