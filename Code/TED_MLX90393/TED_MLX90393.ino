#include <MLX90393.h>
#include <Wire.h>

MLX90393 mlx;
MLX90393::txyzRaw rawData;
MLX90393::txyz data;

bool dataReady = false;

void setup(){
    Serial.begin(115200);
    delay(100);
    Wire.begin();
    delay(100);



    // Wire.begin(0x18);
    byte status = mlx.begin(0,0,5);

    delay(100);

    attachInterrupt(5, mlxInterrupt, RISING);
    

    //Report status from configuration
    Serial.print("Start status: 0x");
    if(status < 0x10) Serial.print("0"); //Pretty output
    Serial.println(status, BIN);

    //set the hall configuration (for setting the hall plate spin phase, 2-Phase: 0xC, 4-Phase: 0x0)
    // mlx.setHallConf(0x0);

    mlx.setGainSel(1);
    mlx.setResolution(0, 0, 0); //x, y, z
    mlx.setOverSampling(0);
    mlx.setDigitalFiltering(0); 
    
    delay(100);

    Serial.println("Measurement Started");
    mlx.startMeasurement(
        MLX90393::X_FLAG | MLX90393::Y_FLAG | MLX90393::Z_FLAG //set the flags for what we want to read 
    );

    //See MLX90393.h and .cpp for additional functions including:
    //set/getOverSample, set/getTemperatureOverSample, set/getDigitalFiltering, set/getResolution
    //set/getTemperatureCompensation, setOffsets, setWThresholds
}

void loop(){
    // mlx.readData(data); //Read the values from the sensor

    if (dataReady){
        // mlx.readData(data);

        mlx.readMeasurement(
            MLX90393::X_FLAG | MLX90393::Y_FLAG | MLX90393::Z_FLAG, //set the flags for what we want to read 
            rawData // read the raw data
        );
        
        // data = mlx.convertRaw(rawData);

        // Serial.print(">X: "); Serial.println(data.x);
        // Serial.print(">Y: "); Serial.println(data.y);
        // Serial.print(">Z: "); Serial.println(data.z);
        dataReady = false;
        
        mlx.startMeasurement(
        MLX90393::X_FLAG | MLX90393::Y_FLAG | MLX90393::Z_FLAG //set the flags for what we want to read 
        );
    }
}

void mlxInterrupt(){
    dataReady = true;
}

