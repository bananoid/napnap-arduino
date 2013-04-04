#include "SensorController.h"
#include <Streaming.h>

SensorController::SensorController(int th){
  threshold = th;
  mx=my=mz=0;
}

void SensorController::begin(){
  Wire.begin();
  accelgyro.initialize();
}

void SensorController::process(){
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  mx = (gx+mx) *.1;
  my = (gy+my) *.1;
  mz = (gz+mz) *.1;

  isMoving = abs(mx) > threshold || abs(my) > threshold || abs(mz) > threshold;

  if(isMoving){
    Serial << "isMoving";
  }else{
    Serial.print(gx); Serial.print("\t");
    Serial.print(gy); Serial.print("\t");
    Serial.print(gz); Serial.print("\t");
  }

}
