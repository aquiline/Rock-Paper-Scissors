#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <GL/glut.h>

#include <vector>
#include "lodepng.h"
#include <GL/glext.h>

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

struct myImage{
vector <unsigned char> image;
unsigned imageWidth;  // image width and height
unsigned imageHeight;

};
GLuint texname; // The texture Id.

/*Each image is made an item with mtImage structure*/
struct myImage menu;
struct myImage prock;
struct myImage ppaper;
struct myImage pscissor;
struct myImage crock;
struct myImage cpaper;
struct myImage cscissor;
struct myImage ins;
struct myImage win;
struct myImage loss;
struct myImage tie;

void setTexture(vector<unsigned char> img, unsigned winw, unsigned winh)
{
    glBindTexture(GL_TEXTURE_2D, texname);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, winw, winh,
                0, GL_RGBA, GL_UNSIGNED_BYTE, &img[0]);
}

void loadImage(const char* name,int img_id)
{
    int error;
    if(img_id == 0)
    {
        if((error=lodepng::decode(menu.image,menu.imageWidth,menu.imageHeight,name)))
        {
            cout<<name<<":"<<lodepng_error_text(error)<<endl;
            exit(1);
        }
    }
    else if(img_id == 1)
    {
        if((error=lodepng::decode(prock.image,prock.imageWidth,prock.imageHeight,name)))
        {
            cout<<name<<":"<<lodepng_error_text(error)<<endl;
            exit(1);
        }
    }

    else if(img_id == 2)
    {
         if((error=lodepng::decode(ppaper.image,ppaper.imageWidth,ppaper.imageHeight,name)))
        {
            cout<<name<<":"<<lodepng_error_text(error)<<endl;
            exit(1);
        }
    }
    else if(img_id == 3)
    {
        if((error=lodepng::decode(pscissor.image,pscissor.imageWidth,pscissor.imageHeight,name)))
        {
            cout<<name<<":"<<lodepng_error_text(error)<<endl;
            exit(1);
        }
    }
     else if(img_id == 4)
    {
        if((error=lodepng::decode(crock.image,crock.imageWidth,crock.imageHeight,name)))
        {
            cout<<name<<":"<<lodepng_error_text(error)<<endl;
            exit(1);
        }
    }

    else if(img_id == 5)
    {
         if((error=lodepng::decode(cpaper.image,cpaper.imageWidth,cpaper.imageHeight,name)))
        {
            cout<<name<<":"<<lodepng_error_text(error)<<endl;
            exit(1);
        }
    }
    else if(img_id == 6)
    {
        if((error=lodepng::decode(cscissor.image,cscissor.imageWidth,cscissor.imageHeight,name)))
        {
            cout<<name<<":"<<lodepng_error_text(error)<<endl;
            exit(1);
        }
    }
    else if(img_id == 7)
    {
        if((error=lodepng::decode(ins.image,ins.imageWidth,ins.imageHeight,name)))
        {
            cout<<name<<":"<<lodepng_error_text(error)<<endl;
            exit(1);
        }
    }
    else if(img_id == 8)
    {
        if((error=lodepng::decode(win.image,win.imageWidth,win.imageHeight,name)))
        {
            cout<<name<<":"<<lodepng_error_text(error)<<endl;
            exit(1);
        }
    }
    else if(img_id == 9)
    {
        if((error=lodepng::decode(loss.image,loss.imageWidth,loss.imageHeight,name)))
        {
            cout<<name<<":"<<lodepng_error_text(error)<<endl;
            exit(1);
        }
    }
    else if(img_id == 10)
    {
        if((error=lodepng::decode(tie.image,tie.imageWidth,tie.imageHeight,name)))
        {
            cout<<name<<":"<<lodepng_error_text(error)<<endl;
            exit(1);
        }
    }


}
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
Button StartButton = {(winw / 2) - 50,(winh / 2) - 12+130, 100,25, 0,0,
                    reinterpret_cast<const unsigned char *>("Start Game"), TheButtonCallback };
