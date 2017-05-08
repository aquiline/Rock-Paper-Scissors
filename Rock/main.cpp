#include<iostream>
#include<GL/glut.h>
#include<stdlib.h>
#include "Text.h"
#include "Button.h"
using namespace std;

int winw = 640 , winh = 480 ;

Text T;
Button B;

void init()
{

    glClearColor(1.0,1.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (0.0, winw, winh, 0);

}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0);
    T.Font(GLUT_BITMAP_TIMES_ROMAN_24,reinterpret_cast<const unsigned char *>("YOYO"),100,100);
    B.Init(280,220, 100,25, 0,0, reinterpret_cast<const unsigned char *>( "Start Game") ,&Button::call);
    (B.*B.callbackFunction)();
    glFlush();
}


void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

int main(int argc,char** argv)
{
    cout<<"Works"<<endl;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("RP");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc (keyboard);
    glutMainLoop();
    return 0;
}
