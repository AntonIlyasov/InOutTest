#ifndef PLANTDISCRETE_H
#define PLANTDISCRETE_H

class PlantDiscrete
{
public:
    PlantDiscrete();
    float update(float input);
private:
    float b1, b2, b3, a11, a12, a13, a21, a22, a23, a31, a32, a33, c1, c2, c3;
    float x1_prev, x2_prev, x3_prev;
};

#endif // PLANTDISCRETE_H
