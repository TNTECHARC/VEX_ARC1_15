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
    chassis.set_drive_constants(10, 1.5, 0, 10, 0);
    chassis.set_heading_constants(6, .4, 0, 1, 0);
    chassis.set_turn_constants(12, .4, .03, 3, 15);
    chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
    chassis.set_drive_exit_conditions(1.5, 50, 5000);
    chassis.set_turn_exit_conditions(1, 300, 3000);
    chassis.set_swing_exit_conditions(1, 300, 3000);
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
void blueRightElim()
{

  thread intakethread = thread(intakee);
  thread autonMoveClawthread = thread(autonMoveClaw);
 // thread rushh = thread(rushh);

  //autonState = START;

  // Rush Mobile Goal
  rush.set(true);
  chassis.drive_distance(37.5);
  rush.set(false);
  chassis.drive_distance(-30.5);
  rush.set(true);
  wait(300, msec);
  chassis.drive_distance(-5);
  rush.set(false);
  wait(100, msec);

  // Grab Mobile Goal
  chassis.turn_to_angle(180);
  wait(200, msec);
  chassis.drive_distance(-18);
  chassis.drive_distance(-10, 180, 3, 12);
  mog.set(true);
  wait(300, msec);

  // Pick up first ring
  chassis.drive_distance(10);
  chassis.turn_to_angle(360-34.1, 6);
  chassis.drive_distance(15, 360-35, 6, 12);
  wait(200, msec);
  steak.set(true);
  wait(200, msec);
  chassis.drive_distance(-4);
  autonState = THIRD;
  wait(300, msec);
  chassis.drive_distance(16, 360-35, 5, 12);
  wait(50, msec);
  intakeOn = true;
  wait(300, msec);
  intakeOn = false;
  steak.set(false);
  chassis.drive_distance(-8);
  autonState = PASSIVE;

  // Pick up second ring
  chassis.turn_to_angle(360-150);
  chassis.drive_distance(20,360-150, 8, 12);
  intakeOn = true;
  chassis.drive_distance(3, 360-150, 8, 12);
  wait(300, msec);
  intakeOn = false;

  // edging Corner
  chassis.drive_distance(-1.5);
  chassis.turn_to_angle(360-110);
  autonState = THIRD;
  chassis.drive_distance(17, 360-110, 4, 12);



  // steak.set(true);
  // wait(300,msec);
  // chassis.drive_distance(-5.5, 110, 2, 12);

  // claw.maxVoltage = 8;
  // autonState = ALLIANCE;
  // wait(200, msec);
  // chassis.drive_distance(6.5);
  // intakeOn = true;
  // wait(300, msec);
  // intakeOn = false;

  steak.set(true);
  wait(300,msec);
  chassis.drive_distance(-5.7, 360-110, 2, 12);

  claw.maxVoltage = 8;
  autonState = ALLIANCE;
  wait(200, msec);
  chassis.drive_distance(6.9);
  //intakeOn = true;
  intakeTarget = inrot.position(deg) + 500;
  wait(220, msec);
  //intakeOn = false;
  //intakeOn = true;




  chassis.drive_distance(-15);
  intakeOn = true;
  wait(700,msec);
  intakeOn = false;
  claw.maxVoltage = 12;
  autonState = PASSIVE;
  wait(400,msec);
  steak.set(false);
  wait(300, msec);
  intakeOn = true;
  wait(700, msec);
  intakeOn = false;

  claw.maxVoltage = 12;

  // Last Ring
  chassis.turn_to_angle(114);
  mog.set(false);
  chassis.drive_distance(20);
  ////////////////////////////////////////////
  chassis.turn_to_angle(360-63);
  autonState = NEG;
  chassis.drive_distance(-18);
  chassis.drive_distance(-20,360-63,4,8);
  mog.set(true);

  // Go to ladder
  // chassis.turn_to_angle(300);
  // autonState = WALL;
  // wait(1, sec);
  // chassis.drive_distance(46);

  chassis.turn_to_angle(360-106);
  chassis.drive_distance(11);
  steak.set(true);
  wait(300,msec);
  autonState = ALLIANCE;
  chassis.drive_distance(-5);
  chassis.turn_to_angle(360-125.5);
  chassis.drive_distance(9.5);
  steak.set(false);
  wait(100,msec);
  autonState = DONTPLS;
  chassis.drive_distance(-10);
      autonState = PASSIVE; //get ring ending also
  chassis.turn_to_angle(360-61);

  //get ring part
  chassis.drive_distance(35,360-90);
  intakeOn = true;
  chassis.drive_distance(7);
}


