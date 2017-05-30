#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <GL/glut.h>

using namespace std;

int select = 1; // Scene selection Variable. This is our GOD (^_^)

/******* Mouse data structure ******/
struct Mouse
{
	int x;		/*	the x coordinate of the mouse cursor	*/
	int y;		/*	the y coordinate of the mouse cursor	*/
	int lmb;	/*	is the left button pressed?		*/

	int xpress; /*	stores the x-coordinate of when the first button press occurred	*/
	int ypress; /*	stores the y-coordinate of when the first button press occurred	*/
};

typedef struct Mouse Mouse; //Typecasting it for "PURPOSES".

Mouse TheMouse = { 0,0,0,0,0 }; // Creating and Initializing a mouse variable again for "PURPOSES".

int winw = 1200;
int winh = 650;


typedef void(*ButtonCallback)(); //Typecasting our button click function .

/******* Button data structure ******/
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
typedef struct Button Button; // Deal with this.


/****** ThE fUnCtIoN wItHoUt WhIcH tExT wOnT't WoRk******/
void Font(void *font, const unsigned char *text, int x, int y)
{
	glRasterPos2i(x, y);

	while (*text != '\0')
	{
		glutBitmapCharacter(font, *text);
		++text;
	}
}

/******* Following Four functions decide what to do on button clicks , for all the buttons in the game ******/
void TheButtonCallback()
{
	select = 2;
}

void TheButtonCallback1()
{
	select = 3;
}

void TheButtonCallback2()
{
	exit(0);
}

void TheButtonCallback3()
{
	select = 1;
}

/****** Declaring all the buttons in our game ******/
Button StartButton = {(winw / 2) - 50,(winh / 2) - 12, 100,25, 0,0, reinterpret_cast<const unsigned char *>("START GAME"), TheButtonCallback };
Button InsButton = {(winw / 2) -50,(winh / 2) + 24, 100,25, 0,0, reinterpret_cast<const unsigned char *>("INSTRUCTION"), TheButtonCallback1 };
Button ExitButton = {(winw / 2) - 50,(winh / 2) + 60, 100,25, 0,0, reinterpret_cast<const unsigned char *>("EXIT"), TheButtonCallback2 };
Button BackButton = { winw  - 650,winh  - 80, 100,25, 0,0, reinterpret_cast<const unsigned char *>("<-BACK"), TheButtonCallback3 };

/****** The following functions define all scenes in the game and its respective computations ******/

void ButtonDraw(Button *b) // Defined here because will be used in every scene.
{
	int fontx;
	int fonty;

	if (b)
	{
		if (b->highlighted)
			glColor3f(1.0f, 0.0f, 0.0f);
		else
			glColor3f(0.6f, 0.6f, 0.6f);

		glBegin(GL_QUADS);
		glVertex2i(b->x, b->y);
		glVertex2i(b->x, b->y + b->h);
		glVertex2i(b->x + b->w, b->y + b->h);
		glVertex2i(b->x + b->w, b->y);
		glEnd();

		glLineWidth(3);

		if (b->state)
			glColor3f(0.4f, 0.4f, 0.4f);
		else
			glColor3f(0.8f, 0.8f, 0.8f);

		glBegin(GL_LINE_STRIP);
		glVertex2i(b->x + b->w, b->y);
		glVertex2i(b->x, b->y);
		glVertex2i(b->x, b->y + b->h);
		glEnd();

		if (b->state)
			glColor3f(0.8f, 0.8f, 0.8f);
		else
			glColor3f(0.4f, 0.4f, 0.4f);

		glBegin(GL_LINE_STRIP);
		glVertex2i(b->x, b->y + b->h);
		glVertex2i(b->x + b->w, b->y + b->h);
		glVertex2i(b->x + b->w, b->y);
		glEnd();

		glLineWidth(1);



		fontx = b->x + (b->w - glutBitmapLength(GLUT_BITMAP_HELVETICA_10, b->label)) / 2;
		fonty = b->y + (b->h + 10) / 2;


		if (b->state) {
			fontx += 2;
			fonty += 2;
		}


		if (b->highlighted)
		{
			glColor3f(0, 0, 0);
			Font(GLUT_BITMAP_HELVETICA_10, b->label, fontx, fonty);
			fontx--;
			fonty--;
		}

		glColor3f(1, 1, 1);
		Font(GLUT_BITMAP_HELVETICA_10, b->label, fontx, fonty);
	}
}

