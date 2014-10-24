#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <string>
#include "gl_framework.hpp" 

using namespace std;

double face_rotate_x = 0;
double face_rotate_y = 0;
double face_rotate_z = 0;

double hood_rotate_x = 0;

double windshield_full_rotate = 0;
double windshield_left_door = 0;
double windshield_right_door = 0;

double left_shoulder_angle = 0;
double right_shoulder_angle = 0;

double left_upper_arm_x = 0;
double left_upper_arm_y = 0;
double left_upper_arm_z = 0;
double right_upper_arm_x = 0;
double right_upper_arm_y = 0;
double right_upper_arm_z = 0;

double left_lower_arm_x = 0;
double left_lower_arm_y = 0;
double left_lower_arm_z = 0;
double right_lower_arm_x = 0;
double right_lower_arm_y = 0;
double right_lower_arm_z = 0;

double leg_translate = 0;

double left_thigh_angle = 0;
double right_thigh_angle = 0;
double left_knee_angle = 0;
double right_knee_angle = 0;
double left_foot_angle = 0;
double right_foot_angle = 0;

double windshield_move = 0;
double foot_move = 0;
double wheel_turn = 0;
double wheel_rotate = 0;

void ListFace()
{
	glNewList(Face, GL_COMPILE);
		glColor3f(0.8,1,0.2);
		glBegin(GL_QUAD_STRIP);
			glVertex3f(-0.1,0.2,-0.001);
			glVertex3f(-0.1,0,-0.001);
			glVertex3f(0.1,0.2,-0.001);
			glVertex3f(0.1,0,-0.001);
			glVertex3f(0.1,0.2,-0.2);
			glVertex3f(0.1,0,-0.2);
			glVertex3f(-0.1,0.2,-0.2);
			glVertex3f(-0.1,0,-0.2);
			glVertex3f(-0.1,0.2,-0.001);
			glVertex3f(-0.1,0,-0.001);
		glEnd();


		glColor3f(0,0,0);
		glBegin(GL_LINE_LOOP);
			glVertex3f(-0.1,0.2,-0.001);
			glVertex3f(-0.1,0,-0.001);
			glVertex3f(0.1,0,-0.001);
			glVertex3f(0.1,0.2,-0.001);		
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex3f(0.1,0.2,-0.2);
			glVertex3f(0.1,0,-0.2);
			glVertex3f(-0.1,0,-0.2);
			glVertex3f(-0.1,0.2,-0.2);
			
		glEnd();


		glColor3f(0,1,0);
		glBegin(GL_QUADS);
			glVertex3f(-0.1,0.2,-0.001);
			glVertex3f(0.1,0.2,-0.001);
			glVertex3f(0.1,0.2,-0.2);
			glVertex3f(-0.1,0.2,-0.2);
		glEnd();
		glColor3f(0,1,0);
		glBegin(GL_QUADS);
			glVertex3f(-0.1,0,-0.001);
			glVertex3f(-0.1,0,-0.2);
			glVertex3f(0.1,0,-0.2);
			glVertex3f(0.1,0,-0.001);
		glEnd();

    glEndList();
}

