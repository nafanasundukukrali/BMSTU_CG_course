#include "model.h"


void Model::add(std::shared_ptr<Object> object)
{
    _objects.emplace_back(object);
}

void Model::generate_kd_tree()
{
    _kd_tree = std::make_shared<KDTree>(_objects);
    _boundingBox.expand(_kd_tree->boundingBox());
}

void Model::update()
{
    _kd_tree->update();
    _boundingBox = _kd_tree->boundingBox();
}

bool Model::hit(const Ray& r, const double tmin, const double tmax, HitInfo& data) const
{
    bool result = _boundingBox.validate_intersect(r);

    if (result)
        return _kd_tree->hit(r, tmin, tmax, data);

    return false;
}

void Model::move(const Vector3D &d)
{
    for (size_t j = 0; j < 3; j++)
        _center[j] += d[j];

    for (auto &obj: _objects)
       obj->move(d);

    Model::update();
}
