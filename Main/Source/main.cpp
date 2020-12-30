#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include <iostream>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <bme/bme280.h>

int main() {
    char* device0 = "/dev/i2c-0";
    char* device1 = "/dev/i2c-1";

    int devId0 = BME280_I2C_ADDRESS1;
    int devId1 = BME280_I2C_ADDRESS2;
  try {
    BME280* bme2800 = new BME280(device0, devId0);
    BME280* bme2801 = new BME280(device1, devId1);
    int fd0 = bme2800->init();
    int fd1 = bme2801->init();
    bme2800->reset();
    bme2801->reset();

    if (fd0 < 0 || fd1 < 0) {
      printf("Device not found");
      return -1;
    }

    printf("fd       : 0x%02x\n", fd0);
    printf("chip id  : 0x%02x\n", bme2800->getChipId());
    printf("chip ver : 0x%02x\n", bme2800->getChipVersion());

    printf("fd       : 0x%02x\n", fd1);
    printf("chip id  : 0x%02x\n", bme2801->getChipId());
    printf("chip ver : 0x%02x\n", bme2801->getChipVersion());

    bme2800->reset();
    bme2800->setPowerMode(BME280_NORMAL_MODE);
    bme2800->setTemperatureOversampling(BME280_ULTRAHIGHRESOLUTION_OVERSAMP_TEMPERATURE);
    bme2800->setPressureOversampling(BME280_ULTRAHIGHRESOLUTION_OVERSAMP_PRESSURE);
    bme2800->setHumidityOversampling(BME280_ULTRAHIGHRESOLUTION_OVERSAMP_HUMIDITY);
    bme2800->setIrrFilter(BME280_FILTER_COEFF_16);
    bme2800->setStandbyTime(BME280_STANDBY_TIME_250_MS);

    printf("---------------\n");
    printf("pw mode  : 0x%02x\n", bme2800->getPowerMode());
    printf("osrs_p   : 0x%02x\n", bme2800->getPressureOversampling());
    printf("osrs_t   : 0x%02x\n", bme2800->getTemperatureOversampling());
    printf("osrs_h   : 0x%02x\n", bme2800->getHumidityOversampling());
    printf("---------------\n");
    printf("filter   : 0x%02x\n", bme2800->getIrrFilter());
    printf("t_sb     : 0x%02x\n", bme2800->getStandbyTime());
    printf("---------------\n");
    printf("spi3w sts: 0x%02x\n", bme2800->getSpi3w());
    printf("measuring: 0x%02x\n", bme2800->getMeasuringStatus());
    printf("im_update: 0x%02x\n", bme2800->getImUpdateStatus());
    printf("---------------\n");

    while (1) {
      delay(1000);
      BMP280Data * bme2800Data = bme2800->getBMP280Data();
      printf("pressure   : %.2f \tmm Hg\n", bme2800Data->getPressure() / 1.3332239);
      printf("humidity   : %.2f \t%c\n", bme2800Data->getHumidity(), '%');
      printf("temperature: %.2f \t°C\n", bme2800Data->getTemperature());
      printf("altitude   : %.2f \tm\n\n", bme2800Data->getAltitude());
    }
    delete bme2800;
  } catch (std::exception & e) {
    printf("%s\n", e.what());
  }
  return 0;
}
