#include <MLX90393.h>

#define HIGH_PRIORITY 1
#define DRDY_pin 21
#define DEBUG_pin 18

MLX90393 mlx;
MLX90393::txyzRaw rawData;
MLX90393::txyz data;

const uint axisFlags = MLX90393::X_FLAG | MLX90393::Y_FLAG;

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

    byte status = mlx.begin(0, 0, DRDY_pin, Wire);

    mlx.setGainSel(1);
    mlx.setResolution(0, 0, 0);
    mlx.setOverSampling(0);
    mlx.setDigitalFiltering(0);

    delay(100);

    Serial.printf("Measurement Starting\n");
    mlx.startBurst(axisFlags);

}

void loop(){
  if(dataReady){
    dataReady = false;
    mlx.readMeasurement(
      axisFlags,
      rawData
    );
    data = mlx.convertRaw(rawData);
    procReady = true;
  }
}
