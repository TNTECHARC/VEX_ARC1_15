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

    //out of the way
    autonState = THIRD;
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

    // Clamp preload
    steak.set(true);
    autonState = INTAKE;
    wait(100, msec);

    // Obtain Goal
    chassis.drive_distance(-5.5);
    chassis.turn_to_angle(270);
    chassis.drive_distance(-19);
    chassis.drive_distance(-10, 270, 4, 4);
    mog.set(true);

    // Intake preLoad
    autonState = START;
    wait(100, msec);
    steak.set(false);
    wait(100, msec);
    autonState = INTAKE;
    wait(200, msec);
    intakeOn = true;
    wait(100, msec);
    intakeOn = false;
    wait(300, msec);    

    // Wall Stake
    chassis.drive_distance(-15);
    autonState = START;
    chassis.turn_to_angle(235);
    chassis.drive_distance(10, 235, 4, 4);
    steak.set(true);
    wait(100, msec);

    chassis.drive_distance(-8);
    autonState = ALLIANCE;
    wait(200, msec);
    chassis.turn_to_angle(210);
    chassis.drive_distance(9);
    wait(100, msec);
    steak.set(false);
    wait(100, msec);
    chassis.drive_distance(-5);

    // First Ring
    autonState = START;
    
    chassis.turn_to_angle(296);
    chassis.drive_distance(51);
    chassis.drive_distance(5, 296, 4, 4);
    steak.set(true);
    wait(100, msec);
    chassis.drive_distance(-6);
    autonState = THIRD;
    wait(200, msec);
    chassis.drive_distance(8);
    intakeOn = true;
    chassis.drive_distance(8);
    intakeOn = false;
    wait(500, msec);

    // Second Ring
    steak.set(false);
    wait(100, msec);
    chassis.drive_distance(-1);
    autonState = START;
    chassis.turn_to_angle(180);
    chassis.drive_distance(30);
    steak.set(true);
    chassis.drive_distance(-7);
    steak.set(false);
    wait(200, msec);
    autonState = INTAKE;
    wait(500, msec);
    intakeOn = true;
    wait(100, msec);
    intakeOn = false;

    // Edging the positive corner for rings
    chassis.turn_to_angle(225);

    autonState = THIRD;
    chassis.drive_distance(18, 225, 5, 12);//18
    steak.set(true);
    wait(100, msec);
    chassis.drive_distance(-3, 225, 3, 12);
    autonState = WALL;
    chassis.drive_distance(5, 225, 5, 12);
    intakeOn = true;
    wait(100, msec);
    chassis.drive_distance(-10);
    intakeOn = false;

    autonState = START;
    wait(300, msec);
    steak.set(false);
    wait(100, msec);
    autonState = INTAKE;
    wait(200, msec);
    intakeOn = true;
    wait(200, msec);
    intakeOn = false;

    doinker.set(true);
    chassis.drive_distance(6);
    chassis.right_swing_to_angle(290);
    doinker.set(false);
    chassis.turn_to_angle(45);
    chassis.drive_distance(-20);//13 to low
    mog.set(false);
    wait(300, msec);
    chassis.drive_distance(10);

    //out of the way
    autonState = THIRD;

}

void blue_left_middle_pos()
{

}

void blue_left_front_pos()
{
    initAutonThreads();
    intakeOn = false;
    autonState = INTAKE;
    
    //done to pick which route is used
    chassis.set_heading(90);


    //match load stuff
    steak.set(true);

    //doinker.set(true);
    //wait(700, msec);
    chassis.drive_distance(22);

    //doinker.set(false);
    chassis.turn_to_angle(360-140);
    chassis.drive_distance(14);
    //doinker down
    doinker.set(true);
    chassis.turn_to_angle(360-146);
    chassis.drive_distance(-30, 360-146, 6, 6); //previously -24, -30works
    //doinker up
    doinker.set(false);
    chassis.turn_to_angle(360-315); //last 326
    chassis.drive_distance(-20, 360-315, 4, 4);//last -15, 20 works ish, -23works
    //back clamp
    mog.set(true);
    //wait(300, msec);

    //Above is working

    //match load stuff
    autonState = INTAKE;
    steak.set(false);
    wait(200, msec);
    intakeOn = true;
    wait(200, msec);
    intakeOn = false;


    // chassis.drive_distance(18, 326, 6, 6); //24
    // chassis.turn_to_angle(180);//182

    chassis.turn_to_angle(360-210); //225 is too right?
    chassis.drive_distance(15, 360-210, 6, 6); //17

    //intake top ring
    
    //chassis.drive_distance(26, 182, 6, 6); //previosly 23(too low)
    
    //wait(300, msec);
    steak.set(true);
    //wait(300, msec);
    chassis.drive_distance(-7);
    autonState = SOMTHING; //second is iffy
    wait(200, msec);
    chassis.drive_distance(8); //10 mostly works
    //wait(300, msec);
    
    intakeOn = true;
    chassis.drive_distance(7, 360-182, 3, 3);//formorly 5, 8 barly to high
    //wait(300, msec);
    intakeOn = false;
    chassis.drive_distance(3);

    //newstuff
    //chassis.drive_distance(6,182,6,6); // 18 is slightly to high
    chassis.turn_to_angle(360-360);//360 works
    steak.set(false);
    wait(200, msec);

    //squares up
    chassis.turn_to_angle(360-135);
    chassis.drive_distance(12);//7 works, formorly 8

    
    chassis.turn_to_angle(360-90); //formorly 110
    autonState = BOTTOM;
    chassis.drive_distance(3); //4 is what it was at

    //fixed above
    
    //ring stack on line
    chassis.drive_distance(7,360-90,3,3); // 6 doesnt cross
    steak.set(true);
    //wait(300, msec);
    chassis.drive_distance(-5);
    //chassis.turn_to_angle(80);
    chassis.turn_to_angle(360-10);
    chassis.turn_to_angle(360-285); //290, 280 to left
    steak.set(false);
    //wait(300, msec);
    intakeOn = true;
    wait(100, msec);
    intakeOn = false;

    //everything above works

    autonState = SECOND;
    chassis.drive_distance(40, 360-285, 5, 5); //24 is to low, 290, 280 to left, 30 works
    intakeOn = true;
    wait(100, msec);
    intakeOn = false;
    chassis.drive_distance(-10);

    chassis.drive_distance(7); //formorly 5
    chassis.turn_to_angle(360-220);
    //chassis.drive_distance(2);

    //above working

    // edging the Corner
    //chassis.drive_distance(-1);
    //chassis.turn_to_angle(225);
    autonState = THIRD;
    chassis.drive_distance(14, 360-220, 5, 12);//18
    steak.set(true);
    //wait(300,msec);
    chassis.drive_distance(-5.5, 360-225, 2, 12);

    claw.maxVoltage = 8;
    autonState = ALLIANCE;
    wait(200, msec);
    chassis.drive_distance(6.5);
    intakeOn = true;
    wait(200, msec);
    intakeOn = false;
    chassis.drive_distance(-15);
    autonState = PASSIVE;
    wait(300,msec);
    steak.set(false);
    wait(300, msec);
    intakeOn = true;
    wait(200, msec);
    intakeOn = false;

    //corrnor done

    //chassis.turn_to_angle(225);
    chassis.drive_distance(-2);
    doinker.set(true);
    chassis.drive_distance(12);
    chassis.turn_to_angle(290);
    doinker.set(false);
    chassis.turn_to_angle(40);
    chassis.drive_distance(-10);//12 to far
    mog.set(false);
    chassis.drive_distance(20);

    //out of the way
    autonState = THIRD;




}