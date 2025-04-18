#pragma once

#include "../Config.h"

Scalar fRand(Scalar fMin, Scalar fMax)
{
    Scalar f = (Scalar)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

Scalar fpRand()
{
    return fRand(-1, 1);
}

Scalar normalDist() {
    return exp(-pow(fRand(-2, 2),2)/0.09);
}