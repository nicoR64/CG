#ifndef Point3D_hpp
#define Point3D_hpp

#include <array>
#include <list>
#include <vector>

struct Point3D
{
    ///////
    // TODO
    // Implement the constructor
    Point3D(double x, double y, double z) {
        coords[0] = x;
        coords[1] = y;
        coords[2] = z;
    }

    ///////
    // TODO
    // Implement access to the three coordinate values.
    double x() const { 
        return coords[0];
    }
    
    double y() const {
        return coords[1];
    }

    double z() const {
        return coords[2];
    }

private:
    ///////
    // TODO
    // Use a suitable STL container to store the three values of a point in 3d space.
    std::array<double, 3> coords;

};

#endif // !Point3D_hpp
