# Why ESP32 Might be slower than Teensy?

- difference could be related to FreeRTOS as that is running under the hood for ESP32
  - Doing through the i2c library i find;
    - the timeout, which is set to 50ms, however this is to long for what ime seeing
      - The minimum use of the timeout of the use of Timeout is the ESP is 50ms. The Teensy also set the timeout to 50ms, but they also use it else where with a timeout of 16ms
    - The ESP32 `Wire.h` appears to try and get the a lock before calling `i2cRead()` (line `504` in `Wire.cpp`)
      - **THIS COULD BE THE REASON WHY IT IS SLOWER**