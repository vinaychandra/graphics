#include "transformer.hpp"

GLuint LoadTexture(const char* pic)
{
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;		// Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;	// = width*height*3

	unsigned char * data;
	FILE * file = fopen(pic,"rb");
	fread(header, 1, 54, file);
	dataPos		= *(int*)&(header[0x0A]);
	imageSize	= *(int*)&(header[0x22]);
	width			= *(int*)&(header[0x12]);
	height		= *(int*)&(header[0x16]);
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

void struct_transformer::draw(){
	//	Clear screen and Z-buffer
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

/*	glColor3f(1,0,0);
	glBegin(GL_QUADS);
		glVertex3f(-10,0,10);
		glVertex3f(10,0,10);
		glVertex3f(10,0,-10);
		glVertex3f(-10,0,-10);
	glEnd();*/

	//Set the orientation of the car properly


	glTranslatef(0,extra_movement_translation,0);
	glRotatef(extra_movement_rotation,-1,0,0);

	glTranslatef(0,0.1,0);
	glRotatef(90,1,0,0);
	
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






//GLfloat light_ambient2[]={0.4, 0.4, 0.4, 1.0};
		GLfloat light_diffuse2[]={0.4, 0.4, 0.4, 1.0};
		GLfloat light_specular2[]={1.0, 1.0, 1.0, 1.0};
		GLfloat light_position2[]={0.19, 0.6, -0.05, 1.0};
		GLfloat light_position3[]={-0.19, 0.6, -0.05, 1.0};
		GLfloat light_direction2[]={0.0, -1.0, 0.0};

		//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient2);
		//glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse2);
		glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular2);
		glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light_direction2);
		glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 5.0);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 25.0);
		glEnable(GL_LIGHT2);

		//glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse2);
		glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular2);
		glLightfv(GL_LIGHT3, GL_POSITION, light_position3);
		glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light_direction2);
		glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 5.0);
		glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 25.0);
		glEnable(GL_LIGHT3);

		GLfloat matSpot[]={1.f,1.f,1.f,1.f};
		GLfloat matpot[]={0.1f,0.1f,0.1f,1.f};
		GLfloat mat[]={400.0};
		glMaterialfv(GL_FRONT,GL_SHININESS,mat);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,matpot);
		glMaterialfv(GL_FRONT,GL_SPECULAR,matSpot);


		glCallList(Hood);


		GLfloat materialprop[]={0.6f,0.6f,0.6f,1.f};
		GLfloat matx[]={100.0};
		glMaterialfv(GL_FRONT,GL_SHININESS,matx);
		glMaterialfv(GL_FRONT,GL_DIFFUSE,materialprop);
		glMaterialfv(GL_FRONT,GL_SPECULAR,materialprop);

		glPushMatrix();
			glColor3f(0.1,0.1,0.1);
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
			glColor3f(0.1,0.1,0.1);
			quadratic = gluNewQuadric();
			glTranslatef(0.28,0,0);

			glRotatef(90.0, 0.0, -1.0, 0.0);
			glRotatef(wheel_turn,1,0,0);
			glRotatef(wheel_rotate,0,0,1);

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

		glPushMatrix();
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
			// glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
			
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
				// glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
				
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
		glColor3f(1,1,0);
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


void struct_transformer::GenLists()
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

double absolute(double x)
{
	if (x >= 0) return x;
	else return -1.0*x;
}

bool nearFunc(double &variable, double target = 0.0, double step = 1.0)
{
	if (absolute(variable - target) < step){
		variable = target;
		return false;
	}
	if (variable > target)
		variable -= step;
	if (variable < target)
		variable += step;
	return true;
}

void struct_transformer::toCar()
{

	if (nearFunc(face_rotate_x))return;
	if (nearFunc(face_rotate_y))return;

	nearFunc(windshield_move,0,0.002);
	if (nearFunc(leg_translate,0,0.002)||nearFunc(windshield_move,0,0.002))return;

	if (nearFunc(hood_rotate_x))return;


	if(nearFunc(left_shoulder_angle) || nearFunc(right_shoulder_angle))return;

	if(nearFunc(left_upper_arm_x) || nearFunc(left_upper_arm_y) || nearFunc(left_upper_arm_z) || nearFunc(right_upper_arm_x) || nearFunc(right_upper_arm_y) || nearFunc(right_upper_arm_z))return;

	if(nearFunc(left_lower_arm_x) || nearFunc(left_lower_arm_y) || nearFunc(left_lower_arm_z) || nearFunc(right_lower_arm_x) || nearFunc(right_lower_arm_y) || nearFunc(right_lower_arm_z))return;
	
	if(nearFunc(windshield_full_rotate) || nearFunc(windshield_right_door) || nearFunc(windshield_left_door))return;



	if(nearFunc(foot_move,0,0.0025))return;

	if(nearFunc(left_thigh_angle) || nearFunc(right_thigh_angle) || nearFunc(left_knee_angle) || nearFunc(right_knee_angle) || nearFunc(left_foot_angle) || nearFunc(right_foot_angle))
		return;

	if (nearFunc(extra_movement_rotation))return;	
	if (nearFunc(extra_movement_translation))return;
	
	car_mode = false;
	return;
}

void struct_transformer::toRobot()
{

	if (nearFunc(extra_movement_translation,1.2,0.1))return;
	if (nearFunc(extra_movement_rotation,90))return;	

	if(nearFunc(hood_rotate_x,180))return;
	
	if(nearFunc(face_rotate_x))return;
	if(nearFunc(face_rotate_y,180))return;


	if(nearFunc(windshield_right_door,35))return;
	if(nearFunc(windshield_left_door,35))return;
	if(nearFunc(windshield_full_rotate,120))return;
	

	if(nearFunc(left_shoulder_angle,90))return;
	if(nearFunc(right_shoulder_angle,90))return;

	nearFunc(windshield_move,0.26,0.002);
	if(nearFunc(leg_translate,0.26,0.002)||nearFunc(windshield_move,0.26,0.002))return;

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

	if(nearFunc(foot_move,-0.1,0.0025))return;

	
	
	robot_mode = false;
	return;
}

void struct_transformer::accelerate()
{
	if(velocity >= 0)
		velocity += 0.01;
	else 
		velocity = 0;
}

void struct_transformer::brake() 
{
	if(velocity > 0)
		velocity = 0;
	else
		velocity -= 0.01;
}

void struct_transformer::position_routine()
{
	wheel_rotate -= velocity*300;
	
	position_z += velocity*cos(direction/180*PI);
	position_x += velocity*sin(direction/180*PI);
}

void struct_transformer::LoadTextures()
{	
	//Load Textures
	tyretex=LoadTexture("textures/rim.bmp");
	retex=LoadTexture("textures/face.bmp");
	rtex=LoadTexture("textures/autobot.bmp");
	tex=LoadTexture("textures/nameplate.bmp");
}