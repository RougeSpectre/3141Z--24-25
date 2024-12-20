#ifndef __Tools__
#define __Tools__
#include "vex.h"
#include "robotConfig.h"
using namespace vex;

extern bool VisionSensorControl(int SearchHueLow,int SearchHueHigh,optical Sensor,double LedPct);
extern bool TouchInRange(int XPress,int YPress,int XPos,int YPos,int Width,int Height);
extern int SafeLoopControl(int Input, int Added, int Maximum, int Minimum);
extern void RotateToDegree(motor Motor, rotation RotationSensor, int Degree, int kP, int DirectionMultiplier);

#endif __Tools__