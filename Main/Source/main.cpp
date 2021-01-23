#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <station/station.h>
#include <QApplication>

int main(int argc, char* argv[]) {
    try {
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("MeteoStation");

    Station::Station* station = new Station::Station;
    station->show();

    station->LoopBME();

    return app.exec();
    } catch (std::exception& ex) {
            return -1;
        }
}
