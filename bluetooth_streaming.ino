#include <Wire.h>
#include <BLEPeripheral.h>

// Define IMU and Bluetooth settings
#define IMU_ADDRESS 0x68
BLEPeripheral blePeripheral;
BLEService imuService("12345678-1234-5678-1234-56789abcdef0");
BLECharacteristic imuDataCharacteristic("abcdef01-1234-5678-1234-56789abcdef0", BLERead | BLENotify, 100);

// Function to write to IMU register
void writeRegister(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(IMU_ADDRESS);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

// Function to read IMU data
int16_t readIMUData(uint8_t reg) {
    Wire.beginTransmission(IMU_ADDRESS);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(IMU_ADDRESS, 2);
    return (Wire.read() << 8 | Wire.read());
}

void setup() {
    Serial.begin(115200);
    Wire.begin();

    // Initialize IMU
    writeRegister(0x06, 0x01); // Wake up IMU, set clock source
    writeRegister(0x14, 0x07); // Accel config: ±8g, 6kHz
    writeRegister(0x01, 0x03); // Gyro config: ±1000 dps, 92 Hz DLPF

    // Initialize Bluetooth
    blePeripheral.setLocalName("IMU_Bluetooth");
    blePeripheral.setAdvertisedServiceUuid(imuService.uuid());
    blePeripheral.addAttribute(imuService);
    blePeripheral.addAttribute(imuDataCharacteristic);
    blePeripheral.begin();

    Serial.println("Bluetooth streaming initialized.");
}

void loop() {
    // BLE connection handling
    blePeripheral.poll();

    // Read IMU data
    int16_t accelX = readIMUData(0x3B);
    int16_t accelY = readIMUData(0x3D);
    int16_t accelZ = readIMUData_
