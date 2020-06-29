#ifndef ROUE_H
#define ROUE
#include <GL\glut.h>

#include <math.h>
class Roue
{
    public:
        Roue(float x, float y, GLfloat angle);
        virtual ~Roue();

        float Getx() { return x; }
        void Setx(float val) { x = val; }
        float Gety() { return y; }
        void Sety(float val) { y = val; }
        GLfloat Getangle() { return angle; }
        void Setangle(GLfloat val) { angle = val; }

        void drawWheel();

    protected:

    private:
        float x;
        float y;
        GLfloat angle;
};

#endif // ROUE_H
