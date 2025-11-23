#include "sceneobject.h"

#include "util.h"
#include "vec3.h"

#include <cmath>
#include <utility>

/**
 * @brief SceneObject::SceneObject
 */
SceneObject::SceneObject() :
    _color(1.0, 1.0, 1.0)
{
}

/**
 * @brief SceneObject::SceneObject
     * @param color Color of the object, if it is not overwritten by the derived class.
 */
SceneObject::SceneObject(const Vec3d& color) :
    _color(color)
{
}

/**
 * @brief Plane::intersect
 */
bool Plane::intersect(const Ray &ray, double &t) const
{
    double denom = this->_normal.dot(ray.dir);

    // check if parallel
    if (!Vec3d::approxEq(denom, 0.))
    {
        const Vec3d origin2point = this->_point - ray.origin;

        t = origin2point.dot(this->_normal) / denom;

        return (t >= 0.);
    }

    return false;
}

/**
 * @brief Plane::getSurfaceColor
 * @param p_hit point where the surface was hit
 */
Vec3d Plane::getSurfaceColor(const Vec3d &p_hit) const
{
    // generate grey/white chess board pattern
    const double pi = std::acos(-1);

    const double freq = 0.125;
    const double s = cos(p_hit[0] * 2.0 * pi * freq) * cos(p_hit[2] * 2.0 * pi * freq);

    return Vec3d(0.2) + (s > 0) * Vec3d(0.4);
}


/**
 * @brief Sphere::intersect
 * @param ray Reference to the ray to be checked for intersection with objects.
 * @param t Reference to the intersection distance along the ray.
 */
bool Sphere::intersect(const Ray &ray, double &t) const
{
    Vec3d delta = ray.origin - _center;

    double A = ray.dir.dot(ray.dir);
    double B = 2.0 * ray.dir.dot(delta);
    double C = delta.dot(delta) - (_radius * _radius);
    double discriminant = B * B - 4 * A * C;

    if (discriminant < 0.0)
    {
        return false;
    }

    //Schnittpunkte berechnen 
    double sqrtD = std::sqrt(discriminant);
    double t1 = (-B - sqrtD) / (2.0 * A);
    double t2 = (-B + sqrtD) / (2.0 * A);

    //Suche kleinsten positiven Schnittpunkt
    if (t1 > 0.0f) 
    {
        t = t1;
        return true;
    } 
    else if (t2 > 0.0f) 
    {
        t = t2;
        return true;
    }

    ///////////
    // TODO
    // Implement a ray-sphere intersection test.
    //
    // cf., lecture slides raytracing 37ff
    return false;
    // END TODO
    ///////////
}

/**
 * @brief Sphere::getSurfaceColor
 */
Vec3d Sphere::getSurfaceColor(const Vec3d &p_hit) const
{
    return this->_color;
}
