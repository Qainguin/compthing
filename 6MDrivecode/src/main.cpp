/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Justin Lopez                                              */
/*    Created:      4/23/2024, 2:27:03 PM                                     */
/*    Description:  Code for 2024-2025 VRC High Stakes                        */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
controller user;

// define your global instances of motors and other devices here

// Diameter of wheels
const float WHEEL_DIAMETER = 3.25; 
// Circumference of wheels
const float WHEEL_CIRCUMFERENCE = WHEEL_DIAMETER * 3.1416; 
// Distance between top-left wheel and bottom-right wheel
const float TURNING_DIAMETER = 19.0;

// RPM of drivetrain
const int RPM = 200;
// Gear ratio of drivetrain
const int GEAR_RATIO = 18;


// Speed values
const int QUARTER_SPEED = 25;
const int HALF_SPEED = 50;
const int FULL_SPEED = 100;

// L = 17, 18, 19
motor L1 = motor(17, true);
motor L2 = motor(18, true);
motor L3 = motor(19, true);

// R = 10, 11, 12
motor R1 = motor(10);
motor R2 = motor(11);
motor R3 = motor(12);

motor_group left_drive_motors = motor_group(L1, L2, L3);
motor_group right_drive_motors = motor_group(R1, R2, R3);

motor_group all_drive_motors = motor_group(L1, L2, L3, R1, R2, R3);

drivetrain robot = drivetrain(left_drive_motors, right_drive_motors);

float drive_velocity = 0;



// Resets the drive velocities to 0.
void reset() {
  robot.setDriveVelocity(0, pct);
  robot.setTurnVelocity(0, pct);
}

// Sets drive velocities to the given speed parameter.
void drive(int speed = 0) {
  robot.drive(fwd, speed, pct);
}

// Sets the left drive velocity to the speed variable and the right drive velocity to the opposite of speed.
void turn(int speed = 0) {
  robot.turn(right, speed, pct);
}


void auton_drive(float inches = 0, float speed = FULL_SPEED) {
  robot.driveFor(inches, in, speed, pct);
}

void auton_turn(float degrees = 0, float speed = FULL_SPEED) {
  robot.turnFor(degrees, deg, speed, pct);
}


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

    reset()
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