Button InsButton = {(winw / 2) -50,(winh / 2) + 24+130, 100,25, 0,0,
                    reinterpret_cast<const unsigned char *>("Instructions"), TheButtonCallback1 };
Button ExitButton = {(winw / 2) - 50,(winh / 2) + 60+130, 100,25, 0,0,
                    reinterpret_cast<const unsigned char *>("Exit"), TheButtonCallback2 };
Button BackButton = { winw  - 650,winh  - 80, 100,25, 0,0,
                    reinterpret_cast<const unsigned char *>("<-Back"), TheButtonCallback3 };

/****** The following functions define all scenes in the game and its respective computations ******/

void ButtonDraw(Button *b) // Defined here because will be used in every scene.
{
	int fontx;
	int fonty;

	if (b)
	{
		if (b->highlighted)
			glColor3f(1.00, 0.43, 0.00);

		else
			glColor3f(0.56, 0.64, 0.68);


		glBegin(GL_QUADS);
		glVertex2i(b->x, b->y);
		glVertex2i(b->x, b->y + b->h);
		glVertex2i(b->x + b->w, b->y + b->h);
		glVertex2i(b->x + b->w, b->y);
		glEnd();

		glLineWidth(3);

		if (b->state)
			glColor3f(0.47, 0.56, 0.61);
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
            glColor3f(0.47, 0.56, 0.61);

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

void MenuBackground()
{
    glEnable(GL_TEXTURE_2D);
    setTexture(menu.image,menu.imageWidth,menu.imageHeight);
    glPushMatrix();
    glBegin(GL_POLYGON);
        glTexCoord2d(0,0);  glVertex2f(0,0);
        glTexCoord2d(1,0);  glVertex2f(winw,0);
        glTexCoord2d(1,1);  glVertex2f(winw,winh);
        glTexCoord2d(0,1);  glVertex2f(0,winh);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glFlush();
}
void MenuScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, winw, winh, 0);
    MenuBackground();
	ButtonDraw(&StartButton);
	ButtonDraw(&InsButton);
	ButtonDraw(&ExitButton);

	Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("ROCK-----PAPER-----SCISSOR"), 410, 100);

    Font(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char *>("RANJITH D"), 100, 570);
    Font(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char *>("USN : 1MV14CS084"), 100, 600);

	Font(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char *>("PRAVEEN KUMAR G"), 900, 570);
	Font(GLUT_BITMAP_HELVETICA_18, reinterpret_cast<const unsigned char *>("USN : 1MV14CS074"), 900, 600);

	glutSwapBuffers();
	glFlush();
}

float x0=200,y0=250,x1=514,y1=485; ////Co-Ordinate position to draw player's choice.
float pdx=0,pdy=0;//The variable used for the transforming animation.

/* The following functions draw textures on screen to display pictures that are loaded already.*/
void RockScenePlayer()
{
    glEnable(GL_TEXTURE_2D);
    setTexture(prock.image,prock.imageWidth,prock.imageHeight);
    glPushMatrix();
    glTranslatef(pdx,pdy,0);

    glBegin(GL_POLYGON);
        glTexCoord2d(0,0);  glVertex2f(x0,y0);
        glTexCoord2d(1,0);  glVertex2f(x1,y0);
        glTexCoord2d(1,1);  glVertex2f(x1,y1);
        glTexCoord2d(0,1);  glVertex2f(x0,y1);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glFlush();
}
void PaperScenePlayer()
{
    glEnable(GL_TEXTURE_2D);
    setTexture(ppaper.image,ppaper.imageWidth,ppaper.imageHeight);
    glPushMatrix();
    glTranslatef(pdx,pdy,0);

    glBegin(GL_POLYGON);
        glTexCoord2d(0,0);  glVertex2f(x0,y0);
        glTexCoord2d(1,0);  glVertex2f(x1,y0);
        glTexCoord2d(1,1);  glVertex2f(x1,y1);
        glTexCoord2d(0,1);  glVertex2f(x0,y1);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glFlush();
}
void ScissorScenePlayer()
{
    glEnable(GL_TEXTURE_2D);
    setTexture(pscissor.image,pscissor.imageWidth,pscissor.imageHeight);
    glPushMatrix();
    glTranslatef(pdx,pdy,0);

    glBegin(GL_POLYGON);
        glTexCoord2d(0,0);  glVertex2f(x0,y0);
        glTexCoord2d(1,0);  glVertex2f(x1,y0);
        glTexCoord2d(1,1);  glVertex2f(x1,y1);
        glTexCoord2d(0,1);  glVertex2f(x0,y1);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glFlush();
}

