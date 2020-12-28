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
    std::cout << "Main" << std::endl;
  /*try {
    BME280 * bme280 = new BME280(BME280_I2C_ADDRESS1);
    int fd = bme280->init();
    bme280->reset();

    if (fd < 0) {
      printf("Device not found");
      return -1;
    }

    printf("fd       : 0x%02x\n", fd);
    printf("chip id  : 0x%02x\n", bme280->getChipId());
    printf("chip ver : 0x%02x\n", bme280->getChipVersion());

    bme280->reset();
    bme280->setPowerMode(BME280_NORMAL_MODE);
    bme280->setTemperatureOversampling(BME280_ULTRAHIGHRESOLUTION_OVERSAMP_TEMPERATURE);
    bme280->setPressureOversampling(BME280_ULTRAHIGHRESOLUTION_OVERSAMP_PRESSURE);
    bme280->setHumidityOversampling(BME280_ULTRAHIGHRESOLUTION_OVERSAMP_HUMIDITY);
    bme280->setIrrFilter(BME280_FILTER_COEFF_16);
    bme280->setStandbyTime(BME280_STANDBY_TIME_250_MS);

    printf("---------------\n");
    printf("pw mode  : 0x%02x\n", bme280->getPowerMode());
    printf("osrs_p   : 0x%02x\n", bme280->getPressureOversampling());
    printf("osrs_t   : 0x%02x\n", bme280->getTemperatureOversampling());
    printf("osrs_h   : 0x%02x\n", bme280->getHumidityOversampling());
    printf("---------------\n");
    printf("filter   : 0x%02x\n", bme280->getIrrFilter());
    printf("t_sb     : 0x%02x\n", bme280->getStandbyTime());
    printf("---------------\n");
    printf("spi3w sts: 0x%02x\n", bme280->getSpi3w());
    printf("measuring: 0x%02x\n", bme280->getMeasuringStatus());
    printf("im_update: 0x%02x\n", bme280->getImUpdateStatus());
    printf("---------------\n");

    while (1) {
      delay(1000);
      BMP280Data * bme280Data = bme280->getBMP280Data();
      printf("pressure   : %.2f \tmm Hg\n", bme280Data->getPressure() / 1.3332239);
      printf("humidity   : %.2f \t%c\n", bme280Data->getHumidity(), '%');
      printf("temperature: %.2f \t°C\n", bme280Data->getTemperature());
      printf("altitude   : %.2f \tm\n\n", bme280Data->getAltitude());
    }
    delete bme280;
  } catch (std::exception & e) {
    printf("%s\n", e.what());
  }*/
  return 0;
}
