#include <stdlib.h>
#include <GL/glut.h>
#include "imageloader.h"

float _angle = 0.0;
GLuint _textureBrick, _textureDoor, _textureGrass, _textureRoof, _textureWindow, _textureSky;

static void resize(int width, int height)   //This function is responsible for the size of the display window
{
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);   //initialization of viewport of given width and height
    glMatrixMode(GL_PROJECTION);     //selection of matrix mode
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);    // intialization of viewing frustum
    glMatrixMode(GL_MODELVIEW);   //selection of matrix mode
    glLoadIdentity();
}

void renderScene(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // clearing the buffer
    glEnable(GL_TEXTURE_2D);    //enabling 2d texture

    // Sky
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureSky);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-10);      // translating to the position where we want our sky to start
	glRotatef(_angle,0.0,0.0,1.0);
        glBegin(GL_QUADS);     // here we are marking the coordinates where our sky will be
            glTexCoord3f(0.0,1.0,0.1);  glVertex3f(-10,10,0);
            glTexCoord3f(1.0,1.0,0.1);  glVertex3f(10,10,0);
            glTexCoord3f(1.0,0.0,0.1);  glVertex3f(10,-10,0);
            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-10,-10,0);
        glEnd();
    glPopMatrix();

    // Grass
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureGrass);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-6);   //translating to the position where we want our grass to start
        glRotatef(_angle, 0.0, 1.0, 0.0); // roatating  degrees to see the grass
        glBegin(GL_QUADS);   //here we are marking the coordinates where we our grassy portion will be
            glTexCoord3f(0.0,70.0,1);  glVertex3f(-50,-1.5,50);
            glTexCoord3f(0.0,0.0,-1);  glVertex3f(-50,-1.5,-50);
            glTexCoord3f(70.0,0.0,-1);  glVertex3f(50,-1.5,-50);
            glTexCoord3f(70.0,70.0,1);  glVertex3f(50,-1.5,50);
        glEnd();
    glPopMatrix();

    // Front side
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureBrick);   //for the front wall
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-6);     // translating to the position where we want our front side of house to begin
        glRotatef(_angle, 0.0, 1.0, 0.0);  //rotating degrees to see the front side
        glBegin(GL_QUADS);  // here we are marking the coordinates of the front Wall
            glTexCoord3f(0.0,2.0,0.1);  glVertex3f(-2,0,1);
            glTexCoord3f(4.0,2.0,0.1);  glVertex3f(2,0,1);
            glTexCoord3f(4.0,0.0,0.1);  glVertex3f(2,-1.5,1);
            glTexCoord3f(0.0,0.0,0.1);  glVertex3f(-2,-1.5,1);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, _textureRoof);  //for the part of the roof visible from the front side
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBegin(GL_QUADS);  //here we are marking the coordinates of the Roof that is visible from the front side
            glTexCoord3f(0.0,2.0,0); glVertex3f(-2.2,0.5,0);
            glTexCoord3f(4.0,2.0,0);glVertex3f(2.2,0.5,0);
            glTexCoord3f(4.0,0.0,1.25); glVertex3f(2.2,-0.1,1.25);
            glTexCoord3f(0.0,0.0,1.25); glVertex3f(-2.2,-0.1,1.25);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, _textureDoor);  // for the front door
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBegin(GL_QUADS);  //here we are marking the coordinates of the front Door
            glTexCoord3f(0.0,1.0,1.0001); glVertex3f(-0.3,-0.4,1.0001);
            glTexCoord3f(1.0,1.0,1.0001); glVertex3f(0.3,-0.4,1.0001);
            glTexCoord3f(1.0,0.0,1.0001); glVertex3f(0.3,-1.5,1.0001);
            glTexCoord3f(0.0,0.0,1.0001); glVertex3f(-0.3,-1.5,1.0001);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, _textureWindow); // for the front windows on the left
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBegin(GL_QUADS);  //here we are specifying the coordinates of the left Window on the front side
            glTexCoord3f(0.0,1.0,1.0001); glVertex3f(-1.5,-0.3,1.0001);
            glTexCoord3f(1.0,1.0,1.0001); glVertex3f(-0.75,-0.3,1.0001);
            glTexCoord3f(1.0,0.0,1.0001); glVertex3f(-0.75,-0.8,1.0001);
            glTexCoord3f(0.0,0.0,1.0001); glVertex3f(-1.5,-0.8,1.0001);
        glEnd();

        glBegin(GL_QUADS);  //now here we are specifying the coordinates of  the front Window on the Right side
            glTexCoord3f(0.0,1.0,1.0001); glVertex3f(1.5,-0.3,1.0001);
            glTexCoord3f(1.0,1.0,1.0001); glVertex3f(0.75,-0.3,1.0001);
            glTexCoord3f(1.0,0.0,1.0001); glVertex3f(0.75,-0.8,1.0001);
            glTexCoord3f(0.0,0.0,1.0001); glVertex3f(1.5,-0.8,1.0001);
        glEnd();
    glPopMatrix();

    // Back side
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, _textureBrick);   //for the brick wall on the back side
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-6);  // translating to the position where we want our back wall to start
        glRotatef(_angle, 0.0, 1.0, 0.0);  //rotating degree to see the back side
        glBegin(GL_QUADS);  //specifying the coordinates of the back  Wall
            glTexCoord3f(0.0,2.0,-1);  glVertex3f(-2,0,-1);
            glTexCoord3f(4.0,2.0,-1);  glVertex3f(2,0,-1);
            glTexCoord3f(4.0,0.0,-1);  glVertex3f(2,-1.5,-1);
            glTexCoord3f(0.0,0.0,-1);  glVertex3f(-2,-1.5,-1);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, _textureRoof); //for the part of the roof visible from the back side
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBegin(GL_QUADS);  //specifying the coordinates of the Roof that is visible from the back side
            glTexCoord3f(0.0,2.0,0); glVertex3f(-2.2,0.5,0);
            glTexCoord3f(4.0,2.0,0);glVertex3f(2.2,0.5,0);
            glTexCoord3f(4.0,0.0,-1.25); glVertex3f(2.2,-0.1,-1.25);
            glTexCoord3f(0.0,0.0,-1.25); glVertex3f(-2.2,-0.1,-1.25);
        glEnd();

        glBindTexture(GL_TEXTURE_2D, _textureWindow);  //for the windows on the back side
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBegin(GL_QUADS);  // specifying the coordinates of the window on the left side
            glTexCoord3f(0.0,1.0,-1.0001); glVertex3f(-1.5,-0.3,-1.0001);
            glTexCoord3f(1.0,1.0,-1.0001); glVertex3f(-0.75,-0.3,-1.0001);
            glTexCoord3f(1.0,0.0,-1.0001); glVertex3f(-0.75,-0.8,-1.0001);
            glTexCoord3f(0.0,0.0,-1.0001); glVertex3f(-1.5,-0.8,-1.0001);
        glEnd();

        glBegin(GL_QUADS);  // specifying the coordinates of the window on the right side.
            glTexCoord3f(0.0,1.0,1.0001); glVertex3f(1.5,-0.3,-1.0001);
            glTexCoord3f(1.0,1.0,1.0001); glVertex3f(0.75,-0.3,-1.0001);
            glTexCoord3f(1.0,0.0,1.0001); glVertex3f(0.75,-0.8,-1.0001);
            glTexCoord3f(0.0,0.0,1.0001); glVertex3f(1.5,-0.8,-1.0001);
        glEnd();
    glPopMatrix();

    // Right side
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureBrick);  //for the wall visible from the right side
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-6);  //translating to the position where we want our wall to start
        glRotatef(_angle, 0.0, 1.0, 0.0);  //rotating degrees to see right side
        glBegin(GL_QUADS);  // specifying the coordinates of the Wall on the right side
            glTexCoord3f(0.0,2.0,1); glVertex3f(2,0,1);
            glTexCoord3f(2.0,2.0,-1); glVertex3f(2,0,-1);
            glTexCoord3f(2.0,0.0,-1); glVertex3f(2,-1.5,-1);
            glTexCoord3f(0.0,0.0,1); glVertex3f(2,-1.5,1);
        glEnd();

        glBegin(GL_TRIANGLES);  // specifying the coordinates of the upper Wall which is triangular in shape
            glTexCoord3f(0.0,1.0,0); glVertex3f(2,0.5,0);
            glTexCoord3f(1.0,0.0,1); glVertex3f(2,0,1);
            glTexCoord3f(-1.0,0.0,-1); glVertex3f(2,0,-1);
        glEnd();
    glPopMatrix();

    // Left side
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, _textureBrick);  //for the wall visible from the left side
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTranslatef(0,0,-6);  //translating to the position where our left wall starts
        glRotatef(_angle, 0.0, 1.0, 0.0);  //rotatinmg 90 degrees to see the left wall
        glBegin(GL_QUADS);  //specifying the coordinates of the Wall on the left side
            glTexCoord3f(0.0,2.0,1);    glVertex3f(-2,0,1);
            glTexCoord3f(2.0,2.0,-1);    glVertex3f(-2,0,-1);
            glTexCoord3f(2.0,0.0,-1);    glVertex3f(-2,-1.5,-1);
            glTexCoord3f(0.0,0.0,1);    glVertex3f(-2,-1.5,1);
        glEnd();

        glBegin(GL_TRIANGLES);  //specifying the coordinates of the wall on the upper side which is triangular in shape
            glTexCoord3f(0.0,1.0,0);    glVertex3f(-2,0.5,0);
            glTexCoord3f(1.0,0.0,1);    glVertex3f(-2,0,1);
            glTexCoord3f(-1.0,0.0,-1);    glVertex3f(-2,0,-1);
        glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

