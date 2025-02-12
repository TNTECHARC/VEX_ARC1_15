#include "intakee.h"

double intakeTarget = 0;
bool intakeOn = false;

double kPP = 0.08;  // Proportional gain
double kII = 0.0; // Integral gain
double kDD = 0.1; // Derivative gain

// Variables for PID control
double error = 0;
double previousError = 0;
double integral = 0;
double derivative = 0;

// Target velocity for the motor

// Function to calculate PID output
void intakeePID() {
    error = intakeTarget - inrot.position(deg);
    integral += error;
    derivative = error - previousError;
    previousError = error;

    // Calculate PID output
    double output = (kPP * error) + (kII * integral) + (kDD * derivative);
    intake.spin(fwd, output, voltageUnits::volt);
}

double oneRot =  2339.74;
void intakee() {
    while(1) {
        if(intakeOn) {
            intake.spin(fwd,100,pct);
            wait(300,msec);
            waitUntil(intakeOn == false);
            intake.stop();
            intakeTarget = ((((int)(inrot.position(deg) / oneRot))+1)*oneRot);
        } else {
            intakeePID();
        }
        wait(10,msec);
    }
}
 