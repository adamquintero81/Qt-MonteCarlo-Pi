//Copyright 2015 Adam Quintero
//This program is distributed under the terms of the GNU General Public License.

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  //connect signals and slots
  connect(ui->setDiameter, SIGNAL(valueChanged(int)), this, SLOT(diamter(int)));
  connect(ui->setIts, SIGNAL(valueChanged(int)), this, SLOT(iters(int)));

  //init lcd displays
  ui->estimateLCD->setPalette(Qt::darkGreen);
  ui->accuracyLCD->setPalette(Qt::darkGreen);

  //init thread active checkboxes
  ui->activeThread1->setChecked(true);
  ui->activeThread2->setChecked(true);
  ui->activeThread3->setChecked(true);
  ui->activeThread4->setChecked(true);

  //init simView
  simScene1 = new QGraphicsScene();
  simScene2 = new QGraphicsScene();
  simScene3 = new QGraphicsScene();
  simScene4 = new QGraphicsScene();

  low = 0;
  high = ui->setDiameter->value();
  its = ui->setIts->value();
  gCounter = 1;

  initSimView(ui->simView1, simScene1);
  initSimView(ui->simView2, simScene2);
  initSimView(ui->simView3, simScene3);
  initSimView(ui->simView4, simScene4);

  //init sim engine
  initEngine();
}

MainWindow::~MainWindow()
{
  delete ui;

  threadOne.quit();
  threadOne.wait();
  threadTwo.quit();
  threadTwo.wait();
  threadThree.quit();
  threadThree.wait();
  threadFour.quit();
  threadFour.wait();

  delete simScene1;
  delete simScene2;
  delete simScene3;
  delete simScene4;

  delete simulation1;
  delete simulation2;
  delete simulation3;
  delete simulation4;

}

void MainWindow::initEngine()
{
  //setup simulation threads
  simulation1 = new simMake(high, low, 1);
  simulation1->moveToThread(&threadOne);
  connect(&threadOne, SIGNAL(finished()), simulation1, SLOT(deleteLater()), Qt::QueuedConnection);
  connect(this, SIGNAL(simStart(int,int,int,int,int)), simulation1, SLOT(makeDot(int,int,int,int,int)), Qt::QueuedConnection);
  connect(simulation1, SIGNAL(innerDot(QPointF,int)), this, SLOT(makeInnerDot(QPointF,int)), Qt::QueuedConnection);
  connect(simulation1, SIGNAL(outerDot(QPointF,int)), this, SLOT(makeOuterDot(QPointF,int)), Qt::QueuedConnection);
  connect(this, SIGNAL(simInit(int,int)), simulation1, SLOT(init(int,int)),Qt::QueuedConnection);
  threadOne.start();

  simulation2 = new simMake(high, low, 2);
  simulation2->moveToThread(&threadTwo);
  connect(&threadTwo, SIGNAL(finished()), simulation2, SLOT(deleteLater()), Qt::QueuedConnection);
  connect(this, SIGNAL(simStart(int,int,int,int,int)), simulation2, SLOT(makeDot(int,int,int,int,int)), Qt::QueuedConnection);
  connect(simulation2, SIGNAL(innerDot(QPointF,int)), this, SLOT(makeInnerDot(QPointF,int)), Qt::QueuedConnection);
  connect(simulation2, SIGNAL(outerDot(QPointF,int)), this, SLOT(makeOuterDot(QPointF,int)), Qt::QueuedConnection);
  connect(this, SIGNAL(simInit(int,int)), simulation2, SLOT(init(int,int)),Qt::QueuedConnection);
  threadTwo.start();

  simulation3 = new simMake(high, low, 3);
  simulation3->moveToThread(&threadThree);
  connect(&threadThree, SIGNAL(finished()), simulation3, SLOT(deleteLater()), Qt::QueuedConnection);
  connect(this, SIGNAL(simStart(int,int,int,int,int)), simulation3, SLOT(makeDot(int,int,int,int,int)), Qt::QueuedConnection);
  connect(simulation3, SIGNAL(innerDot(QPointF,int)), this, SLOT(makeInnerDot(QPointF,int)), Qt::QueuedConnection);
  connect(simulation3, SIGNAL(outerDot(QPointF,int)), this, SLOT(makeOuterDot(QPointF,int)), Qt::QueuedConnection);
  connect(this, SIGNAL(simInit(int,int)), simulation3, SLOT(init(int,int)),Qt::QueuedConnection);
  threadThree.start();

  simulation4 = new simMake(high, low, 4);
  simulation4->moveToThread(&threadFour);
  connect(&threadFour, SIGNAL(finished()), simulation4, SLOT(deleteLater()), Qt::QueuedConnection);
  connect(this, SIGNAL(simStart(int,int,int,int,int)), simulation4, SLOT(makeDot(int,int,int,int,int)), Qt::QueuedConnection);
  connect(simulation4, SIGNAL(innerDot(QPointF,int)), this, SLOT(makeInnerDot(QPointF,int)), Qt::QueuedConnection);
  connect(simulation4, SIGNAL(outerDot(QPointF,int)), this, SLOT(makeOuterDot(QPointF,int)), Qt::QueuedConnection);
  connect(this, SIGNAL(simInit(int,int)), simulation4, SLOT(init(int,int)),Qt::QueuedConnection);
  threadFour.start();

}

