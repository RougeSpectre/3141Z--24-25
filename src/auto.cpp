#include "vex.h"
#include "robotConfig.h"
#include "preAuto.h"
#include "tools.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>
using namespace vex;

bool IntakeToArm = false;
int LoadAngle = 315;
int ScoreAngle = 205;
int AllowableRange = 20;

void ClampGoal(int ForceState){
    if (ForceState == 0){
        GoalClamp.set(!GoalClamp.value());
    }else{
        GoalClamp.set(ForceState==1);
    }
}

void ActuateHighArm(int ForceState){
    if (ForceState == 0){ // Neutral
        while((HighStakeRotation.angle() > AllowableRange && HighStakeRotation.angle() < 360 - AllowableRange)){
            HighStakeArm.spin(fwd, (HighStakeRotation.angle(deg) - AllowableRange) * 0.2,pct);
        }

        HighStakeArm.setBrake(coast);
        HighStakeArm.stop();
    }else if (ForceState == 1){ // Load
        /*while((HighStakeRotation.angle() > LoadAngle + AllowableRange && HighStakeRotation.angle() < LoadAngle - AllowableRange)){
            HighStakeArm.spin(fwd, (HighStakeRotation.angle(deg) - LoadAngle) * 0.2,pct);
        }*/

        while (true){
            Brain.Screen.setCursor(10,10);
            Brain.Screen.print((HighStakeRotation.angle() > LoadAngle + AllowableRange && HighStakeRotation.angle() < LoadAngle - AllowableRange));
            wait(0.5,sec);
        }

        HighStakeArm.setBrake(brake);
        HighStakeArm.stop();
    }else if (ForceState == 2){ // Score
        
    }
}

void IntakeState(int State, int Pct){
    if (State == 0 || Pct == 0){
        Intake.stop();
    }else{
        Intake.spin(fwd, Pct, pct);
    }
}

void ActuateArm(int ForceState){
    if (ForceState == 0){
        Arm.set(!Arm.value());
    }else{
        Arm.set(ForceState==1);
    }
}

void Move(double Amount, double Speed){
    LeftDrive.stop();
    RightDrive.stop();
    if (Amount < 0){
        Speed *= -1;
    }
    LeftDrive.setVelocity(Speed, pct);
    RightDrive.setVelocity(Speed, pct);
    LeftDrive.spinFor(fwd, Amount, rev, false);
    RightDrive.spinFor(fwd, Amount, rev);
    LeftDrive.stop();
    RightDrive.stop();
}

void TimedDrive(double Time, int Speed){
    LeftDrive.spin(fwd, Speed, pct);
    RightDrive.spin(fwd, Speed, pct);
    wait(Time, sec);
    LeftDrive.stop();
    RightDrive.stop();
}

void PIDDrive(double Amount, double SpeedLimit){
    LeftDrive.stop();
    RightDrive.stop();
    double kP = 0; double kI = 0; double kD = 0;
    float prevE,E,I,D=0;
    
    LeftDrive.stop();
    RightDrive.stop();
}

void Turn(double Degree){
    LeftDrive.stop();
    RightDrive.stop();
    double kP = 0.6;
    // Function
    while (InertialSensor.rotation() < Degree - 2 || InertialSensor.rotation() > Degree + 2){
        RightDrive.spin(fwd, (InertialSensor.rotation() - Degree) * kP, pct);
        LeftDrive.spin(reverse, (InertialSensor.rotation() - Degree) * kP, pct);
        wait(20, msec);
    }
    // Function
    LeftDrive.stop();
    RightDrive.stop();
    LeftDrive.setPosition(0,rev);
    RightDrive.setPosition(0,rev);
}

void PIDTurn(double Degree){
    LeftDrive.stop();
    RightDrive.stop();
    double kP = 0.72; double kI = 0; double kD = 0.12;
    float prevE,E,I,D = 0;
    int EPasses = 0;
    // Function
    while (true){
        E = Degree - InertialSensor.rotation();
        if (std::abs(E)<1){
            EPasses += 1;
            if (EPasses >=3){
                break;
            }
        }

        if (E < 10 && E > -10) { // |E| < 10
            I += E; // Set new Integral
        }

        D = E-prevE; // Set new Derivative
        double Power = (kP * E) + (kI * I) + (kD * D); // Motor Power

        LeftDrive.spin(fwd, Power, pct);
        RightDrive.spin(reverse, Power, pct);
        prevE = E;
    }
    // Function
    LeftDrive.stop();
    RightDrive.stop();
    LeftDrive.setPosition(0,rev);
    RightDrive.setPosition(0,rev);
}

int IntakeSafety(){
    while (true){
        if (Intake.torque() >= 1.1 && Intake.velocity(pct) <= 10){
            Intake.stop();
        }
    }
    return 0;
}

void ResetItems(){
    ClampGoal(2);
    IntakeState(0,0);
    ActuateHighArm(0);
    ActuateArm(2);
    LeftDrive.stop();
    RightDrive.stop();
}