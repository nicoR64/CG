#include "ColorSpaces.hpp"

#include "Image.hpp"
#include "ImageIO.hpp"
#include "ImageConverter.hpp"
#include "ImageManipulation.hpp"

#include <exception>
#include <iostream>
#include <string>

int main(const int argc, const char** argv)
{
    // Read command line arguments
    if (argc != 3)
    {
        std::cerr << "Error: No input and output file specified" << std::endl;
        std::cout << "Call program with parameters <source> <target>" << std::endl << std::endl;

        return 1;
    }

    std::string source_file(argv[1]);
    std::string target_file(argv[2]);

    std::cout << "Source file: " << source_file << std::endl;
    std::cout << "Target file: " << target_file << std::endl << std::endl;

    // Ask user to execute one of the exercises
    unsigned int exercise;
    std::cout << "Select exercise [1-4]: ";
    std::cin >> exercise;

    switch (exercise)
    {
    case 1:
        aufgabe1(source_file, target_file);
        break;
    case 2:
        aufgabe2(source_file, target_file);
        break;
    case 3:
        aufgabe3(source_file, target_file);
        break;
    case 4:
        aufgabe4(source_file, target_file);
        break;
    default:
        std::cerr << "Invalid exercise: " << exercise << std::endl;
    }

    return 0;
}

void aufgabe1(const std::string& source_file, const std::string& target_file)
{
    try
    {
        ////////
        // TODO:
        // 1. Load the RGB input image using a function from image_io
        // 2. Convert the image to grayscale using the image_converter class
        // 3. Save the grayscale image to the given target file path using
        //    a function from image_io
        auto rgbImage = cg::image_io::load_rgb_image(source_file);
        auto grayImage = cg::image_converter::rgb_to_gray(rgbImage);
        cg::image_io::save_grayscale_image(target_file, grayImage);

        std::cout << "File successfully created" << std::endl << std::endl;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown error" << std::endl;
    }
}

void aufgabe2(const std::string& source_file, const std::string& target_file)
{
    try
    {
        ////////
        // TODO:
        // 1. Load the grayscale input image using a function from image_io
        // 2. Convert the image to black & white using the image_converter
        //    class
        // 3. Save the grayscale image to the given target file path using
        //    a function from image_io

        auto grayImage = cg::image_io::load_grayscale_image(source_file);
        auto bwImage = cg::image_converter::gray_to_bw(grayImage);
        cg::image_io::save_bw_image(target_file, bwImage);

        std::cout << "File successfully created" << std::endl << std::endl;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown error" << std::endl;
    }
}

void aufgabe3(const std::string& source_file, const std::string& target_file)
{
    try
    {
        ////////
        // TODO:
        // 1. Load the RGB input image using a function from image_io
        // 2. Convert the RGB image to HSV using the image_converter class
        // 3. Convert the HSV image back to RGB using the image_converter class
        // 4. Save the RGB image to the given target file path using a
        //    function from image_io
        auto rgbImage = cg::image_io::load_rgb_image(source_file);
        auto hsvImage = cg::image_converter::rgb_to_hsv(rgbImage);
        auto convertedRgbImage = cg::image_converter::hsv_to_rgb(hsvImage);
        cg::image_io::save_rgb_image(target_file, convertedRgbImage);

        std::cout << "File successfully created" << std::endl << std::endl;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown error" << std::endl;
    }
}

void aufgabe4(const std::string& source_file, const std::string& target_file)
{
    try
    {
        ////////
        // TODO:
        // 1. Load the RGB input image using a function from image_io
        // 2. Convert the RGB image to HSV using the image_converter class
        // 3. Apply a color-key-effect to the image in HSV color space
        //    with a function from the image_manipulation class
        // 4. Convert the modified HSV image back to RGB using the
        //    image_converter class
        // 5. Save the modified RGB image to the given target file path using a
        //    function from image_io

        auto rgbImage = cg::image_io::load_rgb_image(source_file);
        auto hsvImage = cg::image_converter::rgb_to_hsv(rgbImage);
        auto modifiedHsvImage = cg::image_manipulation::modify_in_hsv(hsvImage);
        auto convertedRgbImage = cg::image_converter::hsv_to_rgb(modifiedHsvImage);
        cg::image_io::save_rgb_image(target_file, convertedRgbImage);

        std::cout << "File successfully created" << std::endl << std::endl;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Unknown error" << std::endl;
    }
}
