#include "Point3D.hpp"
#include "LineStrip3D.hpp"

#include <iostream>
#include <array>
#include <list>
#include <vector>
#include <algorithm>
#include "01_stl.h"

void print_all_strip_lengths(std::vector<LineStrip3D>& strips) {
    for (const LineStrip3D& strip : strips) {
        std::cout << strip.computeLength() << std::endl;
    }
}

int main()
{

    ///////
    // TODO
    // Create a container for linestrips
    std::vector<LineStrip3D> strips;

    ///////
    // TODO
    // Add three linestrips to the container and add a couple of points to each linestrip
    LineStrip3D a;
    Point3D p_1{ 0.0F, 3.8F, 4.56F };
    Point3D p_2{ 5.0F, 7.236F, 6.0F };
    Point3D p_3{ 3.789F, 10.0F, -4.57F };
    a.addPoint(p_1);
    a.addPoint(p_2);
    a.addPoint(p_3);
    strips.push_back(a);

    LineStrip3D b;
    Point3D p_4{ 1.0F, 1.0F, 1.0F };
    Point3D p_5{ 4.0F, 5.0F, 6.0F };
    Point3D p_6{ 7.0F, 8.0F, 9.0F };
    b.addPoint(p_4);
    b.addPoint(p_5);
    b.addPoint(p_6);
    strips.push_back(b);

    LineStrip3D c;
    Point3D p_7{ -2.0F, 4.0F, 1.5F };
    Point3D p_8{ 0.0F, 0.0F, 0.0F };
    Point3D p_9{ 2.5F, -3.4F, 8.0F };
    c.addPoint(p_7);
    c.addPoint(p_8);
    c.addPoint(p_9);
    strips.push_back(c);

    std::cout << "==================================" << std::endl;
    std::cout << "Length of all linestrips:" << std::endl;

    ///////
    // TODO
    // Print the length of all line strips on the command line
    print_all_strip_lengths(strips);

    std::cout << "==================================" << std::endl;
    std::cout << "Length of all linestrips (sorted):" << std::endl;

    ///////
    // TODO
    // Sort the line strips in the container based on their length.
    // For validation, print the lengths of all linestrips on the command line one more time.
    std::sort(strips.begin(), strips.end());

    print_all_strip_lengths(strips);

    return 0;
}
