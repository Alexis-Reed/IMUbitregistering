#include <Wire.h>

#define IMU_ADDRESS 0x68 // ICM-20948 I2C Address

void setup() {
    Wire.begin();
    Serial.begin(115200);

    // Wake up IMU and set clock source to PLL
    writeRegister(0x06, 0x01); 

    // Set accelerometer full-scale range to ±8g and ODR to 6 kHz
    writeRegister(0x14, 0x07);

    // Set gyroscope full-scale range to ±1000 dps and DLPF to 92 Hz
    writeRegister(0x01, 0x03);

    // Enable FIFO for accelerometer and gyroscope
    writeRegister(0x67, 0x78);

    // Enable data-ready interrupt
    writeRegister(0x10, 0x01);
}

void loop() {
    // Read data from IMU...
}

void writeRegister(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(IMU_ADDRESS);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}
