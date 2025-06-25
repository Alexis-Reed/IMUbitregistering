#include <Wire.h>

#define IMU_ADDRESS 0x68 // ICM-20948 I2C address
#define ACCEL_CONFIG 0x14
#define GYRO_CONFIG_1 0x01

void writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(IMU_ADDRESS);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

void setup() {
  Wire.begin();
  Serial.begin(115200);

  // Enable DLPF for accelerometer (50 Hz cutoff)
  writeRegister(ACCEL_CONFIG, 0x01); // 0x01 sets DLPF to 50 Hz

  // Enable DLPF for gyroscope (50 Hz cutoff)
  writeRegister(GYRO_CONFIG_1, 0x01); // 0x01 sets DLPF to 50 Hz

  Serial.println("DLPF configured for accelerometer and gyroscope.");
}

void loop() {
  // Collect and process data
}
