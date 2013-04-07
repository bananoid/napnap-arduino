#include "SensorController.h"
#include <Streaming.h>

SensorController::SensorController(int th){
  threshold = th;
  mx=my=mz=0;
  intensity = 0;
  intensityDecay = 0.01;
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

  // isMoving = abs(mx) > threshold || abs(my) > threshold || abs(mz) > threshold;
  int instInt = abs(mx) + abs(my) + abs(mz);
  intensity = max(intensity, instInt);
  intensity -= intensityDecay;
  intensity = max(intensity,0.0);
  isMoving = intensity > threshold;

  if(isMoving){
    Serial << "isMoving" << "\r\n";
  }else{
    // Serial.print(gx); Serial.print("\t");
    // Serial.print(gy); Serial.print("\t");
    // Serial.print(gz); Serial.print("\t");
  }

}
