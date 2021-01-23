#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <thread>
#include <station/station.h>
#include <QApplication>
#include <QMainWindow>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("MeteoStation");

    Station::Station* station = new Station::Station;
    station->show();

    station->Loop();

    return app.exec();
}
