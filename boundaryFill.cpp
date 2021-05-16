#define GL_SILENCE_DEPRECATION

#include <bits/stdc++.h>
#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

 int width = 500, height = 500;  
 float colorToFill[3] = {0.4,0.0,0.8};  
 float borderCol[3] = {0.0,0.0,0.0}; 

 void myinit()  
 {         
      glViewport(0,0,width,height);  //window
      glMatrixMode(GL_PROJECTION);  //stack for projection
      glLoadIdentity();  
      gluOrtho2D(0.0,(GLdouble)width,0.0,(GLdouble)height);  //clipping
      glMatrixMode(GL_MODELVIEW);  //stack for model
 }
 
  void boundaryfillAlgo(int x,int y,float fillColor[3],float borderColor[3])  
 {  
      float interiorColor[3];  
      glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,interiorColor); //current pixel data
 
      if((interiorColor[0] != borderColor[0] && (interiorColor[1])!=borderColor[1] && (interiorColor[2])!=borderColor[2]) &&
       (interiorColor[0]!=fillColor[0] && (interiorColor[1])!=fillColor[1] && (interiorColor[2])!=fillColor[2]))  
      {  
           //Fill the pixel
           glBegin(GL_POINTS);  
           glColor3fv(fillColor);  
           glVertex2i(x,y);  
           glEnd();  
           glFlush();
           
           //Recursion for all sides
           boundaryfillAlgo(x+1,y,fillColor,borderColor);  
           boundaryfillAlgo(x-1,y,fillColor,borderColor);  
           boundaryfillAlgo(x,y+1,fillColor,borderColor);  
           boundaryfillAlgo(x,y-1,fillColor,borderColor);
           
      }  
 } 

 void drawPolygon(int x1, int y1, int x2, int y2)  //150,250,300,400
 {       
      glColor3f(0.0,0.0,0.0);  

      glBegin(GL_LINES);  //Line drawing
           glVertex2i(x1, y1);  
           glVertex2i(x1, y2);   
      glEnd();  
      glBegin(GL_LINES);  
           glVertex2i(x2, y1);  
           glVertex2i(x2, y2);  
      glEnd();
        
      glBegin(GL_LINES);  
           glVertex2i(x1, y1);  
           glVertex2i(x2, y1);  
      glEnd();  
      glBegin(GL_LINES);  
           glVertex2i(x1, y2);  
           glVertex2i(x2, y2);  
      glEnd();  

      glFlush();  
 }  
 
//For Triangle
//   glBegin(GL_LINES);
//    glVertex2i(150,150);
//    glVertex2i(350,150);
//  glEnd();  
//  glBegin(GL_LINES);
//    glVertex2i(150,150);
//    glVertex2i(250,250);
//  glEnd();
//  glBegin(GL_LINES);
//    glVertex2i(250,250);
//    glVertex2i(350,150);
//  glEnd();

 void display()  
 {  
      glClearColor(1,1,1,1);  
      glClear(GL_COLOR_BUFFER_BIT);  
      drawPolygon(150,250,300,400);  
      glFlush();  
 }  
  
 void mousePosition(int btn, int state, int x, int y)  
 {  
      if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN)   
      {  
           int start_X = x;  
           int start_Y = (height-y);  
           boundaryfillAlgo(start_X,start_Y,colorToFill,borderCol);  
      }  
 }  

 int main(int argc, char** argv)  
 {  
      glutInit(&argc,argv);  
      glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);  
      glutInitWindowSize(width, height);  
      glutCreateWindow("Bounadary-Fill-Recursive");  
      glutDisplayFunc(display);  
      myinit();  
      glutMouseFunc(mousePosition);  
      glutMainLoop();  
      return 0;  
 }  
