# Sensor Notes

## Interesting things found during development

ESP32 AND TEENSY 4.0 HAVE DIFFERENT SPEEDS.

ESP32 IS APRROXIMATELY HALF THE SPEED OF THE TEENSY.
THE `arduino.h` and `wire.h` libraries are different in them.

~~investigate the changes as that could be the reason.~~
The reason is (possibly) due to the differences in how the ESP32 is heavily based around FreeRTOS and therefore has a operating overhead associated with a lot of it's actions. A bit more can be found [here](Why%20ESP32%20Might%20be%20slower%20than%20Teensy?.md)

# #Sample Rate Development Test Results

Setup: 
- Teensy 4.0
- 1K Resistors on both SDA and SCL pins
- Adafruit MLX90393 Breakout Board

`const byte axisFlags = MLX90393::X_FLAG | MLX90393::Y_FLAG | MLX90393::Z_FLAG;`
- Max reading rate is 385hz @ i2c_clk=100kHz
- Max reading rate is 570hz @ i2c_clk=400kHz

`const byte axisFlags = MLX90393::X_FLAG | MLX90393::Y_FLAG;`
- Removing the z-axis from the reading increases 385hz -> 460hz @ i2c_clk=100kHz
- Removing the z-axis from the reading increases 570hz -> 680hz @ i2c_clk=400kHz

`const byte axisFlags = MLX90393::Y_FLAG;`
- Removing the z-axis from the reading increases 460hz -> 578hz @ i2c_clk=100kHz
- Removing the z-axis from the reading increases 680hz -> 870hz @ i2c_clk=400kHz

## MLX90393 (Adafruit Breakout PCB)

-  As of 1st May 2023, the i2c address for the sensor has changes from `0x0C` (_12U_) to ` 0x18` (_24_).
-  Adafruit Library cap out at ~15Hz Max Sample Rate according to this [issues](https://github.com/adafruit/Adafruit_MLX90393_Library/issues/13)
   -  We have found that through a basic setup with the Adafruit Library we can actually reach ~230Hz
      -  Using the [MLX90393_Basic_Read](MLX90393_Basic_Read/MLX90393_Basic_Read.ino) with a ESP32 Dev Board connected over i2c
   -  The issue above state that **teyapos's** library, [arduino-MLX90393](https://github.com/tedyapo/arduino-MLX90393), could achieve ~500Hz, however we are yet to get this library to work
-  The Adafruit PCB include internal Pull-up resistor on board, therefore we don't need to add our own

## Teensy 4.0 (and any other microcontroller used for I2C comms)

- You need to disable the internal Pull-up resistor on the i2c pin as the Sensor PCB include them.
  - **HOWEVER**, we do in fact add 1K resistors to both the SDA and SCL pins as additional pull-up so our signal voltage doesn't drop
    - Ideally these resistors should be ~1.2K
