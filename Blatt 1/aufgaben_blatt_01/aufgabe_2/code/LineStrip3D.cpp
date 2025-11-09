#include "LineStrip3D.hpp"
#include <cmath>
#include <iostream>

bool LineStrip3D::operator<(LineStrip3D const& rhs) const
{
    ///////
    // TODO
    // Implement comparison based on length.
    return computeLength() < rhs.computeLength();
}

void LineStrip3D::addPoint(Point3D p)
{
    ///////
    // TODO
    // Implement adding a given point to the line strip.
    strip.push_back(p);
}

void LineStrip3D::removePoint(size_t idx)
{
    ///////
    // TODO
    // Implement the removal of the point with the given index.
    if (idx < getPointCount()) {
        auto it = strip.cbegin();
        std::advance(it, idx);
        strip.erase(it);
    }
    else {
        std::cout << "The provided index is out of bounds." << std::endl;
    }
}

size_t LineStrip3D::getPointCount() const
{
    ///////
    // TODO
    // Return the number of points of the line strip.
    return strip.size();
}

float LineStrip3D::computeLength() const
{
    ///////
    // TODO
    // Implement computation of the line strip's length,
    // that is, the sum of the lengths of all segements.
    float len = 0.0F;
    auto prev_it = strip.begin();
    for (auto curr_it = std::next(strip.begin()); curr_it != strip.end(); ++curr_it) {
        len += calculate_distance(*curr_it, *prev_it);
        prev_it = curr_it;
    }
    return len;
}

float LineStrip3D::calculate_distance(const Point3D& curr, const Point3D& prev) const
{
    return sqrt(pow(curr.x() - prev.x(), 2) + pow(curr.y() - prev.y(), 2) + pow(curr.z() - prev.z(), 2));
}
