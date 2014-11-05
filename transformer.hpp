#include <iostream>
#include <unistd.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <string.h>

using namespace std;

#ifndef _TRANSFORMER_HPP_
#define _TRANSFORMER_HPP_

struct struct_transformer {
	double position_x;
	double position_y;
	double position_z;

	double direction;
	double velocity;

	bool forward;
	bool backward;

	double face_rotate_x;
	double face_rotate_y;
	double face_rotate_z;

	double hood_rotate_x;

	double windshield_full_rotate;
	double windshield_left_door;
	double windshield_right_door; 

	double left_shoulder_angle;
	double right_shoulder_angle; 

	double left_upper_arm_x;
	double left_upper_arm_y;
	double left_upper_arm_z;
	double right_upper_arm_x;
	double right_upper_arm_y;
	double right_upper_arm_z;

	double left_lower_arm_x;
	double left_lower_arm_y;
	double left_lower_arm_z;
	double right_lower_arm_x;
	double right_lower_arm_y;
	double right_lower_arm_z;

	double leg_translate;

	double left_thigh_angle;
	double right_thigh_angle;
	double left_knee_angle;
	double right_knee_angle;
	double left_foot_angle;
	double right_foot_angle;

	double windshield_move;
	double foot_move;
	double wheel_turn;
	double wheel_rotate;

	bool car_mode;
	bool robot_mode;

	double extra_movement_translation;
	double extra_movement_rotation;

	GLuint tyretex;
	GLuint retex;
	GLuint rtex;
	GLuint tex;

	struct_transformer(){

		extra_movement_translation = 0;
		extra_movement_rotation = 0;

		forward = false;
		backward = false;
		velocity = 0;

		direction = 0; //with z

		car_mode = false;
		robot_mode = false;

		position_x = 0;
		position_y = 0;
		position_z = 0;

		face_rotate_x = 0;
		face_rotate_y = 0;
		face_rotate_z = 0;

		hood_rotate_x = 0;

		windshield_full_rotate = 0;
		windshield_left_door = 0;
		windshield_right_door = 0;

		left_shoulder_angle = 0;
		right_shoulder_angle = 0;

		left_upper_arm_x = 0;
		left_upper_arm_y = 0;
		left_upper_arm_z = 0;
		right_upper_arm_x = 0;
		right_upper_arm_y = 0;
		right_upper_arm_z = 0;

		left_lower_arm_x = 0;
		left_lower_arm_y = 0;
		left_lower_arm_z = 0;
		right_lower_arm_x = 0;
		right_lower_arm_y = 0;
		right_lower_arm_z = 0;

		leg_translate = 0;

		left_thigh_angle = 0;
		right_thigh_angle = 0;
		left_knee_angle = 0;
		right_knee_angle = 0;
		left_foot_angle = 0;
		right_foot_angle = 0;

		windshield_move = 0;
		foot_move = 0;
		wheel_turn = 0;
		wheel_rotate = 0;
	}

	void accelerate();
	void brake();

	void GenLists();
	void LoadTextures();

	void draw();
	void toCar();
	void toRobot();

	void position_routine();
};

extern struct_transformer transformer, transformer_2;
extern int camera_mode;

#define Face 1
#define Torso 2
#define Hood 3
#define Windshield 4
#define LeftDoor 5
#define RightDoor 6
#define ShoulderJoint 7
#define Hand 8
#define BackBone 9
#define Thigh 10
#define Leg 11
#define Foot 12

#define PI 3.14159265359

GLuint LoadTexture(const char* pic);


#endif