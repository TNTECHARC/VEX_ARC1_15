#pragma once
#include "vex.h"
#include "drive.h"

class Robot
{
    private:

    public:

    Drive chassis;
    ClawMech claw;

    Robot(Drive drive, ClawMech clawMech);
};

extern Robot robot;