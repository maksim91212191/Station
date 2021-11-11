#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <thread>
#include <station/station.h>
#include <QApplication>
#include <QMainWindow>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("MeteoStation");

    Station::MainWindow* stationWindow = new Station::MainWindow;
    stationWindow->show();

    stationWindow->Loop();
    return app.exec();
}
