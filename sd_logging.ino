#include <Wire.h>
#include <SD.h>
#include <SPI.h>

// Define pins and addresses
#define IMU_ADDRESS 0x68
#define CS_PIN 10

// File for logging
File logFile;

// Function to write to a register
void writeRegister(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(IMU_ADDRESS);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

void setup() {
    Serial.begin(115200);
    Wire.begin();

    // Initialize SD card
    if (!SD.begin(CS_PIN)) {
        Serial.println("SD card initialization failed!");
        while (1);
    }
    Serial.println("SD card initialized.");

    // Open file for writing
    logFile = SD.open("datalog.csv", FILE_WRITE);
    if (logFile) {
        logFile.println("Timestamp, Accel_X, Accel_Y, Accel_Z, Gyro_X, Gyro_Y, Gyro_Z");
        logFile.close();
    } else {
        Serial.println("Failed to create log file.");
    }

    // Wake up IMU and set configuration
    writeRegister(0x06, 0x01); // Wake up IMU, set clock source
    writeRegister(0x14, 0x07); // Accel config: ±8g, 6kHz
    writeRegister(0x01, 0x03); // Gyro config: ±1000dps, 92Hz DLPF
}

void loop() {
    // Read IMU data
    int16_t accelX = readIMUData(0x3B);
    int16_t accelY = readIMUData(0x3D);
    int16_t accelZ = readIMUData(0x3F);
    int16_t gyroX = readIMUData(0x43);
    int16_t gyroY = readIMUData(0x45);
    int16_t gyroZ = readIMUData(0x47);

    // Log data to SD card
    logFile = SD.open("datalog.csv", FILE_WRITE);
    if (logFile) {
        logFile.print(millis());
        logFile.print(", ");
        logFile.print(accelX);
        logFile.print(", ");
        logFile.print(accelY);
        logFile.print(", ");
        logFile.print(accelZ);
        logFile.print(", ");
        logFile.print(gyroX);
        logFile.print(", ");
        logFile.print(gyroY);
        logFile.print(", ");
        logFile.println(gyroZ);
        logFile.close();
    } else {
        Serial.println("Failed to open log file for writing.");
    }

    delay(50); // Log every 50ms
}

int16_t readIMUData(uint8_t reg) {
    Wire.beginTransmission(IMU_ADDRESS);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(IMU_ADDRESS, 2);
    return (Wire.read() << 8 | Wire.read());
}
