#include "SensorController.h"
#include <Streaming.h>

#define GYRO_ZERO_VEL 0.0001;
#define THRESHOLD_VEL 0.001;
#define INTESITY_DECAY 10

SensorController::SensorController(){
  threshold = 100;
  mx=my=mz=0;
  intensity = 0;
  threshold = 20000;
}

void SensorController::begin(){
  Wire.begin();
  accelgyro.initialize();

  timeOut = 0;
}

void SensorController::process(){
  accelgyro.getRotation(&gx, &gy, &gz);

  mx += (gx-mx) * GYRO_ZERO_VEL;
  my += (gy-my) * GYRO_ZERO_VEL;

  instIntensity = abs( mx - gx ) + abs( my - gy );

  intensity -= INTESITY_DECAY;
  intensity = max(intensity,0.0);
  intensity = max(intensity, instIntensity);

  // threshold += ( intensity - threshold ) * THRESHOLD_VEL;

  // float thInc = intensity - threshold;
  // threshold += min( abs(thInc) , 1 ) * ( thInc>0 ? 1 : -1 ) * 0.1;

  bool isM = intensity > ( threshold );

  if(isMoving != isM){
    if(isM){
      beginMove();
    }else{
      endMove();
    }
  }

  maxIntensity = max( maxIntensity , intensity - threshold );

  isMoving = isM;

  if( millis() < timeOut ) return;
  timeOut = millis() + 500;
  // Serial << "gx " << gx  << " mx " << mx  << " i " << intensity << " th " << threshold << (isMoving?" MOVE":" ") << "\r\n";
}

void SensorController::beginMove(){
  maxIntensity = 0;
  // Serial << "BEGIN MOVE \r\n" ;
  delegate->sensorBeginMove();
}

void SensorController::endMove(){
  delegate->sensorEndMove();
  // Serial << "END MOVE " << maxIntensity <<"\r\n" ;
}
