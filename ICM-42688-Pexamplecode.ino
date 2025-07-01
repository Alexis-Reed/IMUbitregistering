#include <SPI.h>
#include <SparkFun_ICM_42688.h> // Install this library from Arduino Library Manager

#define CS_PIN 6 // Chip Select pin for SPI communication

ICM_42688 imu;

void setup() {
  Serial.begin(115200);
  
  // Initialize SPI and set CS pin as output
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH); // Ensure CS is high before initialization
  
  SPI.begin(); // Initialize SPI bus
  
  // Initialize ICM-42688 using SPI
  if (imu.beginSPI(SPI, CS_PIN) != ICM_42688::IMU_SUCCESS) {
    Serial.println("Failed to initialize ICM-42688 over SPI!");
    while (1);
  }
  
  // Set up the ICM-42688 for the highest supported sample rate
  imu.setSampleRate(8000); // Replace with the actual maximum sample rate supported
  
  Serial.println("ICM-42688 Initialized over SPI");
}

void loop() {
  // Check if new data is ready
  if (imu.dataReady()) {
    float accelX, accelY, accelZ;
    float gyroX, gyroY, gyroZ;
    
    // Read accelerometer data
    imu.readAccelerometer(accelX, accelY, accelZ);
    // Read gyroscope data
    imu.readGyroscope(gyroX, gyroY, gyroZ);
    
    // Print data to Serial Monitor
    Serial.printf("Accel X: %.2f Y: %.2f Z: %.2f | ", accelX, accelY, accelZ);
    Serial.printf("Gyro X: %.2f Y: %.2f Z: %.2f\n", gyroX, gyroY, gyroZ);
  }
}