void blueRightWP()
{
  thread intakethread = thread(intakee);
  thread autonMoveClawthread = thread(autonMoveClaw);
 // thread rushh = thread(rushh);

  //autonState = START;

  // Rush Mobile Goal
  rush.set(true);
  chassis.drive_distance(37.5);
  rush.set(false);
  chassis.drive_distance(-30.5);
  rush.set(true);
  wait(300, msec);
  chassis.drive_distance(-5);
  rush.set(false);
  wait(100, msec);

  // Grab Mobile Goal
  chassis.turn_to_angle(180);
  wait(200, msec);
  chassis.drive_distance(-18);
  chassis.drive_distance(-10, 180, 3, 12);
  mog.set(true);
  wait(300, msec);

  // Pick up first ring
  chassis.drive_distance(10);
  chassis.turn_to_angle(34.1, 6);
  chassis.drive_distance(15, 35, 6, 12);
  wait(200, msec);
  steak.set(true);
  wait(200, msec);
  chassis.drive_distance(-4);
  autonState = THIRD;
  wait(300, msec);
  chassis.drive_distance(16, 35, 5, 12);
  wait(50, msec);
  intakeOn = true;
  wait(300, msec);
  intakeOn = false;
  steak.set(false);
  chassis.drive_distance(-8);
  autonState = PASSIVE;

  // Pick up second ring
  chassis.turn_to_angle(150);
  chassis.drive_distance(20, 150, 8, 12);
  intakeOn = true;
  chassis.drive_distance(3, 150, 8, 12);
  wait(300, msec);
  intakeOn = false;

  // edging Corner
  chassis.drive_distance(-1.5);
  chassis.turn_to_angle(110);
  autonState = THIRD;
  chassis.drive_distance(17, 110, 4, 12);



  // steak.set(true);
  // wait(300,msec);
  // chassis.drive_distance(-5.5, 110, 2, 12);

  // claw.maxVoltage = 8;
  // autonState = ALLIANCE;
  // wait(200, msec);
  // chassis.drive_distance(6.5);
  // intakeOn = true;
  // wait(300, msec);
  // intakeOn = false;

  steak.set(true);
  wait(300,msec);
  chassis.drive_distance(-5.7, 110, 2, 12);

  claw.maxVoltage = 8;
  autonState = ALLIANCE;
  wait(200, msec);
  chassis.drive_distance(6.9);
  //intakeOn = true;
  intakeTarget = inrot.position(deg) + 500;
  wait(220, msec);
  //intakeOn = false;
  //intakeOn = true;




  chassis.drive_distance(-15);
  intakeOn = true;
  wait(700,msec);
  intakeOn = false;
  claw.maxVoltage = 12;
  autonState = PASSIVE;
  wait(400,msec);
  steak.set(false);
  wait(300, msec);
  intakeOn = true;
  wait(700, msec);
  intakeOn = false;

  claw.maxVoltage = 12;

  // Last Ring
  chassis.turn_to_angle(-114);
  mog.set(false);
  chassis.drive_distance(20);
  chassis.turn_to_angle(63);
  autonState = NEG;
  chassis.drive_distance(-18);
  chassis.drive_distance(-20,63,4,8);
  mog.set(true);

  // Go to ladder
  // chassis.turn_to_angle(300);
  // autonState = WALL;
  // wait(1, sec);
  // chassis.drive_distance(46);

  chassis.turn_to_angle(106);
  chassis.drive_distance(11);
  steak.set(true);
  wait(300,msec);
  autonState = ALLIANCE;
  chassis.drive_distance(-5);
  chassis.turn_to_angle(124);
  chassis.drive_distance(9.5);
  steak.set(false);
  wait(100,msec);
  autonState = DONTPLS;
  chassis.drive_distance(-10);
     //utonState = PASSIVE; //get ring ending also
  chassis.turn_to_angle(18);

  //get ring part
  chassis.drive_with_voltage(5,5);
  wait(700,msec);
  chassis.drive_with_voltage(0,0);



}

