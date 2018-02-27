#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <GL/glut.h>
#include <time.h>
using namespace std;


// Global variables
#define SIZE 360
int sides = 4;
float xangle = 0;
float yangle = 0;
float zangle = 0;
float yMax = 20;
int count = 0;
int right = 0;
int left = 0;
float radius = 5;
float index = 0;
float x[SIZE + 1];
float y[SIZE + 1];

float xLadder[3];
float yLadder[3];
//GLenum mode = GL_POLYGON;
GLenum mode = GL_LINE_LOOP;

//---------------------------------------
// Init function for OpenGL
//---------------------------------------
void init()
{
   glClearColor(0.0, 0.0, 0.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-yMax, yMax, -yMax, yMax, -yMax, yMax);
   glEnable(GL_DEPTH_TEST);
   cout << "Enter + to increase the number of sides and - to decrease the number of lines" << endl;
 
}

void drawCircle(float radius, float centerX, float centerY, int high, int low, int qx, int qy)
{
  float midX = (x[high] + x[low])/2;
  float midY = (y[high] + y[low])/2;
  int midI = (high + low)/2;

  //if statement to start the circle on the axis
  if((high - low) > 1)
  {



    //need to find the distance from the midpoint to the center
    float centerDistance = sqrt(pow((midX - centerX), 2.0) + pow((midY - centerY), 2.0));
    //need to find the distance form the chosen axis to midpoint
    float axisDistance = sqrt(pow((midX - midX), 2.0) + pow((midY -0), 2.0));
    //next find the angle between the axis and line from the center of the circle to the midpoint
    float theta;
    if(centerDistance == 0)
      theta = 0;
    else
      theta = asin((axisDistance/centerDistance));


    //finding the x and y values with the angle
      x[midI] = qx * radius * cos(theta);
      y[midI] = qy * radius * sin(theta);

    //setting the coordinate for all of the quadrants
    drawCircle(radius, centerX, centerY, midI, low, qx, qy);
    drawCircle(radius, centerX, centerY, high, midI, qx, qy);

  }
}
void draw()
{

  x[0] = radius;
  y[0] = 0;
  x[sides/4] = 0;
  y[sides/4] = radius;
  x[2*sides/4] = -radius;
  y[2*sides/4] = 0;
  x[3*sides/4] = 0;
  y[3*sides/4] = -radius;
  x[sides] = radius;
  y[sides] = 0;
  glBegin(mode);
  glColor3f(1.0, 0, 0);
  drawCircle(radius, 0, 0, sides/4, 0, 1, 1);
  drawCircle(radius, 0, 0, 2*sides/4, sides/4, -1, 1);
  drawCircle(radius, 0, 0, 3*sides/4, 2*sides/4, -1, -1);
  drawCircle(radius, 0, 0, sides, 3*sides/4, 1, -1);
  for(int i = 0; i <= sides; i++)
  {
    //cout << x[i] << " " << y[i] << endl;
    glVertex2f(x[i], y[i]);
  }
  glEnd();


}


void keyboard(unsigned char key, int x, int y)
{
   // Update angles
   if (key == 'x')
      xangle -= 5;
   else if (key == 'y')
      yangle -= 5;
   else if (key == 'z')
      zangle -= 5;
   else if (key == 'X')
      xangle += 5;
   else if (key == 'Y')
      yangle += 5;
   else if (key == 'Z')
      zangle += 5;

  if(key == '+')
      sides += 4 % SIZE;
  else if(key == '-')
      sides -= 4 % SIZE;

   // Redraw objects
   glutPostRedisplay();
}


void display()
{

   // Incrementally rotate objects
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glRotatef(xangle, 1.0, 0.0, 0.0);
   glRotatef(yangle, 0.0, 1.0, 0.0);
   glRotatef(zangle, 0.0, 0.0, 1.0);

   // Draw tables and book cases
  draw();
   glFlush();
}



void idle(){
  index += 0.01;
  if(index > (10.0/4.0))
    index = 0;
  glutPostRedisplay();
}

int main(int argc, char *argv[])
{



   glutInit(&argc, argv);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(250, 250);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
   glutCreateWindow("circle");
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   //glutIdleFunc(idle);
   init();
   glutMainLoop();
   return 0;
}