void ListHood()
{
	glNewList(Hood, GL_COMPILE);
		glColor3f(0.5,0.75,0);
		glBegin(GL_QUADS);
			glVertex3f(-0.21,0.2,-0.3);
			glVertex3f(-0.21,0,-0.3);
			glVertex3f(-0.1,0,-0.3);
			glVertex3f(-0.1,0.2,-0.3);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(0.21,0.2,-0.3);
			glVertex3f(0.1,0.2,-0.3);
			glVertex3f(0.1,0,-0.3);
			glVertex3f(0.21,0,-0.3);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(0.1,0.2,-0.3);
			glVertex3f(0.1,0,-0.3);
			glVertex3f(0.1,0,-0);
			glVertex3f(0.1,0.2,-0);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-0.1,0.2,-0.3);
			glVertex3f(-0.1,0,-0.3);
			glVertex3f(-0.1,0,-0);
			glVertex3f(-0.1,0.2,-0);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-0.21,0.5,0);
			glVertex3f(-0.21,0,0);
			glVertex3f(0.21,0,0);
			glVertex3f(0.21,0.5,0);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-0.21,0.5,0);
			glVertex3f(0.21,0.5,0);
			glVertex3f(0.21,0.5,-0.15);
			glVertex3f(-0.21,0.5,-0.15);			
		glEnd();

		glColor3f(1,1,1);
		glBegin(GL_QUADS);
			glVertex3f(-0.2,0.501,-0.05);
			glVertex3f(-0.18,0.501,-0.05);
			glVertex3f(-0.18,0.501,-0.075);
			glVertex3f(-0.2,0.501,-0.075);			
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(0.2,0.501,-0.05);
			glVertex3f(0.18,0.501,-0.05);
			glVertex3f(0.18,0.501,-0.075);
			glVertex3f(0.2,0.501,-0.075);			
		glEnd();



		glColor3f(0,0,0);
		glBegin(GL_LINE_LOOP);
			glVertex3f(-0.21,0.5,0);
			glVertex3f(0.21,0.5,0);
			glVertex3f(0.21,0.5,-0.15);
			glVertex3f(-0.21,0.5,-0.15);			
		glEnd();
		glColor3f(0.5,0,0.1);
		glBegin(GL_QUADS);
			glVertex3f(-0.21,0.5,-0.15);
			glVertex3f(0.21,0.5,-0.15);
			glVertex3f(0.21,0.2,-0.3);
			glVertex3f(-0.21,0.2,-0.3);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(-0.21,0,0);
			glVertex3f(-0.21,0.5,0);
			glVertex3f(-0.21,0.5,-0.15);
			glVertex3f(-0.21,0.2,-0.3);
			glVertex3f(-0.21,0,-0.3);
			glVertex3f(-0.21,0,0);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(0.21,0,0);
			glVertex3f(0.21,0.5,0);
			glVertex3f(0.21,0.5,-0.15);
			glVertex3f(0.21,0.2,-0.3);
			glVertex3f(0.21,0,-0.3);
			glVertex3f(0.21,0,0);
		glEnd();

		
	glEndList();
}

void ListWindshield()
{
	glNewList(Windshield, GL_COMPILE);
		/*glColor3f(0,0,0);
		glBegin(GL_QUADS);
			glVertex3f(-0.21,0,-0.3);
			glVertex3f(0.21,0,-0.3);
			glVertex3f(0.21,-0.19,-0.5);
			glVertex3f(-0.21,-0.19,-0.5);
		glEnd();
		glColor3f(1,1,0);
		glBegin(GL_LINE_LOOP);
			glVertex3f(-0.21,0,-0.3);
			glVertex3f(0.21,0,-0.3);
			glVertex3f(0.21,-0.19,-0.5);
			glVertex3f(-0.21,-0.19,-0.5);
		glEnd();*/
		glColor3f(1,1,0);
		glBegin(GL_QUADS);
			glVertex3f(-0.21,0,-0.3);
			glVertex3f(0.21,0,-0.3);
			glVertex3f(0.21,-0.19,-0.5);
			glVertex3f(-0.21,-0.19,-0.5);
		glEnd();
		glColor3f(0,0,0);
		glBegin(GL_QUADS);
			glVertex3f(-0.2,0.01,-0.31);
			glVertex3f(0.2,0.01,-0.31);
			glVertex3f(0.2,-0.18,-0.49);
			glVertex3f(-0.2,-0.18,-0.49);
		glEnd();

		glColor3f(1,1,0);
		glBegin(GL_QUADS);
			glVertex3f(-0.21,0,-0.3);
			glVertex3f(-0.21,0.19,-0.3);
			glVertex3f(0.21,0.19,-0.3);
			glVertex3f(0.21,0,-0.3);
		glEnd();
		glBegin(GL_TRIANGLES);
			glVertex3f(-0.21,0,-0.3);
			glVertex3f(-0.21,0.095,-0.2);
			glVertex3f(-0.21,0.19,-0.3);
		glEnd();
		glBegin(GL_TRIANGLES);
			glVertex3f(0.21,0,-0.3);
			glVertex3f(0.21,0.095,-0.2);
			glVertex3f(0.21,0.19,-0.3);
		glEnd();
	glEndList();
}

void ListLeftDoor()
{
	glNewList(LeftDoor, GL_COMPILE);
		glColor3f(1,1,0);
		glBegin(GL_POLYGON);
			glVertex3f(0.21,0.1,-0.2);
			glVertex3f(0.21,-0.19,-0.5);
			glVertex3f(0.21,-0.5,-0.5);
			glVertex3f(0.21,-0.5,-0.1);
			glVertex3f(0.21,0.1,-0.1);
			glVertex3f(0.21,0.1,-0.2);
		glEnd();

		glColor3f(0,0,0);
		glBegin(GL_LINE_LOOP);
			glVertex3f(0.21,0.1,-0.2);
			glVertex3f(0.21,-0.19,-0.5);
			glVertex3f(0.21,-0.5,-0.5);
			glVertex3f(0.21,-0.5,-0.1);
			glVertex3f(0.21,0.1,-0.1);
			glVertex3f(0.21,0.1,-0.2);
		glEnd();

		glColor3f(0,0,0);
		glBegin(GL_QUADS);
			glVertex3f(0.211,-0.19,-0.48);
			glVertex3f(0.211,-0.48,-0.48);
			glVertex3f(0.211,-0.48,-0.3);
			glVertex3f(0.211,-0.02,-0.3);
			
		glEnd();
	glEndList();
}

