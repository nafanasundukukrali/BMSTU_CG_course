#include "kdtree.h"

KDTree::KDTree(std::vector<std::shared_ptr<Object>> objects)
{
    rootNode = create_tree(objects, 0);
}

void KDTree::update(std::vector<std::shared_ptr<Object>> objects)
{
    rootNode = create_tree(objects, 0);
}

std::shared_ptr<KDTree::KDNode> KDTree::create_tree(const std::vector<std::shared_ptr<Object>> objects, const int depth)
{
    auto node = std::make_shared<KDNode>();
    node->left = 0;
    node->right = 0;
    node->axis = 0;

    if (objects.size() == 0)
        return node;

    node->boundingBox = objects[0]->boundingBox();

    Vector3D average_position(0.0f);

    for (auto& entity : objects)
    {
        average_position += entity->center();
        node->boundingBox.expand(entity->boundingBox());
    }

    average_position /= objects.size();

    if (objects.size() <= 4 || depth > 8)
    {
        for (auto &object : objects)
            node->objects.emplace_back(object);

        return node;
    }

    const Vector3D boundingBoxSize = node->boundingBox.max() - node->boundingBox.min();
    size_t buffer_axis;

    if (boundingBoxSize[0] >= boundingBoxSize[1] && boundingBoxSize[0] >= boundingBoxSize[2])
        buffer_axis = 0;
    else if (boundingBoxSize[1] >= boundingBoxSize[2])
        buffer_axis = boundingBoxSize[1] >= boundingBoxSize[2];
    else
        buffer_axis = 2;

    node->axis = buffer_axis;

    std::vector<std::shared_ptr<Object>> left_objects;
    std::vector<std::shared_ptr<Object>> right_objects;

    for (auto& object : objects)
        if (object->center()[buffer_axis] < average_position[buffer_axis])
            left_objects.emplace_back(object);
        else
            right_objects.emplace_back(object);

    if (left_objects.size() > 0)
    {
        node->left = create_tree(left_objects, depth + 1);
        node->boundingBox.expand(node->left->boundingBox);
        node->left->f = true;
    }

    if (right_objects.size() > 0)
    {
        node->right = create_tree(right_objects, depth + 1);
        node->boundingBox.expand(node->right->boundingBox);
        node->right->f = false;
    }

    return node;
}

bool KDTree::hit(const Ray& r, const double tmin, const double tmax, HitInfo &data) const
{
    data.t = tmax;

    if (rootNode)
        return rootNode->hit(r, tmin, tmax, data);

    throw "No tree!";
}

bool KDTree::KDNode::hit(const Ray& r, const double tmin, const double tmax, HitInfo &data) const
{
    if (!boundingBox.validate_intersect(r))
        return false;

    std::shared_ptr<KDNode> first;
    std::shared_ptr<KDNode> second;

    if (r.direction()[axis] > 0)
    {
        first = left;
        second = right;
    }
    else
    {
        first = right;
        second = left;
    }

    double tmax_buffer = tmax;
    bool hit_first = false;

    if (first)
    {
        hit_first = first->hit(r, tmin, tmax_buffer, data);

        if (hit_first)
            tmax_buffer = data.t;
    }

    bool hit_second = false;

    if (second)
    {
        hit_second = second->hit(r, tmin, tmax_buffer, data);

        if (hit_second)
            tmax_buffer = data.t;
    }

    if (hit_first || hit_second)
        return true;

    HitInfo buffer_data;
    double closest_hit = tmax_buffer;

    for (const auto object : objects)
        if (object->hit(r, tmin, closest_hit, data))
            closest_hit = data.t;

    return closest_hit < tmax;
}
