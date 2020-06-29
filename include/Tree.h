#ifndef TREE_H
#define TREE_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <fstream>
#include <iostream>

using namespace std;

class Tree
{
    public:
        Tree(double height = 1.0, double width = 0.2, int levels = 3);
        void setTexture(GLuint brack, GLuint top);
        double getHeight(GLfloat x, GLfloat z);
        void draw();
        void setPosition(GLfloat x, GLfloat y, GLfloat z);

    private:
        GLuint brackTexture, topTexture;
        GLfloat rootX, rootY, rootZ;
        GLfloat height, width, levels;
};

#endif // TREE_H
