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
		
		if(key == GLFW_KEY_UP)
			transformer.accelerate();
		if(key == GLFW_KEY_DOWN && action == GLFW_PRESS)
			transformer.brake();
		
		if(key == GLFW_KEY_LEFT){
			transformer.wheel_turn = -20;
			if (transformer.velocity >= 0)
				transformer.direction += 1;
			else 
				transformer.direction -= 1;
		}
		if(key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
			transformer.wheel_turn = 0;


		if(key == GLFW_KEY_RIGHT){
			transformer.wheel_turn = 20;
			if (transformer.velocity >= 0)
				transformer.direction -= 1;
			else
				transformer.direction += 1;
		}
		if(key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
			transformer.wheel_turn = 0;
		

		if (key == GLFW_KEY_SPACE && mods == GLFW_MOD_SHIFT){
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
	}
};

void Camera(){
	if(CameraMode == 0)
			gluLookAt(2,5,8,0,0,0,0,1,0);
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