#include "mythread.h"
#include "mysolver.h"
#include<QDebug>

MyThread::MyThread(QObject *parent)
    : QThread{parent}
{
    qDebug() << "MyThread()";
}

void MyThread::run()
{
    // time consumer
    qDebug() << "Task started";

    MySolver *newSolver = new MySolver();
    newSolver -> setRequirement();
    newSolver ->setSolver("cplex");
    newSolver ->readModel("/home/atefe/Networking/sampleNet1/sampleServer/test1.mod");
    newSolver ->solve();
    double d = newSolver ->getVariableValue("x1");
    qDebug() << "Task done '\n"<< "x1 is :" ;
    emit Result(d);
}
