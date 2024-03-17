#pragma once

#include "../Config.h"

Scalar fRand(Scalar fMin, Scalar fMax)
{
    Scalar f = (Scalar)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

Scalar fpRand()
{
    return fRand(0, 1);
}

Scalar normalDist() {
    return exp(-pow(fpRand(),2)/0.09);
}