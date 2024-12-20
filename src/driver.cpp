#include "vex.h"
#include "robotConfig.h"
#include "preAuto.h"
#include "auto.h"
#include "tools.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
using namespace vex;

// Driver Variables
bool IntakeSpinning = false;
bool IntakeLockout = false;
bool IntakeLast = true;
double MaxIntake = 100;
double MinIntake = 50;
double IntakeStep = 10;
double IntakeSpeed = 90;
double MaxIntakeTorque = 1.1;
double DriveSpeed = 1;
int HighArmCycle = 0;

// Driver Functions

void UpdateCScreen(){
  Controller.Screen.clearScreen();
  Controller.Screen.setCursor(1,1);
  Controller.Screen.print("Bat: %d Goal: %d Arm: %d",Brain.Battery.capacity(pct)-1,GoalClamp.value(),Arm.value());
  Controller.Screen.setCursor(2,1);
  Controller.Screen.print("HA: %d DTmp: %.1f",HighArmCycle,(LeftDrive.temperature(fahrenheit)+RightDrive.temperature(fahrenheit))/2);
  Controller.Screen.setCursor(3,1);
  Controller.Screen.print("Intake: %.0f Drive: %.0f",IntakeSpeed,DriveSpeed*100);
}

int GoalClampControl(){
  while (true){ // Make sure the task is constant and not one-time use.
    if (Controller.ButtonUp.pressing()){
      GoalClamp.set(!GoalClamp.value()); // Set the state of piston to the opposite of current.
      waitUntil(!Controller.ButtonUp.pressing()); // Make it a toggle
      UpdateCScreen();
    }
    wait(20, msec); // Allow other tasks to be completed.
  }
  return 0;
}

int IntakeToggle(){
  while (true){
    if (Controller.ButtonR1.pressing() && !IntakeLockout && !Controller.ButtonR2.pressing()){
      if (IntakeLast){
        IntakeSpinning = !IntakeSpinning;
      }else{
        IntakeSpinning = true;
      }
      UpdateCScreen();

      if (IntakeSpinning){
        Intake.spin(fwd, IntakeSpeed, pct);
      }else{
        Intake.stop();
      }
      IntakeLast=true;
      waitUntil(!Controller.ButtonR1.pressing());
    }else if (Controller.ButtonR2.pressing() && !IntakeLockout && !Controller.ButtonR1.pressing()){
      if (!IntakeLast){
        IntakeSpinning = !IntakeSpinning;
      }else{
        IntakeSpinning = true;
      }
      UpdateCScreen();

      if (IntakeSpinning){
        Intake.spin(reverse, IntakeSpeed, pct);
      }else{
        Intake.stop();
      }
      IntakeLast=false;
      waitUntil(!Controller.ButtonR2.pressing());
    }

    if (IntakeSpinning && Intake.torque() >= MaxIntakeTorque && Intake.velocity(pct) <= 10){
      IntakeLockout = true;
      Intake.spin(reverse, IntakeSpeed, pct);
      wait(0.5, sec);
      Intake.stop();
      IntakeLockout = false;
      IntakeSpinning = false;
    }
    wait(20, msec);
  }
}

int HighArmControl(){
  while (true){ // Make sure the task is constant and not one-time use.
    if (Controller.ButtonLeft.pressing()){ // When the LeftArrow is pressed.
      HighArmCycle = SafeLoopControl(HighArmCycle, 1, 1, 0);
      waitUntil(!Controller.ButtonLeft.pressing()); // Make it a toggle
      UpdateCScreen();
      ActuateHighArm(HighArmCycle);
    }else if (Controller.ButtonDown.pressing()){ // When the DownArrow is pressed.
      if (HighArmCycle == 1){
        HighArmCycle = 2;
      }else{
        HighArmCycle = 1;
      }
      waitUntil(!Controller.ButtonDown.pressing());
      UpdateCScreen();
      ActuateHighArm(HighArmCycle);
    }
    wait(20, msec); // Allow other tasks to be completed.
  }
  return 0;
}

int ArmControl(){
  while (true){
    if (Controller.ButtonL2.pressing()){
      Arm.set(!Arm.value());
      waitUntil(!Controller.ButtonL2.pressing());
      UpdateCScreen();
    }
    wait(20, msec);
  }
  return 0;
}

int DeadzoneCheck(int Input, int Minimum){
  if (abs(Input) < Minimum){
    return 0;
  }
  return Input;
}

void Driver(){
  ControlMode = 3;
  SetupSystems();
  ActuateHighArm(0);
  //vex::task TaskName(Function);
  vex::task GoalClampController(GoalClampControl);
  vex::task IntakeControl(IntakeToggle);
  vex::task HighArmController(HighArmControl);
  vex::task ArmController(ArmControl);

  // Driving Control
  double LFwd; double RFwd;
  while (1) { // Make sure the driver control is constant and not one-time use.

    LFwd = DeadzoneCheck(Controller.Axis3.value(), 8)*DriveSpeed;
    RFwd = DeadzoneCheck(Controller.Axis2.value(), 8)*DriveSpeed;
    LeftDrive.spin(fwd, LFwd, pct);
    RightDrive.spin(fwd, RFwd, pct);

    wait(30, msec); // Allow other tasks to be completed.
  }
}