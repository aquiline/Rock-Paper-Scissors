#include "Text.h"
#include <GL/glut.h>

void Text::Font(void *font,const unsigned char *text,int x,int y)
{
    glRasterPos2i(x, y);

	while( *text != '\0' )
	{
		glutBitmapCharacter( font, *text );
		++text;
	}
}
