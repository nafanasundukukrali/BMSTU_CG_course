#include "utils/vector3d/vector3d.h"
#include "utils/ray/ray.h"

class BoundingBox
{
public:
    BoundingBox() = default;
    BoundingBox(const Vector3D min, const Vector3D max): _min(min), _max(max) {};

    Vector3D min() const;
    Vector3D max() const;

    void expand(const BoundingBox &box);
    bool validate_intersect(const Ray &r) const;

private:
    Vector3D _min;
    Vector3D _max;
};
