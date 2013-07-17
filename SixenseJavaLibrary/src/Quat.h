#ifndef Quat_h
#define Quat_h

#include <assert.h>
#include <stdlib.h>
#include <math.h>

//-------------------------------------------------------------------------------------
// Constants for 3D world/axis definitions.

// Definitions of axes for coordinate and rotation conversions.
enum Axis
{
    Axis_X = 0, Axis_Y = 1, Axis_Z = 2
};

// RotateDirection describes the rotation direction around an axis, interpreted as follows:
//  CW  - Clockwise while looking "down" from positive axis towards the origin.
//  CCW - Counter-clockwise while looking from the positive axis towards the origin,
//        which is in the negative axis direction.
//  CCW is the default for the RHS coordinate system. Oculus standard RHS coordinate
//  system defines Y up, X right, and Z back (pointing out from the screen). In this
//  system Rotate_CCW around Z will specifies counter-clockwise rotation in XY plane.
enum RotateDirection
{
    Rotate_CCW = 1,
    Rotate_CW  = -1 
};

enum HandedSystem
{
    Handed_R = 1, Handed_L = -1
};

// AxisDirection describes which way the axis points. Used by WorldAxes.
enum AxisDirection
{
    Axis_Up    =  2,
    Axis_Down  = -2,
    Axis_Right =  1,
    Axis_Left  = -1,
    Axis_In    =  3,
    Axis_Out   = -3
};

struct WorldAxes
{
    AxisDirection XAxis, YAxis, ZAxis;

    WorldAxes(AxisDirection x, AxisDirection y, AxisDirection z)
        : XAxis(x), YAxis(y), ZAxis(z) {}
};


//-------------------------------------------------------------------------------------
// ***** Math

// Math class contains constants and functions. This class is a template specialized
// per type, with Math<float> and Math<double> being distinct.
template<class Type>
class Math
{  
};

// Single-precision Math constants class.
template<>
class Math<float>
{
public:
    static const float Pi;
    static const float TwoPi;
    static const float PiOver2;
    static const float PiOver4;
    static const float E;

    static const float MaxValue;          // Largest positive float Value
    static const float MinPositiveValue;  // Smallest possible positive value

    static const float RadToDegreeFactor;
    static const float DegreeToRadFactor;

    static const float Tolerance; //  0.00001f;
    static const float SingularityRadius; //0.00000000001f for Gimbal lock numerical problems
};

// Double-precision Math constants class.
template<>
class Math<double>
{
public:
    static const double Pi;
    static const double TwoPi;
    static const double PiOver2;
    static const double PiOver4;
    static const double E;

    static const double MaxValue;          // Largest positive double Value
    static const double MinPositiveValue;  // Smallest possible positive value

    static const double RadToDegreeFactor;
    static const double DegreeToRadFactor;

    static const double Tolerance; //  0.00001f;
    static const double SingularityRadius; //0.00000000001 for Gimbal lock numerical problems
};

typedef Math<float>  Mathf;
typedef Math<double> Mathd;

// Conversion functions between degrees and radians
template<class FT>
FT RadToDegree(FT rads) { return rads * Math<FT>::RadToDegreeFactor; }
template<class FT>
FT DegreeToRad(FT rads) { return rads * Math<FT>::DegreeToRadFactor; }

template<class T>
class Quat;


//-------------------------------------------------------------------------------------
// ***** Quat

// Quatf represents a quaternion class used for rotations.
// 
// Quaternion multiplications are done in right-to-left order, to match the
// behavior of matrices.


template<class T>
class Quat
{
public:
    // w + Xi + Yj + Zk
    T x, y, z, w;    

    Quat() : x(0), y(0), z(0), w(1) {}
    Quat(T x_, T y_, T z_, T w_) : x(x_), y(y_), z(z_), w(w_) {}


    bool operator== (const Quat& b) const   { return x == b.x && y == b.y && z == b.z && w == b.w; }
    bool operator!= (const Quat& b) const   { return x != b.x || y != b.y || z != b.z || w != b.w; }

    Quat  operator+  (const Quat& b) const  { return Quat(x + b.x, y + b.y, z + b.z, w + b.w); }
    Quat& operator+= (const Quat& b)        { w += b.w; x += b.x; y += b.y; z += b.z; return *this; }
    Quat  operator-  (const Quat& b) const  { return Quat(x - b.x, y - b.y, z - b.z, w - b.w); }
    Quat& operator-= (const Quat& b)        { w -= b.w; x -= b.x; y -= b.y; z -= b.z; return *this; }

    Quat  operator*  (T s) const            { return Quat(x * s, y * s, z * s, w * s); }
    Quat& operator*= (T s)                  { w *= s; x *= s; y *= s; z *= s; return *this; }
    Quat  operator/  (T s) const            { T rcp = T(1)/s; return Quat(x * rcp, y * rcp, z * rcp, w *rcp); }
    Quat& operator/= (T s)                  { T rcp = T(1)/s; w *= rcp; x *= rcp; y *= rcp; z *= rcp; return *this; }

