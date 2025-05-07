#pragma once
#include "JAR-Template/drive.h"

class Drive;
class ClawMech;

extern Drive chassis;
extern ClawMech claw;

void default_constants();

void blueLeftElim();
void blueLeftWP();
void blueRightElim();
void blueRightWP();

void red_route_skills();
void red_route_skills_Sec();

//Worlds Routes
void red_right_front_pos();
void red_right_middle_pos();
void red_right_back_pos();
void red_left_front_neg();
void red_left_middle_neg();
void red_left_back_neg();
void blue_right_front_pos();
void blue_right_middle_pos();
void blue_right_back_pos();
void blue_left_front_neg();
void blue_left_middle_neg();
