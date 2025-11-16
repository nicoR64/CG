#include "ImageConverter.hpp"

#include <cmath>

cg::image<cg::color_space_t::HSV> cg::image_converter::rgb_to_hsv(const image<color_space_t::RGB>& original)
{
    // Convert RGB to HSV
    cg::image<cg::color_space_t::HSV> converted(original.get_width(), original.get_height());

    for (unsigned int j = 0; j < original.get_height(); ++j)
    {
        for (unsigned int i = 0; i < original.get_width(); ++i)
        {
            const float r = original(i, j)[0];
            const float g = original(i, j)[1];
            const float b = original(i, j)[2];

            const float c_max = std::max(std::max(r, g), b);
            const float c_min = std::min(std::min(r, g), b);
            const float delta = c_max - c_min;

            float h = 0.f, s = 0.f, v = 0.f;

            ////////
            // TODO:
            // Implement the conversion from RGB to HSV as described in
            // https://de.wikipedia.org/wiki/HSV-Farbraum#Umrechnung_RGB_in_HSV/HSL

            // ...
            if (delta == 0) {
                h = 0;
            }
            else if (c_max == r) {
                h = 60.f * ((g - b) / delta);
            }
            else if (c_max == g) {
                h = 60.f * (2 + (b - r) / delta);
            }
            else if (c_max == b) {
                h = 60.f * (4 + (r - g) / delta);
            }
            if (h < 360) {
                h += 360;
            }
            h /= 360;

            s = c_max == c_min ? 0 : (c_max - c_min) / c_max;

            v = c_max;

            converted(i, j)[0] = h;
            converted(i, j)[1] = s;
            converted(i, j)[2] = v;
        }
    }

    return converted;
}

cg::image<cg::color_space_t::RGB> cg::image_converter::hsv_to_rgb(const image<color_space_t::HSV>& original)
{
    // Convert HSV to RGB
    image<color_space_t::RGB> converted(original.get_width(), original.get_height());

    for (unsigned int j = 0; j < original.get_height(); ++j)
    {
        for (unsigned int i = 0; i < original.get_width(); ++i)
        {
            const float h = original(i, j)[0];
            const float s = original(i, j)[1];
            const float v = original(i, j)[2];

            float r = 0.f, g = 0.f, b = 0.f;

            ////////
            // TODO:
            // Implement the conversion from HSV to RGB as described in
            // https://de.wikipedia.org/wiki/HSV-Farbraum#Umrechnung_HSV_in_RGB

            // ...
            int h_i = std::floor(h * 6); // H = |_ h * 360 / 60 _|
            float f = h * 6 - h_i;
            float p = v * (1 - s);
            float q = v * (1 - s * f);
            float t = v * (1 - s * (1 - f));

            switch (h_i % 6)
            {
            case 0:
                r = v;
                g = t;
                b = p;
                break;

            case 1:
                r = q;
                g = v;
                b = p;
                break;

            case 2:
                r = p;
                g = v;
                b = t;
                break;

            case 3:
                r = p;
                g = q;
                b = v;
                break;

            case 4:
                r = t;
                g = p;
                b = v;
                break;

            case 5:
                r = v;
                g = p;
                b = q;
                break;

            default:
                break;
            }

            converted(i, j)[0] = r;
            converted(i, j)[1] = g;
            converted(i, j)[2] = b;
        }
    }

    return converted;
}

cg::image<cg::color_space_t::Gray> cg::image_converter::rgb_to_gray(const image<color_space_t::RGB>& original)
{
    // Convert RGB to grayscale
    image<color_space_t::Gray> converted(original.get_width(), original.get_height());

    ////////
    // TODO:
    // Implement the conversion from RGB to grayscale using the luminance
    // approximation formula presented in the lecture.

    for (unsigned int j = 0; j < original.get_height(); ++j)
    {
        for (unsigned int i = 0; i < original.get_width(); ++i)
        {
            converted(i, j)[0] = original(i, j)[0] * 0.299 + original(i, j)[1] * 0.587 + original(i, j)[2] * 0.114;
        }
    }

    return converted;
}

cg::image<cg::color_space_t::BW> cg::image_converter::gray_to_bw(const image<color_space_t::Gray>& original)
{
    // Convert grayscale to black and white
    image<color_space_t::BW> converted(original.get_width(), original.get_height());

    ////////
    // TODO:
    // Implement the conversion from grayscale to black and white such that
    // luminance values < 0.5 are mapped to black (0.0) and values >= 0.5
    // are mapped to white (1.0).

    for (unsigned int j = 0; j < original.get_height(); ++j)
    {
        for (unsigned int i = 0; i < original.get_width(); ++i)
        {
            auto grayscale = original(i, j)[0] * 0.299 + original(i, j)[1] * 0.587 + original(i, j)[2] * 0.114;
            converted(i, j)[0] = grayscale < 0.5 ? 0 : 1;
        }
    }

    return converted;
}
