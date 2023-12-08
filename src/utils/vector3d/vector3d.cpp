#include "vector3d.h"

Vector3D::Vector3D(double init_value)
{
    for (size_t i = 0; i < 3; i++)
        _points[i] = init_value;
}

Vector3D::Vector3D(double x, double y, double z)
{
    _points[0] = x;
    _points[1] = y;
    _points[2] = z;
}

const Vector3D& Vector3D::operator + () const
{
    return *this;
}

Vector3D Vector3D::operator - () const
{
    return {-_points[0], -_points[1], -_points[2]};
}

Vector3D& Vector3D::operator += (const Vector3D &v)
{
    _points[0] += v[0];
    _points[1] += v[1];
    _points[2] += v[2];

    return *this;
}


Vector3D& Vector3D::operator = (const Vector3D &v)
{
    _points[0] = v[0];
    _points[1] = v[1];
    _points[2] = v[2];

    return *this;
}

Vector3D& Vector3D::operator -= (const Vector3D &v)
{
    _points[0] -= v[0];
    _points[1] -= v[1];
    _points[2] -= v[2];

    return *this;
}

Vector3D& Vector3D::operator-=(const double &v)
{
    _points[0] -= v;
    _points[1] -= v;
    _points[2] -= v;

    return *this;
}

Vector3D& Vector3D::operator *= (const Vector3D &v)
{
    _points[0] *= v[0];
    _points[1] *= v[1];
    _points[2] *= v[2];

    return *this;
}

Vector3D& Vector3D::operator /= (const Vector3D &v)
{
    if (v[0] == 0.0f || v[1] == 0.0f || v[2] == 0.0f)
        throw "Error divide vector: zero division!";

    _points[0] /= v[0];
    _points[1] /= v[1];
    _points[2] /= v[2];

    return *this;
}

Vector3D& Vector3D::operator *= (const double &value)
{
    _points[0] *= value;
    _points[1] *= value;
    _points[2] *= value;

    return *this;
}

Vector3D& Vector3D::operator /= (const double &value)
{
    if (value == 0.0f)
        throw "Error divide vector: zero division!";

    _points[0] /= value;
    _points[1] /= value;
    _points[2] /= value;

    return *this;
}

Vector3D operator + (const Vector3D &v1, const Vector3D &v2)
{
    return {v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]};
}

Vector3D operator - (const Vector3D &v1, const Vector3D &v2)
{
    return {v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]};
}

Vector3D operator * (const Vector3D &v1, const Vector3D &v2)
{
    return {v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]};
}

Vector3D operator / (const Vector3D &v1, const Vector3D &v2)
{
    if (v2[0] == 0.0f || v2[1] == 0.0f || v2[2] == 0.0f)
        throw "Error divide vector: zero division!";

    return {v1[0] / v2[0], v1[1] / v2[1], v1[2] / v2[2]};
}

Vector3D operator * (const double value, const Vector3D v)
{
    return {v[0] * value, v[1] * value, v[2] * value};
}

Vector3D operator * (const Vector3D v, const double value)
{
    return {v[0] * value, v[1] * value, v[2] * value};
}

Vector3D operator / (const Vector3D v, const double value)
{
    if (value == 0.0f)
        throw "Error divide vector: zero division!";

    return {v[0] / value, v[1] / value, v[2] / value};
}

Vector3D operator / (const double value, const Vector3D v)
{
    if (v[0] == 0.0f || v[1] == 0.0f || v[2] == 0.0f)
        throw "Error divide vector: zero division!";

    return {value / v[0], value / v[1], value / v[2]};
}

double Vector3D::operator [] (size_t i) const
{
    return _points[i];
}

double& Vector3D::operator [] (size_t i)
{
    return _points[i];
}

double Vector3D::x() const
{
    return _points[0];
}

double Vector3D::y() const
{
    return _points[1];
}

double Vector3D::z() const
{
    return _points[2];
}

double Vector3D::r() const
{
    return _points[0];
}

double Vector3D::g() const
{
    return _points[1];
}

double Vector3D::b() const
{
    return _points[2];
}

double Vector3D::dot(const Vector3D &v2) const
{
    return _points[0] * v2[0] + _points[1] * v2[1] + _points[2] * v2[2];
}

Vector3D Vector3D::cross(const Vector3D &v2) const
{
    return {(_points[1] * v2[2] - _points[2] * v2[1]),
           -(_points[0] * v2[2] - _points[2] * v2[0]),
            (_points[0] * v2[1] - _points[1] * v2[0])};
}

Vector3D Vector3D::reflect(const Vector3D &v) const
{
    return v - 2.0f * dot(v) * (*this);
}

double Vector3D::length() const
{
    return sqrt(squared_length());
}
double Vector3D::squared_length() const
{
    return _points[0] * _points[0] + _points[1] * _points[1] + _points[2] * _points[2];
}

void Vector3D::normalize()
{
    double d = length();

    if (length() == 0)
        throw "Vector can't normalize: zero length!";

    _points[0] /= d;
    _points[1] /= d;
    _points[2] /= d;
}

Vector3D Vector3D::normalized() const
{
    double d = length();

    if (length() == 0)
        throw "Vector can't be normalized: zero length!";

    return {_points[0] / d, _points[1] / d, _points[2] / d};
}
