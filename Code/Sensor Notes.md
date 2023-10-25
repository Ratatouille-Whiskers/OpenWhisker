# Sensor Notes

-  As of 1st May 2023, the i2c address for the sensor has changes from `0x0C` (_12U_) to ` 0x18` (_24_).
-  Adafruit Library cap out at ~15Hz Max Sample Rate according to this [issues](https://github.com/adafruit/Adafruit_MLX90393_Library/issues/13)
   -  We have found that through a basic setup with the Adafruit Library we can actually reach ~230Hz
      -  Using the [MLX90393_Basic_Read](MLX90393_Basic_Read/MLX90393_Basic_Read.ino) with a ESP32 Dev Board connected over i2c
   -  The issue above state that **teyapos's** library, [arduino-MLX90393](https://github.com/tedyapo/arduino-MLX90393), could achieve ~500Hz, however we are yet to get this library to work
-  