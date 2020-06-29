#include "Arbre.h"

Arbre::Arbre()
{
    //ctor
}

Arbre::~Arbre()
{
    //dtor
}


void Arbre::makeTree()
{

    float angle;
    makeCylinder(height, base);
    glTranslatef(0.0, height, 0.0);
    height -= height*.2;
    base-= base*0.3;
    for(int a= 0; a<3; a++)
    {
        angle = rand()%50+20;
        if(angle >48)
            angle = -(rand()%50+20);
        if (height >1)
        {
            glPushMatrix();
            glRotatef(angle,1,0.0,1);
            makeTree(height,base);
            glPopMatrix();

        }
//else glColor3f(0.0,1.0/a,0.0);glutSolidSphere(.2,10,10); add like fruits...
    }

}
