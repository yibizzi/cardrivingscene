#include "Roue.h"
#include <GL\glut.h>

#include <math.h>

Roue::Roue(float x, float y, GLfloat angle)
{
    this->x = x;
    this->y = y;
    this->angle = angle;

}

Roue::~Roue()
{
    //dtor
}

void Roue::drawWheel()
{

    glBegin(GL_LINE_STRIP);
    for(float theta=0; theta<360; theta=theta+40)
    {
        glVertex3f(this->x,0.2,this->y);
        glVertex3f(this->x+(0.08*(cos(((theta+this->angle)*3.14)/180))),0.2+(0.08*(sin(((theta+this->angle)*3.14)/180))),this->y);
    }
    glEnd();




}
