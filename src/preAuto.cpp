#include "vex.h"
#include "robotConfig.h"
#include "ScreenDrawing.h"
#include "tools.h"
#include <stdio.h>
#include <sstream>
#include <string>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
using namespace vex;

// Other Definitions
int ControlMode=0; /*1:PreAuto 2:Auto 3:Driver*/
int AutoType=0; /*0:Qualifications 1:Eliminations 2:Testing*/
int SelectedAuto=0; /*First Num = Color, Second Num = Selected Auto*/

struct AutoDefs{int AutoTeam;std::string AutoNames[9];vex::color AutoColor;vex::color SelectedColor;int SelectedAuto;int AutoPage;};
int Color=0;int AutoPerPage=3;AutoDefs Autons[]={
  {0,{"Left Skills","PID Test","Right Skills"},vex::color(130,130,0),vex::color(50,50,0),3,1},
  {1,{"Right","Left"},vex::color(130,0,0),vex::color(50,0,0),0,1},
  {2,{"Right","Left"},vex::color(0,0,130),vex::color(0,0,50),0,1},
};int ColorCount=sizeof(Autons)/sizeof(Autons[0]);

// Screen Position Definitions
struct ScreenItem{int XPos;int YPos;int Width;int Height;std::string Text;bool NeededState;vex::color BackgroundColor;vex::color TextColor;};
bool AutoCalibrate=true;bool Calibrating=AutoCalibrate;double CalibrateRotation=3;bool NeedsCalibration=!AutoCalibrate;ScreenItem ScreenObjects[]={
  {320,20,150,30,"Page Up",true,vex::color(50,50,50),vex::color(255,255,255)},
  {320,200,150,30,"Page Down",true,vex::color(50,50,50),vex::color(255,255,255)},
  {320,50,150,150,"Autonomous",true,vex::color(50,50,50),vex::color(255,255,255)},
  {25,30,240,70,"Calibrate",true,vex::color(0,130,0),vex::color(255,255,255)},
  {25,120,110,40,"MatchType",true,vex::color(50,50,50),vex::color(255,255,255)},
  {155,120,110,40,"Team",true,vex::color(130,130,0),vex::color(255,255,255)},
};

void ScreenRedraw(){
  if(ControlMode==1){

    for (int i = 0; i < sizeof(ScreenObjects)/sizeof(ScreenObjects[0]); i++){
      if (ScreenObjects[i].NeededState){
        int X=ScreenObjects[i].XPos;int Y=ScreenObjects[i].YPos;
        int Width=ScreenObjects[i].Width;int Height=ScreenObjects[i].Height;
        std::string MainText=ScreenObjects[i].Text;
        vex::color BackgroundColor=Calibrating?vex::color(25,25,25):NeedsCalibration&&std::strcmp(MainText.c_str(),"Calibrate")==0?vex::color(130,0,0):ScreenObjects[i].BackgroundColor;
        vex::color TextColor=ScreenObjects[i].TextColor;
        if (std::strcmp(MainText.c_str(),"Team")==0){
          BackgroundColor=Color==0?vex::color(130,130,0):Color==1?vex::color(130,0,0):vex::color(0,0,130);
        }else if(std::strcmp(MainText.c_str(),"MatchType")==0){
          MainText=AutoType==0?"Quals":AutoType==1?"Elims":"Test";
        }

        if (std::strcmp(MainText.c_str(),"Autonomous")==0){
          auto SelectedArrary=Autons[Color];
          int AutoCount=sizeof(SelectedArrary.AutoNames)/sizeof(SelectedArrary.AutoNames[0]);
          int SelectedAutoPage=(SelectedArrary.SelectedAuto-1)/AutoPerPage+1;

          for (int v=0;v<AutoPerPage;v++){
            int AutoIndex=((SelectedArrary.AutoPage-1)*AutoPerPage)+v;
            if (AutoIndex+1==SelectedArrary.SelectedAuto&&SelectedArrary.AutoPage==SelectedAutoPage){
              BackgroundColor=SelectedArrary.SelectedColor;
            }else{
              BackgroundColor=SelectedArrary.AutoColor;
            }

            std::string AutoName="EMPTY";
            if (AutoIndex<AutoCount){
              AutoName=SelectedArrary.AutoNames[AutoIndex];
            }
            DrawRoundedRectangle(X,Y+10+(v*45),Width,(Height/AutoPerPage)-10,AutoName,BackgroundColor,TextColor);
          }
        }else{
          DrawRoundedRectangle(X,Y,Width,Height,MainText,BackgroundColor,TextColor);
        }
      }
    }

  }
}

void CalibrateHandler(){
  Calibrating=true;
  Controller.rumble("...");
  InertialSensor.calibrate();
  ScreenRedraw();
  waitUntil(!InertialSensor.isCalibrating());
  Calibrating=false;
  NeedsCalibration=false;
  ScreenRedraw();
  Controller.rumble("--");
}

