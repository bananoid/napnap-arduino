#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

class SensorController {
private:
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  float mx, my, mz;

  int threshold;

  MPU6050 accelgyro;
public:
  bool isMoving;
  SensorController(int th);
  void begin();
  void process();
};