    // Get quaternion length.
    T       Length() const                  { return sqrt(x * x + y * y + z * z + w * w); }
    // Get quaternion length squared.
    T       LengthSq() const                { return (x * x + y * y + z * z + w * w); }
    // Simple Eulidean distance in R^4 (not SLERP distance, but at least respects Haar measure)
    T       Distance(const Quat& q) const
    {
        T d1 = (*this - q).Length();
        T d2 = (*this + q).Length(); // Antipoldal point check
        return (d1 < d2) ? d1 : d2;
    }
    T       DistanceSq(const Quat& q) const
    {
        T d1 = (*this - q).LengthSq();
        T d2 = (*this + q).LengthSq(); // Antipoldal point check
        return (d1 < d2) ? d1 : d2;
    }

    // Normalize
    bool    IsNormalized() const            { return fabs(LengthSq() - 1) < Math<T>::Tolerance; }
    void    Normalize()                     { *this /= Length(); }
    Quat    Normalized() const              { return *this / Length(); }

    // Returns conjugate of the quaternion. Produces inverse rotation if quaternion is normalized.
    Quat    Conj() const                    { return Quat(-x, -y, -z, w); }

    // AnnaSteve fixed: order of quaternion multiplication
    // Quaternion multiplication. Combines quaternion rotations, performing the one on the 
    // right hand side first.
    Quat  operator* (const Quat& b) const   { return Quat(w * b.x + x * b.w + y * b.z - z * b.y,
                                                          w * b.y - x * b.z + y * b.w + z * b.x,
                                                          w * b.z + x * b.y - y * b.x + z * b.w,
                                                          w * b.w - x * b.x - y * b.y - z * b.z); }


    
    // Inversed quaternion rotates in the opposite direction.
    Quat        Inverted() const
    {
        return Quat(-x, -y, -z, w);
    }

    // Sets this quaternion to the one rotates in the opposite direction.
    void        Invert() const
    {
        *this = Quat(-x, -y, -z, w);
    }
    
    
    // GetEulerAngles extracts Euler angles from the quaternion, in the specified order of
    // axis rotations and the specified coordinate system. Right-handed coordinate system
    // is the default, with CCW rotations while looking in the negative axis direction.
    // Here a,b,c, are the Yaw/Pitch/Roll angles to be returned.
    // rotation a around axis A1
    // is followed by rotation b around axis A2
    // is followed by rotation c around axis A3
    // rotations are CCW or CW (D) in LH or RH coordinate system (S)
    template <Axis A1, Axis A2, Axis A3, RotateDirection D, HandedSystem S>
    void GetEulerAngles(T *a, T *b, T *c)
    {
        T Q[3] = { x, y, z };  //Quaternion components x,y,z

        T ww  = w*w;
        T Q11 = Q[A1]*Q[A1];
        T Q22 = Q[A2]*Q[A2];
        T Q33 = Q[A3]*Q[A3];

        T psign = T(-1.0);
        // Determine whether even permutation
        if (((A1 + 1) % 3 == A2) && ((A2 + 1) % 3 == A3))
            psign = T(1.0);
        
        T s2 = psign * T(2.0) * (psign*w*Q[A2] + Q[A1]*Q[A3]);

        if (s2 < (T)-1.0 + Math<T>::SingularityRadius)
        { // South pole singularity
            *a = T(0.0);
            *b = -S*D*Math<T>::PiOver2;
            *c = S*D*atan2((T)2.0*(psign*Q[A1]*Q[A2] + w*Q[A3]),
		                   ww + Q22 - Q11 - Q33 );
        }
        else if (s2 > (T)1.0 - Math<T>::SingularityRadius)
        {  // North pole singularity
            *a = (T)0.0;
            *b = S*D*Math<T>::PiOver2;
            *c = S*D*atan2((T)2.0*(psign*Q[A1]*Q[A2] + w*Q[A3]),
		                   ww + Q22 - Q11 - Q33);
        }
        else
        {
            *a = -S*D*atan2((T)-2.0*(w*Q[A1] - psign*Q[A2]*Q[A3]),
		                    ww + Q33 - Q11 - Q22);
            *b = S*D*asin(s2);
            *c = S*D*atan2((T)2.0*(w*Q[A3] - psign*Q[A1]*Q[A2]),
		                   ww + Q11 - Q22 - Q33);
        }      
        return;
    }

    template <Axis A1, Axis A2, Axis A3, RotateDirection D>
    void GetEulerAngles(T *a, T *b, T *c)
    { GetEulerAngles<A1, A2, A3, D, Handed_R>(a, b, c); }

    template <Axis A1, Axis A2, Axis A3>
    void GetEulerAngles(T *a, T *b, T *c)
    { GetEulerAngles<A1, A2, A3, Rotate_CCW, Handed_R>(a, b, c); }
};


typedef Quat<float>  Quatf;
typedef Quat<double> Quatd;

#endif
