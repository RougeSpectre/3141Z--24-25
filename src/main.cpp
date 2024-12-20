#include "vex.h"
#include "robotConfig.h"
#include "preAuto.h"
#include "auto.h"
#include "driver.h"
#include "tools.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace vex;

void Autonomous(){
  ControlMode = 2; ResetItems(); Brain.Screen.clearScreen();
  SetupSystems();
  vex::task SafeIntake(IntakeSafety);

  if (SelectedAuto%(int)pow(10,(int)log10(SelectedAuto)) == 0){
    Controller.rumble("----------");
  }else{
    if (SelectedAuto==11){ //? Red Right
      if (AutoType==0){ //! Quals
        Move(0.6,80);
        Turn(90);
        TimedDrive(0.5,-80);
        wait(0.2,sec);
        IntakeState(1,80);
        wait(0.35,sec);
        Move(0.5,80);
        Turn(-50);
        Move(-1.5,80);
        Turn(-50);
        wait(0.1,sec);
        Move(-0.5,50);
        ClampGoal(0);
        wait(0.4,sec);
        Turn(-180);
        Move(1.5,80);
        IntakeState(1,40);
        Move(-0.7,50);
        IntakeState(1,100);
        Turn(-140);
        wait(1,sec);
        Move(-2,80);
        ActuateHighArm(0);
      }else if(AutoType==1){ //! Elims
        Move(0.6,80);
        Turn(90);
        TimedDrive(0.5,-80);
        wait(0.2,sec);
        IntakeState(1,80);
        wait(0.35,sec);
        Move(0.5,80);
        Turn(-50);
        Move(-1.5,80);
        Turn(-50);
        wait(0.1,sec);
        Move(-0.5,50);
        ClampGoal(0);
        wait(0.4,sec);
        Turn(-180);
        Move(1.5,80);
        IntakeState(1,40);
        Move(-0.7,50);
        IntakeState(1,100);
        Turn(-140);
        Move(1.6,80);
        IntakeState(1,-80);
        ActuateArm(0);
        Turn(-80);
        wait(0.5,sec);
        Turn(60);
        TimedDrive(-0.5,80);
      }else if(AutoType==2){ //! Testing
        IntakeState(1,-40);
        Move(1.5/2,50);
        Move(1.5/2,80);
        ActuateHighArm(0);
        wait(100,msec);
        Turn(-95);
        Move(0.085,50);
        ActuateHighArm(0);
        wait(250,msec);
        Move(-0.1,25);
        Turn(-40);
        Move(-2.5,75);
        ClampGoal(0);
        Turn(-180);
        IntakeState(1,80);
        Move(2,70);
        IntakeState(1,50);
        Move(-1,50);
        IntakeState(1,80);
        wait(2,sec);
        IntakeState(0,0);
        Turn(10);
        Move(2,80);
        ActuateHighArm(0);
      }
    }else if (SelectedAuto==12){ //? Red Left
      Move(-1.65,35);
      ClampGoal(0);
      IntakeState(1,80);
      wait(0.2,sec);
      Turn(50);
      Move(1.8,50);
      IntakeState(1,55);
      wait(0.08,sec);
      Move(-0.55,80);
      IntakeState(1,100);
      Turn(125);
      Move(0.52,50);
      wait(0.5,sec);
      Move(-0.5,80);
      Turn(60);
      Move(-1.8,80);
      IntakeState(0,0);
      ActuateHighArm(0);
    }else if (SelectedAuto==21){ //? Blue Right
      Move(-1.6,35);
      ClampGoal(0);
      IntakeState(1,100);
      wait(0.2,sec);
      Turn(-60);
      Move(1.8,50);
      IntakeState(1,55);
      Move(-0.8,80);
      IntakeState(1,100);
      Turn(-145);
      Move(1.1,50);
      wait(0.25,sec);
      Move(-0.43,80);
      Turn(-240);
      Move(2,80);
      IntakeState(0,0);
      ActuateHighArm(0);
    }else if (SelectedAuto==22){ //? Blue Left
      if (AutoType == 0 || AutoType == 1){
        Move(-1.6,35);
        ClampGoal(0);
        IntakeState(1,100);
        Turn(60);
        Move(1.7,50);
        wait(0.2,sec);
        Move(-1.1,80);
        Turn(-85);
        Move(1.4,80);
        IntakeState(0,0);
        ActuateArm(0);
        Turn(-40);
        ActuateArm(0);
        Turn(-25);
        IntakeState(1,100);
        Move(1.3,50);
        wait(0.1,sec);
        Move(-1.8,80);
        Turn(15);
        IntakeState(0,0);
        Move(-1.2,80);
        ActuateHighArm(0);
      }else if(AutoType == 2){
        IntakeState(1,-40);
        Move(1.25/2,50);
        Move(1.25/2,80);
        ActuateHighArm(0);
        wait(100,msec);
        Turn(100);
        Move(0.085,50);
        ActuateHighArm(0);
        wait(250,msec);
        Move(-0.1,25);
        Turn(55);
        Move(-2.5,65);
        ClampGoal(0);
        Turn(180);
        IntakeState(1,80);
        Move(1.75,70);
        IntakeState(1,50);
        Move(-1,50);
        IntakeState(1,80);
        wait(2,sec);
        IntakeState(0,0);
        Turn(-10);
        Move(2,80);
        ActuateHighArm(0);
      }
    }else if (SelectedAuto==01){ //? Left Skills
      Move(-0.5,80);
      ClampGoal(0);//Collect first goal
      wait(0.05,sec);
      IntakeState(1,80);
      wait(0.15,sec);
      Turn(-145);
      Move(0.95,50);
      wait(0.15,sec);
      Turn(-225);
      Move(1.2,50);
      wait(0.15,sec);
      Turn(-325);
      IntakeState(1,90);
      Move(1,60);
      TimedDrive(1,30);
      Turn(-200);
      Move(0.5,60);
      IntakeState(1,80);
      wait(0.3,sec);
      Turn(-115);
      TimedDrive(0.75,-70);
      ClampGoal(0);// Release first goal
      IntakeState(1,-65);
      Move(0.5,80);
      Turn(-55);
      Move(3,50);
      Turn(110);
      Move(-1,40);
      ClampGoal(0);//Collect second goal
      Turn(-55);
    }else if(SelectedAuto==02){ //? PID Test
      Controller.rumble("...");
      PIDTurn(90);
      wait(5,sec);
      PIDTurn(180);
      wait(5,sec);
      PIDTurn(0);
      wait(5,sec);
      PIDTurn(-90);
    }else if(SelectedAuto==03){ //? Right Skills
      Move(-0.15,80);
      ClampGoal(0);
      ActuateHighArm(0);
      PIDTurn(15);
      Move(1,60);
      PIDTurn(-8);
      ActuateHighArm(0);
      wait(0.3,sec);
      Move(-0.5,80);
      PIDTurn(165);
      IntakeState(1,80);
      Move(1.5,80);
      PIDTurn(220);
      Move(1.65,80);
      PIDTurn(155);
      Move(1.9,80);
      wait(0.15,sec);
      Move(-0.65,80);
      PIDTurn(-30);
      
    }else{
      Brain.Screen.printAt(50,50,"Invalid Autonomous Selected");
      Controller.rumble(".....------");
    }
  }
  wait(5,sec);
  ResetItems();
}

int main(){
  //? REQUIRED
  Competition.autonomous(Autonomous); // Setup what VEX calls for Autonomous mode. //! ALWAYS ENABLE BEFORE MATCHES!
  Competition.drivercontrol(Driver); // Setup what VEX calls for Driver mode. //! ALWAYS ENABLE BEFORE MATCHES!
  PreAutonomous(); // Setup Pre-Autonomous mode so it's always intiated before match. //! ALWAYS ENABLE BEFORE MATCHES!
  //? REQUIRED

  //? Setup Controller & Such
  SetupSystems();
  UpdateCScreen();
  //? Setup Controller & Such

  while (true){
    wait(100, msec); // Make sure everything can run before cycling again.
  }
}