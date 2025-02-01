/* system includes */
#include "mainwindow.h"
#include "ui_mainwindow.h"
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

/* external includes */
#include <Windows.h>

/* own includes */
#include "FTDI_Library/libMPSSE_spi.h"
#include "FTDI_Library/ftd2xx.h"
#include "radiolistener.h"
#include "Connection/Connection.h"

// WAŻNE - trzeba z poziomu UI zrobić żeby nie dało się odpalić telemetrii bez wybranej bazy !



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
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

    // Inicjalizacja slotów/sygnałów które tworzą, operują i usuwają wątek
    connect(listeningTask, SIGNAL(workRequested()), telemetryListeningThread, SLOT(start()));
    connect(telemetryListeningThread, SIGNAL(started()), listeningTask, SLOT(listen()));
    connect(listeningTask, SIGNAL(finished()), telemetryListeningThread, SLOT(quit()), Qt::DirectConnection);
    connect(listeningTask, SIGNAL(gotFrame(Frame&)), listeningTask, SLOT(handleFrameReceived(Frame&)));

    // Inicjalizacja wątku
    telemetryListeningThread->wait();
    listeningTask->requestWork();
}

void MainWindow::cleanListeningThread()
{
    listeningTask->abort();
    telemetryListeningThread->wait();

    qDebug()<<"Deleting thread and worker in Thread "<<this->QObject::thread()->currentThreadId();
}

void MainWindow::on_pushButton_Search_clicked()
{
    FT_STATUS ftStatus;
    FT_DEVICE_LIST_INFO_NODE devices;
    uint32 channelCount = 0;

    ftStatus = SPI_GetNumChannels(&channelCount);

    if (ftStatus == FT_OK || channelCount == 0)
    {
         qDebug () << "Successfuly readed connected devices";
    }
    else
    {
        qDebug () << "Couldn't find any device";
    }

    ui->comboBox_FTDI_devices->clear();
    if(channelCount == 0)
    {
        ui->comboBox_FTDI_devices->addItem("None", QColor(QColorConstants::Red));
    }
    for(int i = 0; i < channelCount; i++)
    {
        SPI_GetChannelInfo(i, &devices);
        ui->comboBox_FTDI_devices->addItem(devices.Description);
    }
    ui->pushButton_Start->setEnabled(true);
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

//    ui->pushButton_Start->setEnabled(true);
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

    //QQmlComponent* textBoxComponent = new QQmlComponent(widget->engine(), QStringLiteral("qrc:/Main.qml"));
    QQmlComponent* textBoxComponent = new QQmlComponent(widget->engine(), QStringLiteral("qrc:/Main.qml"));
    QObject* textBoxObject = textBoxComponent->create();
    //QObject* textSignals = textBoxObject->findChild<QObject*>("receivedSignals");
    QObject* obj = (QObject*) widget->rootObject();
    //QObject* speedometerSignals = obj->findChild<QObject*>("speedometer");
    //textBoxObject->ch
    //connection->setTextHandler(textSignals)
    //connection->setSpeedometerHandler(speedometerSignals);
    listeningTask->setConnection(connection);
    // QApplication::allWindows().
}

void MainWindow::on_pushButton_Choose_clicked()
{
    QString databaseFilePath = QFileDialog::getOpenFileName(this, "Database File",
                                                            "C://", "*.dbc");
    ui->label_Database_Name->setText(databaseFilePath);
    dataParser->setDatabaseName(databaseFilePath);
}

