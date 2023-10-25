#include "Adafruit_MLX90393.h"

Adafruit_MLX90393 mlx = Adafruit_MLX90393();

uint8_t mxlAddr = 0x18;

sensors_event_t mlxData;

void setup() {
    Serial.begin(115200);

    // check if sensor is connected and started
    if (!mlx.begin_I2C(mxlAddr)) {
        Serial.println("MLX90393 not found.\nCheck Wiring.\nCheck I2C address.");
        while (1) {delay(100);};
    }

    // setup MLX90393 settings

    // set Gain
    mlx.setGain(MLX90393_GAIN_1_33X);

    // set Resolution for each axis
    mlx.setResolution(MLX90393_X, MLX90393_RES_16);
    mlx.setResolution(MLX90393_Y, MLX90393_RES_16);
    mlx.setResolution(MLX90393_Z, MLX90393_RES_16);

    // set Oversampling
    mlx.setOversampling(MLX90393_OSR_0);

    // set Digital Filter
    mlx.setFilter(MLX90393_FILTER_0);
}

void loop() {
    // read MLX90393 data
    mlx.getEvent(&mlxData);
    // Print the data for TelePlots
    Serial.print(">X: "); Serial.println(mlxData.magnetic.x);
    Serial.print(">Y: "); Serial.println(mlxData.magnetic.y);
    Serial.print(">Z: "); Serial.println(mlxData.magnetic.z);
}