void CheckScreenPressed(){
  if (ControlMode==1&&Brain.Screen.pressing()){
    int XPress=Brain.Screen.xPosition();int YPress=Brain.Screen.yPosition();
    for (int i = 0; i < sizeof(ScreenObjects)/sizeof(ScreenObjects[0]); i++){
      if (ScreenObjects[i].NeededState){
        int X=ScreenObjects[i].XPos;int Y=ScreenObjects[i].YPos;
        int Width=ScreenObjects[i].Width;int Height=ScreenObjects[i].Height;
        std::string MainText=ScreenObjects[i].Text;

        if (TouchInRange(XPress,YPress,X,Y,Width,Height) && std::strcmp(MainText.c_str(),"Autonomous")!=0){
          //? Other Selection
          if(std::strcmp(MainText.c_str(),"Page Up")==0){
            auto SelectedArrary=Autons[Color];
            int AutoCount=sizeof(SelectedArrary.AutoNames)/sizeof(SelectedArrary.AutoNames[0]);
            SelectedArrary.AutoPage+=1;

            if (SelectedArrary.AutoPage>(AutoCount+1)/AutoPerPage){
              SelectedArrary.AutoPage=1;
              }
            break;
          }else if(std::strcmp(MainText.c_str(),"Page Down")==0){
            auto SelectedArrary=Autons[Color];
            int AutoCount=sizeof(SelectedArrary.AutoNames)/sizeof(SelectedArrary.AutoNames[0]);
            SelectedArrary.AutoPage-=1;

            if (SelectedArrary.AutoPage<0){
              SelectedArrary.AutoPage=(AutoCount+1)/AutoPerPage;
              }
            break;
          }else if(std::strcmp(MainText.c_str(),"Calibrate")==0){
            CalibrateHandler();
            break;
          }else if(std::strcmp(MainText.c_str(),"MatchType")==0){
            AutoType+=1;
            if(AutoType>=3){AutoType=0;}
            break;
          }else if(std::strcmp(MainText.c_str(),"Team")==0){
            Color+=1;
            if(Color>=ColorCount){Color=0;}
            auto& SelectedArrary = Autons[Color];
            if (SelectedArrary.SelectedAuto>1){
              std::string SelectedName = Autons[Color].AutoNames[SelectedArrary.SelectedAuto-1];
              Controller.Screen.setCursor(2,1);
              Controller.Screen.print("C: %d A: %s",Color,SelectedName.c_str());
            }
            break;
          }else{
            Controller.rumble("...........");
          }
          //? Other Selection
        }else{
          //? Autonomous Selection
          if (std::strcmp(MainText.c_str(), "Autonomous") == 0) {
            auto& SelectedArrary = Autons[Color];
            for (int v = 0; v < AutoPerPage; v++) {
              if (TouchInRange(XPress, YPress, X, Y + 10 + (v * 45), Width, (Height / AutoPerPage) - 10)) {
                int AutoIndex = ((SelectedArrary.AutoPage - 1) * AutoPerPage) + v + 1;
                
                if (AutoIndex <= sizeof(SelectedArrary.AutoNames) / sizeof(SelectedArrary.AutoNames[0])) {
                  SelectedArrary.SelectedAuto = AutoIndex;
                }

                SelectedAuto=Color*pow(10,(int)log10(AutoIndex)+1)+AutoIndex;
                Controller.rumble(".");
                std::string SelectedName = Autons[Color].AutoNames[SelectedArrary.SelectedAuto-1];
                Controller.Screen.setCursor(2,1);
                Controller.Screen.print("C: %d A: %s",Color,SelectedName.c_str());
                break;
              }
            }
          }
          //? Autonomous Selection
        }
      }
    }

    waitUntil(!Brain.Screen.pressing());
    ScreenRedraw();
  }
}

void SetupSystems(){
  //! Do Not Modify Outside 'Setup Controller & Brain' Section.
  Brain.Screen.clearScreen();
  Controller.Screen.clearScreen();
  Brain.Screen.setFillColor(vex::color(0,0,0));
  Brain.Screen.setPenColor(vex::color(220,220,0));
  
  for (int i = 0; i < 16; i++) {
    Brain.Screen.printAt(1,(i+1)*15,":");
  }

  Brain.Screen.printAt(10,17,"System Setup For 3141Z Bot Commencing...........");
  // Setup Controller & Brain

  if (Competition.isAutonomous() && Competition.isEnabled()){ //? Autonomous
    Controller.Screen.setCursor(1,1);
    Controller.Screen.print("Selected Auto: %d",SelectedAuto);
    Controller.Screen.setCursor(2,1);
    Controller.Screen.print("Needs Calibration: %d",NeedsCalibration&&!Calibrating);
  }else if(Competition.isDriverControl() && Competition.isEnabled()){ //? Driver

  }else{ //? Pre-Auto & Final
    Controller.Screen.setCursor(1,1);
    Controller.Screen.print("Battery: %d",Brain.Battery.capacity(pct));
    if (Competition.isAutonomous() && !Competition.isEnabled()){ //? Pre-Autonomous
      
    }else if(!Competition.isAutonomous()){ //? Match Finished

    }
  }

  //! Finished System Setup.
  wait(5,msec);
  Brain.Screen.printAt(10,17,"System Setup For 3141Z Bot Complete............");
  Brain.Screen.setFillColor(vex::color(0,0,0));
  Brain.Screen.setPenColor(vex::color(255,255,255));
}

void PreAutonomous(void) {
  vexcodeInit(); //! REQUIRED

  ControlMode=1;
  SetupSystems();
  wait(30,msec);
  ScreenRedraw();
  if (AutoCalibrate){CalibrateHandler();}

  auto& SelectedArrary = Autons[Color];
  SelectedAuto=Color*pow(10,(int)log10(SelectedArrary.SelectedAuto)+1)+SelectedArrary.SelectedAuto;

  while (ControlMode==1){ //? Make the button pressing & calibrate coloring run while Pre-Autonomous
    CheckScreenPressed();
    if (std::abs(InertialSensor.rotation()) >= CalibrateRotation&&!NeedsCalibration){
      NeedsCalibration = true;
      ScreenRedraw();
    }
    wait(10, msec);
  }
}