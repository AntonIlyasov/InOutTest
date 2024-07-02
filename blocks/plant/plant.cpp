#include "plant.h"
#include <QDebug>

Plant::Plant()
{
    integrator[0] = new Integrator(0.0);
    integrator[1] = new Integrator(0.0);
    integrator[2] = new Integrator(0.0);

    b1      = 4;
    b2      = 0;
    b3      = 0;

    a11     = -0.6;
    a12     = -1.0;
    a13     = -0.5;
    a21     = 1;
    a22     = 0;
    a23     = 0;
    a31     = 0;
    a32     = 1;
    a33     = 0;

    c1      = 0.25;
    c2      = 2.5;
    c3      = 0.025;
}

float Plant::update(float input, float dt){

    qDebug() << input << dt;

    float x1 =integrator[0]->getState();
    float x2 =integrator[1]->getState();
    float x3 =integrator[2]->getState();

    float x1d = b1*input + a11*x1 + a12*x2 + a13*x3;
    float x2d = b2*input + a21*x1 + a22*x2 + a23*x3;
    float x3d = b3*input + a31*x1 + a32*x2 + a33*x3;

    integrator[0]->update(x1d, dt);
    integrator[1]->update(x2d, dt);
    integrator[2]->update(x3d, dt);

    return c1*x1 + c2*x2 + c3*x3;
}







