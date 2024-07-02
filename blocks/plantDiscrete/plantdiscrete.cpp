#include "plantdiscrete.h"
#include <QDebug>

PlantDiscrete::PlantDiscrete()
{
    b1      = 0.5;
    b2      = 0;
    b3      = 0;

    a11     = 2.932;
    a12     = -1.437;
    a13     = 0.9418;
    a21     = 2;
    a22     = 0;
    a23     = 0;
    a31     = 0;
    a32     = 0.5;
    a33     = 0;

    c1      = 0.2918;
    c2      = -0.1947;
    c3      = 0.09782;

    x1_prev = 0;
    x2_prev = 0;
    x3_prev = 0;
}

float PlantDiscrete::update(float input){

//    qDebug() << input;

    float x1_new = b1*input + a11*x1_prev + a12*x2_prev + a13*x3_prev;
    float x2_new = b2*input + a21*x1_prev + a22*x2_prev + a23*x3_prev;
    float x3_new = b3*input + a31*x1_prev + a32*x2_prev + a33*x3_prev;

    float y = c1*x1_prev + c2*x2_prev + c3*x3_prev;

    x1_prev = x1_new;
    x2_prev = x2_new;
    x3_prev = x3_new;

    return y;
}
