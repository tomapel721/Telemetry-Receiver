#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/*
 * mainwindow.hpp
 *
 *  Created on: March 1, 2022
 *     Company: Polsl Racing
 * Departament: Electronics Team
 *      Author: Tomasz Pelan
 */

#include <QMainWindow>
#include <QThread>
#include <KVASER/CAN_Data_Parser/CANDataParser.h>
#include <QQuickWidget>
#include <QQmlApplicationEngine>

#include "radiolistener.h"
#include "Connection/Connection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    /**
     *  Method which prepares radio listening thread to work
     */
    void prepareListeningThread();

    /**
     *  Method is cleaning after radio listening thread
     */
    void cleanListeningThread();

    /**
     *  Method prepares the front-end part of telemetry GUI after start
     */
    void prepareGraphicalInterface();

private slots:

    void on_pushButton_Search_clicked();

    void on_pushButton_Start_clicked();

    void on_pushButton_Choose_clicked();

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    /** Widget handle */
    QQuickWidget* widget;

    /** Connection handle */
    Connection* connection;

    /** UI handle */
    Ui::MainWindow *ui;

    /** Thread object which will represent listening thread */
    QThread* telemetryListeningThread;

    /** Object which contains methods which will be resposible for actual listening */
    RadioListener* listeningTask;

    /** Object which contains methods which will be resposible for CAN data parsing and processing */
    CANDataParser* dataParser;
    /** Variable which stores info if telemetry system has been started */
    bool isTelemetryStarted = false;
};
#endif // MAINWINDOW_H