void MenuScene()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, winw, winh, 0);

	ButtonDraw(&StartButton);
	ButtonDraw(&InsButton);
	ButtonDraw(&ExitButton);

	Font(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char *>("ROCK-----PAPER-----SCISSOR"), 450, 100);
	Font(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char *>("PROJECT BY "), 900, 580);
	Font(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char *>("RANJITH D"), 950, 600);
	Font(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char *>("PRAVEEN KUMAR G"), 950, 620);

	glutSwapBuffers();
	glFlush();
}


int userChoice = 0;
int cpuChoice = 0;
int same = 0; // This variable keeps the screen from Unwanted Redisplays

void kb(unsigned char key, int x, int y)
{
	switch (key) {
	case 'z':  userChoice = 1;same = 0; glutPostRedisplay(); break;
	case 'x':  userChoice = 2;same = 0; glutPostRedisplay(); break;
	case 'c':  userChoice = 3;same = 0; glutPostRedisplay(); break;
	}
}

void cpuDisplay()
{
	if (cpuChoice == 1)
	{
		Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("Rock"), 900, 300);
		cout << cpuChoice;
	}
	else if (cpuChoice == 2)
	{
		Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("Paper"), 900, 300);
		cout << cpuChoice;
	}
	else if (cpuChoice == 3)
	{
		Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("Scissor"), 900, 300);
		cout << cpuChoice;
	}
}
void computeWinner()
{
	if ((cpuChoice == 1 && userChoice == 1) || (cpuChoice == 2 && userChoice == 2) || (cpuChoice == 3 && userChoice == 3))
	{
		Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("TIED"), 570, 500);
		cout << cpuChoice;
	}
	else if ((cpuChoice == 3 && userChoice == 1) || (cpuChoice == 1 && userChoice == 2) || (cpuChoice == 2 && userChoice == 3))
	{
		Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("Player Wins"), 550, 500);
		cout << cpuChoice;
	}
	else if ((cpuChoice == 1 && userChoice == 3) || (cpuChoice == 2 && userChoice == 1) || (cpuChoice == 3 && userChoice == 2))
	{
		Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("CPU Wins"), 560, 500);
		cout << cpuChoice;
	}
}
void gameplay()
{
	Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("Enter Your Choice"), 520, 100);
	Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("Player"), 200, 200);
	Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("CPU"), 900, 200);

    if(!same)cpuChoice = rand() % 3 + 1; // New values only for Fresh Input.

    same = 1; // Display for one User Input case.
    if (userChoice == 1)
    {
        //cpuChoice = rand() % 3 + 1;
        Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("Rock"), 200, 300);
        cpuDisplay();
        computeWinner();
    }
    else if (userChoice == 2)
    {
        //cpuChoice = rand() % 3 + 1;
        Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("Paper"), 200, 300);
        cpuDisplay();
        computeWinner();
    }
    else if (userChoice == 3)
    {
        //cpuChoice = rand() % 3 + 1;
        Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("Scissor"), 200, 300);
        cpuDisplay();
        computeWinner();
    }


}

void GameScene()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, winw, winh, 0);
	ButtonDraw(&BackButton);
	gameplay();
	glutSwapBuffers();
	glFlush();
}

