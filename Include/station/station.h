#ifndef STATION_H
#define STATION_H

// #pragma once

#include <QWidget>
#include <QMainWindow>
#include <QString>
#include <QPalette>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QThread>
#include <bme/bme280.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <cstdio>
#include <iostream>
#include <exception>
#include <thread>
#include <cstdint>
#include <time.h>
#include <math.h>
#include <string.h>
#include <station/resources.h>
#include <station/managerRemote.h>

#define devIdTCA 0x70
#define devIdBME BME280_I2C_ADDRESS1

namespace Station {                        /*Station*/

class StationBME : public QObject {
    Q_OBJECT
public:
    StationBME();
    virtual ~StationBME();
public slots:
    void Loop();

signals:
    void NewBMEData(QString str);

private:
    int*         BMENum;
    int          fdTCA;
    BME::BME280* bme280;
    std::FILE*   logs;
};


class UI : public QWidget {
    Q_OBJECT
public:
    UI(QWidget* parent = nullptr);

public slots:
    void UpdateBMEInfo(QString str);
    void UpdateRemoteInfo(QString str);

private:
    QHBoxLayout* layBME;
    QLabel*      labBMETags;
    QLabel*      labBMEInfo;
    QLabel*      labRemote;
};


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();
    void Loop();

private:
    UI*            ui;
    StationBME*    widBME;
    ManagerRemote* managerRemote;
    QThread        thrBME;
    QThread        thrRemote;
    QPalette       palBack;
};

}    /*Station*/

#endif
