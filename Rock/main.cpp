#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#endif

#include <GL/glut.h>

using namespace std;

struct Mouse
{
	int x;		/*	the x coordinate of the mouse cursor	*/
	int y;		/*	the y coordinate of the mouse cursor	*/
	int lmb;	/*	is the left button pressed?		*/
	int mmb;	/*	is the middle button pressed?	*/
	int rmb;	/*	is the right button pressed?	*/

	int xpress; /*	stores the x-coord of when the first button press occurred	*/
	int ypress; /*	stores the y-coord of when the first button press occurred	*/
};

typedef struct Mouse Mouse;

Mouse TheMouse = {0,0,0,0,0};

int winw = 1200;
int winh = 650;


typedef void (*ButtonCallback)();

struct Button
{
	int   x;							/* top left x coord of the button */
	int   y;							/* top left y coord of the button */
	int   w;							/* the width of the button */
	int   h;							/* the height of the button */
	int	  state;						/* the state, 1 if pressed, 0 otherwise */
	int	  highlighted;					/* is the mouse cursor over the control? */
	const unsigned char* label;						/* the text label of the button */
	ButtonCallback callbackFunction;	/* A pointer to a function to call if the button is pressed */
};
typedef struct Button Button;

void Font(void *font,const unsigned char *text,int x,int y)
{
	glRasterPos2i(x, y);

	while( *text != '\0' )
	{
		glutBitmapCharacter( font, *text );
		++text;
	}
}
int userChoice=0;
int cpuChoice=0;

void kb(unsigned char key, int x, int y)
{
   switch (key) {
      case 'z':  userChoice=1;glutPostRedisplay();break;
      case 'x':  userChoice=2;glutPostRedisplay();break;
      case 'c':  userChoice=3;glutPostRedisplay();break;
   }
}
void cpuDisplay()
{
    if(cpuChoice == 1)
    {
        Font(GLUT_BITMAP_TIMES_ROMAN_24,reinterpret_cast<const unsigned char *>("Rock"),900,300);
        cout<<cpuChoice;
    }
    else if(cpuChoice == 2)
    {
        Font(GLUT_BITMAP_TIMES_ROMAN_24,reinterpret_cast<const unsigned char *>("Paper"),900,300);
        cout<<cpuChoice;
    }
    else if(cpuChoice == 3)
    {
        Font(GLUT_BITMAP_TIMES_ROMAN_24,reinterpret_cast<const unsigned char *>("Scissor"),900,300);
        cout<<cpuChoice;
    }
}
void computeWinner()
{
    if((cpuChoice == 1 && userChoice == 1) || (cpuChoice == 2 && userChoice == 2) || (cpuChoice == 3 && userChoice == 3))
    {
        Font(GLUT_BITMAP_TIMES_ROMAN_24,reinterpret_cast<const unsigned char *>("TIED"),600,600);
        cout<<cpuChoice;
    }
    else if((cpuChoice == 3 && userChoice == 1) || (cpuChoice == 1 && userChoice == 2) || (cpuChoice == 2 && userChoice == 3))
    {
        Font(GLUT_BITMAP_TIMES_ROMAN_24,reinterpret_cast<const unsigned char *>("Player Wins"),600,600);
        cout<<cpuChoice;
    }
    else if((cpuChoice == 1 && userChoice == 3) || (cpuChoice == 2 && userChoice == 1) || (cpuChoice == 3 && userChoice == 2))
    {
        Font(GLUT_BITMAP_TIMES_ROMAN_24,reinterpret_cast<const unsigned char *>("Cpu Wins"),600,600);
        cout<<cpuChoice;
    }
}
void gameplay()
{
    Font(GLUT_BITMAP_TIMES_ROMAN_24,reinterpret_cast<const unsigned char *>( "Enter Your Choice" ),100,100);
    Font(GLUT_BITMAP_TIMES_ROMAN_24,reinterpret_cast<const unsigned char *>( "Player" ),200,200);
    Font(GLUT_BITMAP_TIMES_ROMAN_24,reinterpret_cast<const unsigned char *>( "CPU" ),800,200);


    if(userChoice == 1)
    {
        cpuChoice = rand()%3+1;
        Font(GLUT_BITMAP_TIMES_ROMAN_24,reinterpret_cast<const unsigned char *>("Rock"),300,300);
        cpuDisplay();
        computeWinner();
    }
    else if(userChoice == 2)
    {
        cpuChoice = rand()%3+1;
        Font(GLUT_BITMAP_TIMES_ROMAN_24,reinterpret_cast<const unsigned char *>("Paper"),300,300);
        cpuDisplay();
        computeWinner();
    }
    else if(userChoice == 3)
    {
        cpuChoice = rand()%3+1;
        Font(GLUT_BITMAP_TIMES_ROMAN_24,reinterpret_cast<const unsigned char *>("Scissor"),300,300);
        cpuDisplay();
        computeWinner();
    }
}
void scene2()
{
    glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,winw,winh,0);
    gameplay();
    glutSwapBuffers();
    glFlush();
}

void TheButtonCallback()
{
	glutDisplayFunc(scene2);
}


Button MyButton = {(winw/2)-50,(winh/2)-12, 100,25, 0,0, reinterpret_cast<const unsigned char *>( "Start Game" ), TheButtonCallback };





