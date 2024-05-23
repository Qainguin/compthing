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

float drive_velocity = 0;

// This function runs before the autonomous period.

void pre_auton(void) {
  robot.setStopping(brake);
}

void autonomous(void) {
  drive(FULL_SPEED);
  wait(200, msec);
  reset();
}

void usercontrol(void) {
  // User control code here, inside the loop
  autonomous();

  while (1) {
    reset();
    drive(user.Axis3.position(pct));
    turn(user.Axis1.position(pct));

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// main will set up the competition functions and callbacks.
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