float xc0=700,yc0=250,xc1=1014,yc1=485; //Co-Ordinate position to draw cpu's choice.
float cdx=0,cdy=0;

void RockSceneCpu()
{
    glEnable(GL_TEXTURE_2D);
    setTexture(crock.image,crock.imageWidth,crock.imageHeight);
    glPushMatrix();
    glTranslatef(cdx,cdy,0);

    glBegin(GL_POLYGON);
        glTexCoord2d(0,0);  glVertex2f(xc0,yc0);
        glTexCoord2d(1,0);  glVertex2f(xc1,yc0);
        glTexCoord2d(1,1);  glVertex2f(xc1,yc1);
        glTexCoord2d(0,1);  glVertex2f(xc0,yc1);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glFlush();
}
void PaperSceneCpu()
{
    glEnable(GL_TEXTURE_2D);
    setTexture(cpaper.image,cpaper.imageWidth,cpaper.imageHeight);
    glPushMatrix();
    glTranslatef(cdx,cdy,0);

    glBegin(GL_POLYGON);
         glTexCoord2d(0,0);  glVertex2f(xc0,yc0);
        glTexCoord2d(1,0);  glVertex2f(xc1,yc0);
        glTexCoord2d(1,1);  glVertex2f(xc1,yc1);
        glTexCoord2d(0,1);  glVertex2f(xc0,yc1);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glFlush();
}
void ScissorSceneCpu()
{
    glEnable(GL_TEXTURE_2D);
    setTexture(cscissor.image,cscissor.imageWidth,cscissor.imageHeight);
    glPushMatrix();
    glTranslatef(cdx,cdy,0);

    glBegin(GL_POLYGON);
        glTexCoord2d(0,0);  glVertex2f(xc0,yc0);
        glTexCoord2d(1,0);  glVertex2f(xc1,yc0);
        glTexCoord2d(1,1);  glVertex2f(xc1,yc1);
        glTexCoord2d(0,1);  glVertex2f(xc0,yc1);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glFlush();
}
void youWin()
{
    glEnable(GL_TEXTURE_2D);
    setTexture(win.image,win.imageWidth,win.imageHeight);
    glPushMatrix();

    glBegin(GL_POLYGON);
        glTexCoord2d(0,0);  glVertex2f(140,250);
        glTexCoord2d(1,0);  glVertex2f(440,250);
        glTexCoord2d(1,1);  glVertex2f(440,550);
        glTexCoord2d(0,1);  glVertex2f(140,550);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glFlush();
}
void youLost()
{
    glEnable(GL_TEXTURE_2D);
    setTexture(loss.image,loss.imageWidth,loss.imageHeight);
    glPushMatrix();

    glBegin(GL_POLYGON);
        glTexCoord2d(0,0);  glVertex2f(150,250);
        glTexCoord2d(1,0);  glVertex2f(450,250);
        glTexCoord2d(1,1);  glVertex2f(450,550);
        glTexCoord2d(0,1);  glVertex2f(150,550);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glFlush();
}
void tied()
{
    glEnable(GL_TEXTURE_2D);
    setTexture(tie.image,tie.imageWidth,tie.imageHeight);
    glPushMatrix();

    glBegin(GL_POLYGON);
        glTexCoord2d(0,0);  glVertex2f(150,250);
        glTexCoord2d(1,0);  glVertex2f(450,250);
        glTexCoord2d(1,1);  glVertex2f(450,550);
        glTexCoord2d(0,1);  glVertex2f(150,550);
    glEnd();
     glBegin(GL_POLYGON);
        glTexCoord2d(0,0);  glVertex2f(800,250);
        glTexCoord2d(1,0);  glVertex2f(1100,250);
        glTexCoord2d(1,1);  glVertex2f(1100,550);
        glTexCoord2d(0,1);  glVertex2f(800,550);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glFlush();
}
int userChoice = 0;
int cpuChoice = 0;
int same = 0; // This variable keeps the screen from Unwanted Redisplays
int ipScore = 0;
int icScore = 0;
char pScore[10];
char cScore[10];

