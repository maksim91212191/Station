#include <station/station.h>

namespace Station {                  /*Station*/
    StationBME::StationBME() {

        char* device0 = "/dev/i2c-1";
        BMENum = new int(3);
        BMENum[0] = 2;
        BMENum[1] = 4;
        BMENum[2] = 7;

        if (!(logs = std::fopen("logsBME.txt", "w"))) {
            std::cout << "Logs error\n";
        }

        try {
            fdTCA = wiringPiI2CSetup(devIdTCA);

            for (size_t i = 0; i < 3; ++i) {
                std::fprintf(logs, "Dev num  : %d\n", BMENum[i]);
                if (wiringPiI2CWrite(fdTCA, 1 << BMENum[i]) < 0) {
                    std::fprintf(logs, "Multiplexer channel changing error\n");
                    throw std::runtime_error("Multiplexer channel changing error");
                }
                if (i == 0) {
                    bme280 = new BME::BME280(device0, devIdBME);
                }
                int fdBME = bme280->init();
                bme280->reset();

                if (fdBME < 0) {
                    fprintf(logs, "Device not found");
                    throw std::runtime_error("Device not found");
                }

                std::fprintf(logs, "fd       : 0x%02x\n", fdBME);
                std::fprintf(logs, "chip id  : 0x%02x\n", bme280 ->getChipId());
                std::fprintf(logs, "chip ver : 0x%02x\n", bme280->getChipVersion());

                bme280->reset();
                bme280->setPowerMode(BME280_NORMAL_MODE);
                bme280->setTemperatureOversampling(BME280_ULTRAHIGHRESOLUTION_OVERSAMP_TEMPERATURE);
                bme280->setPressureOversampling(BME280_ULTRAHIGHRESOLUTION_OVERSAMP_PRESSURE);
                bme280->setHumidityOversampling(BME280_ULTRAHIGHRESOLUTION_OVERSAMP_HUMIDITY);
                bme280->setIrrFilter(BME280_FILTER_COEFF_16);
                bme280->setStandbyTime(BME280_STANDBY_TIME_250_MS);

                std::fprintf(logs, "---------------\n");
                std::fprintf(logs, "pw mode  : 0x%02x\n", bme280->getPowerMode());
                std::fprintf(logs, "osrs_p   : 0x%02x\n", bme280->getPressureOversampling());
                std::fprintf(logs, "osrs_t   : 0x%02x\n", bme280->getTemperatureOversampling());
                std::fprintf(logs, "osrs_h   : 0x%02x\n", bme280->getHumidityOversampling());
                std::fprintf(logs, "---------------\n");
                std::fprintf(logs, "filter   : 0x%02x\n", bme280->getIrrFilter());
                std::fprintf(logs, "t_sb     : 0x%02x\n", bme280->getStandbyTime());
                std::fprintf(logs, "---------------\n");
                std::fprintf(logs, "spi3w sts: 0x%02x\n", bme280->getSpi3w());
                std::fprintf(logs, "measuring: 0x%02x\n", bme280->getMeasuringStatus());
                std::fprintf(logs, "im_update: 0x%02x\n", bme280->getImUpdateStatus());
                std::fprintf(logs, "---------------\n");
            }

        } catch (std::exception& e) {
            fprintf(logs, "%s\n", e.what());
        }
        std::fclose(logs);
    }

    StationBME::~StationBME() {
        delete[] BMENum;
        delete bme280;
    }

    void StationBME::Loop() {

        if (!(logs = std::fopen("logsBME.txt", "a"))) {
            std::cout << "Logs error\n";
        }

        while (1) {
            delay(1000);

            float pressure = 0;
            float humidity = 0;
            float temperature = 0;

            for (size_t i = 0; i < 3; ++i) {
                if (wiringPiI2CWrite(fdTCA, 1 << BMENum[i]) < 0) {
                    std::fprintf(logs, "Dev num  : %d\nMultiplexer channel changing error\n", BMENum[i]);
                    throw std::runtime_error("Multiplexer channel changing error");
                }
                BME::BMP280Data* bme280Data = bme280->getBMP280Data();
                std::fprintf(logs, "pressure   : %.2f \thPa\n", bme280Data->getPressure());
                std::fprintf(logs, "humidity   : %.2f \t%c\n", bme280Data->getHumidity(), '%');
                std::fprintf(logs, "temperature: %.2f \t°C\n", bme280Data->getTemperature());
                std::fprintf(logs, "altitude   : %.2f \tm\n\n", bme280Data->getAltitude());

                pressure += bme280Data->getPressure();
                humidity += bme280Data->getHumidity();
                temperature += bme280Data->getTemperature();
            }

            QString str = "";
            str += "Temperature = ";
            str += QString::number(temperature / 3);
            str += " °C\nPressure = ";
            str += QString::number(pressure / 3);
            str += " hPa\nHumidity = ";
            str += QString::number(humidity / 3);
            str += "%";

            emit NewBMEData(0, str);
        }
        fclose(logs);
    }

    MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent) {

        setFixedSize(1024, 720);

        palBack.setColor(QPalette::Background, QColor(0, 189, 222));
        setAutoFillBackground(true);
        setPalette(palBack);

        widBME = new StationBME;
        widBME->moveToThread(&thrBME);
        connect(&thrBME, SIGNAL(started()), widBME, SLOT(Loop()));

        managerRemote = new ManagerRemote("127.0.0.1", 1111);
        // Хардкодим ид для датчика, добавить конфиги
        managerRemote->AddRemote(1, RemoteTypes::A);
        managerRemote->AddRemote(2, RemoteTypes::B);
        managerRemote->moveToThread(&thrRemote);
        connect(&thrRemote, SIGNAL(started()), managerRemote, SLOT(Loop()));

        ui = new UI(GetSensorsNum(), this);
        connect(widBME, SIGNAL(NewBMEData(int, QString)), ui, SLOT(UpdateInfo(int, QString)));
        connect(managerRemote, SIGNAL(NewData(int, QString)), ui, SLOT(UpdateInfo(int, QString)));
        setCentralWidget(ui);
    }

    int MainWindow::GetSensorsNum() const {
        // 1 на станции + ремоуты
        return 1 + (managerRemote->GetRemoteNum());
    }

    MainWindow::~MainWindow() {
        thrBME.wait();
        thrRemote.wait();
        delete widBME;
        delete managerRemote;
    }

    void MainWindow::Loop() {
        thrBME.start();
        thrRemote.start();
    }

    UI::UI(int labNum, QWidget* parent)
        : QWidget(parent) {
        layBME = new QHBoxLayout();
        for (int i = 0; i < labNum; ++i) {
            labels[i] = new QLabel("", this);
            QFont front("Times New Roman", 20, QFont::Bold);
            labels[i]->setFont(front);
            layBME->addWidget(labels[i]);
        }
        setLayout(layBME);
    }

    void UI::UpdateInfo(int id, QString str) {
        QString msg = "ID = " + QString::number(id) + '\n' + str;
        labels[id]->setText(msg);
    }

}   /*Station*/
