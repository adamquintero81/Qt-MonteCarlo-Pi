#ifndef SIMTHREAD_H
#define SIMTHREAD_H

#include <QThread>

class simThread : public QThread
{
  Q_OBJECT
public:
  explicit simThread(QObject *parent = 0);

signals:

public slots:

protected:
  void run();
};

#endif // SIMTHREAD_H