void ListRightDoor()
{
	glNewList(RightDoor, GL_COMPILE);
		glColor3f(1,1,0);
		glBegin(GL_POLYGON);
			glVertex3f(-0.21,0.1,-0.2);
			glVertex3f(-0.21,-0.19,-0.5);
			glVertex3f(-0.21,-0.5,-0.5);
			glVertex3f(-0.21,-0.5,-0.1);
			glVertex3f(-0.21,0.1,-0.1);
			glVertex3f(-0.21,0.1,-0.2);
		glEnd();

		glColor3f(0,0,0);
		glBegin(GL_LINE_LOOP);
			glVertex3f(-0.21,0.1,-0.2);
			glVertex3f(-0.21,-0.19,-0.5);
			glVertex3f(-0.21,-0.5,-0.5);
			glVertex3f(-0.21,-0.5,-0.1);
			glVertex3f(-0.21,0.1,-0.1);
			glVertex3f(-0.21,0.1,-0.2);
		glEnd();

		glColor3f(0,0,0);
		glBegin(GL_QUADS);
			glVertex3f(-0.211,-0.19,-0.48);
			glVertex3f(-0.211,-0.48,-0.48);
			glVertex3f(-0.211,-0.48,-0.3);
			glVertex3f(-0.211,-0.02,-0.3);
			
		glEnd();
	glEndList();
}

void ListShoulderJoint()
{
	glNewList(ShoulderJoint, GL_COMPILE);
		glColor3f(0.1,0.3,0.4);
		glBegin(GL_QUAD_STRIP);
			glVertex3f(-0.07,0,-0.001);
			glVertex3f(-0.07,-0.14,-0.001);
			glVertex3f(0.07,0,-0.001);
			glVertex3f(0.07,-0.14,-0.001);
			glVertex3f(0.07,0,-0.1399);
			glVertex3f(0.07,-0.14,-0.1399);
			glVertex3f(-0.07,0,-0.1399);
			glVertex3f(-0.07,-0.14,-0.1399);
			glVertex3f(-0.07,0,-0.001);
			glVertex3f(-0.07,-0.14,-0.001);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-0.07,0,-0.001);
			glVertex3f(0.07,0,-0.001);
			glVertex3f(0.07,0,-0.1399);
			glVertex3f(-0.07,0,-0.1399);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-0.07,-0.14,-0.001);
			glVertex3f(-0.07,-0.14,-0.1399);
			glVertex3f(0.07,-0.14,-0.1399);
			glVertex3f(0.07,-0.14,-0.001);
		glEnd();
	glEndList();
}

void ListHand()
{
	glNewList(Hand, GL_COMPILE);
		glColor3f(1,1,0.1);
		glBegin(GL_QUAD_STRIP);
			glVertex3f(-0.08,0,0);
			glVertex3f(-0.08,-0.27,0);
			glVertex3f(0.08,0,0);
			glVertex3f(0.08,-0.27,0);
			glVertex3f(0.08,0,-0.16);
			glVertex3f(0.08,-0.27,-0.16);
			glVertex3f(-0.08,0,-0.16);
			glVertex3f(-0.08,-0.27,-0.16);
			glVertex3f(-0.08,0,0);
			glVertex3f(-0.08,-0.27,0);
		glEnd();
		/*glColor3f(0,0,0);
		glBegin(GL_LINE_LOOP);
			glVertex3f(-0.08,0,0);
			glVertex3f(-0.08,-0.27,0);
			glVertex3f(0.08,-0.27,0);
			glVertex3f(0.08,0,0);
			
			glVertex3f(0.08,0,-0.16);
			glVertex3f(0.08,-0.27,-0.16);
			glVertex3f(-0.08,-0.27,-0.16);
			glVertex3f(-0.08,0,-0.16);
			

			//glVertex3f(-0.08,0,0);
			//glVertex3f(-0.08,-0.27,0);
		glEnd();
		*/
		glColor3f(0.7,0.7,0.1);
		glBegin(GL_QUADS);
			glVertex3f(-0.08,0,0);
			glVertex3f(0.08,0,0);
			glVertex3f(0.08,0,-0.16);
			glVertex3f(-0.08,0,-0.16);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-0.08,-0.27,0);
			glVertex3f(-0.08,-0.27,-0.16);
			glVertex3f(0.08,-0.27,-0.16);
			glVertex3f(0.08,-0.27,0);
		glEnd();
	glEndList();
}

