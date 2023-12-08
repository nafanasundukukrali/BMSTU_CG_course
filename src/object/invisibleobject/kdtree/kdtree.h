#pragma once

#include "object/invisibleobject/invisibleobject.h"

class KDTree: public InvisibleObject
{
public:
    KDTree(std::vector<std::shared_ptr<Object>> objects);
    virtual void material(const Vector3D &ref, const double &p) override;
    void update() override;
    virtual bool hit(const Ray& r, const double tmin, const double tmax, HitInfo &data) const override;
    void move(const Vector3D &d) override { throw "Called move in KDTree!"; };
    void delete_node(const double min_x, const double min_y, const double max_x, const double max_y);
    void insert_node(std::shared_ptr<Object> object);
private:
    struct KDNode: public std::enable_shared_from_this<KDNode>
    {
        void material(const Vector3D &ref, const double &p);
        bool hit(const Ray& r, const double tmin, const double tmax, HitInfo &data) const;
        std::shared_ptr<KDNode> delete_node(const double min_x, const double min_y, const double max_x, const double max_y);
        std::shared_ptr<KDNode> insert_node(std::shared_ptr<Object> object);
        bool validate_bounding_box_in_params(const double min_x, const double min_y, const double max_x,
                                             const double max_y, const BoundingBox &box);
        bool validate_params_in_boinding_box(const double min_x, const double min_y, const double max_x,
                                                             const double max_y, const BoundingBox &box);
        void update();
        bool f;
        BoundingBox boundingBox;
        size_t axis;
        size_t _depth;
        std::shared_ptr<KDNode> left;
        std::shared_ptr<KDNode> right;
        std::vector<std::shared_ptr<Object>> objects;
    };

    std::shared_ptr<KDNode> create_tree(std::vector<std::shared_ptr<Object>> objects, const int depth);
    std::shared_ptr<KDNode> _root_node;
};
