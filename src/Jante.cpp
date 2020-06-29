#include "Jante.h"


Jante::Jante(float x, float y, float z)
{

    this->x = x;
    this->y = y;
    this->z = z;

}

Jante::~Jante()
{
    //dtor
}

void Jante::drawJante()
{
    glColor3f(0,0,0);
    glTranslatef(this->x,this->y,this->z);
    glutSolidTorus(0.025,0.07,10,25);

}