void ListBackBone()
{
	glNewList(BackBone, GL_COMPILE);
		glColor3f(0,0,1);
		glBegin(GL_QUAD_STRIP);
			glVertex3f(0.20999,-0.14,-0.2999);
			glVertex3f(0.20999,-0.14,-0.1);
			glVertex3f(0.20999,0,-0.2999);
			glVertex3f(0.20999,0,-0.1);
			glVertex3f(-0.20999,0,-0.2999);
			glVertex3f(-0.20999,0,-0.1);
			glVertex3f(-0.20999,-0.14,-0.2999);
			glVertex3f(-0.20999,-0.14,-0.1);
			glVertex3f(0.20999,-0.14,-0.2999);
			glVertex3f(0.20999,-0.14,-0.1);
		glEnd();
		glColor3f(1,1,0);
		glBegin(GL_QUADS);
			glVertex3f(0.20999,0,-0.2999);
			glVertex3f(0.20999,-0.14,-0.2999);
			glVertex3f(-0.20999,-0.14,-0.2999);
			glVertex3f(-0.20999,0,-0.2999);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(0.20999,-0.14,-0.1);
			glVertex3f(0.20999,0,-0.1);
			glVertex3f(-0.20999,0,-0.1);
			glVertex3f(-0.20999,-0.14,-0.1);
		glEnd();



		glColor3f(0,0,0);
		glBegin(GL_LINE_LOOP);
			glVertex3f(0.20999,0,-0.2999);
			glVertex3f(0.20999,-0.14,-0.2999);
			glVertex3f(-0.20999,-0.14,-0.2999);
			glVertex3f(-0.20999,0,-0.2999);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3f(-0.2099,-0.39001,-0.5);
			glVertex3f(0.2099,-0.39001,-0.5);
			glVertex3f(0.2099,-0.7,-0.5);
			glVertex3f(-0.2099,-0.7,-0.5);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex3f(-0.2099,-0.2001,-0.3);
			glVertex3f(0.2099,-0.2001,-0.3);
			glVertex3f(0.2099,-0.39001,-0.5);
			glVertex3f(-0.2099,-0.39001,-0.5);
		glEnd();
		/*glBegin(GL_LINE_LOOP);
			glVertex3f(0.20999,-0.14,-0.1);
			glVertex3f(0.20999,0,-0.1);
			glVertex3f(-0.20999,0,-0.1);
			glVertex3f(-0.20999,-0.14,-0.1);
		glEnd();
		glBegin(GL_LINE_LOOP);
			glVertex3f(0.21,-0.2001,-0.2999);
			glVertex3f(-0.21,-0.2001,-0.2999);
			glVertex3f(-0.21,-0.1,-0.2999);
			glVertex3f(0.21,-0.1,-0.2999);
		glEnd();

		*/



		glColor3f(1,1,0);
		glBegin(GL_QUADS);
			glVertex3f(0.2099,-0.2001,-0.2999);
			glVertex3f(-0.2099,-0.2001,-0.2999);
			glVertex3f(-0.2099,-0.1,-0.2999);
			glVertex3f(0.2099,-0.1,-0.2999);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(-0.2099,-0.2001,-0.3);
			glVertex3f(0.2099,-0.2001,-0.3);
			glVertex3f(0.2099,-0.39001,-0.5);
			glVertex3f(-0.2099,-0.39001,-0.5);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(-0.2099,-0.39001,-0.5);
			glVertex3f(0.2099,-0.39001,-0.5);
			glVertex3f(0.2099,-0.7,-0.5);
			glVertex3f(-0.2099,-0.7,-0.5);
		glEnd();

		glBegin(GL_POLYGON);
			glVertex3f(-0.20998,-0.7,-0.5);
			glVertex3f(-0.20998,-0.7,-0.2);
			glVertex3f(-0.20998,-0.15,-0.2);
			glVertex3f(-0.20998,-0.15,-0.3);
			glVertex3f(-0.20998,-0.2,-0.3);
			glVertex3f(-0.20998,-0.39,-0.5);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex3f(0.20998,-0.7,-0.5);
			glVertex3f(0.20998,-0.7,-0.2);
			glVertex3f(0.20998,-0.15,-0.2);
			glVertex3f(0.20998,-0.15,-0.3);
			glVertex3f(0.20998,-0.2,-0.3);
			glVertex3f(0.20998,-0.39,-0.5);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(0.20998,-0.15,-0.2);
			glVertex3f(-0.20998,-0.15,-0.2);
			glVertex3f(-0.20998,-0.7,-0.2);
			glVertex3f(0.20998,-0.7,-0.2);
		glEnd();

	glEndList();
}

