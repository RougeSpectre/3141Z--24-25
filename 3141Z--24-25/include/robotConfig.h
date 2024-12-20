#ifndef __RobotConfig__
#define __RobotConfig__

using namespace vex;

extern brain Brain;
extern competition Competition;
extern controller Controller;
extern inertial InertialSensor;

extern pneumatics GoalClamp;
extern pneumatics Arm;

extern motor M1R;
extern motor M2R;
extern motor M3R;
extern motor_group RightDrive;

extern motor M1L;
extern motor M2L;
extern motor M3L;
extern motor_group LeftDrive;

extern motor IntakeRight;
extern motor_group Intake;

extern motor HighStakeArm;
extern optical HighStakeVision;
extern rotation HighStakeRotation;

void vexcodeInit(void);

#endif __RobotConfig__