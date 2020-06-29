#include "Route.h"

Route::Route()
{
    //ctor
}

Route::~Route()
{
    //dtor
}

void Route::drawRoad(float xw, int flag1, int wheelflag)
{

//*****************************road and surrounding development***********************************
    if(flag1)
    {
        glBegin(GL_QUADS);
        glPushMatrix();
        glTranslatef(xw,0,0);
        glColor3f(0,1,0);
        glVertex3f(-100,0.1,-100);
        glVertex3f(-100,0.1,0);         //a green surroundings
        glVertex3f(100,0.1,0);
        glVertex3f(100,0.1,-100);

        glColor3f(0.7,0.7,0.7);
        glVertex3f(-100,0.1,0);
        glVertex3f(-100,0.1,0.45);         //a long road
        glVertex3f(100,0.1,0.45);
        glVertex3f(100,0.1,0);

        glColor3f(1.0,0.75,0.0);
        glVertex3f(-100,0.1,0.45);       //a median
        glVertex3f(-100,0.1,0.55);
        glVertex3f(100,0.1,0.55);
        glVertex3f(100,0.1,0.45);

        glColor3f(0.7,0.7,0.7);
        glVertex3f(-100,0.1,0.55);
        glVertex3f(-100,0.1,1);         //a long road
        glVertex3f(100,0.1,1);
        glVertex3f(100,0.1,0.55);

        glColor3f(0.33,0.48,0.27);
        glVertex3f(-100,0.1,1);
        glVertex3f(-100,0.1,100);         //a green surroundings
        glVertex3f(100,0.1,100);
        glVertex3f(100,0.1,1);
        glPopMatrix();
        glEnd();
    }


    //Si on active le choix: wheel effect
    if(wheelflag)
    {
        glPushMatrix();
        glTranslatef(xw,0,0);
        glColor3f(0.5,.2,0.3);
        glBegin(GL_QUADS);
        // 1ere ligne de barrière s
        for(float i=0; i<200; i+=0.2)
        {
            glVertex3f(-100+i,0,1);
            glVertex3f(-99.9+i,0,1);
            glVertex3f(-99.9+i,0.2,1);
            glVertex3f(-100+i,0.2,1);

            i+=0.5;
        }

        // 2eme ligne de barrière s

        for(float i=0; i<200; i+=0.2)
        {
            glVertex3f(-100+i,0,0);
            glVertex3f(-99.9+i,0,0);
            glVertex3f(-99.9+i,0.2,0);
            glVertex3f(-100+i,0.2,0);
            i+=0.5;
        }
        glEnd();
        glPopMatrix();

        //DESSIN DES ARBRES
        for(int j =0; j<50; j++)
        {

            Tree arbre1 = Tree();
            arbre1.setPosition(xw-100+j*5,0,-0.5);
            arbre1.draw();

            Tree arbre2 = Tree();
            arbre2.setPosition(xw-120+j*5, 0.05, -4);
            arbre2.draw();
        }

        for(int j =0; j<50; j++)
        {

            Tree arbre1 = Tree();
            arbre1.setPosition(xw-100+j*5, 0, 2);
            arbre1.draw();

            Tree arbre2 = Tree();
            arbre2.setPosition(xw-120+j*5, -0.05, 5);
            arbre2.draw();
        }


    }


}
