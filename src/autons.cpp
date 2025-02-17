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

/**
 * The expected behavior is to return to the start position.
 */

void drive_test(){
  chassis.drive_distance(6);
  chassis.drive_distance(12);
  chassis.drive_distance(18);
  chassis.drive_distance(-36);
}

/**
 * The expected behavior is to return to the start angle, after making a complete turn.
 */

void turn_test(){
  chassis.turn_to_angle(5);
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
}

/**
 * Should swing in a fun S shape.
 */

void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

/**
 * A little of this, a little of that; it should end roughly where it started.
 */

void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

/**
 * Doesn't drive the robot, but just prints coordinates to the Brain screen 
 * so you can check if they are accurate to life. Push the robot around and
 * see if the coordinates increase like you'd expect.
 */

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    //task::sleep(20);
  }
}

/**
 * Should end in the same place it began, but the second movement
 * will be curved while the first is straight.
 */

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

/**
 * Drives in a square while making a full turn in the process. Should
 * end where it started.
 */

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_pose(0, 18, 90);
  chassis.holonomic_drive_to_pose(18, 0, 180);
  chassis.holonomic_drive_to_pose(0, 18, 270);
  chassis.holonomic_drive_to_pose(0, 0, 0);
}


CLAWSTATES autonState = START;

void autonMoveClaw()
{
  
  CLAWSTATES temp = autonState;
  while(true)
  {
    claw.moveTo(autonState);

    temp = autonState;
    waitUntil(temp != autonState);
  }
}

// void rushh()
// {
//   while (1)
//   {
//     if((chassis.get_left_position_in() + chassis.get_right_position_in() /2) >34.9)
//     {
//       rush.set(false);
//       return;
//     }
//     wait(10,msec);
//   }
// }


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
  chassis.turn_to_angle(-114+177);
  autonState = NEG;
  chassis.drive_distance(-18);
  chassis.drive_distance(-20,-114+177,4,8);
  mog.set(true);

  // Go to ladder
  // chassis.turn_to_angle(300);
  // autonState = WALL;
  // wait(1, sec);
  // chassis.drive_distance(46);

  chassis.turn_to_angle(-114+175+45);
  chassis.drive_distance(11);
  steak.set(true);
  wait(300,msec);
  autonState = ALLIANCE;
  chassis.drive_distance(-5);
  chassis.turn_to_angle(-114+175+45+19.5);
  chassis.drive_distance(9.5);
  steak.set(false);
  wait(100,msec);
  autonState = DONTPLS;
  chassis.drive_distance(-10);
      autonState = PASSIVE; //get ring ending also
  chassis.turn_to_angle(-114+175);

  //get ring part
  chassis.drive_distance(35,90);
  intakeOn = true;
  chassis.drive_distance(7);



}


void blueLeftElim()
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