int ButtonClickTest(Button* b,int x,int y)
{
	if( b)
	{

	    if( x > b->x      &&
			x < b->x+b->w &&
			y > b->y      &&
			y < b->y+b->h ) {
				return 1;
		}
	}
	return 0;
}

void ButtonRelease(Button *b,int x,int y)
{
	if(b)
	{

		if( ButtonClickTest(b,TheMouse.xpress,TheMouse.ypress) &&
			ButtonClickTest(b,x,y) )
		{

			if (b->callbackFunction) {
				b->callbackFunction();
			}
		}

		b->state = 0;
	}
}

void ButtonPress(Button *b,int x,int y)
{
	if(b)
	{
		if( ButtonClickTest(b,x,y) )
		{
			b->state = 1;
		}
	}
}

void ButtonPassive(Button *b,int x,int y)
{
	if(b)
	{
		if( ButtonClickTest(b,x,y) )
		{
			if( b->highlighted == 0 ) {
				b->highlighted = 1;
				glutPostRedisplay();
			}
		}
		else


		if( b->highlighted == 1 )
		{
			b->highlighted = 0;
			glutPostRedisplay();
		}
	}
}

void ButtonDraw(Button *b)
{
	int fontx;
	int fonty;

	if(b)
	{
		if (b->highlighted)
			glColor3f(1.0f,0.0f,0.0f);
		else
			glColor3f(0.6f,0.6f,0.6f);

		glBegin(GL_QUADS);
			glVertex2i( b->x     , b->y      );
			glVertex2i( b->x     , b->y+b->h );
			glVertex2i( b->x+b->w, b->y+b->h );
			glVertex2i( b->x+b->w, b->y      );
		glEnd();

		glLineWidth(3);

		if (b->state)
			glColor3f(0.4f,0.4f,0.4f);
		else
			glColor3f(0.8f,0.8f,0.8f);

		glBegin(GL_LINE_STRIP);
			glVertex2i( b->x+b->w, b->y      );
			glVertex2i( b->x     , b->y      );
			glVertex2i( b->x     , b->y+b->h );
		glEnd();

		if (b->state)
			glColor3f(0.8f,0.8f,0.8f);
		else
			glColor3f(0.4f,0.4f,0.4f);

		glBegin(GL_LINE_STRIP);
			glVertex2i( b->x     , b->y+b->h );
			glVertex2i( b->x+b->w, b->y+b->h );
			glVertex2i( b->x+b->w, b->y      );
		glEnd();

		glLineWidth(1);



		fontx = b->x + (b->w - glutBitmapLength(GLUT_BITMAP_HELVETICA_10,b->label)) / 2 ;
		fonty = b->y + (b->h+10)/2;


		if (b->state) {
			fontx+=2;
			fonty+=2;
		}


		if(b->highlighted)
		{
			glColor3f(0,0,0);
			Font(GLUT_BITMAP_HELVETICA_10,b->label,fontx,fonty);
			fontx--;
			fonty--;
		}

		glColor3f(1,1,1);
		Font(GLUT_BITMAP_HELVETICA_10,b->label,fontx,fonty);
	}
}

void Init()
{
	glEnable(GL_LIGHT0);
}

void Draw2D()
{
	ButtonDraw(&MyButton);
}

void Draw()
{

	glClear( GL_COLOR_BUFFER_BIT |
			 GL_DEPTH_BUFFER_BIT );

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,winw,winh,0,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Draw2D();

	glutSwapBuffers();
}


void Resize(int w, int h)
{
	winw = w;
	winh = h;

	glViewport(0,0,w,h);
}

void MouseButton(int button,int state,int x, int y)
{
	TheMouse.x = x;
	TheMouse.y = y;

	if (state == GLUT_DOWN)
	{

		if ( !(TheMouse.lmb || TheMouse.mmb || TheMouse.rmb) ) {
			TheMouse.xpress = x;
			TheMouse.ypress = y;
		}

		switch(button)
		{
		case GLUT_LEFT_BUTTON:
			TheMouse.lmb = 1;
			ButtonPress(&MyButton,x,y);
		case GLUT_MIDDLE_BUTTON:
			TheMouse.mmb = 1;
			break;
		case GLUT_RIGHT_BUTTON:
			TheMouse.rmb = 1;
			break;
		}
	}
	else
	{

		switch(button)
		{
		case GLUT_LEFT_BUTTON:
			TheMouse.lmb = 0;
			ButtonRelease(&MyButton,x,y);
			break;
		case GLUT_MIDDLE_BUTTON:
			TheMouse.mmb = 0;
			break;
		case GLUT_RIGHT_BUTTON:
			TheMouse.rmb = 0;
			break;
		}
	}
	glutPostRedisplay();
}


void MouseMotion(int x, int y)
{
	TheMouse.x = x;
	TheMouse.y = y;
	ButtonPassive(&MyButton,x,y);
	glutPostRedisplay();
}


void MousePassiveMotion(int x, int y)
{
	TheMouse.x = x;
	TheMouse.y = y;
	ButtonPassive(&MyButton,x,y);
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);
	glutInitWindowSize(winw,winh);
	glutInitWindowPosition(0,0);
	glutCreateWindow("RPS");

	glutKeyboardFunc(kb);
	glutDisplayFunc(Draw);
	glutReshapeFunc(Resize);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
	Init();
	glutMainLoop();
}












