#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <thread>
#include <chrono>


Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    qDebug()<<"tcp socket";
    m_pClientsocket= new QTcpSocket(this);
    // std::this_thread::sleep_for(std::chrono::seconds(1)); // This will pause the program execution for 1 second
    //show ui with setup.
    ui->setupUi(this);
    qDebug()<<"ui";
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    m_pClientsocket->connectToHost(ui->textEditIP->toPlainText(),quint16(ui->textEditPort->toPlainText().toInt()));
    // qDebug() << "1" <<m_pClientsocket->state();
    connect(m_pClientsocket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)),this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(m_pClientsocket, SIGNAL(connected()), this, SLOT(connected()));
    connect(m_pClientsocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(m_pClientsocket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    // qDebug()<<"on push botton clicked";
    // qDebug() << "2" <<m_pClientsocket->state();
}


void Dialog::on_pushButton_2_clicked()
{
    QString message = ui->textEditMessage->toPlainText().trimmed();
    // Only send the text to the chat server if it's not empty:
    if(!message.isEmpty())
    {
        m_pClientsocket->write(QString(message + " ").toUtf8());
    }
    // Clear out the input box so they can type something else:
    ui->textEditMessage->clear();

    // Put the focus back into the input box so they can type again:
    ui->textEditMessage->setFocus();
}


void Dialog::displayError(QAbstractSocket::SocketError socketError){
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            break;

        case QAbstractSocket::HostNotFoundError:
            QMessageBox::information(this, tr("Fortune Client"),
                                     tr("The host was not found. Please check the "
                                        "host name and port settings."));
            break;

        case QAbstractSocket::ConnectionRefusedError:
            QMessageBox::information(this, tr("Fortune Client"),
                                     tr("The connection was refused by the peer. "
                                        "Make sure the fortune server is running, "
                                        "and check that the host name and port "
                                        "settings are correct."));
            break;

        default:
            QMessageBox::information(this, tr("Fortune Client"),
                                     tr("The following error occurred: %1.")
                                         .arg(m_pClientsocket->errorString()));
    }
}


void Dialog::connected()
{
    qDebug() << "Client connected event";
    // qDebug() << "4" << m_pClientsocket->state();
    // qDebug() << m_pClientsocket ->isValid();
}


void Dialog::disconnected()
{
    qDebug() << "Client disconnected";
}

void Dialog::readyRead()
{
    qDebug() << "data from server in readyRead slot";
    // qDebug() << m_pClientsocket->canReadLine();
    QByteArray readData = m_pClientsocket->readAll();
    // qDebug() << readData;
    // remove space from tail or frist of message.
    QString line = QString::fromUtf8(readData).trimmed();
    addMessage(line);
}

void Dialog::addMessage(QString Msg)
{
    qDebug() << Msg ;
    ui->receivedMessage->setText(Msg);
    qDebug() << "add message in dilog.cpp";
}
