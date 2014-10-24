#include "scenery.hpp"

GLuint scenery::load_texture(const char* pic)
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

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	free(data);
	return textureID;
}

void scenery::load_textures()
{
	ground_texture = load_texture("textures/grass.bmp");
	sky_texture = load_texture("textures/sky.bmp");

	make_lights();
}

void scenery::create_all()
{
	create_ground();
	create_sky();
}

void scenery::create_ground()
{
	// std::cout<<ground_texture<<std::endl;
	// glColor3f(1,0,0);

	glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);		
			
		glBindTexture(GL_TEXTURE_2D, ground_texture);
		glBegin(GL_QUADS);
			glTexCoord2f(0,0); glVertex3f(-50,0,50);
			glTexCoord2f(1,0); glVertex3f(50,0,50);
			glTexCoord2f(1,1); glVertex3f(50,0,-50);
			glTexCoord2f(0,1); glVertex3f(-50,0,-50);
		glEnd();
	glDisable(GL_TEXTURE_2D);
}

void scenery::create_sky()
{

	glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);		
			
		glBindTexture(GL_TEXTURE_2D, sky_texture);
		glBegin(GL_QUADS);
			glTexCoord2f(0,0); glVertex3f(-50,0,50);
			glTexCoord2f(1,0); glVertex3f(50,0,50);
			glTexCoord2f(1,1); glVertex3f(50,50,50);
			glTexCoord2f(0,1); glVertex3f(-50,50,50);
		glEnd();
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);		
			
		glBindTexture(GL_TEXTURE_2D, sky_texture);
		glBegin(GL_QUADS);
			glTexCoord2f(0,0); glVertex3f(-50,0,-50);
			glTexCoord2f(1,0); glVertex3f(50,0,-50);
			glTexCoord2f(1,1); glVertex3f(50,50,-50);
			glTexCoord2f(0,1); glVertex3f(-50,50,-50);
		glEnd();
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);		
			
		glBindTexture(GL_TEXTURE_2D, sky_texture);
		glBegin(GL_QUADS);
			glTexCoord2f(0,0); glVertex3f(50,0,50);
			glTexCoord2f(1,0); glVertex3f(50,50,50);
			glTexCoord2f(1,1); glVertex3f(50,50,-50);
			glTexCoord2f(0,1); glVertex3f(50,0,-50);
		glEnd();
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);		
			
		glBindTexture(GL_TEXTURE_2D, sky_texture);
		glBegin(GL_QUADS);
			glTexCoord2f(0,0); glVertex3f(-50,0,50);
			glTexCoord2f(1,0); glVertex3f(-50,50,50);
			glTexCoord2f(1,1); glVertex3f(-50,50,-50);
			glTexCoord2f(0,1); glVertex3f(-50,0,-50);
		glEnd();
	glDisable(GL_TEXTURE_2D);




	glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);		
			
		glBindTexture(GL_TEXTURE_2D, sky_texture);
		glBegin(GL_QUADS);
			glTexCoord2f(0,0); glVertex3f(-50,50,50);
			glTexCoord2f(1,0); glVertex3f(50,50,50);
			glTexCoord2f(1,1); glVertex3f(50,50,-50);
			glTexCoord2f(0,1); glVertex3f(-50,50,-50);
		glEnd();
	glDisable(GL_TEXTURE_2D);
}

void scenery::make_lights()
{
	glEnable(GL_LIGHTING);
		glEnable(GL_NORMALIZE);
	glEnable(GL_SMOOTH);
	

	GLfloat materialprop[]={0.6f,0.6f,0.6f,1.f};
	GLfloat mat[]={100.0};
	glMaterialfv(GL_FRONT,GL_SHININESS,mat);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,materialprop);
	glMaterialfv(GL_FRONT,GL_SPECULAR,materialprop);

	
	GLfloat light_ambient[]={0.9, 0.9, 0.9, 1.0};
	GLfloat light_diffuse[]={1.0, 1.0, 1.0, 1.0};
	GLfloat light_specular[]={1.0, 1.0, 0.0, 1.0};
	GLfloat light_position[]={1.0, 1.0, 1.0, 0.0};
	//GLfloat light_direction[]={0.0, -1.0, 0.0};

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);


	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 2.0);
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 20.0);
	GLfloat light_ambient1[]={1.0, 1.0, 1.0, 1.0};
	GLfloat light_diffuse1[]={1.0, 1.0, 1.0, 1.0};
	GLfloat light_specular1[]={1.0, 1.0, 1.0, 1.0};
	GLfloat light_position1[]={1.0, 1.0, 1.0, 0.0};

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glEnable(GL_LIGHT1);
}