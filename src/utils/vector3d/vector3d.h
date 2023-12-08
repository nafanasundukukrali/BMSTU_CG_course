#pragma once

#include <vector>
#include <cstdlib>
#include <cmath>

class Vector3D
{
public:
        Vector3D() = default;
        explicit Vector3D(double init_value);
        Vector3D(double x, double y, double z);

        const Vector3D& operator + () const;
        Vector3D operator-() const;
        Vector3D& operator += (const Vector3D &v2);
        Vector3D& operator = (const Vector3D &v2);
        Vector3D& operator -= (const Vector3D &v2);
        Vector3D& operator -= (const double &v2);
        Vector3D& operator *= (const Vector3D &v2);
        Vector3D& operator /= (const Vector3D &v2);
        Vector3D& operator *= (const double &value);
        Vector3D& operator /= (const double &value);

        double operator [](size_t i) const;
        double& operator [] (size_t i);

        double x() const;
        double y() const;
        double z() const;
        double r() const;
        double g() const;
        double b() const;

        double dot(const Vector3D &v2) const;
        Vector3D cross(const Vector3D &v2) const;
        Vector3D reflect(const Vector3D &v) const;

        double length() const;
        double squared_length() const;

        void normalize();
        Vector3D normalized() const;
private:
        std::vector<double> _points = {0.0f, 0.0f, 0.0f};
};

Vector3D operator + (const Vector3D &v1, const Vector3D &v2);
Vector3D operator - (const Vector3D &v1, const Vector3D &v2);
Vector3D operator * (const Vector3D &v1, const Vector3D &v2);
Vector3D operator / (const Vector3D &v1, const Vector3D &v2);
Vector3D operator * (double value, Vector3D v);
Vector3D operator * (Vector3D v, double value);
Vector3D operator / (Vector3D v, double value);
Vector3D operator / (double value, Vector3D v);
