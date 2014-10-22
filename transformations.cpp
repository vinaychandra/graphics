#include "gl_framework.hpp"
#include <cstdlib>

bool nearFunc(double &variable, double target = 0, double step = 1)
{
	if (abs(variable - target) < step){
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
	if (nearFunc(hood_rotate_x))return;

	if(nearFunc(left_shoulder_angle) || nearFunc(right_shoulder_angle))return;

	if(nearFunc(left_upper_arm_x) || nearFunc(left_upper_arm_y) || nearFunc(left_upper_arm_z) || nearFunc(right_upper_arm_x) || nearFunc(right_upper_arm_y) || nearFunc(right_upper_arm_z))return;

	if(nearFunc(left_lower_arm_x) || nearFunc(left_lower_arm_y) || nearFunc(left_lower_arm_z) || nearFunc(right_lower_arm_x) || nearFunc(right_lower_arm_y) || nearFunc(right_lower_arm_z))return;
	
	if(nearFunc(windshield_full_rotate) || nearFunc(windshield_right_door) || nearFunc(windshield_left_door))return;

	if(nearFunc(left_thigh_angle) || nearFunc(right_thigh_angle) || nearFunc(left_knee_angle) || nearFunc(right_knee_angle) || nearFunc(left_foot_angle) || nearFunc(right_foot_angle))
		return;
	
	if (nearFunc(leg_translate,0,0.005))return;

	car_mode = false;
	return;
}

void toRobot()
{
	if(nearFunc(hood_rotate_x,180))return;
	
	if(nearFunc(face_rotate_x))return;
	if(nearFunc(face_rotate_y,180))return;


	if(nearFunc(windshield_full_rotate,120))return;
	if(nearFunc(windshield_right_door,35))return;
	if(nearFunc(windshield_left_door,35))return;

	if(nearFunc(left_shoulder_angle,90))return;
	if(nearFunc(right_shoulder_angle,90))return;

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
	

	if(nearFunc(leg_translate,0.2,0.005))return;

	robot_mode = false;
	return;
}