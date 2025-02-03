

#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QList>
#include <QThread>
#include <QMessageBox>
#include <QFileDialog>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQuickView>
#include <QtQuickWidgets/QQuickWidget>
#include <Windows.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FTDI_Library/libMPSSE_spi.h"
#include "FTDI_Library/ftd2xx.h"
#include "radiolistener.h"
#include "Connection/Connection.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    telemetryListeningThread = new QThread();
    listeningTask = new RadioListener();
    dataParser = new CANDataParser;
    listeningTask->setDataParser(dataParser);

    ui->pushButton_Start->setEnabled(true);
    widget = new QQuickWidget;
    connection = new Connection;
}

MainWindow::~MainWindow()
{
    cleanListeningThread();

    delete telemetryListeningThread;
    delete listeningTask;
    delete dataParser;
    delete widget;
    delete connection;

    delete ui;
}


void MainWindow::prepareListeningThread()
{
    listeningTask->moveToThread(telemetryListeningThread);

    // Init of signals/slots which create, use and delete the thread
    connect(listeningTask, SIGNAL(workRequested()), telemetryListeningThread, SLOT(start()));
    connect(telemetryListeningThread, SIGNAL(started()), listeningTask, SLOT(listen()));
    connect(listeningTask, SIGNAL(finished()), telemetryListeningThread, SLOT(quit()), Qt::DirectConnection);
    connect(listeningTask, SIGNAL(gotFrame(Frame&)), listeningTask, SLOT(handleFrameReceived(Frame&)));

    // Init of actual thread
    telemetryListeningThread->wait();
    listeningTask->requestWork();
}

void MainWindow::cleanListeningThread()
{
    listeningTask->abort();
    telemetryListeningThread->wait();

    qDebug() << "Deleting thread and worker in Thread " << this->QObject::thread()->currentThreadId();
}

void MainWindow::on_pushButton_Search_clicked()
{
    FT_STATUS ftStatus;
    FT_DEVICE_LIST_INFO_NODE devices;
    uint32 channelCount = 0;

    //  Get available SPI channels
    ftStatus = SPI_GetNumChannels(&channelCount);

    if (ftStatus == FT_OK || channelCount == 0)
    {
        qDebug () << "Successfuly readed connected devices";
    }
    else
    {
        qDebug () << "Couldn't find any device";
    }

    // Clear UI
    ui->comboBox_FTDI_devices->clear();

    // If nothing was found, show it as an error and leave
    if(channelCount == 0)
    {
        ui->comboBox_FTDI_devices->addItem("None", QColor(QColorConstants::Red));
        return;
    }

    //  If channels were found, show them
    for(int i = 0; i < channelCount; i++)
    {
        SPI_GetChannelInfo(i, &devices);
        ui->comboBox_FTDI_devices->addItem(devices.Description);
    }

    // Enable start button
    ui->pushButton_Start->setEnabled(true);

    // Handle device selection
    auto deviceIndex = ui->comboBox_FTDI_devices->currentIndex();
    if(deviceIndex != 0)
    {
      ui->pushButton_Start->setEnabled(true);
    }
    else
    {
        QMessageBox::information(this, QString("Caution"), QString("Please select FTDI device first."));
    }
}



void MainWindow::on_pushButton_Start_clicked()
{
    if(!dataParser->openDatabase())
    {
        QMessageBox::information(this, QString("Caution"), QString("Please select database first."));
    }
    else
    {
        ui->pushButton_Start->setEnabled(false);
        prepareListeningThread();
    }

    this->close();
    prepareGraphicalInterface();
}

void MainWindow::prepareGraphicalInterface()
{
    QQmlApplicationEngine engine;

    widget->rootContext()->setContextProperty("connection", connection);

    const QUrl url(QStringLiteral("qrc:/Main.qml"));
    QObject::connect(&engine , &QQmlApplicationEngine::objectCreated,
                     QApplication::instance(), [url](QObject *obj, const QUrl &objUrl)
    {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);

    }, Qt::QueuedConnection);

    listeningTask->setConnection(connection);
}

void MainWindow::on_pushButton_Choose_clicked()
{
    QString databaseFilePath = QFileDialog::getOpenFileName(this, "Database File",
                                                            "C://", "*.dbc");
    ui->label_Database_Name->setText(databaseFilePath);
    dataParser->setDatabaseName(databaseFilePath);
}

