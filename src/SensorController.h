#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

class SensorControllerDelegate{
public:
  virtual void sensorBeginMove();
  virtual void sensorEndMove();
};

class SensorController{
private:
  int16_t gx, gy, gz;

  float mx, my, mz;
  float instIntensity;
  float threshold;

  MPU6050 accelgyro;

  unsigned long int timeOut;

  void beginMove();
  void endMove();

public:
  float intensity;

  unsigned long int maxIntensity;

  bool isMoving;
  SensorController();
  void begin();
  void process();

  SensorControllerDelegate *delegate;

};

