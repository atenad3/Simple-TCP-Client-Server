#include "helloserver.h"
#include <QTcpSocket>


helloServer::helloServer(MainWindow* pHelloServer, QObject *parent) :QTcpServer(parent)
{
    m_pHelloWindow = pHelloServer;
}

void helloServer::incomingConnection(qintptr socketfd)
{
    // the second socket for echange the data.
    QTcpSocket *client = new QTcpSocket(this);
    // socket = new QTcpSocket(this);
    qDebug() << "client...";
    client->setSocketDescriptor(socketfd);
    clients.insert(client);

    // "::ffff:127.0.0.1" simply represents the IPv4 loopback address "127.0.0.1" in IPv6-compatible format.
    qDebug() << "client->peerAddress()" << client ->peerAddress();
    m_pHelloWindow->addMessage("New client from: "+ client->peerAddress().toString());

    connect(client, SIGNAL(readyRead()), this, SLOT(onNewData()));
    connect(client, SIGNAL(disconnected()), this, SLOT(disconnected()));
}


void helloServer::onNewData()
{
    //indicate the object that send the signal.
    QTcpSocket *client = (QTcpSocket*)sender();
    qDebug() << client->canReadLine();
    QByteArray readData = client->readAll();
    qDebug() << readData;
    // remove space from tail or frist of message.
    QString line = QString::fromUtf8(readData).trimmed();
    m_pHelloWindow -> addMessage(line);
}

void helloServer::sendMessageToClients(const QString &message) {
    // Loop through all connected clients and send the message
    for(QTcpSocket *client : qAsConst(clients)) {
        client->write(message.toUtf8());
    }
}

void helloServer::disconnected()
{
    QTcpSocket *client = (QTcpSocket*)sender();
    qDebug() <<"client disconnected: " << client -> peerAddress().toString();
    clients.remove(client);
}
