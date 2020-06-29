#ifndef JANTE_H
#define JANTE_H

#include <GL\glut.h>

class Jante
{
    public:
        Jante(float x, float y, float z);
        virtual ~Jante();

        float Getx() { return x; }
        void Setx(float val) { x = val; }
        float Gety() { return y; }
        void Sety(float val) { y = val; }
        float Getz() { return z; }
        void Setz(float val) { z = val; }

        void drawJante();

    protected:

    private:
        float x;
        float y;
        float z;
};

#endif // JANTE_H
