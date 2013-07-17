#include "Quat.h"

#include <float.h>


//-------------------------------------------------------------------------------------
// ***** Math


// Single-precision Math constants class.
const float Math<float>::Pi      = 3.1415926f;
const float Math<float>::TwoPi   = 3.1415926f * 2;
const float Math<float>::PiOver2 = 3.1415926f / 2.0f;
const float Math<float>::PiOver4 = 3.1415926f / 4.0f;
const float Math<float>::E       = 2.7182818f;

const float Math<float>::MaxValue = FLT_MAX;
const float Math<float>::MinPositiveValue = FLT_MIN;

const float Math<float>::RadToDegreeFactor = 360.0f / Math<float>::TwoPi;
const float Math<float>::DegreeToRadFactor = Math<float>::TwoPi / 360.0f;

const float Math<float>::Tolerance = 0.00001f;
const float Math<float>::SingularityRadius = 0.0000001f; // Use for Gimbal lock numerical problems


// Double-precision Math constants class.
const double Math<double>::Pi      = 3.14159265358979;
const double Math<double>::TwoPi   = 3.14159265358979 * 2;
const double Math<double>::PiOver2 = 3.14159265358979 / 2.0;
const double Math<double>::PiOver4 = 3.14159265358979 / 4.0;
const double Math<double>::E       = 2.71828182845905;

const double Math<double>::MaxValue = DBL_MAX;
const double Math<double>::MinPositiveValue = DBL_MIN;

const double Math<double>::RadToDegreeFactor = 360.0 / Math<double>::TwoPi;
const double Math<double>::DegreeToRadFactor = Math<double>::TwoPi / 360.0;

const double Math<double>::Tolerance = 0.00001;
const double Math<double>::SingularityRadius = 0.000000000001; // Use for Gimbal lock numerical problems