void blueLeftWP()
{
  
  thread intakethread = thread(intakee);
  thread autonMoveClawthread = thread(autonMoveClaw);
 // thread rushh = thread(rushh);

  //autonState = START;

  // Rush Mobile Goal
  rush.set(true);
  chassis.drive_distance(37.5);
  rush.set(false);
  chassis.drive_distance(-30.5);
  rush.set(true);
  wait(300, msec);
  chassis.drive_distance(-5);
  rush.set(false);
  wait(100, msec);

  // Grab Mobile Goal
  chassis.turn_to_angle(180);
  wait(200, msec);
  chassis.drive_distance(-18);
  chassis.drive_distance(-10, 180, 3, 12);
  mog.set(true);
  wait(300, msec);

  // Pick up first ring
  chassis.drive_distance(10);
  chassis.turn_to_angle(360-34.1, 6);
  chassis.drive_distance(15, 360-35, 6, 12);
  wait(200, msec);
  steak.set(true);
  wait(200, msec);
  chassis.drive_distance(-4);
  autonState = THIRD;
  wait(300, msec);
  chassis.drive_distance(16, 360-35, 5, 12);
  wait(50, msec);
  intakeOn = true;
  wait(300, msec);
  intakeOn = false;
  steak.set(false);
  chassis.drive_distance(-8);
  autonState = PASSIVE;

  // Pick up second ring
  chassis.turn_to_angle(360-150);
  chassis.drive_distance(20, 360-150, 8, 12);
  intakeOn = true;
  chassis.drive_distance(3, 360-150, 8, 12);
  wait(300, msec);
  intakeOn = false;

  // edging Corner
  chassis.drive_distance(-1.5);
  chassis.turn_to_angle(360-110);
  autonState = THIRD;
  chassis.drive_distance(17, 360-110, 4, 12);



  // steak.set(true);
  // wait(300,msec);
  // chassis.drive_distance(-5.5, 110, 2, 12);

  // claw.maxVoltage = 8;
  // autonState = ALLIANCE;
  // wait(200, msec);
  // chassis.drive_distance(6.5);
  // intakeOn = true;
  // wait(300, msec);
  // intakeOn = false;

  steak.set(true);
  wait(300,msec);
  chassis.drive_distance(-5.7, 360-110, 2, 12);

  claw.maxVoltage = 8;
  autonState = ALLIANCE;
  wait(200, msec);
  chassis.drive_distance(6.9);
  //intakeOn = true;
  intakeTarget = inrot.position(deg) + 500;
  wait(220, msec);
  //intakeOn = false;
  //intakeOn = true;




  chassis.drive_distance(-15);
  intakeOn = true;
  wait(700,msec);
  intakeOn = false;
  claw.maxVoltage = 12;
  autonState = PASSIVE;
  wait(400,msec);
  steak.set(false);
  wait(300, msec);
  intakeOn = true;
  wait(700, msec);
  intakeOn = false;

  claw.maxVoltage = 12;

  // Last Ring
  chassis.turn_to_angle(114);
  mog.set(false);
  chassis.drive_distance(20);
  chassis.turn_to_angle(360-63);
  autonState = NEG;
  chassis.drive_distance(-18);
  chassis.drive_distance(-20,360-63,4,8);
  mog.set(true);

  // Go to ladder
  // chassis.turn_to_angle(300);
  // autonState = WALL;
  // wait(1, sec);
  // chassis.drive_distance(46);

  chassis.turn_to_angle(360-106);
  chassis.drive_distance(11);
  steak.set(true);
  wait(300,msec);
  autonState = ALLIANCE;
  chassis.drive_distance(-5);
  chassis.turn_to_angle(360-124);
  chassis.drive_distance(9.5);
  steak.set(false);
  wait(100,msec);
  autonState = DONTPLS;
  chassis.drive_distance(-10);
     //utonState = PASSIVE; //get ring ending also
  chassis.turn_to_angle(18);

  //get ring part
  chassis.drive_with_voltage(5,5);
  wait(700,msec);
  chassis.drive_with_voltage(0,0);

}