void MainWindow::initSimView(QGraphicsView *view, QGraphicsScene *scene)
{
  scene->clear();
  //Simulation Graphics
  //setup simulation scene/view
  scene->setBackgroundBrush(Qt::lightGray);
  view->setRenderHint(QPainter::HighQualityAntialiasing);
  view->setScene(scene);


  //simulation Square
  simRect.setX(qreal(0));
  simRect.setY(qreal(0));
  simRect.setWidth(high);
  simRect.setHeight(high);
  simSquare *square = new simSquare(qreal(high));
  scene->addItem(square);

  //simulation circle
  simCircle *circle = new simCircle(qreal(high));
  scene->addItem(circle);
}

void MainWindow::makeInnerDot(QPointF mark, int threadID)
{
  double progress;
  if(threadID == 1)
    {
      inDots1.append(mark);
      simDot *dot = new simDot(mark,0);
      simScene1->addItem(dot);
      int totalDots = inDots1.size() + outDots1.size();
      progress = ((double)totalDots / its)*100;
      ui->simBar1->setValue(progress);
    }
  else
    if(threadID == 2)
      {
        inDots2.append(mark);
        simDot *dot = new simDot(mark,0);
        simScene2->addItem(dot);
        int totalDots = inDots2.size() + outDots2.size();
        progress = ((double)totalDots / its)*100;
        ui->simBar2->setValue(progress);
      }
    else
      if(threadID == 3)
        {
          inDots3.append(mark);
          simDot *dot = new simDot(mark,0);
          simScene3->addItem(dot);
          int totalDots = inDots3.size() + outDots3.size();
          progress = ((double)totalDots / its)*100;
          ui->simBar3->setValue(progress);
        }
      else
        if(threadID == 4)
          {
            inDots4.append(mark);
            simDot *dot = new simDot(mark,0);
            simScene4->addItem(dot);
            int totalDots = inDots4.size() + outDots4.size();
            progress = ((double)totalDots / its)*100;
            ui->simBar4->setValue(progress);
          }
        else
          {
            //qDebug() << "main: invalid thread ID = " << threadID;
          }
  ui->estimateLCD->display(estimate());
  if(progress >= double(100.0))
    ui->accuracyLCD->display(precision());
}

void MainWindow::makeOuterDot(QPointF mark, int threadID)
{
  double progress;
  if(threadID == 1)
    {
      outDots1.append(mark);
      simDot *dot = new simDot(mark,1);
      simScene1->addItem(dot);
      int totalDots = inDots1.size() + outDots1.size();
      progress = ((double)totalDots / its)*100;
      ui->simBar1->setValue(progress);
    }
  else
    if(threadID == 2)
      {
        outDots2.append(mark);
        simDot *dot = new simDot(mark,1);
        simScene2->addItem(dot);
        int totalDots = inDots2.size() + outDots2.size();
        progress = ((double)totalDots / its)*100;
        ui->simBar2->setValue(progress);
      }
    else
      if(threadID == 3)
        {
          outDots3.append(mark);
          simDot *dot = new simDot(mark,1);
          simScene3->addItem(dot);
          int totalDots = inDots3.size() + outDots3.size();
          progress = ((double)totalDots / its)*100;
          ui->simBar3->setValue(progress);
        }
      else
        if(threadID == 4)
          {
            outDots4.append(mark);
            simDot *dot = new simDot(mark,1);
            simScene4->addItem(dot);
            int totalDots = inDots4.size() + outDots4.size();
            progress = ((double)totalDots / its)*100;
            ui->simBar4->setValue(progress);
          }
        else
          {
            //qDebug() << "main: invalid thread ID = " << threadID;
          }
  ui->estimateLCD->display(estimate());
  if(progress >= double(100.0))
    ui->accuracyLCD->display(precision());
}

