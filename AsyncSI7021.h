#ifndef AsyncSI7021_H
#define AsyncSI7021_H

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define SI7021_I2C_ADDRESS 0x40

#define SI7021_CMD_RH_HOLDMM 0xE5
#define SI7021_CMD_RH_NOHOLDMM 0xF5
#define SI7021_CMD_TEMP_HOLDMM 0xE3
#define SI7021_CMD_TEMP_NOHOLDMM 0xF3
#define SI7021_CMD_TEMP_LASTRH 0xE0
#define SI7021_CMD_RESET 0xFE
#define SI7021_CMD_RHTREG_WRITE 0xE6
#define SI7021_CMD_RHTREG_READ 0xE7
#define SI7021_CMD_HEATERCTRL_WRITE 0x51
#define SI7021_CMD_HEATERCTRL_READ 0x11
#define SI7021_CMD_SERIAL1_READ 0xFA0F
#define SI7021_CMD_SERIAL2_READ 0xFCC9
#define SI7021_CMD_FIRMREV_READ 0x84B8

class AsyncSI7021 {
  public:
    AsyncSI7021();

    bool begin();

    float syncHumidityMeasurement();
    float syncTemperatureMeasurement();

    bool startHumidityMeasurement();
    bool startTemperatureMeasurement();

    bool isMeasurementReady();

    float getHumditityMeasurement();
    float getTemperatureMeasurement();
    float readTemperatureFromHumidityMeasurement();

  private:
    float _humidityConversion(uint16_t rawHumidity);
    float _temperatureConversion(uint16_t rawTemperature);

    uint8_t _read();
    uint16_t _read16();
    void _write(uint8_t reg, bool i2cStopMessage   = true);
    void _writeValue(uint8_t reg, uint8_t value, bool i2cStopMessage  = true);
};

#endif // AsyncSI7021_H