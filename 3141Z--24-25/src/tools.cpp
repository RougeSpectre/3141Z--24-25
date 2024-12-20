#include "vex.h"
#include "robotConfig.h"
#include "ScreenDrawing.h"
#include <stdio.h>
#include <sstream>
#include <string>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
using namespace vex;

bool VisionSensorControl(int SearchHueLow, int SearchHueHigh, optical Sensor, double LedPct){
    if (Sensor.installed()){
        Sensor.setLightPower(LedPct, pct);
        while (true){
            int SensedHue = Sensor.hue();
            if (SensedHue >= SearchHueLow && SensedHue <= SearchHueHigh && Sensor.isNearObject() || SearchHueLow == SearchHueHigh && Sensor.isNearObject()){
                return true;
            }
        }
    }
    return false;
}

bool TouchInRange(int XPress,int YPress,int XPos,int YPos,int Width,int Height){
  return XPress > XPos & YPress > YPos & XPress < XPos+Width & YPress < YPos+Height;
}

int SafeLoopControl(int Input, int Added, int Maximum, int Minimum){
    Input += Added;
    if (Input > Maximum){
        Input = Minimum;
    }else if (Input < Minimum){
        Input = Maximum;
    }
    return Input;
}

void RotateToDegree(motor Motor, rotation RotationSensor, int Degree, int kP, int DirectionMultiplier){
    if (DirectionMultiplier==0){DirectionMultiplier=1;}
    while (RotationSensor.position(deg) < Degree - 2 || RotationSensor.position(deg) > Degree + 2){
        Motor.spin(fwd, (RotationSensor.position(deg) - Degree) * kP * DirectionMultiplier, pct);
        wait(20, msec);
    }
}