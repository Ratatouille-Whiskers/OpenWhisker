#include <MLX90393.h>
#include <Wire.h>

MLX90393 mlx;
MLX90393::txyzRaw rawData;
MLX90393::txyz data;

bool dataReady = false;

// Max reading rate is 385hz @ i2c_clk=100kHz
// Max reading rate is 570hz @ i2c_clk=400kHz
const byte axisFlags = MLX90393::X_FLAG | MLX90393::Y_FLAG | MLX90393::Z_FLAG; 
// Removing the z-axis from the reading increases 385hz -> 460hz @ i2c_clk=100kHz
// Removing the z-axis from the reading increases 570hz -> 680hz @ i2c_clk=400kHz
// const byte axisFlags = MLX90393::X_FLAG | MLX90393::Y_FLAG; 
// Removing the z-axis from the reading increases 460hz -> 578hz @ i2c_clk=100kHz
// Removing the z-axis from the reading increases 680hz -> 870hz @ i2c_clk=400kHz
// const byte axisFlags = MLX90393::Y_FLAG; 

void setup(){
    Serial.begin(115200);
    delay(100);

    // disable the internal pullup resistors on the i2c pin as we use external pull-ups (in this case the one on the Sensor PCB)
    pinMode(SDA, INPUT);
    pinMode(SCL, INPUT);
    Wire.begin();
    // Wire.setClock(100000);
    // Wire.setClock(400000); // setup for 400kHz on a teensy 4.0 resulted in 570Hz (all axis) being read form the sensor on the interrupts
    delay(100);

    // Wire.begin(0x18);
    // byte status = mlx.begin(0,0,5);
    byte status = mlx.begin(0,0,5, Wire);

    delay(100);

    attachInterrupt(5, mlxInterrupt, RISING);
    

    //Report status from configuration
    Serial.print("Start status: 0x");
    if(status < 0x10) Serial.print("0"); //Pretty output
    Serial.println(status, BIN);

    //set the hall configuration (for setting the hall plate spin phase, 2-Phase: 0xC, 4-Phase: 0x0)
    // mlx.setHallConf(0); // <=== NONE FUNCTIONING !!!

    mlx.setGainSel(1);
    mlx.setResolution(0, 0, 0); //x, y, z
    mlx.setOverSampling(0);
    mlx.setDigitalFiltering(0); 
    
    delay(100);

    Serial.println("Measurement Started");
    mlx.startMeasurement(
        axisFlags //set the flags for what we want to read 
        // MLX90393::X_FLAG | MLX90393::Y_FLAG | MLX90393::Z_FLAG //set the flags for what we want to read 
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
            axisFlags, //set the flags for what we want to read 
            // MLX90393::X_FLAG | MLX90393::Y_FLAG | MLX90393::Z_FLAG, //set the flags for what we want to read 
            rawData // read the raw data
        );
        
        data = mlx.convertRaw(rawData);

        Serial.print(">X: "); Serial.println(data.x);
        Serial.print(">Y: "); Serial.println(data.y);
        Serial.print(">Z: "); Serial.println(data.z);

        dataReady = false;
        
        mlx.startMeasurement(
        axisFlags //set the flags for what we want to read 
        // MLX90393::X_FLAG | MLX90393::Y_FLAG | MLX90393::Z_FLAG //set the flags for what we want to read 
        );
    }
}

void mlxInterrupt(){
    dataReady = true;
}

