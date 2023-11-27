#pragma once

#include "object/invisibleobject/invisibleobject.h"

class KDTree: public InvisibleObject
{
public:
    KDTree(std::vector<std::shared_ptr<Object>> objects);

    virtual void update() override {};
    void update(std::vector<std::shared_ptr<Object>> objects);
    virtual bool hit(const Ray& r, const double tmin, const double tmax, HitInfo &data) const override;

private:
    struct KDNode
    {
        bool hit(const Ray& r, const double tmin, const double tmax, HitInfo &data) const;

        bool f;
        BoundingBox boundingBox;
        size_t axis;
        size_t _depth;
        std::shared_ptr<KDNode> left;
        std::shared_ptr<KDNode> right;
        std::vector<std::shared_ptr<Object>> objects;
    };

    std::shared_ptr<KDNode> create_tree(std::vector<std::shared_ptr<Object>> objects, const int depth);
    std::shared_ptr<KDNode> rootNode;
};
