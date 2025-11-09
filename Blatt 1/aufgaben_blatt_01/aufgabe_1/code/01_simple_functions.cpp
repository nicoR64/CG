#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

///////
// TODO
// Write a function that computes the area of a circle given its radius as input.
float circlearea(float radius) {
    return M_PI * pow(radius, 2);
}

int main() {
    float radius;

    std::cout << "Insert circle radius:" << std::endl;

    ///////
    // TODO
    // Get user input from the command line and store it in radius.
    // Check if input is valid.
    std::cin >> radius;
    if (std::cin.fail()) {
        std::cout << "No valid floating point number was provided as input." << std::endl;
        return 1;
    }
    else if (radius < 0) {
        std::cout << "The provided radius cannot be negative." << std::endl;
        return 1;
    }

    ///////
    // TODO
    // Call the function circlearea and output the computed value to the command line.
    std::cout << "The circle has an area of: " << circlearea(radius) << std::endl;

    return 0;
}
