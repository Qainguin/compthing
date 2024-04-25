/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       vcs                                                       */
/*    Created:      4/23/2024, 2:27:03 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
controller user;

// define your global instances of motors and other devices here

const float wheel_diameter = 3.25; // Diameter of wheels
const float track_width = 16; // Distance betweeen left and right wheels

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

// Drive Velocities
float left_drive_velocity = 0;
float right_drive_velocity = 0;


// User Driving Functions
void update_drivetrain() {
  left_drive_motors.setVelocity(left_drive_velocity);
  right_drive_motors.setVelocity(right_drive_velocity);
}

void drive(speed : int = 0) {
  left_drive_velocity += speed;
  right_drive_velocity += speed;
}

void turn(speed : int = 0) {
  left_drive_velocity += speed;
  right_drive_velocity -= speed;
}

// Autonomous Driving Functions
void auton_drive(time : float = 0.5, speed : int = 100) {
  left_drive_velocity = speed
  right_drive_velocity = speed
  update_drivetrain()
  wait(time)
}

void auton_turn(time : int = 0.5, speed : int = 100) {
  left_drive_velocity = speed
  right_drive_velocity = -speed
  update_drivetrain()
  wait(time)
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/


void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...


  all_drive_motors.setStopping(brake);
  all_drive_motors.spin(forward);

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

  auton_drive(0.5)
  auton_turn(0.5)
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    left_drive_velocity = 0;
    right_drive_velocity = 0;

    drive(user.Axis3.position(pct));
    turn(user.Axis1.position(pct));
    update_drivetrain();

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
