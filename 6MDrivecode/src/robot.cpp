#include "vex.h"
#include "robot.h"


// Speed values
const int QUARTER_SPEED = 25;
const int HALF_SPEED = 50;
const int FULL_SPEED = 100;

// L = 17, 18, 19
vex::motor L1 = vex::motor(17, true);
vex::motor L2 = vex::motor(18, true);
vex::motor L3 = vex::motor(19, true);

// R = 10, 11, 12
vex::motor R1 = vex::motor(10);
vex::motor R2 = vex::motor(11);
vex::motor R3 = vex::motor(12);

vex::motor_group left_drive_motors = vex::motor_group(L1, L2, L3);
vex::motor_group right_drive_motors = vex::motor_group(R1, R2, R3);

vex::motor_group all_drive_motors = vex::motor_group(L1, L2, L3, R1, R2, R3);

vex::drivetrain robot = vex::drivetrain(left_drive_motors, right_drive_motors);

// Function that resets the drive velocities to 0.
void reset() {
  robot.setDriveVelocity(0, vex::pct);
  robot.setTurnVelocity(0, vex::pct);
}

// Function to drive the robot at a certain speed for a certain duration
void drive(int speed) {
    robot.setDriveVelocity(speed, vex::velocityUnits::pct);
    robot.drive(vex::directionType::fwd);
}

// Function to turn the robot by a certain angle at a certain speed
void turn(int speed) {
    robot.setTurnVelocity(speed, vex::velocityUnits::pct);
    robot.turn(vex::right, speed, vex::velocityUnits::pct);
}

// Function to autonomously drive a certain distance at a certain speed
void auton_drive(float speed = FULL_SPEED, float distance = 1.0) {
    robot.setDriveVelocity(speed, vex::velocityUnits::pct);
    robot.driveFor(distance, vex::distanceUnits::in);
}

// Function to autonomously turn the robot by a certain angle
void auton_turn(float angle = 90) {
    robot.setTurnVelocity(50, vex::velocityUnits::pct); // Assuming a default speed of 50%
    robot.turnFor(angle, vex::rotationUnits::deg);
}
