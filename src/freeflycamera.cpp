#include "freeflycamera.h"

#include <cmath>

FreeFlyCamera::FreeFlyCamera(const Vector3D & position)
{
    _position = position;
    _phi = 0;
    _theta = 0;
    VectorsFromAngles();

    _speed = 0.01;
    _sensivity = 0.2;
    _verticalMotionActive = false;

    _keyconf["camera_forward"] = GLUT_KEY_UP;
    _keyconf["camera_back"] = GLUT_KEY_DOWN;

    _keyconf["rotate_right"] = GLUT_KEY_RIGHT;
    _keyconf["rotate_left"] = GLUT_KEY_LEFT;

    _keyconf["camera_up"] = '8';
    _keyconf["camera_down"] = '2';
    _keyconf["camera_right"] = '8';
    _keyconf["camera_left"] = '2';

    _keyconf["boost"] = GLUT_ACTIVE_SHIFT;

    _keystates[_keyconf["camera_forward"]] = false;
    _keystates[_keyconf["camera_back"]] = false;

    _keystates[_keyconf["rotate_right"]] = false;
    _keystates[_keyconf["rotate_left"]] = false;

    _keystates[_keyconf["camera_up"]] = false;
    _keystates[_keyconf["camera_down"]] = false;
    _keystates[_keyconf["camera_right"]] = false;
    _keystates[_keyconf["camera_left"]] = false;

    _keystates[_keyconf["boost"]] = false;

}



void FreeFlyCamera::OnKeyboard(GLubyte key)
{
    for (KeyStates::iterator it = _keystates.begin(); it != _keystates.end();
            it++)
    {
        if (key == it->first)
        {
            it->second = true;
            break;
        }
    }

}
void FreeFlyCamera::OffKeyboard(GLubyte key)
{
    for (KeyStates::iterator it = _keystates.begin(); it != _keystates.end();
            it++)
    {
        if (key == it->first)
        {
            it->second = false;
            break;
        }
    }

}

void FreeFlyCamera::animate(unsigned int timestep)
{
    double realspeed = (_keystates[_keyconf["boost"]])?10*_speed:_speed;

    if (_keystates[_keyconf["camera_forward"]])
        _position += _forward * (realspeed * timestep);
    if (_keystates[_keyconf["camera_back"]])
        _position -= _forward * (realspeed * timestep);
    if (_keystates[_keyconf["camera_left"]])
        _position += _left * (realspeed * timestep);
    if (_keystates[_keyconf["camera_right"]])
        _position -= _left * (realspeed * timestep);

    if (_keystates[_keyconf["camera_up"]])
    {
        _verticalMotionActive = true;
        _timeBeforeStoppingVerticalMotion = 250;
        _verticalMotionDirection = 1;

    }
    if (_keystates[_keyconf["camera_down"]])
    {
        _verticalMotionActive = true;
        _timeBeforeStoppingVerticalMotion = 250;
        _verticalMotionDirection = -1;
    }

    if (_verticalMotionActive)
    {
        if (timestep > _timeBeforeStoppingVerticalMotion)
            _verticalMotionActive = false;
        else
            _timeBeforeStoppingVerticalMotion -= timestep;

        _position += Vector3D(0,0,_verticalMotionDirection*realspeed*timestep);
    }
    else if( _keystates[_keyconf["rotate_right"]])
    {
        _theta +=10*_sensivity;
        _phi += 10*_sensivity;
        VectorsFromAngles();

    }
    else if( _keystates[_keyconf["rotate_left"]])
    {
        _theta -= 10*_sensivity;
        _phi -= 10*_sensivity;
        VectorsFromAngles();

    }


    _target = _position + _forward;

}

void FreeFlyCamera::setSpeed(double speed)
{
    _speed = speed;
}

void FreeFlyCamera::setSensivity(double sensivity)
{
    _sensivity = sensivity;
}

void FreeFlyCamera::setPosition(const Vector3D & position)
{
    _position = position;
    _target = _position + _forward;
}

void FreeFlyCamera::VectorsFromAngles()
{
    static const Vector3D up(0,0,1);
    if (_phi > 89)
        _phi = 89;
    else if (_phi < -89)
        _phi = -89;
    double r_temp = cos(_phi*M_PI/180);
    _forward.Z = sin(_phi*M_PI/180);
    _forward.X = r_temp*cos(_theta*M_PI/180);
    _forward.Y = r_temp*sin(_theta*M_PI/180);

    _left = up.crossProduct(_forward);
    _left.normalize();

    _target = _position + _forward;
}

void FreeFlyCamera::look()
{
    gluLookAt(_position.X,_position.Y,_position.Z,
              _target.X,_target.Y,_target.Z,
              0,0,1);
}