void specialKb(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT  :  userChoice = 1;same = 0;pdx= 0;cdx = 0; glutPostRedisplay(); break;
	case GLUT_KEY_DOWN  :  userChoice = 2;same = 0;pdx= 0;cdx = 0;  glutPostRedisplay(); break;
	case GLUT_KEY_RIGHT :  userChoice = 3;same = 0;pdx= 0;cdx = 0;  glutPostRedisplay(); break;
	}
}
void playerDisplay()
{
	if (userChoice == 1)
	{
		RockScenePlayer();
	}
	else if (userChoice == 2)
	{
		PaperScenePlayer();
	}
	else if (userChoice == 3)
	{
		ScissorScenePlayer();
	}
}
void cpuDisplay()
{
	if (cpuChoice == 1)
	{
		RockSceneCpu();
	}
	else if (cpuChoice == 2)
	{
		PaperSceneCpu();
	}
	else if (cpuChoice == 3)
	{
		ScissorSceneCpu();
	}
}
void computeWinner()
{
	if ((cpuChoice == 1 && userChoice == 1) || (cpuChoice == 2 && userChoice == 2) || (cpuChoice == 3 && userChoice == 3))
	{
	    tied();
		Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("Tied (-_-)"), 550, 515);
		Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("Press any of the Choice to try Again"),440, 550);

        Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>(&pScore), 300, 600);
        Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>(&cScore), 950, 600);
	}
	else if ((cpuChoice == 3 && userChoice == 1) || (cpuChoice == 1 && userChoice == 2) || (cpuChoice == 2 && userChoice == 3))
	{
		youWin();
		Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("Press any of the Choice to try Again"), 440, 550);


        Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>(&pScore), 300, 600);
        Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>(&cScore), 950, 600);
	}
	else if ((cpuChoice == 1 && userChoice == 3) || (cpuChoice == 2 && userChoice == 1) || (cpuChoice == 3 && userChoice == 2))
	{
		youLost();
        Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("Press any of the Choice to try Again"), 440, 550);


        Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>(&pScore), 300, 600);
        Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>(&cScore), 950, 600);
	}
}
void score()
{
    if ((cpuChoice == 3 && userChoice == 1) || (cpuChoice == 1 && userChoice == 2) || (cpuChoice == 2 && userChoice == 3))
	{
        ipScore++;
	}
	else if ((cpuChoice == 1 && userChoice == 3) || (cpuChoice == 2 && userChoice == 1) || (cpuChoice == 3 && userChoice == 2))
	{
	    icScore++;
	}
	sprintf(pScore,"%d",ipScore);
	sprintf(cScore,"%d",icScore);
}
void gameplay()
{
	Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("Enter Your Choice"), 520, 100);
	Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("Player"), 300, 200);
	Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("CPU"), 800, 200);
	Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("PlayerScore :"), 140, 600);
	Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>("CpuScore :"), 800, 600);
	Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>(&pScore), 300, 600);
    Font(GLUT_BITMAP_TIMES_ROMAN_24, reinterpret_cast<const unsigned char *>(&cScore), 950, 600);

    if(!same)// New values only for Fresh Input.
    {
        cpuChoice = rand() % 3 + 1;
        score();
    }

    same = 1; // Display for one User Input case.

    if ((cpuChoice == 1 && userChoice == 1) || (cpuChoice == 2 && userChoice == 2) || (cpuChoice == 3 && userChoice == 3))
	{
	    playerDisplay();
        cpuDisplay();
	}
	else if ((cpuChoice == 3 && userChoice == 1) || (cpuChoice == 1 && userChoice == 2) || (cpuChoice == 2 && userChoice == 3))
	{
        cpuDisplay();
        playerDisplay();
	}
	else if ((cpuChoice == 1 && userChoice == 3) || (cpuChoice == 2 && userChoice == 1) || (cpuChoice == 3 && userChoice == 2))
	{
	    playerDisplay();
	    cpuDisplay();
	}

    if(pdx < 250)
    {
        pdx += .5;
        cdx -= .5;
    }
    if(pdx == 250)
        computeWinner();
}

