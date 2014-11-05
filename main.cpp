#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <string>
#include "transformer.hpp"
#include "gl_framework.hpp"
#include "scenery.hpp"

void renderGL();
void routines();

struct_transformer transformer, transformer_2;
scenery world;

int main(int argc, char** argv)
{

	//! The pointer to the GLFW window
	GLFWwindow* window;

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

		Camera();

		glPushMatrix();
		
			glTranslatef(transformer.position_x,transformer.position_y,transformer.position_z);
			glRotatef(transformer.direction,0,1,0);
		
			transformer.draw();
		glPopMatrix();

		glPushMatrix();
		
			/*glTranslatef(transformer_2.position_x,transformer_2.position_y,transformer_2.position_z);
			glRotatef(transformer_2.direction,0,1,0);*/
		
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