void mySpecialFunc(int key, int x, int y){    //this function deals with the rotation of house to see the 3d view whenever RIGHT or LEFT key is pressed
	switch (key) {
    case GLUT_KEY_RIGHT:
        _angle += 1;    // at each click of RIGHT button it rotates the image with +1 degree in the right direction.
        if (_angle > 360) _angle = 0.0;   // if angle becomes 360 degree so it gets reinitialized to 0 so as to complete one complete rotation of the house
		break;
    case GLUT_KEY_LEFT:
        _angle -= 1;   // at each click of LEFT click it roatates 1 degree in the left direction
        if (_angle > 360) _angle = 0.0;  // if angle becomes 360 degrees it gets reinitialized to 0 so as to complete one complete rotation.
	    break;
	}
	glutPostRedisplay();
}

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void Initialize() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	Image* image = loadBMP("/home/vijay/Downloads/3D-House-using-OpenGL-and-C--master/bricks.bmp");
	_textureBrick = loadTexture(image);
	image = loadBMP("/home/vijay/Downloads/3D-House-using-OpenGL-and-C--master/door.bmp");
	_textureDoor = loadTexture(image);
	image = loadBMP("/home/vijay/Downloads/3D-House-using-OpenGL-and-C--master/grass.bmp");
	_textureGrass = loadTexture(image);
	image = loadBMP("/home/vijay/Downloads/3D-House-using-OpenGL-and-C--master/roof.bmp");
	_textureRoof = loadTexture(image);
	image = loadBMP("/home/vijay/Downloads/3D-House-using-OpenGL-and-C--master/window.bmp");
	_textureWindow = loadTexture(image);
	image = loadBMP("/home/vijay/Downloads/3D-House-using-OpenGL-and-C--master/sky.bmp");
	_textureSky = loadTexture(image);
	delete image;
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(600,600);
	glutCreateWindow("Textured House by Rakib");
	glEnable(GL_DEPTH_TEST);

	glutReshapeFunc(resize);
	glutSpecialFunc(mySpecialFunc);
	glutDisplayFunc(renderScene);
	Initialize();

	glutMainLoop();

	return 0;
}
