#ifndef ROUTE_H
#define ROUTE_H

#include <GL\glut.h>

#include <Tree.h>
class Route
{
    public:
        Route();
        virtual ~Route();


        void drawRoad(float xw, int flag1, int wheelflag);


};

#endif // ROUTE_H
