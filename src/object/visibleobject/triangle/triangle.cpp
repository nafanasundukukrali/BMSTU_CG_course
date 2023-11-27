#include "triangle.h"

Triangle::Triangle(Vector3D p1, Vector3D p2, Vector3D p3, Vector3D normal, std::shared_ptr<Material> material)
{
    _material = material;
    _points[0] = p1;
    _points[1] = p2;
    _points[2] = p3;

    _plane_normal = -normal;
    _plane_normal.normalize();

    Triangle::update();
}

void Triangle::update()
{
    Vector3D min = {std::min(std::min(_points[0].x(), _points[1].x()), _points[2].x()),
                    std::min(std::min(_points[0].y(), _points[1].y()), _points[2].y()),
                    std::min(std::min(_points[0].z(), _points[1].z()), _points[2].z())};
    Vector3D max = {std::max(std::max(_points[0].x(), _points[1].x()), _points[2].x()),
                    std::max(std::max(_points[0].y(), _points[1].y()), _points[2].y()),
                    std::max(std::max(_points[0].z(), _points[1].z()), _points[2].z())};

    _center = {(_points[0].x() + _points[1].x() + _points[2].x()) / 3,
               (_points[0].y() + _points[1].y() + _points[2].y()) / 3,
               (_points[0].z() + _points[1].z() + _points[2].z()) / 3};

    _boundingBox = BoundingBox(min, max);
}

bool Triangle::hit(const Ray& r, const double t_min, const double t_max, HitInfo& data) const
{
    Vector3D edge1 = _points[1] - _points[0];
    Vector3D edge2 = _points[2] - _points[0];
    Vector3D e1e2 = edge1.cross(edge2).normalized();

    if (e1e2.dot(r.direction()) > 0.0f)
        e1e2 = -e1e2;

    Vector3D pvec = r.direction().cross(edge2);
    double det = edge1.dot(pvec);

    if (det <= 1e-9)
        return false;

    float inv_det = 1.0f / det;

    Vector3D tvec = r.origin() - _points[0];
    double u = tvec.dot(pvec) * inv_det;
    Vector3D qvec = tvec.cross(edge1);
    double v = r.direction().dot(qvec) * inv_det;

    if (u < 0.0f || v < 0.0f || u + v > 1.0f)
        return false;

    double t = edge2.dot(qvec) * inv_det;

    if (t > t_max || t < t_min)
        return false;

    data.t = t;
    data.hit_point = r.get_point_by_t(t);
    data.normal = (edge1.cross(edge2)).normalized();
    data.material = _material;
    data.object = shared_from_this();

    return true;
}

