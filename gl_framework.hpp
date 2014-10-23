/*
 * CS475/CS675 - Computer Graphics
 *  ToyLOGO Assignment Base Code
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _GL_FRAMEWORK_HPP_
#define _GL_FRAMEWORK_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdio.h>
#include <cstdlib>

namespace csX75
{
  //! Initialize GL State
  void initGL(void);

  //!GLFW Error Callback
  void error_callback(int error, const char* description);
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height);
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

// ----------------------------------------------------------
// Texture Functions
// ----------------------------------------------------------
GLuint LoadTexture(const char*);

// ----------------------------------------------------------
// Global Variables
// ----------------------------------------------------------

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

extern double rotate_y;
extern double rotate_x;
extern double rotate_z;

extern double face_rotate_x;
extern double face_rotate_y;

extern double hood_rotate_x;

extern double windshield_full_rotate;
extern double windshield_right_door;
extern double windshield_left_door;

extern double left_shoulder_angle;
extern double right_shoulder_angle;

extern double left_upper_arm_x;
extern double left_upper_arm_y;
extern double left_upper_arm_z;
extern double right_upper_arm_x;
extern double right_upper_arm_y;
extern double right_upper_arm_z;

extern double left_lower_arm_x;
extern double left_lower_arm_y;
extern double left_lower_arm_z;
extern double right_lower_arm_x;
extern double right_lower_arm_y;
extern double right_lower_arm_z;

extern double leg_translate;

extern double left_thigh_angle;
extern double right_thigh_angle;
extern double left_knee_angle;
extern double right_knee_angle;
extern double left_foot_angle;
extern double right_foot_angle;

extern bool car_mode;
extern bool robot_mode;

#endif
