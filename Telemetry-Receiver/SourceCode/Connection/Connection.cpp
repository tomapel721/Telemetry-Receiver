/*
 * Connection.cpp
 *
 *  Created on: March 1, 2022
 *     Company: Polsl Racing
 * Departament: Electronics Team
 *      Author: Tomasz Pelan
 */

#include <QUrl>
#include <QQmlComponent>
#include <QDebug>
#include <QQuickItem>

#include "Connection.h"

Connection::Connection(QObject *parent): QObject(parent)
{
}

Connection::~Connection()
{
}
void Connection::setTextHandler(QObject* textSignalsHandler)
{
    textSignals = textSignalsHandler;
}

void Connection::setSpeedometerHandler(QObject *obj)
{
    speedometer = obj;
}

void Connection::changeText()
{
    if(!textSignals)
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
