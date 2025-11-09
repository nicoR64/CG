#ifndef LineStrip3D_hpp
#define LineStrip3D_hpp

#include <array>
#include <list>
#include <vector>

#include "Point3D.hpp"

class LineStrip3D
{
public:
    /** Comparison operator. */
    bool operator<(LineStrip3D const& rhs) const;

    /** Adds a point to the end of the line strip. */
    void addPoint(Point3D p);

    /** Removes the point from the line strip with the given index. */
    void removePoint(size_t idx);

    /** Returns the number of points that make up the line strip. */
    size_t getPointCount() const;

    /** Returns the length of the line strip, that is, the sum of the lengths of all segements.*/
    float computeLength() const;


private:
    ///////
    // TODO
    // Add a container for storing the line strip's points
    std::list<Point3D> strip;

    float calculate_distance(const Point3D& curr, const Point3D& prev) const;
};

#endif // !LineStrip3D_hpp
