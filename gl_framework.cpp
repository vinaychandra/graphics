/*
 * CS475/CS675 - Computer Graphics
 *	ToyLOGO Assignment Base Code
 *
 * Copyright 2009-2014, Parag Chaudhuri, Department of CSE, IIT Bombay
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.	If not, see <http://www.gnu.org/licenses/>.
*/

#include "gl_framework.hpp"
int CameraMode = 0;

double globalCameraX = 1.5;
double globalCameraY = 2;
double globalCameraZ = 3;

double globalCameraLX = 0.5;
double globalCameraLY = 1.3;
double globalCameraLZ = 0;

bool playback_mode = false;

namespace csX75
{
	int win_width;
	int win_height;

	//! Initialize GL State
	void initGL(void)
	{
		glClearDepth(1.0);
		//Set depth test to less-than
		glDepthFunc(GL_LESS);
		//Enable depth testing
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_DEPTH_BUFFER_BIT); 
		
		glEnable(GL_COLOR_MATERIAL);
		
		glMatrixMode(GL_PROJECTION);
		//Enable Gourard shading
		glShadeModel(GL_SMOOTH);
		// glEnable(GL_BLEND);
		// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();				// Reset The Projection Matrix
		
		gluPerspective(50,1, 0.1, 1000);
		glMatrixMode(GL_MODELVIEW);

	}


	//!GLFW Error Callback
	void error_callback(int error, const char* description)
	{
		std::cerr<<description<<std::endl;
	}

	//!GLFW framebuffer resize callback
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	//!GLFW keyboard callback
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		//!Close the window if the ESC key was pressed
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		

		if(key == GLFW_KEY_UP && mods == GLFW_MOD_SHIFT)
			transformer_2.accelerate();
		else if(key == GLFW_KEY_UP)
			transformer.accelerate();
		if(key == GLFW_KEY_DOWN && action == GLFW_PRESS && mods == GLFW_MOD_SHIFT)
			transformer_2.brake();
		else if(key == GLFW_KEY_DOWN && action == GLFW_PRESS)
			transformer.brake();

		
		
		if(key == GLFW_KEY_LEFT && mods == GLFW_MOD_SHIFT){
			transformer_2.wheel_turn = -20;
			if (transformer_2.velocity >= 0)
				transformer_2.direction += 1;
			else 
				transformer_2.direction -= 1;
		}
		else if(key == GLFW_KEY_LEFT){
			transformer.wheel_turn = -20;
			if (transformer.velocity >= 0)
				transformer.direction += 1;
			else 
				transformer.direction -= 1;
		}
		if(key == GLFW_KEY_LEFT && action == GLFW_RELEASE && mods == GLFW_MOD_SHIFT)
			transformer_2.wheel_turn=0;
		else if(key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
			transformer.wheel_turn = 0;


		if(key == GLFW_KEY_RIGHT && mods == GLFW_MOD_SHIFT){
			transformer_2.wheel_turn = 20;
			if (transformer_2.velocity >= 0)
				transformer_2.direction -= 1;
			else 
				transformer_2.direction += 1;
		}
		else if(key == GLFW_KEY_RIGHT){
			transformer.wheel_turn = 20;
			if (transformer.velocity >= 0)
				transformer.direction -= 1;
			else
				transformer.direction += 1;
		}
		if(key == GLFW_KEY_RIGHT && action == GLFW_RELEASE && mods == GLFW_MOD_SHIFT)
			transformer_2.wheel_turn=0;
		else if(key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
			transformer.wheel_turn = 0;
		


		if (key == GLFW_KEY_SPACE && mods==(GLFW_MOD_CONTROL | GLFW_MOD_SHIFT)){
 			transformer_2.car_mode = true;
 			transformer_2.robot_mode = false;
 		}
 		else if (key == GLFW_KEY_SPACE && mods==GLFW_MOD_CONTROL){
 			transformer_2.car_mode = false;
 			transformer_2.robot_mode = true;
 		}
		else if (key == GLFW_KEY_SPACE && mods == GLFW_MOD_SHIFT){
 			transformer.car_mode = true;
 			transformer.robot_mode = false;
 		}
 		else if (key == GLFW_KEY_SPACE){
 			transformer.car_mode = false;
 			transformer.robot_mode = true;
 		}

 		if (key == GLFW_KEY_C && action == GLFW_PRESS){
 			CameraMode += 1;
 			CameraMode %= 3;
 		}

 		if (key == GLFW_KEY_L && mods == GLFW_MOD_SHIFT){
 			glDisable(GL_LIGHT0);
 			glDisable(GL_LIGHT1);
 		}

 		else if (key == GLFW_KEY_L){
 			glEnable(GL_LIGHT0);
 			glEnable(GL_LIGHT1);
 		}

 		if (key == GLFW_KEY_K && mods == GLFW_MOD_SHIFT){
 			glDisable(GL_LIGHT2);
 			glDisable(GL_LIGHT3);
 		}

 		else if (key == GLFW_KEY_K){
 			glEnable(GL_LIGHT2);
 			glEnable(GL_LIGHT3);
 		}

 		if (key == GLFW_KEY_X && action == GLFW_RELEASE){
 			write_frame();
 		}

 		if (key == GLFW_KEY_Z && action == GLFW_RELEASE){
 			if(!playback_mode){
 				playback_mode = true;
 				playback();	
 			}
 		}

 		if (key == GLFW_KEY_Q && mods == (GLFW_MOD_CONTROL | GLFW_MOD_SHIFT))
 			transformer_2.face_rotate_y -= 1; 		
 		else if (key == GLFW_KEY_Q && mods==GLFW_MOD_SHIFT)
 			transformer.face_rotate_y -= 1; 		
 		else if (key == GLFW_KEY_Q && mods==GLFW_MOD_CONTROL)
 			transformer_2.face_rotate_y += 1;
 		else if (key == GLFW_KEY_Q)
 			transformer.face_rotate_y += 1;

 		if (key == GLFW_KEY_W && mods == (GLFW_MOD_CONTROL | GLFW_MOD_SHIFT))
 			transformer_2.left_upper_arm_x -= 1; 		
 		else if (key == GLFW_KEY_W && mods==GLFW_MOD_SHIFT)
 			transformer.left_upper_arm_x -= 1; 		
 		else if (key == GLFW_KEY_W && mods==GLFW_MOD_CONTROL)
 			transformer_2.left_upper_arm_x += 1;
 		else if (key == GLFW_KEY_W)
 			transformer.left_upper_arm_x += 1;

 		if (key == GLFW_KEY_E && mods == (GLFW_MOD_CONTROL | GLFW_MOD_SHIFT))
 			transformer_2.left_upper_arm_z -= 1; 		
 		else if (key == GLFW_KEY_E && mods==GLFW_MOD_SHIFT)
 			transformer.left_upper_arm_z -= 1; 		
 		else if (key == GLFW_KEY_E && mods==GLFW_MOD_CONTROL)
 			transformer_2.left_upper_arm_z += 1;
 		else if (key == GLFW_KEY_E)
 			transformer.left_upper_arm_z += 1;

 		if (key == GLFW_KEY_R && mods == (GLFW_MOD_CONTROL | GLFW_MOD_SHIFT))
 			transformer_2.left_lower_arm_z -= 1; 		
 		else if (key == GLFW_KEY_R && mods==GLFW_MOD_SHIFT)
 			transformer.left_lower_arm_z -= 1; 		
 		else if (key == GLFW_KEY_R && mods==GLFW_MOD_CONTROL)
 			transformer_2.left_lower_arm_z += 1;
 		else if (key == GLFW_KEY_R)
 			transformer.left_lower_arm_z += 1;


 		if (key == GLFW_KEY_O && mods == (GLFW_MOD_CONTROL | GLFW_MOD_SHIFT))
 			transformer_2.right_upper_arm_x -= 1; 		
 		else if (key == GLFW_KEY_O && mods==GLFW_MOD_SHIFT)
 			transformer.right_upper_arm_x -= 1; 		
 		else if (key == GLFW_KEY_O && mods==GLFW_MOD_CONTROL)
 			transformer_2.right_upper_arm_x += 1;
 		else if (key == GLFW_KEY_O)
 			transformer.right_upper_arm_x += 1;

 		if (key == GLFW_KEY_P && mods == (GLFW_MOD_CONTROL | GLFW_MOD_SHIFT))
 			transformer_2.right_upper_arm_z -= 1; 		
 		else if (key == GLFW_KEY_P && mods==GLFW_MOD_SHIFT)
 			transformer.right_upper_arm_z -= 1; 		
 		else if (key == GLFW_KEY_P && mods==GLFW_MOD_CONTROL)
 			transformer_2.right_upper_arm_z += 1;
 		else if (key == GLFW_KEY_P)
 			transformer.right_upper_arm_z += 1;

 		if (key == GLFW_KEY_F && mods == (GLFW_MOD_CONTROL | GLFW_MOD_SHIFT))
 			transformer_2.right_lower_arm_z -= 1; 		
 		else if (key == GLFW_KEY_F && mods==GLFW_MOD_SHIFT)
 			transformer.right_lower_arm_z -= 1; 		
 		else if (key == GLFW_KEY_F && mods==GLFW_MOD_CONTROL)
 			transformer_2.right_lower_arm_z += 1;
 		else if (key == GLFW_KEY_F)
 			transformer.right_lower_arm_z += 1;


 		if (key == GLFW_KEY_T && mods == (GLFW_MOD_CONTROL | GLFW_MOD_SHIFT))
 			transformer_2.position_y -= 0.1; 		
 		else if (key == GLFW_KEY_T && mods==GLFW_MOD_SHIFT)
 			transformer.position_y-= 0.1; 		
 		else if (key == GLFW_KEY_T && mods==GLFW_MOD_CONTROL)
 			transformer_2.position_y += 0.1;
 		else if (key == GLFW_KEY_T)
 			transformer.position_y += 0.1;


 		if (key == GLFW_KEY_Y && mods == (GLFW_MOD_CONTROL | GLFW_MOD_SHIFT))
 			globalCameraLX-= 0.1; 		
 		else if (key == GLFW_KEY_Y && mods==GLFW_MOD_SHIFT)
 			globalCameraX-= 0.1; 		
 		else if (key == GLFW_KEY_Y && mods==GLFW_MOD_CONTROL)
 			globalCameraLX += 0.1;
 		else if (key == GLFW_KEY_Y)
 			globalCameraX += 0.1;

 		if (key == GLFW_KEY_U && mods == (GLFW_MOD_CONTROL | GLFW_MOD_SHIFT))
 			globalCameraLY-= 0.1; 		
 		else if (key == GLFW_KEY_U && mods==GLFW_MOD_SHIFT)
 			globalCameraY-= 0.1; 		
 		else if (key == GLFW_KEY_U && mods==GLFW_MOD_CONTROL)
 			globalCameraLY += 0.1;
 		else if (key == GLFW_KEY_U)
 			globalCameraY += 0.1;

 		if (key == GLFW_KEY_I && mods == (GLFW_MOD_CONTROL | GLFW_MOD_SHIFT))
 			globalCameraLZ-= 0.1; 		
 		else if (key == GLFW_KEY_I && mods==GLFW_MOD_SHIFT)
 			globalCameraZ-= 0.1; 		
 		else if (key == GLFW_KEY_I && mods==GLFW_MOD_CONTROL)
 			globalCameraLZ += 0.1;
 		else if (key == GLFW_KEY_I)
 			globalCameraZ += 0.1;
	}
};

void Camera(){
	if(CameraMode == 0)
			gluLookAt(globalCameraX,globalCameraY,globalCameraZ,globalCameraLX,globalCameraLY,globalCameraLZ,0,1,0);
	else if(CameraMode == 1)
			gluLookAt(
				transformer.position_x-7.0*sin(transformer.direction*PI/180),transformer.position_y+5,transformer.position_z-7.0*cos(transformer.direction*PI/180),
				transformer.position_x,transformer.position_y,transformer.position_z,
				0,1,0
				);
	else if(CameraMode == 2)
			gluLookAt(
				transformer.position_x+0.1*sin(transformer.direction*PI/180),transformer.position_y+0.42,transformer.position_z+0.1*cos(transformer.direction*PI/180),
				transformer.position_x+5*sin(transformer.direction*PI/180),transformer.position_y+0.42,transformer.position_z+5*cos(transformer.direction*PI/180),
				0,1,0
				);
}