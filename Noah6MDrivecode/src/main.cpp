/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       Drive2790.cpp                                             */
/*    Author:       C:\Users\vcs                                              */
/*    Created:      Tue Feb 27 2024                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// R1                   motor         11              
// R2                   motor         12              
// R3                   motor         13              
// L1                   motor         18              
// L2                   motor         19              
// L3                   motor         20              
// Controller1          controller                    
// Intake               motor         16              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;
competition Compitition;

// Set Up Motor Groups

motor_group LDrive = motor_group(L1, L2, L3);
motor_group RDrive = motor_group(R1, R2, R3);
motor_group Allmotors = motor_group(L1, L2, L3, R1, R2, R3);

// Driverain Variables

int joystickMax = 97;
int drivetrain = 0;
int rumbleCount = 0;
double wheelDiam = 3.25; // Wheel Size 
double wheelSeperation = 11.17/2; // space between wheels devided by 2
int autonDelay = 125;


void intakerun(void) {
  Intake.spin(forward);

}
void intakestop(void) {
  Intake.stop();

}
void pre_auton(void){
  vexcodeInit();
  
   //Set Up Motor
  Allmotors.setMaxTorque(100, percent);
  Allmotors.setStopping(brake);
}

double autonSkip = 5000;

void autonDrive(double Inches, int botvel) { //Distance and speed
  Allmotors.setPosition(0, degrees); //Resest positions 
  Allmotors.setVelocity(botvel,rpm); //how fast in rpm
  double mtr_deg = (Inches/wheelDiam) * (216/M_PI); //36 over 60 is gear ratio
  int autonStartTime = Brain.timer(msec);
  if (signbit(Inches) == false) { //signbit(positive) -> false //signbit(negitive) -> true
    Allmotors.spin(forward);
    while(Allmotors.position(degrees) <= mtr_deg) {
      if (Brain.timer(msec) - autonStartTime > autonSkip) { break; }
    }
    Allmotors.stop();
  } else {
    Allmotors.spin(reverse);
    while(Allmotors.position(degrees) >= mtr_deg) {
      if (Brain.timer(msec) - autonStartTime > autonSkip) { break; }
    }
    Allmotors.stop();;
  } 
  wait(200, msec);
}

void autonTurn(double turnDeg, int botVel) {
  LDrive.setVelocity(botVel, rpm);
  RDrive.setVelocity(botVel, rpm);
  LDrive.setPosition(0, degrees);
  RDrive.setPosition(0, degrees);
  double mtr_deg = (1.2 * turnDeg * wheelSeperation)/wheelDiam;
  int autonStartTime = Brain.timer(msec);
  if (signbit(turnDeg) == false) {
    LDrive.spin(forward);
    RDrive.spin(forward);
    while((LDrive.position(degrees) - RDrive.position(degrees))/2 <= mtr_deg) {
      if (Brain.timer(msec) - autonStartTime > autonSkip) { break; }
      }
    LDrive.stop();
    RDrive.stop();
  } else {
    LDrive.spin(reverse);
    RDrive.spin(forward);
    while((-LDrive.position(degrees) + RDrive.position(degrees))/2 <= -mtr_deg) {
      if (Brain.timer(msec) - autonStartTime > autonSkip) { break; }
  }
  LDrive.stop();
  RDrive.stop();
  }
  wait(autonDelay, msec);
}
void autonomous(void) { //put drive code here 
  autonDrive(-10,100); // forward
  autonDrive(10, 100);//backwards
  wait(1, sec); //stop
  autonTurn(180, 100);//Left
  autonTurn(-180,100);//Right
  autonDrive(20,100);
  autonDrive(-20,100);
  autonTurn(180,100);
  autonTurn(-180,100);
 

}

void usercontrol(void) {
  double leftArcade, rightArcade;
  double turnSlope = 200/joystickMax;
  double driveslope = 200/cbrt(joystickMax);
  Allmotors.spin(forward);

  while(true) {
    leftArcade = (driveslope * cbrt(Controller1.Axis3.position())) + (turnSlope * (Controller1.Axis1.position()));
    rightArcade = (driveslope * cbrt(Controller1.Axis3.position())) - (turnSlope * (Controller1.Axis1.position()));

    LDrive.setVelocity(leftArcade,percent);
    RDrive.setVelocity(rightArcade,percent);



    wait(10, msec);
  }
}
int main() {
  Compitition.autonomous(autonomous);
  Compitition.drivercontrol(usercontrol);

  pre_auton();

  Controller1.ButtonR2.pressed(intakerun);
  Controller1.ButtonR2.released(intakestop);

  while(true) {
    wait(50, msec);
  }
 

}