void red_route_skills_Sec(){


  wait(15, sec);
    
  thread intakethread = thread(intakee);
  thread autonMoveClawthread = thread(autonMoveClaw);


    intakeOn = false;
    autonState = INTAKE;


    
    //1
    chassis.set_heading(360-305);
    chassis.drive_distance(-23);
    chassis.drive_distance(-5, 360-305, 3, 12);
    mog.set(true);
    wait(500, msec);
    chassis.drive_distance(7);
    //2
    chassis.turn_to_angle(360-245);
    chassis.drive_distance(13);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;

    //3
    chassis.turn_to_angle(360-228);
    chassis.drive_distance(15);
    chassis.drive_distance(6, 360-228, 3, 12);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;
    chassis.drive_distance(-5);
    autonState = INTAKE;

    //4
    chassis.turn_to_angle(360-47);
    chassis.drive_distance(35);
    chassis.drive_distance(5, 360-44, 3, 12);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;
    chassis.drive_distance(4);

    //5
    chassis.turn_to_angle(360-46);
    chassis.drive_distance(18);
    chassis.drive_distance(12, 360-43, 3, 12);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;
    //6   
    //7
    autonState = INTAKE;
    chassis.drive_distance(17, 360-40, 3, 12);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;
    wait(500, msec);
    chassis.drive_distance(-17);
    //chassis.turn_to_angle(47);
    //8
    chassis.drive_distance(-77);
    mog.set(false);
    //9
    chassis.turn_to_angle(360-63);
    chassis.drive_distance(45);
    //10
    chassis.turn_to_angle(360-266);
    chassis.drive_distance(-27);
    //11
    chassis.turn_to_angle(360-232);
    //12
    chassis.drive_distance(-20, 360-232, 3, 12);
    mog.set(true);
    wait(500, msec);


    //STEP TWO


    //1
    //autonState = START;
    chassis.turn_to_angle(360-223);
    chassis.drive_distance(12);
    //2
    chassis.drive_distance(23, 360-235, 3, 12);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;

    //3
    chassis.turn_to_angle(180);
    //autonState = START;
    chassis.drive_distance(7, 180, 3, 12);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;
    //4
    chassis.drive_distance(-15);
    chassis.turn_to_angle(360-72);
    chassis.drive_distance(40);
    chassis.drive_distance(10, 360-72, 3, 12);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;

    //5
    chassis.turn_to_angle(180);
    chassis.drive_distance(14);
    chassis.drive_distance(10, 180, 3, 12);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;
    chassis.drive_distance(15);
    chassis.drive_distance(-15);
    
    //6
    chassis.turn_to_angle(360-270);
    chassis.drive_distance(20);
    chassis.drive_distance(14);
    chassis.drive_distance(10, 180, 3, 12);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;

    //7
    chassis.turn_to_angle(260-112);
    chassis.drive_distance(70);
    chassis.drive_distance(15, 360-112, 3, 12);
    chassis.drive_distance(14);
    chassis.drive_distance(10, 180, 3, 12);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;

    //8
    chassis.turn_to_angle(360-348);
    mog.set(false);
    chassis.drive_distance(20);









    // autonState = SECOND;
    // //5
    // chassis.turn_to_angle(90);
    // chassis.drive_distance(10);
    // chassis.drive_distance(5, 90, 3, 12);
    // steak.set(true);
    // chassis.drive_distance(8, 90, 3, 12);
    // intakeOn = true;
    // wait(300, msec);
    // intakeOn = false;
    // chassis.turn_to_angle(270);
    // steak.set(false);
    // chassis.turn_to_angle(270);
    // //6
    // chassis.turn_to_angle(48);
    // chassis.drive_distance(18);
    // chassis.drive_distance(4, 48, 3, 12);
    // steak.set(true);
    // chassis.drive_distance(8, 48, 3, 12);
    // intakeOn = true;
    // wait(300, msec);
    // intakeOn = false;
    // chassis.turn_to_angle(270);
    // steak.set(false);
    // chassis.turn_to_angle(48);
    // //7
    // chassis.turn_to_angle(173);
    // chassis.drive_distance(14, 173, 3, 12);
    // intakeOn = true;
    // wait(300, msec);
    // intakeOn = false;
    // //8
    // chassis.drive_distance(8);
    // chassis.turn_to_angle(143);
    // chassis.drive_distance(20);
    // intakeOn = true;
    // wait(300, msec);
    // intakeOn = false;

    //STEP THREE

    chassis.turn_to_angle(360-358);
    mog.set(false);
    chassis.drive_distance(52);
    autonState = START;
    steak.set(true);
    wait(500, msec);
    autonState = WALL;
    chassis.turn_to_angle(0);
    chassis.drive_distance(8);
    chassis.turn_to_angle(360-90);
    steak.set(false);
    chassis.drive_distance(-12);
    mog.set(true);
    chassis.turn_to_angle(0);
    chassis.drive_distance(16);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;








}

