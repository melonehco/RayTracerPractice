/* vec3.h
 * Defines the vec3 class for vectors
 * based on the ray-tracing tutorial at https://www.realtimerendering.com/raytracing/Ray%20Tracing%20in%20a%20Weekend.pdf
 * 
 * Melody Mao
 * Fall 2019
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
    //these inlines basically function the way we used macros in graphics;
    //but macros are discouraged in C++

    //overloaded operators
    inline const vec3& operator+() const { return *this; }
    inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    inline float operator[](int i) const { return e[i]; }
    inline float& operator[](int i) { return e[i]; }
    //const return value vs const member function vs const function parameter (vs const variable)

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

    inline vec3 operator+(const vec3 &v2) const
    {
        return vec3(e[0] + v2.e[0], e[1] + v2.e[1], e[2] + v2.e[2]);
    }

    inline vec3 operator-(const vec3 &v2) const
    {
        return vec3(e[0] - v2.e[0], e[1] - v2.e[1], e[2] - v2.e[2]);
    }

    inline vec3 operator*(const vec3 &v2) const
    {
        return vec3(e[0] * v2.e[0], e[1] * v2.e[1], e[2] * v2.e[2]);
    }

    inline vec3 operator/(const vec3 &v2) const
    {
        return vec3(e[0] / v2.e[0], e[1] / v2.e[1], e[2] / v2.e[2]);
    }

    //vector op functions

    inline float length() const
    {
        return sqrt( e[0] * e[0] + e[1] * e[1] + e[2] * e[2] );
    }
    inline float squared_length() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }
    
    inline void make_unit_vector()
    {
        float k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
        e[0] *= k;
        e[1] *= k;
        e[2] *= k;
    }

    //static functions

    static inline float dot(const vec3 &v1, const vec3 &v2)
    {
        return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
    }

    static inline vec3 cross(const vec3 &v1, const vec3 &v2)
    {
        return vec3( (v1.e[1]*v2.e[2] - v1.e[2]*v2.e[1]),
                     (-(v1.e[0]*v2.e[2] - v1.e[2]*v2.e[0])),
                     (v1.e[0]*v2.e[1] - v1.e[1]*v2.e[0])
                    );
    }

    static inline vec3 unit_vector(vec3 v)
    {
        return scale(v, 1.0/v.length());
    }

    static inline vec3 scale(vec3 v, float t)
    {
        return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
    }

    float e[3];
};

#endif