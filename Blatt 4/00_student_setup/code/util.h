#ifndef util_h
#define util_h

#include <cassert>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "vec3.h"

static int state = { 42 };

/**
 * @brief Simple Ray class. A ray is defined with an origin and a direction.
 */
class Ray
{
public:
    Ray() : origin(Vec3d()), dir(Vec3d()), depth(0) {}
    ~Ray() {}

    Vec3d origin;   //< Orinin of the ray
    Vec3d dir;      //< Direction of the ray.
    int depth;      //< Recursive depth of the ray.
};


//////////////////////////////// Random number generation ////////////////////////////////
/**
 * @brief Own rand() implementation for cross platform deterministc 'randomness'.
 * @return pseudo random number
 */
static unsigned long cpRand()
{
    int const a = 1103515245;
    int const c = 12345;
    state = a * state + c;
    return (state >> 16) & 0x7FFF;
}

/**
 * @brief Generate a pseudorandom number in range [0,1] using the Mersenne Twister.
 * @return A random number in range [0,1] from a uniform distribution.
 */
static double getRand()
{
    std::mt19937 mtGen(cpRand());
    std::uniform_real_distribution<> distribNorm(0.0, 1.0);
    return distribNorm(mtGen);
}


/////////////////////////////////// PPM Image handling ///////////////////////////////////
/**
 * @brief Compare two PPM images pixelwise.
 *        This is a convenient method for testing your results.
 *        Note that only rudamentory error checking/assertions are implemented!
 *
 * @param referenceFileName The reference file to compare against.
 * @param testName The name of the test (here: ray generation resp. sphere intersection)
 * @param framebuffer The framebuffer containing the rendered pixel data.
 */
static void comparePPM(const std::string referenceFileName, const std::string testName,
    const std::vector<Vec3d>& framebuffer)
{
    std::ifstream file(referenceFileName.c_str(), std::ios::in | std::ios::binary);
    if (file.is_open())
    {
        size_t width = 0;
        size_t height = 0;
        std::string magicNumber = "";
        std::string maxValue = "";

        // read header
        file >> magicNumber >> width >> height >> maxValue;
        assert(width * height == framebuffer.size());
        assert(magicNumber == "P6");
        assert(maxValue == "255");

        std::vector<char> pixel_data;
        pixel_data.resize(width * height * 3);

        file.ignore(256, '\n');
        file.read(reinterpret_cast<char*>(pixel_data.data()),
            static_cast<std::streamsize>(pixel_data.size()));

        size_t cnt = 0;
        for (size_t i = 0; i < framebuffer.size(); ++i)
        {
            Vec3d color = Vec3d::clamp(0., 255., framebuffer.at(i));
            if ((pixel_data.at(i * 3 + 0) != static_cast<char>(255 * color[0])) +
                (pixel_data.at(i * 3 + 1) != static_cast<char>(255 * color[1])) +
                (pixel_data.at(i * 3 + 2) != static_cast<char>(255 * color[2])))
                ++cnt;
        }
        if (cnt > 0.001 * framebuffer.size()) // 0.1% tolerance
        {
            std::cout << cnt * 100 / framebuffer.size()
                << "% of the pixel values did not match the reference image in the "
                << testName << "." << std::endl;
        }
        else
        {
            std::cout << "Looks like a perfect match for the " << testName << "!" << std::endl;
        }
        file.close();
    }
    else
    {
        std::cerr << "Somethiong went wrong during comparison to the reference image "
            << referenceFileName << std::endl;
        std::cerr << "Did you check the path to the reference images?" << std::endl;
    }
}

/**
 * @brief Save an array of color values as a PPM image.
 * @param name The file name of the ppm file.
 * @param viewport The size of the viewport.
 * @param framebuffer Framebuffer containing the color values.
 */
static void saveAsPPM(const std::string name, const Vec3i viewport,
    const std::vector<Vec3d>& framebuffer)
{
    if (framebuffer.size() != size_t(viewport[0]) * viewport[1])
    {
        std::cerr << "Invalid framebuffer size, could not write out image." << std::endl;
        return;
    }

    std::ofstream os(name, std::ios::out | std::ios::binary);
    os << "P6\n" << viewport[0] << " " << viewport[1] << "\n255\n";
    for (size_t i = 0; i < framebuffer.size(); ++i)
    {
        Vec3d color = Vec3d::clamp(0., 1., framebuffer.at(i));
        char r = static_cast<char>(255 * color[0]);
        char g = static_cast<char>(255 * color[1]);
        char b = static_cast<char>(255 * color[2]);
        os << r << g << b;
    }
    os.close();
}

#endif // !util_h
