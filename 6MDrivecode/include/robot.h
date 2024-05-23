#ifndef ROBOT_H
#define ROBOT_H

extern vex::drivetrain robot;

void auton_drive(double distance, double speed);
void auton_turn(double angle = 90);

void reset();
void drive(int speed);
void turn(int speed);

#endif // ROBOT_H
