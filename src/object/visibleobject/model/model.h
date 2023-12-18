#pragma once
//#include <visitor/drawvisitor/drawvisitor.h>
//#include <utils/intensity/intensity.h>
#include "object/visibleobject/visibleobject.h"
#include "object/invisibleobject/kdtree/kdtree.h"

class Model: public VisibleObject
{
    friend class BaseBuilder;
public:
    Model() = default;
    ~Model() = default;
    void update() override;
    bool hit(const Ray& r, const double tmin, const double tmax, HitInfo& data) const override;
    void move(const Vector3D &d) override;
    void add(std::shared_ptr<Object> object);
    void generate_kd_tree();
protected:
    bool _generated_tree = false;
    std::vector<std::shared_ptr<Object>> _objects;
    std::shared_ptr<KDTree> _kd_tree;
};