void MainWindow::on_runButton_pressed()
{
  low = 0;
  high = ui->setDiameter->value();
  its = ui->setIts->value();

  //clear
  on_analyzeButton_pressed();

  //reinitialize sim parameters
  emit simInit(high,low);

  //begin simulations
  int a1,a2,a3,a4;
  if(ui->activeThread1->isChecked())
    {
      a1 = 1;
    }
  else
    {
      a1 = 0;
    }
  if(ui->activeThread2->isChecked())
    {
      a2 = 1;
    }
  else
    {
      a2 = 0;
    }
  if(ui->activeThread3->isChecked())
    {
      a3 = 1;
    }
  else
    {
      a3 = 0;
    }
  if(ui->activeThread4->isChecked())
    {
      a4 = 1;
    }
  else
    {
      a4 = 0;
    }
  //qDebug() << "checked: a1=" << a1 << " a2=" << a2 << " a3=" << a3 << " a4=" << a4;
  emit simStart(its,a1,a2,a3,a4);
}

void MainWindow::diamter(int d)
{
  high = d;
  initSimView(ui->simView1, simScene1);
  initSimView(ui->simView2, simScene2);
  initSimView(ui->simView3, simScene3);
  initSimView(ui->simView4, simScene4);
}

void MainWindow::iters(int i)
{
  its = i;
}

double MainWindow::estimate()
{
  double allDots =
      outDots1.size() + inDots1.size()
      + outDots2.size() + inDots2.size()
      + outDots3.size() + inDots3.size()
      + outDots4.size() + inDots4.size();

  double circleDots =
      inDots1.size()
      + inDots2.size()
      + inDots3.size()
      + inDots4.size();

  double ratio = circleDots / allDots;
  double pi = ratio * double(4.0);
  //qDebug() << pi;
  estimateList.append(pi);
  return pi;
}

double MainWindow::precision()
{
  double uncertaintyInterval = 0.0;
  if(estimateList.size() > 0)
    {
      if(estimateList.size() == 1)
        {
          uncertaintyInterval = 0;
        }
      else
        {
          double sum, max, min;
          sum = max = min = 0.0;
          qSort(estimateList);

          for(int i = 0; i < estimateList.size(); i++)
            {
              double test;
              test = QVariant(estimateList.at(i)).toDouble();
              sum += test;
            }
          min = estimateList.first();
          max = estimateList.last();
          double size = QVariant(estimateList.size()).toDouble();
          double mean = sum / size;
          double maxTerm, minTerm;
          maxTerm = max - mean;
          minTerm = mean - min;
          uncertaintyInterval = maxTerm + minTerm;
        }
    }
  //qDebug() << uncertaintyInterval;
  return uncertaintyInterval;
}


void MainWindow::on_analyzeButton_pressed()
{  
  simulation1->clean();
  simulation2->clean();
  simulation3->clean();
  simulation4->clean();

  inDots1.clear();
  inDots2.clear();
  inDots3.clear();
  inDots4.clear();

  outDots1.clear();
  outDots2.clear();
  outDots3.clear();
  outDots4.clear();

  ui->simBar1->setValue(0);
  ui->simBar2->setValue(0);
  ui->simBar3->setValue(0);
  ui->simBar4->setValue(0);

  ui->estimateLCD->display(0);
  ui->accuracyLCD->display(0);

  initSimView(ui->simView1, simScene1);
  initSimView(ui->simView2, simScene2);
  initSimView(ui->simView3, simScene3);
  initSimView(ui->simView4, simScene4);

  estimateList.clear();
}
