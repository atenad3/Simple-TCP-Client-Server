#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"helloserver.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class helloServer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addMessage(QString Msg);
    //the pointer perform such as global var?
    helloServer* m_pBoxServer;

private slots:
    void on_pushButtonStart_clicked();
    void newConnection();
    void hasPendingConnections();
    void on_pushButtonSend_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
