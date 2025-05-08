#pragma once
#include "JAR-Template/drive.h"

class Drive;
class ClawMech;

extern Drive chassis;
extern ClawMech claw;

void default_constants();

// Red Autons
void red_left_front_neg();
void red_left_middle_neg();
void red_left_back_neg();

// Blue Autons
void blue_left_front_pos();
void blue_left_middle_pos();
void blue_left_back_pos();