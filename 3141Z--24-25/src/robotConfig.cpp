#include "vex.h"
using namespace vex;

brain Brain;
competition Competition;
controller Controller;
inertial InertialSensor = inertial(PORT9);

pneumatics GoalClamp = pneumatics(Brain.ThreeWirePort.A);
pneumatics Arm = pneumatics(Brain.ThreeWirePort.C);

motor M1R = motor(PORT16);
motor M2R = motor(PORT19);
motor M3R = motor(PORT17);
motor_group RightDrive = motor_group(M1R,M2R,M3R);

motor M1L = motor(PORT13, true);
motor M2L = motor(PORT12, true);
motor M3L = motor(PORT11, true);
motor_group LeftDrive = motor_group(M1L,M2L,M3L);

motor IntakeRight = motor(PORT10);
motor_group Intake = motor_group(IntakeRight);

motor HighStakeArm = motor(PORT1, true);
optical HighStakeVision = optical(PORT21);
rotation HighStakeRotation = rotation(PORT5);

void vexcodeInit(void) {}

// Avaliable Objects; All Follow the format of the following:
// [DeviceType] [DesignateName] = [DeviceType](DATA);
// ThreeWirePortPath: Brain.ThreeWirePort.[A:H] or [ExpanderDefinition].[A:H]

/*
motor MOTORNAME = motor(PORT#, REVERSEBOOL);
motor_group MOTORGROUPNAME = motor_group(MOTOR1,MOTOR2,...);
pneumatics PNEUMATICNAME = pneumatics(ThreeWirePortPath);
inertial INERTIALNAME = inertial(PORT#);
vision VISIONNAME = vision(PORT#);
bumper BUMPERNAME = bumper(ThreeWirePortPath);
triport TRIPORTNAME = triport(PORT#); // 3 Wire Port Extender
electromagnet MAGNAME = electromagneet(PORT#);
rotation ROTATIONNAME = rotation(PORT#, REVERSEBOOL);
distance DISTANCENAME = distance(PORT#);
optical OPTICALNAME = optical(PORT#);
digital_out DIGITALOUTNAME = digital_out(ThreeWirePortPath);
digital_in DIGITALINNAME = digital_in(ThreeWirePortPath);
accelerometer ACCELNAME = accelerometer(ThreeWirePortPath, HIGHSENSBOOL);
servo SERVONAME = servo(ThreeWirePortPath);
motor29 TWPMOTORNAME = motor29(ThreeWirePortPath, REVERSEBOOL);
gyro GYRONAME = gyro(ThreeWirePortPath);
led LEDNAME = led(ThreeWirePortPath);
potV2 POTENTIOMETERNAME = potV2(ThreeWirePortPath);
pot POTENTIOMETERNaME = pot(ThreeWirePortPath);
light LIGHTNAME = light(ThreeWirePortPath);
line LINENAME = line(ThreeWirePortPath);
sonar RANGEFINDERNAME = sonar(ThreeWirePortPath);
encoder ENCODERNAME = encoder(ThreeWirePortPath);
*/