void ListThigh()
{
	glNewList(Thigh, GL_COMPILE);
		glColor3f(0.8,0,0.8);
		glBegin(GL_QUADS);
			glVertex3f(-0.09,-0.5,-0.3);
			glVertex3f(0.09,-0.5,-0.3);
			glVertex3f(0.09,-0.7,-0.3);
			glVertex3f(-0.09,-0.7,-0.3);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-0.09,-0.7,-0.16);
			glVertex3f(0.09,-0.7,-0.16);
			glVertex3f(0.09,-0.5,-0.16);
			glVertex3f(-0.09,-0.5,-0.16);			
		glEnd();
		glBegin(GL_QUAD_STRIP);
			glVertex3f(0.09,-0.5,-0.3);
			glVertex3f(0.09,-0.5,-0.16);
			glVertex3f(0.09,-0.7,-0.3);
			glVertex3f(0.09,-0.7,-0.16);
			glVertex3f(-0.09,-0.7,-0.3);
			glVertex3f(-0.09,-0.7,-0.16);
			glVertex3f(-0.09,-0.5,-0.3);
			glVertex3f(-0.09,-0.5,-0.16);
			glVertex3f(0.09,-0.5,-0.3);
			glVertex3f(0.09,-0.5,-0.16);
		glEnd();
	glEndList();
}

void ListLeg()
{
	glNewList(Leg, GL_COMPILE);
	//0.39
		glColor3f(0.1,0,0.6);
		glBegin(GL_QUADS);
			glVertex3f(-0.09,-0.7,-0.5);
			glVertex3f(0.09,-0.7,-0.5);
			glVertex3f(0.09,-1.1,-0.3);
			glVertex3f(-0.09,-1.1,-0.3);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-0.09,-1.1,-0.3);
			glVertex3f(0.09,-1.1,-0.3);
			glVertex3f(0.09,-1.1,-0.2);
			glVertex3f(-0.09,-1.1,-0.2);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-0.09,-1.1,-0.2);
			glVertex3f(0.09,-1.1,-0.2);
			glVertex3f(0.09,-0.7,-0.2);
			glVertex3f(-0.09,-0.7,-0.2);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-0.09,-0.7,-0.5);
			glVertex3f(-0.09,-1.1,-0.3);
			glVertex3f(-0.09,-1.1,-0.2);
			glVertex3f(-0.09,-0.7,-0.2);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(0.09,-0.7,-0.5);
			glVertex3f(0.09,-1.1,-0.3);
			glVertex3f(0.09,-1.1,-0.2);
			glVertex3f(0.09,-0.7,-0.2);
		glEnd();
	glEndList();
}

void ListFoot()
{
	glNewList(Foot, GL_COMPILE);
		glColor3f(1,0.8,0);
		glBegin(GL_QUAD_STRIP);
			glVertex3f(-0.09,-0.7,-0.2);
			glVertex3f(-0.09,-1.1,-0.2);
			glVertex3f(0.09,-0.7,-0.2);
			glVertex3f(0.09,-1.1,-0.2);
			glVertex3f(0.09,-0.7,0);
			glVertex3f(0.09,-1.1,0);
			glVertex3f(-0.09,-0.7,0);
			glVertex3f(-0.09,-1.1,0);
			glVertex3f(-0.09,-0.7,-0.2);
			glVertex3f(-0.09,-1.1,-0.2);			
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-0.09,-0.7,-0.2);
			glVertex3f(-0.09,-0.7,0);
			glVertex3f(0.09,-0.7,0);
			glVertex3f(0.09,-0.7,-0.2);
		glEnd();
		glBegin(GL_QUADS);
			glVertex3f(-0.09,-1.1,-0.2);
			glVertex3f(0.09,-1.1,-0.2);
			glVertex3f(0.09,-1.1,0);
			glVertex3f(-0.09,-1.1,0);
		glEnd();
	glEndList();
}


void GenLists()
{
	ListFace();
	ListHood();
	ListWindshield();
	ListLeftDoor();
	ListRightDoor();
	ListShoulderJoint();
	ListHand();
	ListBackBone();
	ListLeg();
	ListThigh();
	ListFoot();
}