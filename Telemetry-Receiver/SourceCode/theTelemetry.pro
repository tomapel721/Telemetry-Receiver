QT += core gui
QT += serialport
QT += quick widgets
QT += charts
QT += quickcontrols2
QT += quickwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    Connection/Connection.cpp \
    KVASER/CAN_Data_Parser/CANDataParser.cpp \
    NRF24/Sources/NRF24.cpp \
    main.cpp \
    mainwindow.cpp \
    radiolistener.cpp

HEADERS += \
    CAN_Frame/Frame.h \
    Connection/Connection.h \
    FTDI_Library/WinTypes.h \
    FTDI_Library/ftd2xx.h \
    FTDI_Library/libMPSSE_spi.h \
    KVASER/CAN_Data_Parser/CANDataParser.h \
    KVASER/CAN_Data_Parser/CanFrameIDs.hpp \
    NRF24/Headers/NRF24.hpp \
    NRF24/Headers/NRF24_Defs.hpp \
    mainwindow.h \
    radiolistener.h

FORMS += \
    mainwindow.ui

win32: LIBS += "$$PWD\FTDI_Library\libMPSSE.lib"
win32: LIBS += "-$$PWD\FTDI_Library\libMPSSE.dll"

INCLUDEPATH += "C:\Kvaser\INC"

win32: LIBS += -L"$$PWD\KVASER\x64" -lkvaDbLib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    QML/qml.qrc

DISTFILES += \
    QML/BatteryTemperature.qml \
    QML/DashboardGaugeStyle.qml \
    QML/EngineTemperature.qml \
    QML/Gauges.qml \
    QML/InverterTemperature.qml \
    QML/Plots.qml \
    QML/RPM_Gauge_Style.qml \
    QML/main.qml \
    QML/powerConsumption.qml \


