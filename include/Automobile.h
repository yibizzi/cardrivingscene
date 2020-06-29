#ifndef AUTOMOBILE_H
#define AUTOMOBILE_H

#include <GL\glut.h>

class Automobile
{
    public:
        Automobile(GLUquadricObj* t);
        virtual ~Automobile();



        GLUquadricObj* Gett() { return t; }
        void Sett(GLUquadricObj* val) { t = val; }

        GLUquadricObj *t;


        void drawAutomobile(GLfloat r, GLfloat g, GLfloat b, GLfloat angle_roue);
};

#endif // AUTOMOBILE_H
