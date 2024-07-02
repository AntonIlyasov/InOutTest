#ifndef PLANT_H
#define PLANT_H
#include "blocks/gain/gain.h"
#include "blocks/integrator/integrator.h"

class Plant
{
public:
    Plant();
    float update(float input, float dt);
private:
    Integrator* integrator[3];
    float b1, b2, b3, a11, a12, a13, a21, a22, a23, a31, a32, a33, c1, c2, c3;
};

#endif // PLANT_H
