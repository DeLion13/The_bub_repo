#include "gyro.h"

#include "radios.h"

int flexSensorPin = A0; //analog pin 0

void setup() {     
  transmit_data[0]=1;
  transmit_data[1]=1; 
  int error;
  uint8_t c;

  radioSetup();
  for(int i=0; i<6; i++) {
    transmit_data[i]=0;
  }
  Serial.begin(38400);
  Wire.begin();


  error = MPU6050_read (MPU6050_WHO_AM_I, &c, 1);

  error = MPU6050_read (MPU6050_PWR_MGMT_2, &c, 1);
  
  MPU6050_write_reg (MPU6050_PWR_MGMT_1, 0);
  
  calibrate_sensors();  
  set_last_read_angle_data(millis(), 0, 0, 0, 0, 0, 0);
}

void loop()
{
  struct angles angles = update_gyro(); 
  int flexSensorReading = analogRead(flexSensorPin); 
  Serial.write("Flex -> ");  Serial.println(flexSensorReading);
  transmit_data[0] = angles.x;
  transmit_data[1] = angles.y;
  transmit_data[2] = flexSensorReading;
  Serial.print(angles.x);
  Serial.print("    ");
  Serial.println(angles.y);
  if (radio.write(&transmit_data, sizeof(transmit_data))) {    // отправка пакета transmit_data
    trnsmtd_pack++;
    if (radio.available()) {                                  // если получаем пустой ответ
      while (radio.available() ) {                    // если в ответе что-то есть
        radio.read(&telemetry, sizeof(telemetry));
      }
    }
  } else {
    failed_pack++;
  }
}
