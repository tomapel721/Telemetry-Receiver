#include "Connection.h"
#include <QUrl>
#include <QQmlComponent>
#include <QDebug>
#include <QQuickItem>

Connection::Connection(QObject *parent): QObject(parent)
{

}

Connection::~Connection()
{

}
void Connection::setTextHandler(QObject* textSignalsHandler) //QQmlApplicationEngine* engine
{
    textSignals = textSignalsHandler;
}

void Connection::setSpeedometerHandler(QObject *obj)
{
    speedometer = obj;
}

void Connection::changeText()
{
    // potem następnym krokiem będzie podpięcie tego do slotu i podpiecię z sygnałem
    if(textSignals)
    {
        textSignals->setProperty("text", "Ale jednak moje wlasne!");
    }
    else
    {
        qDebug() << "Error in component linking - no text field connected";
    }
}

void Connection::updateSpeed()
{
    if(speedometer)
    {
        speedometer->setProperty("value", 50);
    }
    else
    {
        qDebug() << "Error in component linking - no text field connected";
    }
}
