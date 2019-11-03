/*
 *
 */

#ifndef __Vec3__
#define __Vec3__

#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3 {
public:
    //constructors
    vec3() {}
    vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }
    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }
    //TODO: read more on inline functions

    //overloaded operators
    //TODO: look up operator overloading
    //TODO: also what do the consts mean
    inline const vec3& operator+() const { return *this; }
    inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    inline float operator[](int i) const { return e[i]; }
    inline float& operator[](int i) { return e[i]; }

    // inline vec3& operator+=(const vec3 &v2);
    // inline vec3& operator-=(const vec3 &v2);
    // inline vec3& operator*=(const vec3 &v2);
    // inline vec3& operator/=(const vec3 &v2);
    // inline vec3& operator*=(const float t);
    // inline vec3& operator/=(const float t);

    inline vec3& operator+=(const vec3 &v2)
    {
        e[0] += v2.e[0];
        e[1] += v2.e[1];
        e[2] += v2.e[2];

        return *this;
    }

    inline vec3& operator-=(const vec3 &v2)
    {
        e[0] -= v2.e[0];
        e[1] -= v2.e[1];
        e[2] -= v2.e[2];

        return *this;
    }

    inline vec3& operator*=(const vec3 &v2)
    {
        e[0] *= v2.e[0];
        e[1] *= v2.e[1];
        e[2] *= v2.e[2];

        return *this;
    }

    inline vec3& operator/=(const vec3 &v2)
    {
        e[0] /= v2.e[0];
        e[1] /= v2.e[1];
        e[2] /= v2.e[2];

        return *this;
    }

    inline vec3& operator*=(const float t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;

        return *this;
    }

    inline vec3& operator/=(const float t)
    {
        float k = 1.0/t;
        e[0] *= k;
        e[1] *= k;
        e[2] *= k;

        return *this;
    }

    inline vec3 operator+(const vec3 &v2)
    {
        return vec3(e[0] + v2.e[0], e[1] + v2.e[1], e[2] + v2.e[2]);
    }

    inline vec3 operator-(const vec3 &v2)
    {
        return vec3(e[0] - v2.e[0], e[1] - v2.e[1], e[2] - v2.e[2]);
    }

    inline vec3 operator*(const vec3 &v2)
    {
        return vec3(e[0] * v2.e[0], e[1] * v2.e[1], e[2] * v2.e[2]);
    }

    inline vec3 operator/(const vec3 &v2)
    {
        return vec3(e[0] / v2.e[0], e[1] / v2.e[1], e[2] / v2.e[2]);
    }

    //note: requires that vec3 be first operand in multiplication
    inline vec3 operator*(float t)
    {
        return vec3(t * e[0], t * e[1], t * e[2]);
    }

    inline vec3 operator/(float t)
    {
        return vec3(e[0] / t, e[1] / t, e[2]) / t;
    }

    //vector op functions
    inline float dot(const vec3 &v1, const vec3 &v2)
    {
        return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
    }

    inline vec3 cross(const vec3 &v1, const vec3 &v2)
    {
        return vec3( (v1.e[1]*v2.e[2] - v1.e[2]*v2.e[1]),
                     (-(v1.e[0]*v2.e[2] - v1.e[2]*v2.e[0])),
                     (v1.e[0]*v2.e[1] - v1.e[1]*v2.e[0])
                    );
    }

    inline float length() const
    {
        return sqrt( e[0] * e[0] + e[1] * e[1] + e[2] * e[2] );
    }
    inline float squared_length() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }
    
    // inline void make_unit_vector();

    inline void make_unit_vector()
    {
        float k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
        e[0] *= k;
        e[1] *= k;
        e[2] *= k;
    }

    float e[3];
};

#endif