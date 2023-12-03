#pragma once

#include "object/visibleobject/visibleobject.h"

class Triangle: public VisibleObject
{
public:
    Triangle(Vector3D p1, Vector3D p2, Vector3D p3,
             Vector3D normal, std::shared_ptr<Material> material);

    void update() override;
    bool hit(const Ray& r, const double t_min, const double t_max, HitInfo& data) const override;
    void move(const Vector3D &d) override;
private:
    bool _check_in_triangle(const Vector3D &point);
    Vector3D _points[3];
    Vector3D _plane_normal;
};

