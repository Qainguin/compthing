/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       vcs                                                       */
/*    Created:      4/23/2024, 2:27:03 PM                                     */
/*    Description:  Code for 2024-2025 VEX Robotics Season                    */
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
  left_drive_motors.setVelocity(left_drive_velocity, pct);
  right_drive_motors.setVelocity(right_drive_velocity, pct);
}

void reset_drivetrain() {
  left_drive_velocity = 0;
  right_drive_velocity = 0;
  update_drivetrain();
}

void drive(int speed = 0) {
  left_drive_velocity += speed;
  right_drive_velocity += speed;
}

void turn(int speed = 0) {
  left_drive_velocity += speed;
  right_drive_velocity -= speed;
}

// Autonomous Driving Functions
void auton_drive(float inches = 4, int speed = 50) {
  float inches_per_degree = wheel_circumference / 360;
  float degrees = inches / inches_per_degree;

  all_drive_motors.spinFor(degrees * GEAR_RATIO, deg, speed, pct);
}

void auton_turn(float degrees = 90.0, int speed = 50) {
  float turning_ratio = TURNING_DIAMETER / WHEEL_DIAMETER;
  float wheel_degrees = turning_ratio * degrees;

  left_drive_motors.spinFor(wheel_degrees * GEAR_RATIO / 2, deg, speed, pct);
  right_drive_motors.spinFor(wheel_degrees * GEAR_RATIO / 2, deg, -speed, pct);
}

// This function runs before the autonomous period.

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

  all_drive_motors.setStopping(brake);
  all_drive_motors.spin(forward);

}

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

  auton_drive();
  auton_turn(90);
  wait(50, msec);
  auton_drive();
  auton_turn(-90);
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
