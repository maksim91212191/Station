#ifndef STATION_H
#define STATION_H

#include <QWidget>
#include <QString>
#include <QPalette>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
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

#define devIdTCA 0x70
#define devIdBME BME280_I2C_ADDRESS1

namespace Station {                        /*Station*/
    class Station : public QWidget {
        Q_OBJECT
    public:
        Station(QWidget* parent = nullptr);
        virtual ~Station();
        void LoopBME();

    signals:
        void NewBMEData(QString str);

    private:
        int*         BMENum;
        int          fdTCA;
        BME::BME280* bme280;
        std::FILE*   logs;
        QPalette     palBack;
        QHBoxLayout* layBME;
        QLabel*      labBMETags;
        QLabel*      labBMEInfo;
    };
}    /*Station*/

#endif
