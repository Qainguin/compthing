// robot.h
#ifndef ROBOT_H
#define ROBOT_H

#include "vex.h"  // Include the VEX header that defines the drivetrain class

extern vex::drivetrain robot;  // Declare the robot variable

extern const int QUARTER_SPEED;
extern const int HALF_SPEED;
extern const int FULL_SPEED;

void reset();

void drive(int speed = 0);
void turn(int speed = 0);
void auton_drive(int speed, float distance);
void auton_turn(float angle);

#endif // ROBOT_FUNCTIONS_H
