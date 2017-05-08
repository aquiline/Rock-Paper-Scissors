#ifndef BUTTON_H
#define BUTTON_H
#include<iostream>
using namespace std;
class Button
{
    int   x;							/* top left x coordinate of the button */
    int   y;							/* top left y coordinate of the button */
    int   w;							/* the width of the button */
    int   h;							/* the height of the button */
    int	  state;						/* the state, 1 if pressed, 0 otherwise */
    int	  highlighted;					/* is the mouse cursor over the control? */
    const unsigned char* label;			/* the text label of the button */

    public:
        typedef void (Button::*method)();
        method callbackFunction;

        void Init(int a,int b,int c,int d,int e,int f,const unsigned char* g,method i){
            x = a;
            y = b;
            w = c;
            h = d;
            state = e;
            highlighted = f;
            label = g;
            callbackFunction = i;
        }
        void call()
        {
            cout<<"Button pressed";
        }
};

#endif // BUTTON_H