void GameScene()
{
	glClearColor(0.26, 0.65, 0.96, 1.0);
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
    glEnable(GL_TEXTURE_2D);
    setTexture(ins.image,ins.imageWidth,ins.imageHeight);
    glPushMatrix();
    glBegin(GL_POLYGON);
        glTexCoord2d(0,0);  glVertex2f(0,0);
        glTexCoord2d(1,0);  glVertex2f(winw,0);
        glTexCoord2d(1,1);  glVertex2f(winw,winh);
        glTexCoord2d(0,1);  glVertex2f(0,winh);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    glFlush();

}
void InstructionScene()
{
	glClearColor(0.26, 0.65, 0.96, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, winw, winh, 0);
	instructions();
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
        ipScore = 0;
        icScore = 0;
        sprintf(pScore,"%d",ipScore);
        sprintf(cScore,"%d",icScore);

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
	glutReshapeWindow(winw,winh);
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
			if(select == 1)ButtonPress(&StartButton, x, y);
			if(select == 1)ButtonPress(&InsButton, x, y);
			if(select == 1)ButtonPress(&ExitButton, x, y);
			ButtonPress(&BackButton, x, y);
		}
	}
	else
	{

		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			TheMouse.lmb = 0;
			if(select == 1)ButtonRelease(&StartButton, x, y);
			if(select == 1)ButtonRelease(&InsButton, x, y);
			if(select == 1)ButtonRelease(&ExitButton, x, y);
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
	if(select == 1)ButtonPassive(&StartButton, x, y);
	if(select == 1)ButtonPassive(&InsButton, x, y);
	if(select == 1)ButtonPassive(&ExitButton, x, y);
	ButtonPassive(&BackButton, x, y);
	glutPostRedisplay();
}


void MousePassiveMotion(int x, int y)
{
	TheMouse.x = x;
	TheMouse.y = y;
	if(select == 1)ButtonPassive(&StartButton, x, y);
	if(select == 1)ButtonPassive(&InsButton, x, y);
	if(select == 1)ButtonPassive(&ExitButton, x, y);
	ButtonPassive(&BackButton, x, y);
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(winw, winh);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("ROCK-PAPER-SCISSOR");

    /*loadImage("main.png",0);
    loadImage("prock.png",1);
    loadImage("ppaper.png",2);
    loadImage("pscissor.png",3);
    loadImage("crock.png",4);
    loadImage("cpaper.png",5);
    loadImage("cscissor.png",6);
    loadImage("ins.png",7);
    loadImage("win.png",8);
    loadImage("loss.png",9);
    loadImage("tie.png",10);*/
    loadImage("res/main.png",0);
    loadImage("res/prock.png",1);
    loadImage("res/ppaper.png",2);
    loadImage("res/pscissor.png",3);
    loadImage("res/crock.png",4);
    loadImage("res/cpaper.png",5);
    loadImage("res/cscissor.png",6);
    loadImage("res/ins.png",7);
    loadImage("res/win.png",8);
    loadImage("res/loss.png",9);
    loadImage("res/tie.png",10);

	glGenTextures(1, &texname);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

	glutReshapeFunc(Resize);

	glutSpecialFunc(specialKb);

	glutDisplayFunc(display);

	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);

	glutMainLoop();
}
