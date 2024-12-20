#include "vex.h"
#include "robotConfig.h"
#include <stdio.h>
#include <sstream>
#include <string>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace vex;

void DrawRoundedRectangle(int X,int Y,int Width,int Height,std::string Text,vex::color BackgroundColor,vex::color TextColor){
  int CornerRadius=Height/2;

  Brain.Screen.setFillColor(BackgroundColor);
  Brain.Screen.setPenColor(TextColor);
  Brain.Screen.drawCircle(X+CornerRadius,Y+CornerRadius,CornerRadius);
  Brain.Screen.drawCircle(X+Width-CornerRadius,Y+CornerRadius,CornerRadius);
  Brain.Screen.drawRectangle(X+CornerRadius,Y,Width-2*CornerRadius,Height+1);
  Brain.Screen.setPenColor(BackgroundColor);
  Brain.Screen.drawLine(X+CornerRadius,Y+1,X+CornerRadius,Y+Height-1); // Left Cover
  Brain.Screen.drawLine(X+Width-CornerRadius-1,Y+1,X+Width-CornerRadius-1,Y+Height-1); // Right Cover

  Brain.Screen.setPenColor(TextColor);
  int TWidth=Brain.Screen.getStringWidth(Text.c_str());int THeight=Brain.Screen.getStringHeight(Text.c_str());
  Brain.Screen.printAt(X+(Width-TWidth)/2,Y+12+((Height+1)-THeight)/2,Text.c_str());
}