void red_route_skills(){



    
  thread intakethread = thread(intakee);
  thread autonMoveClawthread = thread(autonMoveClaw);


    intakeOn = false;
    autonState = INTAKE;


    
    //1
    chassis.set_heading(305);
    chassis.drive_distance(-23);
    chassis.drive_distance(-5, 305, 3, 12);
    mog.set(true);
    wait(500, msec);
    chassis.drive_distance(7);
    //2
    chassis.turn_to_angle(245);
    chassis.drive_distance(13);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;

    //3
    chassis.turn_to_angle(228);
    chassis.drive_distance(15);
    chassis.drive_distance(6, 228, 3, 12);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;
    chassis.drive_distance(-5);
    autonState = INTAKE;

    //4
    chassis.turn_to_angle(47);
    chassis.drive_distance(35);
    chassis.drive_distance(5, 44, 3, 12);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;
    chassis.drive_distance(4);

    //5
    chassis.turn_to_angle(46);
    chassis.drive_distance(18);
    chassis.drive_distance(12, 43, 3, 12);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;
    //6   
    //7
    autonState = INTAKE;
    chassis.drive_distance(17, 40, 3, 12);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;
    wait(500, msec);
    chassis.drive_distance(-17);
    //chassis.turn_to_angle(47);
    //8
    chassis.drive_distance(-77);
    mog.set(false);
    //9
    chassis.turn_to_angle(63);
    chassis.drive_distance(45);
    //10
    chassis.turn_to_angle(266);
    chassis.drive_distance(-27);
    //11
    chassis.turn_to_angle(232);
    //12
    chassis.drive_distance(-20, 232, 3, 12);
    mog.set(true);
    wait(500, msec);


    //STEP TWO


    //1
    //autonState = START;
    chassis.turn_to_angle(223);
    chassis.drive_distance(12);
    //2
    chassis.drive_distance(23, 235, 3, 12);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;

    //3
    chassis.turn_to_angle(180);
    //autonState = START;
    chassis.drive_distance(7, 180, 3, 12);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;
    //4
    chassis.drive_distance(-15);
    chassis.turn_to_angle(72);
    chassis.drive_distance(40);
    chassis.drive_distance(10, 72, 3, 12);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;

    //5
    chassis.turn_to_angle(180);
    chassis.drive_distance(14);
    chassis.drive_distance(10, 180, 3, 12);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;
    chassis.drive_distance(15);
    chassis.drive_distance(-15);
    
    //6
    chassis.turn_to_angle(270);
    chassis.drive_distance(20);
    chassis.drive_distance(14);
    chassis.drive_distance(10, 180, 3, 12);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;

    //7
    chassis.turn_to_angle(112);
    chassis.drive_distance(70);
    chassis.drive_distance(15, 112, 3, 12);
    chassis.drive_distance(14);
    chassis.drive_distance(10, 180, 3, 12);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;

    //8
    chassis.turn_to_angle(348);
    mog.set(false);
    chassis.drive_distance(20);









    // autonState = SECOND;
    // //5
    // chassis.turn_to_angle(90);
    // chassis.drive_distance(10);
    // chassis.drive_distance(5, 90, 3, 12);
    // steak.set(true);
    // chassis.drive_distance(8, 90, 3, 12);
    // intakeOn = true;
    // wait(300, msec);
    // intakeOn = false;
    // chassis.turn_to_angle(270);
    // steak.set(false);
    // chassis.turn_to_angle(270);
    // //6
    // chassis.turn_to_angle(48);
    // chassis.drive_distance(18);
    // chassis.drive_distance(4, 48, 3, 12);
    // steak.set(true);
    // chassis.drive_distance(8, 48, 3, 12);
    // intakeOn = true;
    // wait(300, msec);
    // intakeOn = false;
    // chassis.turn_to_angle(270);
    // steak.set(false);
    // chassis.turn_to_angle(48);
    // //7
    // chassis.turn_to_angle(173);
    // chassis.drive_distance(14, 173, 3, 12);
    // intakeOn = true;
    // wait(300, msec);
    // intakeOn = false;
    // //8
    // chassis.drive_distance(8);
    // chassis.turn_to_angle(143);
    // chassis.drive_distance(20);
    // intakeOn = true;
    // wait(300, msec);
    // intakeOn = false;

    //STEP THREE

    chassis.turn_to_angle(358);
    mog.set(false);
    chassis.drive_distance(52);
    autonState = START;
    steak.set(true);
    wait(500, msec);
    autonState = WALL;
    chassis.turn_to_angle(0);
    chassis.drive_distance(8);
    chassis.turn_to_angle(90);
    steak.set(false);
    chassis.drive_distance(-12);
    mog.set(true);
    chassis.turn_to_angle(0);
    chassis.drive_distance(16);
    intakeOn = true;
    wait(300, msec);
    intakeOn = false;




}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////NEW ROUTES//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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


