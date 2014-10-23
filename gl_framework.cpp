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

 namespace csX75
 {
 	int win_width;
 	int win_height;

 	void p();

  //! Initialize GL State
 	void initGL(void)
 	{
		//Set framebuffer clear color
		//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		//Set depth buffer furthest depth
		glClearDepth(1.0);

		//Set depth test to less-than
		glDepthFunc(GL_LESS);

		//Enable depth testing
		//  glEnable(GL_DEPTH_TEST);
		//Enable Gourard shading
		//	glEnable(GL_CULL_FACE);

		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		glMatrixMode(GL_PROJECTION);
		glOrtho(-1, 1, -1, 1, -1, 1);
 	}

  //!GLFW Error Callback
 	void error_callback(int error, const char* description)
 	{
 		std::cerr<<description<<std::endl;
 	}

  //!GLFW framebuffer resize callback
 	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
 	{
 		if	( height == 0 ) height = 1;

 		glMatrixMode( GL_PROJECTION );
 		glLoadIdentity();

 		//Draw to the whole window
 		glViewport( 0, 0, width, height );

		//Keep the aspect ratio fixed
 		double aspect;
 		if (width > height)
 		{
 			aspect = (double)width/(double)height;
 			glOrtho(-aspect, aspect, -1.0, 1.0, -1.0, 1.0);
 		}
 		else
 		{
 			aspect = (double)height/(double)width;
 			glOrtho(-1.0, 1.0, -aspect, aspect, -1.0, 1.0);
 		}

 		win_width = width;
 		win_height = height;
 	}

  //!GLFW keyboard callback
 	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
 	{
     //!Close the window if the ESC key was pressed
 		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
 			glfwSetWindowShouldClose(window, GL_TRUE);
 		else if (key == GLFW_KEY_RIGHT)
 			rotate_y += 1;
 		else if (key == GLFW_KEY_LEFT)
 			rotate_y -= 1;
 		else if (key == GLFW_KEY_UP && mods==GLFW_MOD_SHIFT)
 			rotate_z += 1;
 		else if (key == GLFW_KEY_DOWN && mods==GLFW_MOD_SHIFT)
 			rotate_z -= 1;
 		else if (key == GLFW_KEY_UP)
 			rotate_x += 1;
 		else if (key == GLFW_KEY_DOWN)
 			rotate_x -= 1;

 		else if (key == GLFW_KEY_Q && mods==GLFW_MOD_SHIFT)
 			face_rotate_x -= 1;
 		else if (key == GLFW_KEY_Q)
 			face_rotate_x += 1;

 		else if (key == GLFW_KEY_W && mods==GLFW_MOD_SHIFT)
 			face_rotate_y -= 1;
 		else if (key == GLFW_KEY_W)
 			face_rotate_y += 1;

 		else if (key == GLFW_KEY_E && mods==GLFW_MOD_SHIFT)
 			hood_rotate_x -= 1;
 		else if (key == GLFW_KEY_E)
 			hood_rotate_x += 1;

 		else if (key == GLFW_KEY_R && mods==GLFW_MOD_SHIFT)
 			windshield_full_rotate -= 1;
 		else if (key == GLFW_KEY_R)
 			windshield_full_rotate += 1;

 		else if (key == GLFW_KEY_T && mods==GLFW_MOD_SHIFT)
 			windshield_left_door -= 1;
 		else if (key == GLFW_KEY_T)
 			windshield_left_door += 1;

 		else if (key == GLFW_KEY_Y && mods==GLFW_MOD_SHIFT)
 			windshield_right_door -= 1;
 		else if (key == GLFW_KEY_Y)
 			windshield_right_door += 1;

 		else if (key == GLFW_KEY_U && mods==GLFW_MOD_SHIFT)
 			left_shoulder_angle -= 1;
 		else if (key == GLFW_KEY_U)
 			left_shoulder_angle += 1;

 		else if (key == GLFW_KEY_I && mods==GLFW_MOD_SHIFT)
 			right_shoulder_angle -= 1;
 		else if (key == GLFW_KEY_I)
 			right_shoulder_angle += 1;

 		else if (key == GLFW_KEY_O && mods == GLFW_MOD_CONTROL)
 			left_upper_arm_x += 1;
 		else if (key == GLFW_KEY_O && mods == (GLFW_MOD_CONTROL | GLFW_MOD_SHIFT))
 			left_upper_arm_x -= 1;

 		else if (key == GLFW_KEY_O && mods == GLFW_MOD_ALT)
 			left_upper_arm_y += 1;
 		else if (key == GLFW_KEY_O && mods == (GLFW_MOD_ALT | GLFW_MOD_SHIFT))
 			left_upper_arm_y -= 1;

 		else if (key == GLFW_KEY_O && mods == GLFW_MOD_SHIFT)
 			left_upper_arm_z += 1;
 		else if (key == GLFW_KEY_O)
 			left_upper_arm_z -= 1;

 		else if (key == GLFW_KEY_P && mods == GLFW_MOD_CONTROL)
 			right_upper_arm_x += 1;
 		else if (key == GLFW_KEY_P && mods == (GLFW_MOD_CONTROL | GLFW_MOD_SHIFT))
 			right_upper_arm_x -= 1;

 		else if (key == GLFW_KEY_P && mods == GLFW_MOD_ALT)
 			right_upper_arm_y += 1;
 		else if (key == GLFW_KEY_P && mods == (GLFW_MOD_ALT | GLFW_MOD_SHIFT))
 			right_upper_arm_y -= 1;

 		else if (key == GLFW_KEY_P && mods == GLFW_MOD_SHIFT)
 			right_upper_arm_z += 1;
 		else if (key == GLFW_KEY_P)
 			right_upper_arm_z -= 1;

 		else if (key == GLFW_KEY_K && mods == GLFW_MOD_CONTROL)
 			left_lower_arm_x += 1;
 		else if (key == GLFW_KEY_K && mods == (GLFW_MOD_CONTROL | GLFW_MOD_SHIFT))
 			left_lower_arm_x -= 1;

 		else if (key == GLFW_KEY_K && mods == GLFW_MOD_ALT)
 			left_lower_arm_y += 1;
 		else if (key == GLFW_KEY_K && mods == (GLFW_MOD_ALT | GLFW_MOD_SHIFT))
 			left_lower_arm_y -= 1;

 		else if (key == GLFW_KEY_K && mods == GLFW_MOD_SHIFT)
 			left_lower_arm_z += 1;
 		else if (key == GLFW_KEY_K)
 			left_lower_arm_z -= 1;

 		else if (key == GLFW_KEY_L && mods == GLFW_MOD_CONTROL)
 			right_lower_arm_x += 1;
 		else if (key == GLFW_KEY_L && mods == (GLFW_MOD_CONTROL | GLFW_MOD_SHIFT))
 			right_lower_arm_x -= 1;

 		else if (key == GLFW_KEY_L && mods == GLFW_MOD_ALT)
 			right_lower_arm_y += 1;
 		else if (key == GLFW_KEY_L && mods == (GLFW_MOD_ALT | GLFW_MOD_SHIFT))
 			right_lower_arm_y -= 1;

 		else if (key == GLFW_KEY_L && mods == GLFW_MOD_SHIFT)
 			right_lower_arm_z += 1;
 		else if (key == GLFW_KEY_L)
 			right_lower_arm_z -= 1;

 		else if (key == GLFW_KEY_A && mods == GLFW_MOD_SHIFT)
 			left_thigh_angle += 1;
 		else if (key == GLFW_KEY_A)
 			left_thigh_angle -= 1;

 		else if (key == GLFW_KEY_S && mods == GLFW_MOD_SHIFT)
 			right_thigh_angle += 1;
 		else if (key == GLFW_KEY_S)
 			right_thigh_angle -= 1;

 		else if (key == GLFW_KEY_D && mods == GLFW_MOD_SHIFT)
 			left_knee_angle += 1;
 		else if (key == GLFW_KEY_D)
 			left_knee_angle -= 1;

		else if (key == GLFW_KEY_F && mods == GLFW_MOD_SHIFT)
 			right_knee_angle += 1;
 		else if (key == GLFW_KEY_F)
 			right_knee_angle -= 1;

 		else if (key == GLFW_KEY_G && mods == GLFW_MOD_SHIFT)
 			left_foot_angle += 1;
 		else if (key == GLFW_KEY_G)
 			left_foot_angle -= 1;

 		else if (key == GLFW_KEY_H && mods == GLFW_MOD_SHIFT)
 			right_foot_angle += 1;
 		else if (key == GLFW_KEY_H)
 			right_foot_angle -= 1;

 		else if (key == GLFW_KEY_J && mods == GLFW_MOD_SHIFT)
 			leg_translate -= 0.01;
 		else if (key == GLFW_KEY_J)
 			leg_translate += 0.01;

 		else if (key == GLFW_KEY_ENTER)
 			p();

 		else if (key == GLFW_KEY_SPACE && mods == GLFW_MOD_SHIFT){
 			car_mode = true;
 			robot_mode = false;
 		}
 		else if (key == GLFW_KEY_SPACE){
 			car_mode = false;
 			robot_mode = true;
 		}



 		else if (key == GLFW_KEY_Z && mods == GLFW_MOD_SHIFT)
 			wheel_turn += 1;
		else if (key == GLFW_KEY_Z)
 			wheel_turn -= 1;
 		

 		else if (key == GLFW_KEY_X && mods == GLFW_MOD_SHIFT)
 			wheel_rotate += 1;
 		else if (key == GLFW_KEY_X)
 			wheel_rotate -= 1;
 		
 	}	

 	void p()
 	{
		std::cout<<rotate_y<<std::endl;//90
		std::cout<<rotate_x<<std::endl;//11=0
		std::cout<<rotate_z<<std::endl;//0

		std::cout<<face_rotate_x<<std::endl;//0
		std::cout<<face_rotate_y<<std::endl;//180

		std::cout<<hood_rotate_x<<std::endl;//180

		std::cout<<windshield_full_rotate<<std::endl;//120
		std::cout<<windshield_right_door<<std::endl;//35
		std::cout<<windshield_left_door<<std::endl;//35

		std::cout<<left_shoulder_angle<<std::endl;//90
		std::cout<<right_shoulder_angle<<std::endl;//90

		std::cout<<left_upper_arm_x<<std::endl;//0
		std::cout<<left_upper_arm_y<<std::endl;//0
		std::cout<<left_upper_arm_z<<std::endl;//0
		std::cout<<right_upper_arm_x<<std::endl;//0
		std::cout<<right_upper_arm_y<<std::endl;//0
		std::cout<<right_upper_arm_z<<std::endl;//0

		std::cout<<left_lower_arm_x<<std::endl;//0
		std::cout<<left_lower_arm_y<<std::endl;//0
		std::cout<<left_lower_arm_z<<std::endl;//-20
		std::cout<<right_lower_arm_x<<std::endl;//0
		std::cout<<right_lower_arm_y<<std::endl;//0
		std::cout<<right_lower_arm_z<<std::endl;//20

		std::cout<<leg_translate<<std::endl;//0.2

		std::cout<<left_thigh_angle<<std::endl;//0
		std::cout<<right_thigh_angle<<std::endl;//0
		std::cout<<left_knee_angle<<std::endl;//0
		std::cout<<right_knee_angle<<std::endl;//0
		std::cout<<left_foot_angle<<std::endl;//-90
		std::cout<<right_foot_angle<<std::endl;//-90
 	}
 };

 GLuint LoadTexture(const char* pic)
 {
   unsigned char header[54]; // Each BMP file begins by a 54-bytes header
   unsigned int dataPos;     // Position in the file where the actual data begins
   unsigned int width, height;
   unsigned int imageSize;   // = width*height*3

   unsigned char * data;
   FILE * file = fopen(pic,"rb");
   fread(header, 1, 54, file);
   dataPos    = *(int*)&(header[0x0A]);
   imageSize  = *(int*)&(header[0x22]);
   width      = *(int*)&(header[0x12]);
   height     = *(int*)&(header[0x16]);
   data = new unsigned char [imageSize];
   fread(data,1,imageSize,file);
   fclose(file);

   GLuint textureID;
   glGenTextures(1, &textureID);
   glBindTexture(GL_TEXTURE_2D, textureID);
   glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

   glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
   glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
   glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   free(data);
   return textureID;
 }
