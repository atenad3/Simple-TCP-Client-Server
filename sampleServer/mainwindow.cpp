#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonStart_clicked()
{
    //first socket created.
    m_pBoxServer= new helloServer(this);
    //If address is QHostAddress::Any, the server will listen on all network interfaces.
    bool success = m_pBoxServer->listen(QHostAddress::Any, quint16(ui->textEditPort->toPlainText().toInt()));
    if(!success)
    {
        addMessage("Server failed...");

    }
    else
    {
        addMessage("Server Started...");
    }
    qDebug() << m_pBoxServer->isListening();
    connect(m_pBoxServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
    connect(m_pBoxServer,SIGNAL(pendingConnectionAvailable()), this, SLOT(hasPendingConnections()));
    // qDebug() << "hasPendingConnections" << m_pBoxServer->hasPendingConnections();
}

void MainWindow::addMessage(QString Msg)
{
    qDebug() << Msg ;
    ui->textEditStatus->setText(Msg);
    qDebug() << "add message";
}

void MainWindow::newConnection()
{
    qDebug()<<"new connection";
}

void MainWindow::hasPendingConnections()
{
    qDebug() << "test 34";
}

void MainWindow::on_pushButtonSend_clicked()
{
    QString message = ui->textEditresponse->toPlainText().trimmed();
    if(!message.isEmpty())
    {
        // m_pBoxServer -> QIODevice::write(QString(message + " ").toUtf8());
        qDebug() <<"send2";
        m_pBoxServer->sendMessageToClients(message);
        // Clear out the input box so they can type something else:
        ui->textEditresponse->clear();
        // Put the focus back into the input box so they can type again:
        ui->textEditresponse->setFocus();
    }

}
