#include <Wire.h>

#define ICM20948_ADDR 0x68 // I2C address (AD0 pulled low)
#define PWR_MGMT_1 0x06
#define GYRO_CONFIG_1 0x01
#define ACCEL_CONFIG 0x14
#define GYRO_SMPLRT_DIV 0x00
#define ACCEL_SMPLRT_DIV_1 0x10
#define ACCEL_SMPLRT_DIV_2 0x11

void writeRegister(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(ICM20948_ADDR);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

uint8_t readRegister(uint8_t reg) {
  Wire.beginTransmission(ICM20948_ADDR);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(ICM20948_ADDR, 1);
  return Wire.read();
}

void setup() {
  Wire.begin();
  Serial.begin(115200);

  // Wake up the IMU
  writeRegister(PWR_MGMT_1, 0x01); // Clock source to Auto Select
  
  // Configure gyroscope
  writeRegister(GYRO_SMPLRT_DIV, 0x00); // Max ODR
  writeRegister(GYRO_CONFIG_1, 0x00);  // ±250 dps, no filtering

  // Configure accelerometer
  writeRegister(ACCEL_SMPLRT_DIV_1, 0x00); // Max ODR
  writeRegister(ACCEL_SMPLRT_DIV_2, 0x00);
  writeRegister(ACCEL_CONFIG, 0x00);  // ±2g, no filtering

  Serial.println("ICM-20948 configured for maximum sampling rate.");
}

void loop() {
  // Example to read accelerometer and gyroscope data
  int16_t accelX = (readRegister(0x2D) << 8) | readRegister(0x2E);
  int16_t accelY = (readRegister(0x2F) << 8) | readRegister(0x30);
  int16_t accelZ = (readRegister(0x31) << 8) | readRegister(0x32);

  int16_t gyroX = (readRegister(0x33) << 8) | readRegister(0x34);
  int16_t gyroY = (readRegister(0x35) << 8) | readRegister(0x36);
  int16_t gyroZ = (readRegister(0x37) << 8) | readRegister(0x38);

  Serial.print("Accel: X=");
  Serial.print(accelX);
  Serial.print(", Y=");
  Serial.print(accelY);
  Serial.print(", Z=");
  Serial.println(accelZ);

  Serial.print("Gyro: X=");
  Serial.print(gyroX);
  Serial.print(", Y=");
  Serial.print(gyroY);
  Serial.print(", Z=");
  Serial.println(gyroZ);

  delay(10); // Adjust based on data requirements
}
