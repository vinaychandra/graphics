#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <string>
#include "transformer.hpp"
#include "gl_framework.hpp"
#include "scenery.hpp"

#define frames_between_snapshots 30.0
#define time_between_snapshots 1.0

void renderGL();
void routines();

struct_transformer transformer, transformer_2;
scenery world;

//! The pointer to the GLFW window
GLFWwindow* window;

int main(int argc, char** argv)
{
	//! Setting up the GLFW Error callback
	glfwSetErrorCallback(csX75::error_callback);

	//! Initialize GLFW
	if (!glfwInit())
		return -1;

	//! Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(640, 640, "Transformers", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//! Make the window's context current
	glfwMakeContextCurrent(window);

	//Initialize GLEW
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		//Problem: glewInit failed, something is seriously wrong.
		std::cerr<<"GLEW Init Failed : %s"<<std::endl;
	}


	//Keyboard Callback
	glfwSetKeyCallback(window, csX75::key_callback);
	//Framebuffer resize callback
	glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//Initialize GL state
	csX75::initGL();

	//Get the display lists and textures
	transformer.GenLists();	
	transformer_2.GenLists();	
	world.load_textures();
	transformer.LoadTextures();
	transformer_2.LoadTextures();

	// Loop until the user closes the window
	while (glfwWindowShouldClose(window) == 0)
	{
		routines();

		// Render here
		renderGL();

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


void renderGL(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();
	
	glPushMatrix();
		if (transformer.car_mode)	transformer.toCar();
		if (transformer.robot_mode) transformer.toRobot();

		if (transformer_2.car_mode)	transformer_2.toCar();
		if (transformer_2.robot_mode) transformer_2.toRobot();
		
		Camera();

		glPushMatrix();
		
			glTranslatef(transformer.position_x,transformer.position_y,transformer.position_z);
			glRotatef(transformer.direction,0,1,0);
		
			transformer.draw();
		glPopMatrix();

		glPushMatrix();
		
			glTranslatef(transformer_2.position_x,transformer_2.position_y,transformer_2.position_z);
			glRotatef(transformer_2.direction,0,1,0);
		
			transformer_2.draw();
		glPopMatrix();
	
		world.create_all();
		
	glPopMatrix();


}

void routines()
{
	transformer.position_routine();
	transformer_2.position_routine();
}

void write_frame()
{
	ofstream myfile ("keyframes.txt", ios::out | ios::app);
	if (myfile.is_open())
	{
		myfile << " " << transformer.position_x<< " " <<transformer.position_y<< " " <<transformer.position_z<< " " <<transformer.direction<< " " <<transformer.velocity<< " " <<transformer.forward<< " " <<transformer.backward<< " " <<transformer.face_rotate_x<< " " <<transformer.face_rotate_y<< " " <<transformer.face_rotate_z<< " " <<transformer.hood_rotate_x<< " " <<transformer.windshield_full_rotate<< " " <<transformer.windshield_left_door<< " " <<transformer.windshield_right_door<< " " <<transformer.left_shoulder_angle<< " " <<transformer.right_shoulder_angle<< " " <<transformer.left_upper_arm_x<< " " <<transformer.left_upper_arm_y<< " " <<transformer.left_upper_arm_z<< " " <<transformer.right_upper_arm_x<< " " <<transformer.right_upper_arm_y<< " " <<transformer.right_upper_arm_z<< " " <<transformer.left_lower_arm_x<< " " <<transformer.left_lower_arm_y<< " " <<transformer.left_lower_arm_z<< " " <<transformer.right_lower_arm_x<< " " <<transformer.right_lower_arm_y<< " " <<transformer.right_lower_arm_z<< " " <<transformer.leg_translate<< " " <<transformer.left_thigh_angle<< " " <<transformer.right_thigh_angle<< " " <<transformer.left_knee_angle<< " " <<transformer.right_knee_angle<< " " <<transformer.left_foot_angle<< " " <<transformer.right_foot_angle<< " " <<transformer.windshield_move<< " " <<transformer.foot_move<< " " <<transformer.wheel_turn<< " " <<transformer.wheel_rotate<< " " <<transformer.car_mode<< " " <<transformer.robot_mode<< " " <<transformer.extra_movement_translation<< " " <<transformer.extra_movement_rotation <<endl;
		myfile << " " << transformer_2.position_x<< " " <<transformer_2.position_y<< " " <<transformer_2.position_z<< " " <<transformer_2.direction<< " " <<transformer_2.velocity<< " " <<transformer_2.forward<< " " <<transformer_2.backward<< " " <<transformer_2.face_rotate_x<< " " <<transformer_2.face_rotate_y<< " " <<transformer_2.face_rotate_z<< " " <<transformer_2.hood_rotate_x<< " " <<transformer_2.windshield_full_rotate<< " " <<transformer_2.windshield_left_door<< " " <<transformer_2.windshield_right_door<< " " <<transformer_2.left_shoulder_angle<< " " <<transformer_2.right_shoulder_angle<< " " <<transformer_2.left_upper_arm_x<< " " <<transformer_2.left_upper_arm_y<< " " <<transformer_2.left_upper_arm_z<< " " <<transformer_2.right_upper_arm_x<< " " <<transformer_2.right_upper_arm_y<< " " <<transformer_2.right_upper_arm_z<< " " <<transformer_2.left_lower_arm_x<< " " <<transformer_2.left_lower_arm_y<< " " <<transformer_2.left_lower_arm_z<< " " <<transformer_2.right_lower_arm_x<< " " <<transformer_2.right_lower_arm_y<< " " <<transformer_2.right_lower_arm_z<< " " <<transformer_2.leg_translate<< " " <<transformer_2.left_thigh_angle<< " " <<transformer_2.right_thigh_angle<< " " <<transformer_2.left_knee_angle<< " " <<transformer_2.right_knee_angle<< " " <<transformer_2.left_foot_angle<< " " <<transformer_2.right_foot_angle<< " " <<transformer_2.windshield_move<< " " <<transformer_2.foot_move<< " " <<transformer_2.wheel_turn<< " " <<transformer_2.wheel_rotate<< " " <<transformer_2.car_mode<< " " <<transformer_2.robot_mode<< " " <<transformer_2.extra_movement_translation<< " " <<transformer_2.extra_movement_rotation <<endl;
		myfile  << " " << globalCameraX << " " << globalCameraY << " " << globalCameraZ << " " << globalCameraLX << " " << globalCameraLY << " " << globalCameraLZ << endl;
		myfile << CameraMode << " 0"<< endl; //0 means do not interpolate global camera
		myfile.close();
	}
	else cout << "Unable to open file";
	return;
}

void playback()
{
	ifstream myfile ("keyframes.txt");
	if (!myfile.is_open()) {
		cout << "Unable to open file";
		return;
	}
	struct_transformer transformer_o_1,transformer_o_2; //Original Transformers
	struct_transformer transformer_t_1,transformer_t_2; //Next transformers

	double oglobalCameraX, oglobalCameraY, oglobalCameraZ;
	double oglobalCameraLX, oglobalCameraLY, oglobalCameraLZ;
	double tglobalCameraX, tglobalCameraY, tglobalCameraZ;
	double tglobalCameraLX, tglobalCameraLY, tglobalCameraLZ;

	bool interpolate_cam = false;

	myfile >>  transformer_o_1.position_x>> transformer_o_1.position_y>> transformer_o_1.position_z>> transformer_o_1.direction>> transformer_o_1.velocity>> transformer_o_1.forward>> transformer_o_1.backward>> transformer_o_1.face_rotate_x>> transformer_o_1.face_rotate_y>> transformer_o_1.face_rotate_z>> transformer_o_1.hood_rotate_x>> transformer_o_1.windshield_full_rotate>> transformer_o_1.windshield_left_door>> transformer_o_1.windshield_right_door>> transformer_o_1.left_shoulder_angle>> transformer_o_1.right_shoulder_angle>> transformer_o_1.left_upper_arm_x>> transformer_o_1.left_upper_arm_y>> transformer_o_1.left_upper_arm_z>> transformer_o_1.right_upper_arm_x>> transformer_o_1.right_upper_arm_y>> transformer_o_1.right_upper_arm_z>> transformer_o_1.left_lower_arm_x>> transformer_o_1.left_lower_arm_y>> transformer_o_1.left_lower_arm_z>> transformer_o_1.right_lower_arm_x>> transformer_o_1.right_lower_arm_y>> transformer_o_1.right_lower_arm_z>> transformer_o_1.leg_translate>> transformer_o_1.left_thigh_angle>> transformer_o_1.right_thigh_angle>> transformer_o_1.left_knee_angle>> transformer_o_1.right_knee_angle>> transformer_o_1.left_foot_angle>> transformer_o_1.right_foot_angle>> transformer_o_1.windshield_move>> transformer_o_1.foot_move>> transformer_o_1.wheel_turn>> transformer_o_1.wheel_rotate>> transformer_o_1.car_mode>> transformer_o_1.robot_mode>> transformer_o_1.extra_movement_translation>> transformer_o_1.extra_movement_rotation;
	myfile >>  transformer_o_2.position_x>> transformer_o_2.position_y>> transformer_o_2.position_z>> transformer_o_2.direction>> transformer_o_2.velocity>> transformer_o_2.forward>> transformer_o_2.backward>> transformer_o_2.face_rotate_x>> transformer_o_2.face_rotate_y>> transformer_o_2.face_rotate_z>> transformer_o_2.hood_rotate_x>> transformer_o_2.windshield_full_rotate>> transformer_o_2.windshield_left_door>> transformer_o_2.windshield_right_door>> transformer_o_2.left_shoulder_angle>> transformer_o_2.right_shoulder_angle>> transformer_o_2.left_upper_arm_x>> transformer_o_2.left_upper_arm_y>> transformer_o_2.left_upper_arm_z>> transformer_o_2.right_upper_arm_x>> transformer_o_2.right_upper_arm_y>> transformer_o_2.right_upper_arm_z>> transformer_o_2.left_lower_arm_x>> transformer_o_2.left_lower_arm_y>> transformer_o_2.left_lower_arm_z>> transformer_o_2.right_lower_arm_x>> transformer_o_2.right_lower_arm_y>> transformer_o_2.right_lower_arm_z>> transformer_o_2.leg_translate>> transformer_o_2.left_thigh_angle>> transformer_o_2.right_thigh_angle>> transformer_o_2.left_knee_angle>> transformer_o_2.right_knee_angle>> transformer_o_2.left_foot_angle>> transformer_o_2.right_foot_angle>> transformer_o_2.windshield_move>> transformer_o_2.foot_move>> transformer_o_2.wheel_turn>> transformer_o_2.wheel_rotate>> transformer_o_2.car_mode>> transformer_o_2.robot_mode>> transformer_o_2.extra_movement_translation>> transformer_o_2.extra_movement_rotation;
	myfile >> oglobalCameraX >> oglobalCameraY >> oglobalCameraZ >> oglobalCameraLX >> oglobalCameraLY >> oglobalCameraLZ;
	myfile >> CameraMode >> interpolate_cam;

	while(myfile){
		//Get the next transformer positions...
		myfile >>  transformer_t_1.position_x>> transformer_t_1.position_y>> transformer_t_1.position_z>> transformer_t_1.direction>> transformer_t_1.velocity>> transformer_t_1.forward>> transformer_t_1.backward>> transformer_t_1.face_rotate_x>> transformer_t_1.face_rotate_y>> transformer_t_1.face_rotate_z>> transformer_t_1.hood_rotate_x>> transformer_t_1.windshield_full_rotate>> transformer_t_1.windshield_left_door>> transformer_t_1.windshield_right_door>> transformer_t_1.left_shoulder_angle>> transformer_t_1.right_shoulder_angle>> transformer_t_1.left_upper_arm_x>> transformer_t_1.left_upper_arm_y>> transformer_t_1.left_upper_arm_z>> transformer_t_1.right_upper_arm_x>> transformer_t_1.right_upper_arm_y>> transformer_t_1.right_upper_arm_z>> transformer_t_1.left_lower_arm_x>> transformer_t_1.left_lower_arm_y>> transformer_t_1.left_lower_arm_z>> transformer_t_1.right_lower_arm_x>> transformer_t_1.right_lower_arm_y>> transformer_t_1.right_lower_arm_z>> transformer_t_1.leg_translate>> transformer_t_1.left_thigh_angle>> transformer_t_1.right_thigh_angle>> transformer_t_1.left_knee_angle>> transformer_t_1.right_knee_angle>> transformer_t_1.left_foot_angle>> transformer_t_1.right_foot_angle>> transformer_t_1.windshield_move>> transformer_t_1.foot_move>> transformer_t_1.wheel_turn>> transformer_t_1.wheel_rotate>> transformer_t_1.car_mode>> transformer_t_1.robot_mode>> transformer_t_1.extra_movement_translation>> transformer_t_1.extra_movement_rotation;
		myfile >>  transformer_t_2.position_x>> transformer_t_2.position_y>> transformer_t_2.position_z>> transformer_t_2.direction>> transformer_t_2.velocity>> transformer_t_2.forward>> transformer_t_2.backward>> transformer_t_2.face_rotate_x>> transformer_t_2.face_rotate_y>> transformer_t_2.face_rotate_z>> transformer_t_2.hood_rotate_x>> transformer_t_2.windshield_full_rotate>> transformer_t_2.windshield_left_door>> transformer_t_2.windshield_right_door>> transformer_t_2.left_shoulder_angle>> transformer_t_2.right_shoulder_angle>> transformer_t_2.left_upper_arm_x>> transformer_t_2.left_upper_arm_y>> transformer_t_2.left_upper_arm_z>> transformer_t_2.right_upper_arm_x>> transformer_t_2.right_upper_arm_y>> transformer_t_2.right_upper_arm_z>> transformer_t_2.left_lower_arm_x>> transformer_t_2.left_lower_arm_y>> transformer_t_2.left_lower_arm_z>> transformer_t_2.right_lower_arm_x>> transformer_t_2.right_lower_arm_y>> transformer_t_2.right_lower_arm_z>> transformer_t_2.leg_translate>> transformer_t_2.left_thigh_angle>> transformer_t_2.right_thigh_angle>> transformer_t_2.left_knee_angle>> transformer_t_2.right_knee_angle>> transformer_t_2.left_foot_angle>> transformer_t_2.right_foot_angle>> transformer_t_2.windshield_move>> transformer_t_2.foot_move>> transformer_t_2.wheel_turn>> transformer_t_2.wheel_rotate>> transformer_t_2.car_mode>> transformer_t_2.robot_mode>> transformer_t_2.extra_movement_translation>> transformer_t_2.extra_movement_rotation;
		myfile >> tglobalCameraX >> tglobalCameraY >> tglobalCameraZ >> tglobalCameraLX >> tglobalCameraLY >> tglobalCameraLZ;


		glfwSetTime(0);
		double timer = time_between_snapshots/frames_between_snapshots;
		while(glfwGetTime() <= time_between_snapshots){
			while(glfwGetTime() < timer){}

			{
				transformer.position_x = transformer_o_1.position_x + (transformer_t_1.position_x - transformer_o_1.position_x)*timer;
				transformer.position_y = transformer_o_1.position_y + (transformer_t_1.position_y - transformer_o_1.position_y)*timer;
				transformer.position_z = transformer_o_1.position_z + (transformer_t_1.position_z - transformer_o_1.position_z)*timer;
				transformer.direction = transformer_o_1.direction + (transformer_t_1.direction - transformer_o_1.direction)*timer;
				transformer.velocity = transformer_o_1.velocity + (transformer_t_1.velocity - transformer_o_1.velocity)*timer;
				transformer.forward = transformer_o_1.forward;
				transformer.backward = transformer_o_1.backward;
				transformer.face_rotate_x = transformer_o_1.face_rotate_x + (transformer_t_1.face_rotate_x - transformer_o_1.face_rotate_x)*timer;
				transformer.face_rotate_y = transformer_o_1.face_rotate_y + (transformer_t_1.face_rotate_y - transformer_o_1.face_rotate_y)*timer;
				transformer.face_rotate_z = transformer_o_1.face_rotate_z + (transformer_t_1.face_rotate_z - transformer_o_1.face_rotate_z)*timer;
				transformer.hood_rotate_x = transformer_o_1.hood_rotate_x + (transformer_t_1.hood_rotate_x - transformer_o_1.hood_rotate_x)*timer;
				transformer.windshield_full_rotate = transformer_o_1.windshield_full_rotate + (transformer_t_1.windshield_full_rotate - transformer_o_1.windshield_full_rotate)*timer;
				transformer.windshield_left_door = transformer_o_1.windshield_left_door + (transformer_t_1.windshield_left_door - transformer_o_1.windshield_left_door)*timer;
				transformer.windshield_right_door = transformer_o_1.windshield_right_door + (transformer_t_1.windshield_right_door - transformer_o_1.windshield_right_door)*timer;
				transformer.left_shoulder_angle = transformer_o_1.left_shoulder_angle + (transformer_t_1.left_shoulder_angle - transformer_o_1.left_shoulder_angle)*timer;
				transformer.right_shoulder_angle = transformer_o_1.right_shoulder_angle + (transformer_t_1.right_shoulder_angle - transformer_o_1.right_shoulder_angle)*timer;
				transformer.left_upper_arm_x = transformer_o_1.left_upper_arm_x + (transformer_t_1.left_upper_arm_x - transformer_o_1.left_upper_arm_x)*timer;
				transformer.left_upper_arm_y = transformer_o_1.left_upper_arm_y + (transformer_t_1.left_upper_arm_y - transformer_o_1.left_upper_arm_y)*timer;
				transformer.left_upper_arm_z = transformer_o_1.left_upper_arm_z + (transformer_t_1.left_upper_arm_z - transformer_o_1.left_upper_arm_z)*timer;
				transformer.right_upper_arm_x = transformer_o_1.right_upper_arm_x + (transformer_t_1.right_upper_arm_x - transformer_o_1.right_upper_arm_x)*timer;
				transformer.right_upper_arm_y = transformer_o_1.right_upper_arm_y + (transformer_t_1.right_upper_arm_y - transformer_o_1.right_upper_arm_y)*timer;
				transformer.right_upper_arm_z = transformer_o_1.right_upper_arm_z + (transformer_t_1.right_upper_arm_z - transformer_o_1.right_upper_arm_z)*timer;
				transformer.left_lower_arm_x = transformer_o_1.left_lower_arm_x + (transformer_t_1.left_lower_arm_x - transformer_o_1.left_lower_arm_x)*timer;
				transformer.left_lower_arm_y = transformer_o_1.left_lower_arm_y + (transformer_t_1.left_lower_arm_y - transformer_o_1.left_lower_arm_y)*timer;
				transformer.left_lower_arm_z = transformer_o_1.left_lower_arm_z + (transformer_t_1.left_lower_arm_z - transformer_o_1.left_lower_arm_z)*timer;
				transformer.right_lower_arm_x = transformer_o_1.right_lower_arm_x + (transformer_t_1.right_lower_arm_x - transformer_o_1.right_lower_arm_x)*timer;
				transformer.right_lower_arm_y = transformer_o_1.right_lower_arm_y + (transformer_t_1.right_lower_arm_y - transformer_o_1.right_lower_arm_y)*timer;
				transformer.right_lower_arm_z = transformer_o_1.right_lower_arm_z + (transformer_t_1.right_lower_arm_z - transformer_o_1.right_lower_arm_z)*timer;
				transformer.leg_translate = transformer_o_1.leg_translate + (transformer_t_1.leg_translate - transformer_o_1.leg_translate)*timer;
				transformer.left_thigh_angle = transformer_o_1.left_thigh_angle + (transformer_t_1.left_thigh_angle - transformer_o_1.left_thigh_angle)*timer;
				transformer.right_thigh_angle = transformer_o_1.right_thigh_angle + (transformer_t_1.right_thigh_angle - transformer_o_1.right_thigh_angle)*timer;
				transformer.left_knee_angle = transformer_o_1.left_knee_angle + (transformer_t_1.left_knee_angle - transformer_o_1.left_knee_angle)*timer;
				transformer.right_knee_angle = transformer_o_1.right_knee_angle + (transformer_t_1.right_knee_angle - transformer_o_1.right_knee_angle)*timer;
				transformer.left_foot_angle = transformer_o_1.left_foot_angle + (transformer_t_1.left_foot_angle - transformer_o_1.left_foot_angle)*timer;
				transformer.right_foot_angle = transformer_o_1.right_foot_angle + (transformer_t_1.right_foot_angle - transformer_o_1.right_foot_angle)*timer;
				transformer.windshield_move = transformer_o_1.windshield_move + (transformer_t_1.windshield_move - transformer_o_1.windshield_move)*timer;
				transformer.foot_move = transformer_o_1.foot_move + (transformer_t_1.foot_move - transformer_o_1.foot_move)*timer;
				transformer.wheel_turn = transformer_o_1.wheel_turn + (transformer_t_1.wheel_turn - transformer_o_1.wheel_turn)*timer;
				transformer.wheel_rotate = transformer_o_1.wheel_rotate + (transformer_t_1.wheel_rotate - transformer_o_1.wheel_rotate)*timer;
				transformer.car_mode = transformer_o_1.car_mode;
				transformer.robot_mode = transformer_o_1.robot_mode;
				transformer.extra_movement_translation = transformer_o_1.extra_movement_translation + (transformer_t_1.extra_movement_translation - transformer_o_1.extra_movement_translation)*timer;
				transformer.extra_movement_rotation = transformer_o_1.extra_movement_rotation + (transformer_t_1.extra_movement_rotation - transformer_o_1.extra_movement_rotation)*timer;
			}

			{
				transformer_2.position_x = transformer_o_2.position_x + (transformer_t_2.position_x - transformer_o_2.position_x)*timer;
				transformer_2.position_y = transformer_o_2.position_y + (transformer_t_2.position_y - transformer_o_2.position_y)*timer;
				transformer_2.position_z = transformer_o_2.position_z + (transformer_t_2.position_z - transformer_o_2.position_z)*timer;
				transformer_2.direction = transformer_o_2.direction + (transformer_t_2.direction - transformer_o_2.direction)*timer;
				transformer_2.velocity = transformer_o_2.velocity + (transformer_t_2.velocity - transformer_o_2.velocity)*timer;
				transformer_2.forward = transformer_o_2.forward;
				transformer_2.backward = transformer_o_2.backward;
				transformer_2.face_rotate_x = transformer_o_2.face_rotate_x + (transformer_t_2.face_rotate_x - transformer_o_2.face_rotate_x)*timer;
				transformer_2.face_rotate_y = transformer_o_2.face_rotate_y + (transformer_t_2.face_rotate_y - transformer_o_2.face_rotate_y)*timer;
				transformer_2.face_rotate_z = transformer_o_2.face_rotate_z + (transformer_t_2.face_rotate_z - transformer_o_2.face_rotate_z)*timer;
				transformer_2.hood_rotate_x = transformer_o_2.hood_rotate_x + (transformer_t_2.hood_rotate_x - transformer_o_2.hood_rotate_x)*timer;
				transformer_2.windshield_full_rotate = transformer_o_2.windshield_full_rotate + (transformer_t_2.windshield_full_rotate - transformer_o_2.windshield_full_rotate)*timer;
				transformer_2.windshield_left_door = transformer_o_2.windshield_left_door + (transformer_t_2.windshield_left_door - transformer_o_2.windshield_left_door)*timer;
				transformer_2.windshield_right_door = transformer_o_2.windshield_right_door + (transformer_t_2.windshield_right_door - transformer_o_2.windshield_right_door)*timer;
				transformer_2.left_shoulder_angle = transformer_o_2.left_shoulder_angle + (transformer_t_2.left_shoulder_angle - transformer_o_2.left_shoulder_angle)*timer;
				transformer_2.right_shoulder_angle = transformer_o_2.right_shoulder_angle + (transformer_t_2.right_shoulder_angle - transformer_o_2.right_shoulder_angle)*timer;
				transformer_2.left_upper_arm_x = transformer_o_2.left_upper_arm_x + (transformer_t_2.left_upper_arm_x - transformer_o_2.left_upper_arm_x)*timer;
				transformer_2.left_upper_arm_y = transformer_o_2.left_upper_arm_y + (transformer_t_2.left_upper_arm_y - transformer_o_2.left_upper_arm_y)*timer;
				transformer_2.left_upper_arm_z = transformer_o_2.left_upper_arm_z + (transformer_t_2.left_upper_arm_z - transformer_o_2.left_upper_arm_z)*timer;
				transformer_2.right_upper_arm_x = transformer_o_2.right_upper_arm_x + (transformer_t_2.right_upper_arm_x - transformer_o_2.right_upper_arm_x)*timer;
				transformer_2.right_upper_arm_y = transformer_o_2.right_upper_arm_y + (transformer_t_2.right_upper_arm_y - transformer_o_2.right_upper_arm_y)*timer;
				transformer_2.right_upper_arm_z = transformer_o_2.right_upper_arm_z + (transformer_t_2.right_upper_arm_z - transformer_o_2.right_upper_arm_z)*timer;
				transformer_2.left_lower_arm_x = transformer_o_2.left_lower_arm_x + (transformer_t_2.left_lower_arm_x - transformer_o_2.left_lower_arm_x)*timer;
				transformer_2.left_lower_arm_y = transformer_o_2.left_lower_arm_y + (transformer_t_2.left_lower_arm_y - transformer_o_2.left_lower_arm_y)*timer;
				transformer_2.left_lower_arm_z = transformer_o_2.left_lower_arm_z + (transformer_t_2.left_lower_arm_z - transformer_o_2.left_lower_arm_z)*timer;
				transformer_2.right_lower_arm_x = transformer_o_2.right_lower_arm_x + (transformer_t_2.right_lower_arm_x - transformer_o_2.right_lower_arm_x)*timer;
				transformer_2.right_lower_arm_y = transformer_o_2.right_lower_arm_y + (transformer_t_2.right_lower_arm_y - transformer_o_2.right_lower_arm_y)*timer;
				transformer_2.right_lower_arm_z = transformer_o_2.right_lower_arm_z + (transformer_t_2.right_lower_arm_z - transformer_o_2.right_lower_arm_z)*timer;
				transformer_2.leg_translate = transformer_o_2.leg_translate + (transformer_t_2.leg_translate - transformer_o_2.leg_translate)*timer;
				transformer_2.left_thigh_angle = transformer_o_2.left_thigh_angle + (transformer_t_2.left_thigh_angle - transformer_o_2.left_thigh_angle)*timer;
				transformer_2.right_thigh_angle = transformer_o_2.right_thigh_angle + (transformer_t_2.right_thigh_angle - transformer_o_2.right_thigh_angle)*timer;
				transformer_2.left_knee_angle = transformer_o_2.left_knee_angle + (transformer_t_2.left_knee_angle - transformer_o_2.left_knee_angle)*timer;
				transformer_2.right_knee_angle = transformer_o_2.right_knee_angle + (transformer_t_2.right_knee_angle - transformer_o_2.right_knee_angle)*timer;
				transformer_2.left_foot_angle = transformer_o_2.left_foot_angle + (transformer_t_2.left_foot_angle - transformer_o_2.left_foot_angle)*timer;
				transformer_2.right_foot_angle = transformer_o_2.right_foot_angle + (transformer_t_2.right_foot_angle - transformer_o_2.right_foot_angle)*timer;
				transformer_2.windshield_move = transformer_o_2.windshield_move + (transformer_t_2.windshield_move - transformer_o_2.windshield_move)*timer;
				transformer_2.foot_move = transformer_o_2.foot_move + (transformer_t_2.foot_move - transformer_o_2.foot_move)*timer;
				transformer_2.wheel_turn = transformer_o_2.wheel_turn + (transformer_t_2.wheel_turn - transformer_o_2.wheel_turn)*timer;
				transformer_2.wheel_rotate = transformer_o_2.wheel_rotate + (transformer_t_2.wheel_rotate - transformer_o_2.wheel_rotate)*timer;
				transformer_2.car_mode = transformer_o_2.car_mode;
				transformer_2.robot_mode = transformer_o_2.robot_mode;
				transformer_2.extra_movement_translation = transformer_o_2.extra_movement_translation + (transformer_t_2.extra_movement_translation - transformer_o_2.extra_movement_translation)*timer;
				transformer_2.extra_movement_rotation = transformer_o_2.extra_movement_rotation + (transformer_t_2.extra_movement_rotation - transformer_o_2.extra_movement_rotation)*timer;
			}

			if(interpolate_cam){
				globalCameraX = oglobalCameraX + (tglobalCameraX - oglobalCameraX)*timer;
				globalCameraY = oglobalCameraY + (tglobalCameraY - oglobalCameraY)*timer;
				globalCameraZ = oglobalCameraZ + (tglobalCameraZ - oglobalCameraZ)*timer;
				globalCameraLX = oglobalCameraLX + (tglobalCameraLX - oglobalCameraLX)*timer;
				globalCameraLY = oglobalCameraLY + (tglobalCameraLY - oglobalCameraLY)*timer;
				globalCameraLZ = oglobalCameraLZ + (tglobalCameraLZ - oglobalCameraLZ)*timer;
			}
			else {
				globalCameraX = oglobalCameraX;
				globalCameraY = oglobalCameraY;
				globalCameraZ = oglobalCameraZ;
				globalCameraLX = oglobalCameraLX;
				globalCameraLY = oglobalCameraLY;
				globalCameraLZ = oglobalCameraLZ;
			}

			if (glfwWindowShouldClose(window) != 0)
				return;

			routines();
			renderGL();

			// Swap front and back buffers
			glfwSwapBuffers(window);

			// Poll for and process events
			glfwPollEvents();

			timer += time_between_snapshots/frames_between_snapshots;

		}
		transformer_o_1 = transformer_t_1;
		transformer_o_2 = transformer_t_2;
		
		oglobalCameraX = tglobalCameraX;
		oglobalCameraY = tglobalCameraY;
		oglobalCameraZ = tglobalCameraZ;
		oglobalCameraLX = tglobalCameraLX;
		oglobalCameraLY = tglobalCameraLY;
		oglobalCameraLZ = tglobalCameraLZ;

		myfile >> CameraMode >> interpolate_cam;

	}	
	return;
}