void red_right_front_pos(){

          
  thread intakethread = thread(intakee);
  thread autonMoveClawthread = thread(autonMoveClaw);


    intakeOn = false;
    autonState = INTAKE;
    
    //done to pick which route is used
    chassis.set_heading(90);
   
    //doinker.set(true);
    //wait(700, msec);
    chassis.drive_distance(22);

    //doinker.set(false);
    chassis.turn_to_angle(140);
    chassis.drive_distance(14);
    //doinker down
    doinker.set(true);
    chassis.turn_to_angle(146);
    chassis.drive_distance(-30, 146, 6, 6); //previously -24
    //doinker up
    doinker.set(false);
    chassis.turn_to_angle(315); //last 326
    chassis.drive_distance(-23, 315, 4, 4);//last -15, 20 works ish
    //back clamp
    mog.set(true);
    wait(500, msec);

    //Above is working


    chassis.drive_distance(18, 326, 6, 6); //24
    chassis.turn_to_angle(180);//182
    //intake top ring
    
    chassis.drive_distance(26, 182, 6, 6); //previosly 23(too low)
    
    wait(300, msec);
    steak.set(true);
    wait(300, msec);
    chassis.drive_distance(-7);
    autonState = SECOND;
    chassis.drive_distance(7);
    wait(500, msec);
  
    intakeOn = true;
    chassis.drive_distance(8, 182, 3, 3);
    wait(300, msec);
    intakeOn = false;

    //newstuff
    //chassis.drive_distance(6,182,6,6); // 18 is slightly to high
    steak.set(false);
    chassis.turn_to_angle(110);
    autonState = BOTTOM;
    chassis.drive_distance(16); //18 too high 14 to low

    //fixed above


    //replace with doinker to get rings off
    //ring stack on line
    chassis.drive_distance(4,110,3,3);
    steak.set(true);
    wait(700, msec);
    chassis.turn_to_angle(290);
    steak.set(false);
    intakeOn = true;
    chassis.drive_distance(15);
    intakeOn = false;
    chassis.drive_distance(15);
    //intake back ring stack

    chassis.drive_distance(15);
    //take match load sat to the side of robot
    chassis.drive_distance(-15);
    chassis.turn_to_angle(225);
    chassis.drive_distance(16);

    

      



    //PUT CODE TO EMPTY BOTTOM AND THIRD RINGS ONTO GOAL / CLEAR GOAL / AND BUT GOAL INTO CORRNER




}



void red_right_middle_pos(){
  
  intakeOn = false;
  autonState = INTAKE;
  
  // Start heading set to match photo's right-side orientation
  chassis.set_heading(90);
  
  
  
  }



void red_left_front_neg(){};
void red_left_middle_neg(){};

void blue_right_front_pos(){};
void blue_right_middle_pos(){};
void blue_right_back_pos(){};






