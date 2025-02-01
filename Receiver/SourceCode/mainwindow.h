#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QThread>
#include "radiolistener.h"
#include <KVASER/CAN_Data_Parser/CANDataParser.h>
#include <QQuickWidget>
#include <QQmlApplicationEngine>
#include "Connection/Connection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    bool isTelemetryStarted = false;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    QQuickWidget* widget;

    Connection* connection;

    Ui::MainWindow *ui;
    /**
     * @brief Thread object which will represent listening thread
     */
    QThread* telemetryListeningThread;
    /**
     * @brief Object which contains methods which will be resposible for actual listening
     */
    RadioListener* listeningTask;
    /**
     * @brief Object which contains methods which will be resposible for CAN data parsing and processing
     */
    CANDataParser* dataParser;

private:

    /* Method which prepares radio listening thread to work */
    void prepareListeningThread();

    /* Method is cleaning after radio listening thread */
    void cleanListeningThread();

    /* Method prepares the front-end part of telemetry GUI after start */
    void prepareGraphicalInterface();

private slots:

    void on_pushButton_Search_clicked();

    void on_pushButton_Start_clicked();

    void on_pushButton_Choose_clicked();
};
#endif // MAINWINDOW_H
