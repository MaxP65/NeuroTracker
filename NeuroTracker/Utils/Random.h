#pragma once

#include "../Config.h"

Scalar fRand(Scalar fMin, Scalar fMax)
{
    Scalar f = (Scalar)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

Scalar fRand()
{
    return fRand(-1000, 1000);
}