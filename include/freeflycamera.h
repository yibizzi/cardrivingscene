#ifndef FREEFLYCAMERA_H
#define FREEFLYCAMERA_H

#include "Vector3d.h"
#include <GL\glut.h>
#include <map>
#include <string>

class FreeFlyCamera
{
public:
    FreeFlyCamera(const Vector3D & position = Vector3D(0,0,0));


    virtual void OnKeyboard(GLubyte key); //key is pressed
    virtual void OffKeyboard(GLubyte key); // key is released

    virtual void animate(unsigned int timestep);

    virtual void setSpeed(double speed);
    virtual void setSensivity(double sensivity);

    virtual void setPosition(const Vector3D & position);

    virtual void look();

   // virtual ~FreeFlyCamera();
protected:
    double _speed;
    double _sensivity;

    //vertical motion stuffs
    unsigned int _timeBeforeStoppingVerticalMotion;

    bool _verticalMotionActive;
    int _verticalMotionDirection;

    typedef std::map<GLubyte, bool> KeyStates;
    KeyStates _keystates;
    typedef std::map<std::string,GLubyte> KeyConf;
    KeyConf _keyconf;

    Vector3D _position;
    Vector3D _target;
    Vector3D _forward;
    Vector3D _left;
    double _theta;
    double _phi;

    void VectorsFromAngles();
    //void Init();
};

#endif //FREEFLYCAMERA_H
