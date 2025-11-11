#include "ImageConverter.hpp"

#include <cmath>

cg::image<cg::color_space_t::HSV> cg::image_converter::rgb_to_hsv(const image<color_space_t::RGB> &original)
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

            v = c_max;

            if (c_max > 0.f)
            {
                s = delta / c_max;
            }
            else
            {
                s = 0.f;
            }

            if (delta == 0.f)
            {
                h = 0.f;
            }
            float h_prime;
            if (c_max == r)
            {
                h_prime = (g - b) / delta;
            }
            else if (c_max == g)
            {
                h_prime = 2.f + (b - r) / delta;
            }
            else // c_max == b
            {
                h_prime = 4.f + (r - g) / delta;
            }

            h = h_prime / 6.f;
            if (h < 0.f)
            {
                h += 1.f;
            }
            converted(i, j)[0] = h;
            converted(i, j)[1] = s;
            converted(i, j)[2] = v;
        }
    }

    return converted;
}

cg::image<cg::color_space_t::RGB> cg::image_converter::hsv_to_rgb(const image<color_space_t::HSV> &original)
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

            if (s == 0.f)
            {
                r = v;
                g = v;
                b = v;
            }
            else
            {
                float h_scaled = h * 6.f;
                if (h_scaled >= 6.f)
                    h_scaled = 0.f;

                const int h_i = static_cast<int>(std::floor(h_scaled));
                const float f = h_scaled - h_i;
                const float p = v * (1.f - s);
                const float q = v * (1.f - f * s);
                const float t = v * (1.f - (1.f - f) * s);

                switch (h_i)
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
            }
            converted(i, j)[0] = r;
            converted(i, j)[1] = g;
            converted(i, j)[2] = b;
        }
    }

    return converted;
}

cg::image<cg::color_space_t::Gray> cg::image_converter::rgb_to_gray(const image<color_space_t::RGB> &original)
{
    // Convert RGB to grayscale
    image<color_space_t::Gray> converted(original.get_width(), original.get_height());

    ////////
    // TODO:
    // Implement the conversion from RGB to grayscale using the luminance
    // approximation formula presented in the lecture.
    // geht hier von den vertikalen pixeln aus und iteriert dann über die horizontalen pixel, heißt wir bauen das Bild zeilenweise auf

    for (unsigned int j = 0; j < original.get_height(); ++j)
    {
        for (unsigned int i = 0; i < original.get_width(); ++i)
        {
            const float r = original(i, j)[0];
            const float g = original(i, j)[1];
            const float b = original(i, j)[2];

            float l = 0.f;

            l = 0.2126f * r + 0.7152f * g + 0.0722f * b;
            converted(i, j)[0] = l;
        }
    }

    return converted;
}

cg::image<cg::color_space_t::BW> cg::image_converter::gray_to_bw(const image<color_space_t::Gray> &original)
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
            float l = original(i, j)[0];
            converted(i, j)[0] = (l < 0.5f) ? 0.0f : 1.0f;
        }
    }

    return converted;
}
