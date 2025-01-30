#include "vex.h"

using namespace vex;
competition Competition;

/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors. In VEXcode Pro V5, you can do this using the graphical          */
/*  configurer port icon at the top right. In the VSCode extension, you'll   */
/*  need to go to robot-config.cpp and robot-config.h and create the         */
/*  motors yourself by following the style shown. All motors must be         */
/*  properly reversed, meaning the drive should drive forward when all       */
/*  motors spin forward.                                                     */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your motors.                                     */
/*---------------------------------------------------------------------------*/

Drive chassis(

//Pick your drive setup from the list below:
//ZERO_TRACKER_NO_ODOM
//ZERO_TRACKER_ODOM
//TANK_ONE_FORWARD_ENCODER
//TANK_ONE_FORWARD_ROTATION
//TANK_ONE_SIDEWAYS_ENCODER
//TANK_ONE_SIDEWAYS_ROTATION
//TANK_TWO_ENCODER
//TANK_TWO_ROTATION
//HOLONOMIC_TWO_ENCODER
//HOLONOMIC_TWO_ROTATION
//
//Write it here:
ZERO_TRACKER_NO_ODOM,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

//Left Motors:
motor_group(L1,L2,L3,L4),

//Right Motors:
motor_group(R1,R2,R3,R4),

//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT4,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
2.5,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
1,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
360,

/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT1,     -PORT2,

//LB:      //RB: 
PORT3,     -PORT4,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
3,

//Input the Forward Tracker diameter (reverse it to make the direction switch):
2.75,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
-2,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
1,

//Sideways tracker diameter (reverse to make the direction switch):
-2.75,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
5.5

);

int current_auton_selection = 0;
bool auto_started = false;

/**
 * Function before autonomous. It prints the current auton number on the screen
 * and tapping the screen cycles the selected auton by 1. Add anything else you
 * may need, like resetting pneumatic components. You can rename these autons to
 * be more descriptive, if you like.
 */

void pre_auton() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  default_constants();
  chassis.Gyro.calibrate();
  waitUntil(!chassis.Gyro.isCalibrating());

  
}

/**
 * Auton function, which runs the selected auton. Case 0 is the default,
 * and will run in the brain screen goes untouched during preauton. Replace
 * drive_test(), for example, with your own auton function you created in
 * autons.cpp and declared in autons.h.
 */

void autonomous(void) {
  auto_started = true;
  switch(current_auton_selection){ 
    case 0:
      red_route_match();
      break;
    case 1:         
      red_route_match();
      break;
    
 }
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

//lift desired poition degree times 7


//Intake Thread Function
void intaker() 
{
  bool intakePress = false;

  while (true) 
  {
    //When pressed L1 activate intake
    if(Controller1.ButtonL1.pressing() && !intakePress)
    {
      Lin.setVelocity(100, pct);
      Rin.setVelocity(100, pct);
      Lin.spinFor((270 * 78 / 12), deg);
      Rin.spinFor((270 * 78 / 12), deg);
      intakePress = true;
    }
    else if(!Controller1.ButtonL1.pressing() && intakePress)
    {
      intakePress = false;
    }

    if(Controller1.ButtonX.pressing())
    {
      Lin.spin(reverse, 4, volt);
      Rin.spin(reverse, 4, volt);

      wait(500, msec);

      Lin.spin(reverse, 0, volt);
      Rin.spin(reverse, 0, volt);
    }
        
        wait(20, msec);
        task::sleep(200);
    }
}

//Mobile Goal Thread Function
void mogg() 
{
  bool toggleMobileGoal = false;

  while (true) 
  {
    //Toggle Mobile Goal Clamp
    if(Controller1.ButtonL2.pressing() && !toggleMobileGoal)
    {
      mog.set(!mog.value());
      toggleMobileGoal = true;
    }
    else if(!Controller1.ButtonL2.pressing() && toggleMobileGoal)
    {
      toggleMobileGoal = false;
    }
        
        wait(20, msec);
        task::sleep(200);
    }
}

void usercontrol(void) {
  thread intakeThread(intaker);
  thread mogclamp(mogg);

  steak.set(false);
  ClawMech claw(motor_group(LLift, RLift), 0.16, 0.1, 0.16, 0, 1.5, 500, 3000);

  bool toggleClawState = false;
  bool toggleArm = false;

  while (1) {

    chassis.control_arcade();

    //ARM IF statements
    if(Controller1.ButtonR1.pressing() && clawState == PASSIVE && !toggleArm)
    {
      clawState = INTAKE;
      toggleArm = true;
    }
    else if(Controller1.ButtonR1.pressing() && clawState == INTAKE && !toggleArm)
    {
      clawState = WALL;
      toggleArm = true;
    }
    else if(Controller1.ButtonX.pressing() && clawState == WALL && !toggleArm)
    {
      clawState = ALLIANCE;
      toggleArm = true;
    }
    else if(Controller1.ButtonX.pressing() && clawState == ALLIANCE && !toggleArm)
    {
      clawState = WALL;
      toggleArm = true;
    }
    else if(Controller1.ButtonR1.pressing() && (clawState == WALL || clawState == ALLIANCE) && !toggleArm)
    {
      clawState = PASSIVE;
      toggleArm = true;
    }
    else if(Controller1.ButtonR1.pressing() && toggleArm)
    {
      toggleArm = false;
    }

    //CLAW IF statements
    if(Controller1.ButtonR2.pressing() && clawState == INTAKE && !toggleClawState)
    {
      steak.set(true);
      toggleClawState = true;
    }
    else if(Controller1.ButtonR2.pressing() && (clawState == WALL || clawState == ALLIANCE) && !toggleClawState)
    {
      steak.set(false);
      toggleClawState = true;
    }
    else if(Controller1.ButtonR2.pressing() && toggleClawState)
    {
      toggleClawState = false;
    }


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
