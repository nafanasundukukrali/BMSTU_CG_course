#include "kdtree.h"

KDTree::KDTree(std::vector<std::shared_ptr<Object>> objects)
{
    _root_node = create_tree(objects, 0);
    _boundingBox = _root_node->boundingBox;
}

void KDTree::update()
{
    _root_node->update();
    _boundingBox = _root_node->boundingBox;
}

void KDTree::material(const Vector3D &ref, const double &p)
{
    _root_node->material(ref, p);
}

void KDTree::KDNode::material(const Vector3D &ref, const double &p)
{
    if (left)
    {
        left->material(ref, p);
    }

    if (right)
    {
        right->material(ref, p);
    }

    if (objects.size())
        for (auto& object : objects)
            if (!object->is_chess_desk())
                object->material(ref, p);
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

    for (auto& object : objects)
    {
        average_position += object->center();
        node->boundingBox.expand(object->boundingBox());
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
    }

    if (right_objects.size() > 0)
    {
        node->right = create_tree(right_objects, depth + 1);
        node->boundingBox.expand(node->right->boundingBox);
    }

    return node;
}

bool KDTree::hit(const Ray& r, const double tmin, const double tmax, HitInfo &data) const
{
    data.t = tmax;

    if (_root_node)
        return _root_node->hit(r, tmin, tmax, data);

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
    bool hit_first = false, hit_second = false;

    if (first)
    {
        hit_first = first->hit(r, tmin, tmax_buffer, data);

        if (hit_first)
            tmax_buffer = data.t;
    }

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

void KDTree::KDNode::update()
{
    if (left)
    {
        left->update();
        boundingBox = left->boundingBox;
    }

    if (!left && right)
    {
        right->update();
        boundingBox = right->boundingBox;
    }
    else if (left && right)
    {
        right->update();
        boundingBox.expand(right->boundingBox);
    }

    if (objects.size())
    {
        boundingBox = objects[0]->boundingBox();

        for (auto& object : objects)
            boundingBox.expand(object->boundingBox());

        return;
    }
}


void KDTree::delete_node(const double min_x, const double min_y, const double max_x, const double max_y)
{
    _root_node = _root_node->delete_node(min_x, min_y, max_x, max_y);
    update();
}

void KDTree::insert_node(std::shared_ptr<Object> object)
{
    _root_node = _root_node->insert_node(object);
    update();
}


std::shared_ptr<KDTree::KDNode> KDTree::KDNode::insert_node(std::shared_ptr<Object> object)
{
    Vector3D min = boundingBox.min();
    Vector3D max = boundingBox.max();
    Vector3D center = object->center();

    if (min.x() <= center.x() && min.y() <= center.y() && min.z() <= center.z() &&
                    max.x() >= center.x() && max.y() >= center.y() && max.z() >= center.z())
    {

        if (objects.size() > 0)
        {
            objects.emplace_back(object);
        }
        else
        {
            Vector3D l_min = left->boundingBox.min();
            Vector3D l_max = left->boundingBox.max();

            if (l_min.x() <= center.x() && l_min.y() <= center.y() && l_min.z() <= center.z() &&
                    l_max.x() >= center.x() && l_max.y() >= center.y() && l_max.z() >= center.z())
                left = left->insert_node(object);
            else
                right = right->insert_node(object);
        }
    }

    return shared_from_this();
}

bool KDTree::KDNode::validate_bounding_box_in_params(const double min_x, const double min_y, const double max_x,
                                                     const double max_y, const BoundingBox &box)
{
    Vector3D min = box.min();
    Vector3D max = box.max();

    if (min.x() <= min_x && min.y() <= min_y && max.x() >= max_x && max.y() >= max_y)
        return true;

    return false;
}

bool KDTree::KDNode::validate_params_in_boinding_box(const double min_x, const double min_y, const double max_x,
                                                     const double max_y, const BoundingBox &box)
{
    Vector3D min = box.min();
    Vector3D max = box.max();

    if (min.x() >= min_x && min.y() >= min_y && max.x() <= max_x && max.y() <= max_y && max.z() > 0)
        return true;

    return false;
}

std::shared_ptr<KDTree::KDNode> KDTree::KDNode::delete_node(const double min_x, const double min_y, const double max_x, const double max_y)
{
    if (max_x < boundingBox.min().x() ||  max_y < boundingBox.min().y() ||
            min_x > boundingBox.max().x() || min_y > boundingBox.max().y())
        return shared_from_this();

    if (objects.size() == 0)
    {
        if (right)
            right = right->delete_node(min_x, min_y, max_x, max_y);
        if (left)
            left = left->delete_node(min_x, min_y, max_x, max_y);

        if (right == nullptr && left == nullptr)
            return nullptr;
    }
    else
    {
        size_t i = 0;

        while (i < objects.size() &&
               !validate_params_in_boinding_box(min_x, min_y, max_x, max_y, objects[i]->boundingBox()))
            i++;

        if (i < objects.size())
        {
            objects.erase(objects.begin() + i);

            if (!objects.size())
                return nullptr;
        }
    }

    return shared_from_this();
}
