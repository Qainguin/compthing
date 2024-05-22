/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Justin Lopez                                              */
/*    Created:      4/23/2024, 2:27:03 PM                                     */
/*    Description:  Code for 2024-2025 VRC High Stakes                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "robot.h"
#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
controller user;

// define your global instances of motors and other devices here


// Diameter of wheels
const float WHEEL_DIAMETER = 3.25; 

// RPM of drivetrain
const int RPM = 200;
// Gear ratio of drivetrain
const int GEAR_RATIO = 18;

float drive_velocity = 0;

// This function runs before the autonomous period.

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

  robot.setStopping(brake);
}

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

  drive(FULL_SPEED);
  wait(200, msec);
  reset();
}

void usercontrol(void) {
  // User control code here, inside the loop
  autonomous();

  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    reset();
    drive(user.Axis3.position(pct));
    turn(user.Axis1.position(pct));

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
