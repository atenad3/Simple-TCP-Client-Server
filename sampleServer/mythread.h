#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

signals:
    // notify to the main thread when we're done
    // void Result(const QList<QVariant> &data);
    void Result(double Number);

protected:
    void run();

};

#endif // MYTHREAD_H
