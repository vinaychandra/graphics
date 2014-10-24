#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <string>
#include "gl_framework.hpp"

double rotate_y = 0;
double rotate_x = -10;
double rotate_z = 0;

bool car_mode = false;
bool robot_mode = false;
GLuint tyretex, retex, rtex, tex;

void GenLists();
void toCar();
void toRobot();

void renderGL();

int main (int argc, char *argv[]) 
{
	//! The pointer to the GLFW window
	GLFWwindow* window;

	//! Setting up the GLFW Error callback
	glfwSetErrorCallback(csX75::error_callback);

	//! Initialize GLFW
	if (!glfwInit())
		return -1;

	int win_width=512;
	int win_height=512;

	//! Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(win_width, win_height, "Transformers", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//! Make the window's context current 
	glfwMakeContextCurrent(window);

	//Keyboard Callback
	glfwSetKeyCallback(window, csX75::key_callback);
	//Framebuffer resize callback
	//glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glfwGetFramebufferSize(window, &win_width, &win_height);
	csX75::framebuffer_size_callback(window, win_width, win_height);
	//Initialize GL state
	csX75::initGL();

	//Enabling several things
	//glEnable(GL_CULL_FACE); 			// Back face culling


	//Load all the lists
	GenLists();

	//Load Textures
	tyretex=LoadTexture("textures/rim.bmp");
	retex=LoadTexture("textures/face.bmp");
	rtex=LoadTexture("textures/autobot.bmp");
	tex=LoadTexture("textures/nameplate.bmp");
	//glDisable(GL_TEXTURE_2D);


	// Loop until the user closes the window
	while (glfwWindowShouldClose(window) == 0)
	{

	// Render here
		renderGL();

	// Swap front and back buffers
		glfwSwapBuffers(window);


	// Poll for and process events
		glfwPollEvents();
	}
 
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//
	//	Render code
	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//	//



void renderGL()
{
	if (car_mode)	toCar();
	if (robot_mode) toRobot();
	//	Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 
	// Reset transformations
	glLoadIdentity();

	// Other Transformations
	// glTranslatef( 0.1, 0.0, 0.0 );			// Not included
	// glRotatef( 180, 0.0, 1.0, 0.0 );		// Not included
	
	//glRotatef(90,-1,0,0);
	//glRotatef(-8,0,1,0);
	//glRotatef(-74,0,0,1);
	
// Rotate when user changes rotate_x and rotate_y
	glRotatef( rotate_x, 1.0, 0.0, 0.0 );
	glRotatef( rotate_y, 0.0, 1.0, 0.0 );
	glRotatef( rotate_z, 0.0, 0.0, 1.0 );
	glScalef( 1, 1, -1);
	glTranslatef(0,0.4,0);


	glCallList(Torso);
	glPushMatrix();

		glRotatef(face_rotate_x, 1.0, 0.0, 0.0 );
		glRotatef(face_rotate_y, 0.0, 1.0, 0.0 );

		glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			
			glBindTexture(GL_TEXTURE_2D, retex);
			
			glBegin(GL_QUADS);
				glTexCoord2f(0,0); glVertex3f(0.1,0,-0.201);
				glTexCoord2f(1,0); glVertex3f(-0.1,0,-0.201);
				glTexCoord2f(1,1); glVertex3f(-0.1,0.2,-0.201);
				glTexCoord2f(0,1); glVertex3f(0.1,0.2,-0.201);
			glEnd();
			
		glDisable(GL_TEXTURE_2D);
		glCallList(Face);
	glPopMatrix();

	glPushMatrix();
		glRotatef(hood_rotate_x, 1.0,0,0);



		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			
		glBindTexture(GL_TEXTURE_2D, tex);
		glBegin(GL_QUADS);
			glTexCoord2f(0,0); glVertex3f(-0.15,0.501,-0.025);
			glTexCoord2f(1,0); glVertex3f(0.15,0.501,-0.025);
			glTexCoord2f(1,1); glVertex3f(0.15,0.501,-0.125);
			glTexCoord2f(0,1); glVertex3f(-0.15,0.501,-0.125);
		glEnd();
		glDisable(GL_TEXTURE_2D);


		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			
		glBindTexture(GL_TEXTURE_2D, rtex);
		glBegin(GL_QUADS);
			glTexCoord2f(0,0); glVertex3f(-0.21,0.5,-0.151);
			glTexCoord2f(1,0); glVertex3f(0.21,0.5,-0.151);
			glTexCoord2f(1,1); glVertex3f(0.21,0.2,-0.301);
			glTexCoord2f(0,1); glVertex3f(-0.21,0.2,-0.301);
		glEnd();
		glDisable(GL_TEXTURE_2D);


		glCallList(Hood);
		glPushMatrix();
			glColor3f(0.05,0.05,0.05);
			GLUquadricObj *quadratic;
			quadratic = gluNewQuadric();
			glTranslatef(-0.28,0,0);
			
			glRotatef(90.0, 0.0, 1.0, 0.0);
			glRotatef(wheel_turn,-1,0,0);
			glRotatef(wheel_rotate,0,0,-1);



			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			
			glBindTexture(GL_TEXTURE_2D, tyretex);
			
			glBegin(GL_QUADS);
				glTexCoord2f(0,0);	glVertex3f(-0.07,-0.07,-0.001);
				glTexCoord2f(1,0); glVertex3f(0.07,-0.07,-0.001);
				glTexCoord2f(1,1);	glVertex3f(0.07,0.07,-0.001);
				glTexCoord2f(0,1); glVertex3f(-0.07,0.07,-0.001);
			glEnd();
			
			glDisable(GL_TEXTURE_2D);

			gluCylinder(quadratic,0.1,0.1,0.1,32,32);
			gluDisk(quadratic,0,0.1,32,32);

		glPopMatrix();

		glPushMatrix();
			glColor3f(0.05,0.05,0.05);
			quadratic = gluNewQuadric();
			glTranslatef(0.28,0,0);
			
			glRotatef(90.0, 0.0, -1.0, 0.0);
			glRotatef(wheel_turn,1,0,0);//
			glRotatef(wheel_rotate,0,0,1);//


			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			
			glBindTexture(GL_TEXTURE_2D, tyretex);
			
			glBegin(GL_QUADS);
				glTexCoord2f(0,0);	glVertex3f(-0.07,-0.07,-0.001);
				glTexCoord2f(1,0); glVertex3f(0.07,-0.07,-0.001);
				glTexCoord2f(1,1);	glVertex3f(0.07,0.07,-0.001);
				glTexCoord2f(0,1); glVertex3f(-0.07,0.07,-0.001);
			glEnd();
			
			glDisable(GL_TEXTURE_2D);

			gluCylinder(quadratic,0.1,0.1,0.1,32,32);
			gluDisk(quadratic,0,0.1,32,32);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,0,windshield_move);
		glTranslatef(0,-0.2,0);
		glTranslatef(0,0.19,-0.3);
		glRotatef(windshield_full_rotate, 1,0,0);
		glTranslatef(0,-0.19,0.3);

		glCallList(Windshield);
		
		glPushMatrix();

			glTranslatef(0.21,0.1,-0.15);
			glRotatef(windshield_left_door,0,0,1);
			glTranslatef(-0.21,-0.1,0.15);
			glCallList(LeftDoor);
			glPopMatrix();

			glTranslatef(-0.21,0.1,-0.3);
			glRotatef(windshield_right_door,0,0,-1);
			glTranslatef(0.21,-0.1,0.3);
			glCallList(RightDoor);

		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.12999,0,-0.001);
		glTranslatef(-0.09,0,0);
		glRotatef(left_shoulder_angle,0,0,-1);
		glTranslatef(0.09,0,0);
		glCallList(ShoulderJoint);

		glPushMatrix();
			glTranslatef(0,-0.14,0);
			glRotatef(left_upper_arm_x,1,0,0);
			glRotatef(left_upper_arm_y,0,1,0);
			glRotatef(left_upper_arm_z,0,0,1);
			glCallList(Hand);

			glPushMatrix();
				glTranslatef(0,-0.27,0);
				glRotatef(left_lower_arm_x,1,0,0);
				glRotatef(left_lower_arm_y,0,1,0);
				glRotatef(left_lower_arm_z,0,0,1);
				glCallList(Hand);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();


	glPushMatrix();
		glTranslatef(0.12999,0,-0.001);
		glTranslatef(0.09,0,0);
		glRotatef(right_shoulder_angle,0,0,1);
		glTranslatef(-0.09,0,0);
		glCallList(ShoulderJoint);

		glPushMatrix();
			glTranslatef(0,-0.14,0);
			glRotatef(right_upper_arm_x,1,0,0);
			glRotatef(right_upper_arm_y,0,1,0);
			glRotatef(right_upper_arm_z,0,0,1);
			glCallList(Hand);

			glPushMatrix();
				glTranslatef(0,-0.27,0);
				glColor3f(0.3,0.9,0.8);
				glRotatef(right_lower_arm_x,1,0,0);
				glRotatef(right_lower_arm_y,0,1,0);
				glRotatef(right_lower_arm_z,0,0,1);	
				glCallList(Hand);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0,0,windshield_move);//we are moving both the windshield and backbone by the same amount
		glCallList(BackBone);
	glPopMatrix();

	glPushMatrix();
		//Right leg
		glTranslatef(-0.11999,-0.5,0);
		glRotatef(right_thigh_angle,0,0,1);
		glTranslatef(0,0.5,0);
		//glCallList(Thigh);

		glTranslatef(0,0,leg_translate);

		glTranslatef(0,-0.7,-0.4);
		glRotatef(right_knee_angle,-1,0,0);
		glTranslatef(0,0.7,0.4);
		glCallList(Leg);
		
		glTranslatef(0,0,foot_move);	
		glTranslatef(0,-1.1,-0.2);
		glRotatef(right_foot_angle,-1,0,0);
		glTranslatef(0,1.1,0.2);
		glCallList(Foot);
		
		glPushMatrix();

			glColor3f(0.05,0.05,0.05);
			//GLUquadricObj *quadratic;
			quadratic = gluNewQuadric();
			//glRotatef(wheel_turn,0,0,1);
			glTranslatef(-0.15,-0.75,0);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			glRotatef(wheel_rotate,0,0,-1);


			
			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
			
			glBindTexture(GL_TEXTURE_2D, tyretex);
			//glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0,0);	glVertex3f(-0.07,-0.07,-0.001);
				glTexCoord2f(1,0); glVertex3f(0.07,-0.07,-0.001);
				glTexCoord2f(1,1);	glVertex3f(0.07,0.07,-0.001);
				glTexCoord2f(0,1); glVertex3f(-0.07,0.07,-0.001);
			glEnd();
			
			glDisable(GL_TEXTURE_2D);


			gluCylinder(quadratic,0.1,0.1,0.1,32,32);
			gluDisk(quadratic,0,0.1,32,32);

		glPopMatrix();
	glPopMatrix();

	glPushMatrix();
		//Left leg
		glTranslatef(0.11999,-0.5,0);
		glRotatef(left_thigh_angle,0,0,-1);
		glTranslatef(0,0.5,0);
		//glCallList(Thigh);
		
		glTranslatef(0,0,leg_translate);
	
		glTranslatef(0,-0.7,-0.4);
		glRotatef(left_knee_angle,-1,0,0);
		glTranslatef(0,0.7,0.4);
		glCallList(Leg);
		
		glTranslatef(0,0,foot_move);
		glTranslatef(0,-1.1,-0.2);
		glRotatef(left_foot_angle,-1,0,0);
		glTranslatef(0,1.1,0.2);
		glCallList(Foot);
		
		glPushMatrix();
			glColor3f(0.05,0.05,0.05);
			quadratic = gluNewQuadric();
			glTranslatef(0.15,-0.75,0);
			glRotatef(90.0, 0.0, -1.0, 0.0);
			glRotatef(wheel_rotate,0,0,1);


			glEnable(GL_TEXTURE_2D);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
			
			glBindTexture(GL_TEXTURE_2D, tyretex);
			//glPushMatrix();
			glBegin(GL_QUADS);
				glTexCoord2f(0,0);	glVertex3f(0.07,0.07,-0.001);
				glTexCoord2f(1,0); glVertex3f(0.07,-0.07,-0.001);
				glTexCoord2f(1,1);	glVertex3f(-0.07,-0.07,-0.001);
				glTexCoord2f(0,1); glVertex3f(-0.07,0.07,-0.001);
			glEnd();
			
			glDisable(GL_TEXTURE_2D);
			
			gluCylinder(quadratic,0.1,0.1,0.1,32,32);
			gluDisk(quadratic,0,0.1,32,32);

		glPopMatrix();
	glPopMatrix();
}

