#ifndef VECTOR2_H
#define VECTOR2_H

#include <cmath>
#include <iostream>

class Vector2  {
public:
    
    Vector2() { mV[0]=0; mV[1]=0; }
    Vector2(float e0, float e1) {mV[0]=e0; mV[1]=e1; }
    float x() const { return mV[0]; }
    float y() const { return mV[1]; }
    void setX(float a) { mV[0] = a; }
    void setY(float a) { mV[1] = a; }

    Vector2(const Vector2 &v) {
         mV[0] = v.mV[0]; mV[1] = v.mV[1]; 
    }

    const Vector2& operator+() const { return *this; }
    Vector2 operator-() const { return Vector2(-mV[0], -mV[1]); }
    float& operator[](int i) { assert ( i >= 0 && i < 2 ); return mV[i]; }
    float operator[](int i) const { assert ( i >= 0 && i < 2 ); return mV[i];}

    Vector2& operator+=(const Vector2 &v2);
    Vector2& operator-=(const Vector2 &v2);
    Vector2& operator*=(const float t);
    Vector2& operator/=(const float t);

	// 这个算法不明白是什么意思？
    void scramble(); 

    
    float length() const { return sqrt(mV[0]*mV[0] + mV[1]*mV[1] ); }
    float squaredLength() const { return mV[0]*mV[0] + mV[1]*mV[1] ; }

    void makeUnitVector();

	friend Vector2 unitVector(const Vector2& v);
	friend Vector2 operator+(const Vector2 &v1, const Vector2 &v2);
	friend Vector2 operator-(const Vector2 &v1, const Vector2 &v2);
	friend Vector2 operator*(float t, const Vector2 &v);
	friend Vector2 operator*(const Vector2 &v, float t);
	friend Vector2 operator/(const Vector2 &v, float t);
	friend float dot(const Vector2 &v1, const Vector2 &v2);

private:
    float mV[2];
};

inline void Vector2::scramble()
{
   float _x;
   float _y = mV[0];

   _x =  mV[1] * 1234.12345054321f; 
   mV[0] = _x - (int)_x;
   _y = _y * 7654.54321012345f;
   mV[1] = _y - (int)_y;
}

inline bool operator==(const Vector2 &t1, const Vector2 &t2) {
   return ((t1[0]==t2[0])&&(t1[1]==t2[1]));
}

inline bool operator!=(const Vector2 &t1, const Vector2 &t2) {
   return ((t1[0]!=t2[0])||(t1[1]!=t2[1]));
}

inline std::istream &operator>>(std::istream &is, Vector2 &t) {
   is >> t[0] >> t[1];
   return is;
}

inline std::ostream &operator<<(std::ostream &os, const Vector2 &t) {
   os << t[0] << " " << t[1] ;
   return os;
}

inline Vector2 unitVector(const Vector2& v) {
    float k = 1.0f / sqrt(v.mV[0]*v.mV[0] + v.mV[1]*v.mV[1]);
    return Vector2(v.mV[0]*k, v.mV[1]*k);
}

inline void Vector2::makeUnitVector() {
    float k = 1.0f / sqrt(mV[0]*mV[0] + mV[1]*mV[1]);
    mV[0] *= k; mV[1] *= k; 
}

inline Vector2 operator+(const Vector2 &v1, const Vector2 &v2) {
    return Vector2( v1.mV[0] + v2.mV[0], v1.mV[1] + v2.mV[1]);
}

inline Vector2 operator-(const Vector2 &v1, const Vector2 &v2) {
    return Vector2( v1.mV[0] - v2.mV[0], v1.mV[1] - v2.mV[1]);
}

inline Vector2 operator*(float t, const Vector2 &v) {
    return Vector2(t*v.mV[0], t*v.mV[1]); 
}

inline Vector2 operator*(const Vector2 &v, float t) {
    return Vector2(t*v.mV[0], t*v.mV[1]); 
}

inline Vector2 operator/(const Vector2 &v, float t) {
    return Vector2(v.mV[0]/t, v.mV[1]/t); 
}


inline float dot(const Vector2 &v1, const Vector2 &v2) {
    return v1.mV[0] *v2.mV[0] + v1.mV[1] *v2.mV[1];
}



inline Vector2& Vector2::operator+=(const Vector2 &v){
    mV[0]  += v.mV[0];
    mV[1]  += v.mV[1];
    return *this;
}

inline Vector2& Vector2::operator-=(const Vector2& v) {
    mV[0]  -= v.mV[0];
    mV[1]  -= v.mV[1];
    return *this;
}

inline Vector2& Vector2::operator*=(const float t) {
    mV[0]  *= t;
    mV[1]  *= t;
    return *this;
}

inline Vector2& Vector2::operator/=(const float t) {
    mV[0]  /= t;
    mV[1]  /= t;
    return *this;
}



#endif
