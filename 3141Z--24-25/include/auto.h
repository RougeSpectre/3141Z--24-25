#ifndef __Auto__
#define __Auto__

extern void ResetItems();
extern void IntakeState(int State, int Pct);
extern void ClampGoal(int ForceState);
extern void ActuateHighArm(int ForceState);
extern void ActuateArm(int ForceState);
extern void Move(double Amount, double Speed);
extern void TimedDrive(double Time, int Speed);
extern void Turn(double Degree);
extern void PDTurn(double Degree);
extern void PIDTurn(double Degree);
extern int IntakeSafety();
extern bool IntakeToArm;
extern void CurveDrive();

#endif __Auto__