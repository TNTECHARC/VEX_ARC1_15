#include "vex.h"

/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
    chassis.set_drive_constants(12, 1.5, 0, 10, 0);
    chassis.set_heading_constants(6, .4, 0, 1, 0);
    chassis.set_turn_constants(10, .4, .03, 3, 15);
    chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
    chassis.set_drive_exit_conditions(1.5, 50, 3000);
    chassis.set_turn_exit_conditions(1, 300, 1500);
    chassis.set_swing_exit_conditions(1, 300, 2000);
}

/**
 * Sets constants to be more effective for odom movements.
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */

void odom_constants(){
    default_constants();
    chassis.heading_max_voltage = 10;
    chassis.drive_max_voltage = 8;
    chassis.drive_settle_error = 3;
    chassis.boomerang_lead = .5;
    chassis.drive_min_voltage = 0;
}

CLAWSTATES autonState = START;

void autonMoveClaw()
{
    autonState = START;
    CLAWSTATES temp = START;
    while(true)
    {
        claw.moveTo(autonState);

        temp = autonState;
        waitUntil(temp != autonState);
    }
}

void initAutonThreads()
{
    thread autonClaw = thread(autonMoveClaw);
    thread intakeThread = thread(intakee);
}

/// NOTES
///
///doinker: doinker.set(true/false)
///
///back clamp: mog.set(true/false)
///
///Wait: wait(500, msec)
///
///Intake: intakeOn = true/false
///
///lift height: autonState = START/INTAKE/SECOND/THIRD/PASSIVE/WALL/ALLIANCE
///
///Lift clamp: steak.set(true/false)
///
///

////////////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////////////
// 15 in Red Routes


void red_left_front_neg()
{
  initAutonThreads();

    // Obtain Goal
    chassis.drive_distance(17);
    //chassis.turn_to_angle(315); // Mirrored from 45
    chassis.turn_to_angle(340);
    chassis.drive_distance(15);
    doinker.set(true);
    wait(300, msec);
    chassis.drive_distance(-19);
    doinker.set(false);
    wait(100, msec);
    //chassis.turn_to_angle(145); // Mirrored from 215
    chassis.turn_to_angle(150);
    wait(100, msec);
    chassis.drive_distance(-17, 150, 4, 4);
    wait(100, msec);
    mog.set(true);
    wait(500, msec);
    chassis.drive_distance(11);

    // Get First Ring
    chassis.turn_to_angle(270);
    autonState = THIRD;
    wait(500, msec);
    chassis.drive_distance(4, 270, 4, 4);
    autonState = INTAKE;
    wait(200, msec);
    steak.set(true);
    wait(100, msec);
    autonState = THIRD;
    wait(300, msec);
    intakeOn = true;
    wait(100, msec);
    intakeOn = false;
    autonState = ALLIANCE;
    chassis.drive_distance(22);

    // Second Ring
    chassis.turn_to_angle(0);
    autonState = THIRD;
    chassis.drive_distance(14, 0, 4, 4);
    autonState = THIRD;
    intakeOn = true;
    wait(100, msec);
    intakeOn = false;
    steak.set(false);

    chassis.left_swing_to_angle(270);
    chassis.turn_to_angle(165);

    // Third Ring
    autonState = START;
    chassis.drive_distance(20);
    chassis.drive_distance(6, 165, 4, 4);
    steak.set(true);
    chassis.drive_distance(-7);
    autonState = THIRD;
    wait(500, msec);
    chassis.drive_distance(12);
    intakeOn = true;
    chassis.drive_distance(4, 165, 4, 4);
    intakeOn = false;

    // Drop current ring
    autonState = TOP;
    steak.set(false);
    wait(200, msec);
    chassis.drive_distance(-2);
    autonState = TOP;
    chassis.turn_to_angle(225); // Mirrored from 130

    // Edging the corner for enemy rings
    autonState = TOP;
    chassis.drive_distance(15, 225, 4, 4);
    autonState = TOP;
    wait(100, msec);
    steak.set(true);
    wait(200, msec);
    chassis.drive_distance(-9);
    autonState = START;
    wait(500, msec);
    steak.set(false);
    wait(100, msec);
    autonState = INTAKE;
    intakeOn = true;
    wait(500, msec);
    intakeOn = false;

    autonState = SECOND;
    wait(100, msec);
    chassis.drive_distance(12, 225, 4, 4);
    steak.set(true);
    wait(300, msec);
    chassis.drive_distance(-9);
    autonState = START;
    steak.set(false);
    autonState = INTAKE;
    intakeOn = true;
    wait(100, msec);
    intakeOn = false;

    // Drop Goal in Corner
    doinker.set(true);
    chassis.drive_distance(4);
    chassis.turn_to_angle(0); // Mirrored from 210
    chassis.turn_to_angle(45);  // Mirrored from 310
    doinker.set(false);
    chassis.drive_distance(-15);
    mog.set(false);
    wait(100, msec);
    chassis.drive_distance(10);
    chassis.turn_to_angle(225);
    chassis.drive_distance(5);
    chassis.drive_distance(-10);
}

void red_left_middle_neg()
{
    initAutonThreads();
}

void red_left_back_neg()
{
    initAutonThreads();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////////////////////////////////////
// 15 in Blue Routes

void blue_left_back_pos()
{
    initAutonThreads();

    // Obtain Goal
    chassis.drive_distance(-5.5);
    chassis.turn_to_angle(270);
    chassis.drive_distance(-19);
    chassis.drive_distance(-10, 270, 4, 4);
    mog.set(true);
    chassis.drive_distance(-3);
    chassis.turn_to_angle(315);
    autonState = INTAKE;
    chassis.drive_distance(20);
    intakeOn = true;
    chassis.drive_distance(5, 315, 4, 4);
    intakeOn = false;
    chassis.turn_to_angle(125);
    chassis.drive_distance(23);
    chassis.turn_to_angle(180);
}

void blue_left_middle_pos()
{

}

void blue_left_front_pos()
{

}