void instructions()
{
	Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("WELCOME"), 520, 100);
	Font(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char *>("THERE ARE THREE ENTITIES IN THIS GAME"), 100, 300);
	Font(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char *>("i.e 'ROCK', 'PAPER' AND 'SCISSOR' "), 100, 320);
	Font(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char *>("THE RULES ARE"), 100, 340);
	Font(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char *>("ROCK BEATS SCISSOR"), 200, 360);
	Font(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char *>("PAPER BEATS ROCK"), 200, 380);
	Font(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char *>("SCISSOR BEATS PAPER"), 200, 400);
	Font(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char *>("THE PLAYER HAS TO CHOOSE BETWEEN ROCK,PAPER AND SCISSOR"), 100, 420);
	Font(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char *>("PRESS Z FOR ROCK"), 200, 440);
	Font(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char *>("PRESS X FOR PAPER"), 200, 460);
	Font(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char *>("PRESS C FOR SCISSOR"), 200, 480);
	Font(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char *>("DEPENDING ON WHAT CPU CHOOSES THE RESULT WILL BE REVEALED"), 100, 500);

}
void InstructionScene()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, winw, winh, 0);
	instructions();
	ButtonDraw(&BackButton);
	glutSwapBuffers();
	glFlush();
}
void PlayAgainScene()
{
    glClearColor(1.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, winw, winh, 0);
	//instructions();
	ButtonDraw(&BackButton);
	glutSwapBuffers();
	glFlush();
}
/****** Main Display Function ******/
void display()
{
	if(select == 1)
	{
        userChoice = 0; // Refreshing Inputs
        cpuChoice = 0;  //
		MenuScene();
	}
	if(select == 2)
	{
		GameScene();
	}
	if(select == 3)
	{
		InstructionScene();
	}
	if(select == 4)
    {
        PlayAgainScene();
    }
}

/*******Mouse and Button Animations******/

int ButtonClickTest(Button* b, int x, int y)
{
	if (b)
	{

		if (x > b->x      &&
			x < b->x + b->w &&
			y > b->y      &&
			y < b->y + b->h) {
			return 1;
		}
	}
	return 0;
}
void ButtonPassive(Button *b, int x, int y)
{
	if (b)
	{
		if (ButtonClickTest(b, x, y))
		{
			if (b->highlighted == 0) {
				b->highlighted = 1;
				glutPostRedisplay();
			}
		}
		else


			if (b->highlighted == 1)
			{
				b->highlighted = 0;
				glutPostRedisplay();
			}
	}
}

void ButtonRelease(Button *b, int x, int y)
{
	if (b)
	{

		if (ButtonClickTest(b, TheMouse.xpress, TheMouse.ypress) &&
			ButtonClickTest(b, x, y))
		{

			if (b->callbackFunction) {
				b->callbackFunction();
			}
		}

		b->state = 0;
	}
}

void ButtonPress(Button *b, int x, int y)
{
	if (b)
	{
		if (ButtonClickTest(b, x, y))
		{
			b->state = 1;
		}
	}
}

void Resize(int w, int h)
{
	winw = w;
	winh = h;
	glViewport(0, 0, w, h);
}

void MouseButton(int button, int state, int x, int y)
{
	TheMouse.x = x;
	TheMouse.y = y;

	if (state == GLUT_DOWN)
	{

		if (!(TheMouse.lmb)) {
			TheMouse.xpress = x;
			TheMouse.ypress = y;
		}

		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			TheMouse.lmb = 1;
			ButtonPress(&StartButton, x, y);
			ButtonPress(&InsButton, x, y);
			ButtonPress(&ExitButton, x, y);
			ButtonPress(&BackButton, x, y);
		}
	}
	else
	{

		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			TheMouse.lmb = 0;
			ButtonRelease(&StartButton, x, y);
			ButtonRelease(&InsButton, x, y);
			ButtonRelease(&ExitButton, x, y);
			ButtonRelease(&BackButton, x, y);
			break;
		}
	}
	glutPostRedisplay();
}


void MouseMotion(int x, int y)
{
	TheMouse.x = x;
	TheMouse.y = y;
	ButtonPassive(&StartButton, x, y);
	ButtonPassive(&InsButton, x, y);
	ButtonPassive(&ExitButton, x, y);
	ButtonPassive(&BackButton, x, y);
	glutPostRedisplay();
}


void MousePassiveMotion(int x, int y)
{
	TheMouse.x = x;
	TheMouse.y = y;
	ButtonPassive(&StartButton, x, y);
	ButtonPassive(&InsButton, x, y);
	ButtonPassive(&ExitButton, x, y);
	ButtonPassive(&BackButton, x, y);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(winw, winh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("ROCK-PAPER-SCISSOR");
	glutReshapeFunc(Resize);

	glutKeyboardFunc(kb);

	glutDisplayFunc(display);

	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);

	glutMainLoop();
}
