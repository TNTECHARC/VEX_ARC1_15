#pragma once
#include "vex.h"
//24 inch passive = 125
enum CLAWSTATES {START = 0, INTAKE = 70, SECOND = 110, THIRD = 159, PASSIVE = 91, WALL = 647, ALLIANCE = 475, SHOVE = 80};

class ClawMech
{
    private:

        CLAWSTATES currentState = START;
        motor_group lift;
        float kp, ki, kd, starti, settle_error, settle_time, timeout;

    public:

        led grab;

        ClawMech(motor_group lift, led grab, float kp, float ki, float kd, float starti, float settle_error, float settle_time, float timeout);

        CLAWSTATES getCurrentState();
        void setCurrentState(CLAWSTATES state);

        void moveTo(CLAWSTATES state);
};