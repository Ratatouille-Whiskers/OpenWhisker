#include <MLX90393.h>
#include <math.h>

#define HIGH_PRIORITY 1
#define DRDY_pin 21
#define DEBUG_pin 18

MLX90393 mlx;
MLX90393::txyzRaw rawData;
MLX90393::txyzRaw rawData_offset;
MLX90393::txyz data;

const uint axisFlags = MLX90393::X_FLAG | MLX90393::Y_FLAG;
// const uint axisFlags = MLX90393::X_FLAG | MLX90393::Y_FLAG | MLX90393::Z_FLAG;

volatile bool dataReady = false;
volatile bool procReady = false;

void loop1()
{
    int reads = 0;
    unsigned long duration = micros();
    unsigned long prev_time = micros();

    while (1)
    {
        if (procReady)
        {
          procReady = false;

          // reads++;
          // if (reads > 1000)
          // {
          //     duration = micros() - prev_time;
          //     Serial.print(duration);
          //     Serial.print(" ");
          //     Serial.print(reads);
          //     Serial.print(" | ");
          //     Serial.print("READ FREQ:");
          //     Serial.println(1000000.0 / (float(duration) / reads));

          //     for (int i = 0; i < 30; i++){delay(100);}

          //     reads = 0;
          //     prev_time = micros();
          // }

          // gpio_put(DEBUG_pin, 1);
          Serial.printf(">X: %f\r\n", data.x);
          Serial.printf(">Y: %f\r\n", data.y);
          // Serial.printf(">Z: %f\r\n", data.z);
          // Serial.printf(">X: %u\r\n", rawData.x - rawData_offset.x);
          // Serial.printf(">Y: %u\r\n", rawData.y - rawData_offset.y);
          // Serial.printf(">Z: %u\r\n", rawData.z - rawData_offset.z);
          // gpio_put(DEBUG_pin, 0);
        }
    }
}

void mlxInterrupt() {
    dataReady = true;
}

void setup() {
    Serial.begin(115200);
    // Serial.begin(921600);

    while (!Serial)
    {
        delay(10);
    }

    attachInterrupt(DRDY_pin , mlxInterrupt, RISING);

    pinMode(DRDY_pin, INPUT_PULLDOWN);
    pinMode(DEBUG_pin, OUTPUT);

    Wire.setSDA(16); 
    Wire.setSCL(17);
    Wire.setClock(400000);
    Wire.begin();

    // byte status = mlx.begin(0, 0, DRDY_pin, Wire); // OLD INIT
    byte status = mlx.begin(0x18, DRDY_pin, Wire);

    mlx.setGainSel(0);
    mlx.setOverSampling(0);
    mlx.setDigitalFiltering(0);
    mlx.setResolution(1, 1, 1);
    mlx.setTemperatureCompensation(0);
    Serial.println(mlx.setOffsets(0,0,0));

    delay(100);

    Serial.printf("Measurement Starting\n");
    mlx.startBurst(axisFlags);
    
    delay(500);

    // Auto-Zero?
    // NON ROLLING AVG
    // TODO: ROLLING AVG?
    uint16_t i=0;
    while(i<1000){
      if(dataReady){
        dataReady = false;
        mlx.readMeasurement(
          axisFlags,
          rawData
        );

        if(i==0){
          rawData_offset.x = rawData.x;
          rawData_offset.y = rawData.y;
          rawData_offset.z = rawData.z;
        }

        rawData_offset.x = (rawData_offset.x >> 1) + (rawData.x >> 1);
        rawData_offset.y = (rawData_offset.y >> 1) + (rawData.y >> 1);
        rawData_offset.z = (rawData_offset.z >> 1) + (rawData.z >> 1);

        i++;
        Serial.printf("I: %u\r\n", i);

      }
    }

    // TEMP COMP OFFSET
    // rawData_offset.x -= (uint16_t) 0x8000;
    // rawData_offset.y -= (uint16_t) 0x8000;
    // rawData_offset.z -= (uint16_t) 0x8000;

    Serial.printf("offset_X: %u\r\n", rawData_offset.x);
    Serial.printf("offset_Y: %u\r\n", rawData_offset.y);
    Serial.printf("offset_Z: %u\r\n", rawData_offset.z);

    // delay(15000);

}

void loop(){
  if(dataReady){
    dataReady = false;
    mlx.readMeasurement(
      axisFlags,
      rawData
    );

    rawData.x -= rawData_offset.x;
    rawData.y -= rawData_offset.y;
    // rawData.z -= rawData_offset.z;

    data = mlx.convertRaw(rawData);
    procReady = true;
  }
}
