#include "gl_framework.hpp"
#include <cstdlib>

double absolute(double x)
{
	if (x >= 0) return x;
	else return -1.0*x;
}

bool nearFunc(double &variable, double target = 0.0, double step = 1.0)
{
	if (absolute(variable - target) < step){
		variable = target;
		return false;
	}
	if (variable > target)
		variable -= step;
	if (variable < target)
		variable += step;
	return true;
}

void toCar()
{

	if (nearFunc(face_rotate_x))return;
	if (nearFunc(face_rotate_y))return;

	nearFunc(windshield_move,0,0.002);
if (nearFunc(leg_translate,0,0.002)||nearFunc(windshield_move,0,0.002))return;

	if (nearFunc(hood_rotate_x))return;


	if(nearFunc(left_shoulder_angle) || nearFunc(right_shoulder_angle))return;

	if(nearFunc(left_upper_arm_x) || nearFunc(left_upper_arm_y) || nearFunc(left_upper_arm_z) || nearFunc(right_upper_arm_x) || nearFunc(right_upper_arm_y) || nearFunc(right_upper_arm_z))return;

	if(nearFunc(left_lower_arm_x) || nearFunc(left_lower_arm_y) || nearFunc(left_lower_arm_z) || nearFunc(right_lower_arm_x) || nearFunc(right_lower_arm_y) || nearFunc(right_lower_arm_z))return;
	
	if(nearFunc(windshield_full_rotate) || nearFunc(windshield_right_door) || nearFunc(windshield_left_door))return;



if(nearFunc(foot_move,0,0.0025))return;

	if(nearFunc(left_thigh_angle) || nearFunc(right_thigh_angle) || nearFunc(left_knee_angle) || nearFunc(right_knee_angle) || nearFunc(left_foot_angle) || nearFunc(right_foot_angle))
		return;
	
	
	
	car_mode = false;
	return;
}

void toRobot()
{
	if(nearFunc(hood_rotate_x,180))return;
	
	if(nearFunc(face_rotate_x))return;
	if(nearFunc(face_rotate_y,180))return;


	if(nearFunc(windshield_right_door,35))return;
	if(nearFunc(windshield_left_door,35))return;
	if(nearFunc(windshield_full_rotate,120))return;
	

	if(nearFunc(left_shoulder_angle,90))return;
	if(nearFunc(right_shoulder_angle,90))return;

	nearFunc(windshield_move,0.26,0.002);
	if(nearFunc(leg_translate,0.26,0.002)||nearFunc(windshield_move,0.26,0.002))return;

//if()return;

	nearFunc(left_upper_arm_x);
	nearFunc(left_upper_arm_y);
	nearFunc(left_upper_arm_z);
	nearFunc(right_upper_arm_x);
	nearFunc(right_upper_arm_y);
	if(nearFunc(right_upper_arm_z) || nearFunc(left_upper_arm_x) ||  nearFunc(left_upper_arm_y) || nearFunc(left_upper_arm_z)  || nearFunc(right_upper_arm_x)  || nearFunc(right_upper_arm_y))return;

	if(nearFunc(left_lower_arm_x))return;
	if(nearFunc(left_lower_arm_y))return;
	if(nearFunc(left_lower_arm_z,-20))return;
	if(nearFunc(right_lower_arm_x))return;
	if(nearFunc(right_lower_arm_y))return;
	if(nearFunc(right_lower_arm_z,20))return;

	if(nearFunc(left_thigh_angle))return;
	if(nearFunc(right_thigh_angle))return;
	if(nearFunc(left_knee_angle))return;
	if(nearFunc(right_knee_angle))return;
	if(nearFunc(left_foot_angle,-90))return;
	if(nearFunc(right_foot_angle,-90))return;

	if(nearFunc(foot_move,-0.1,0.0025))return;

	
	
	robot_mode = false;
	return;
}