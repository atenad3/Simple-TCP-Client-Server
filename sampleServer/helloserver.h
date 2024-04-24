#ifndef HELLOSERVER_H
#define HELLOSERVER_H

#include <QTcpServer>
#include "mainwindow.h"
#include <QIODevice>
#include <mythread.h>


class MainWindow;
class helloServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit helloServer(MainWindow* pHelloServer, QObject *parent = nullptr);
    MainWindow* m_pHelloWindow;
    void sendMessageToClients(const QString &message);

private slots:
    void onNewData();
    void disconnected();


protected:
    void incomingConnection(qintptr socketfd);

private:
    QSet<QTcpSocket*> clients;
    QTcpSocket *socket;
};

#endif // HELLOSERVER_H
