#include <cmath>

#include "ImageFilter.h"

#define _USE_MATH_DEFINES

namespace cg
{
    namespace filter
    {
        namespace
        {
            /** Computes and stores gaussian values in given kernel for the given sigma value */
            void setGaussianValues(Kernel& k, float sigma)
            {
                ///////
                // TODO
                //
                // Implement the computation of gaussian filter kernel values
                // and store them in k:
                // 1. Iterate over the 2D kernel and compute the individual
                //    values/ entries.
                // 2. Sum up all values of the kernel.
                // 3. Normalize the filter kernel values with the accumulated
                //    sum.
                float sum = 0.0f;

                const float norm_factor = 1 / (2 * M_PI * sigma * sigma);

                const auto vert_range = k.getVerticalRange();
                const auto hor_range = k.getHorizontalRange();
                
                // Compute the individual entries and their sum
                // ...
                for (int y{vert_range.first}; y <= vert_range.second; ++y)
                {
                    for (int x{hor_range.first}; x <= hor_range.second; ++x)
                    {
                        float exponent = - (x*x + y*y)/(2*sigma*sigma);
                        float gauss_value = norm_factor * exp(exponent);
                        k.setValue(x, y, gauss_value);
                        sum += gauss_value;
                    }
                }
                
                // Normalize the filter kernel
                // ...
                for (int y{vert_range.first}; y <= vert_range.second; ++y)
                {
                    for (int x{hor_range.first}; x <= hor_range.second; ++x)
                    {
                        float gauss_value = k.getValue(x, y);
                        k.setValue(x, y, gauss_value / sum);
                    }
                }
            }
        }

        Kernel::Kernel(std::pair<unsigned int, unsigned int> extents)
            : m_data((std::get<0>(extents) * 2 + 1)* (std::get<1>(extents) * 2 + 1)), m_extents(extents)
        {
            std::fill(m_data.begin(), m_data.end(), 0.0f);
            setValue(0, 0, 1.0f);
        }

        float Kernel::getValue(int x, int y) const
        {
            return m_data[getDataIndex(x, y)];
        }

        float* Kernel::data()
        {
            return m_data.data();
        }

        float const* Kernel::data() const
        {
            return m_data.data();
        }

        std::pair<int, int> Kernel::getHorizontalRange() const
        {
            return std::make_pair(-static_cast<int>(std::get<0>(m_extents)), static_cast<int>(std::get<0>(m_extents)));
        }

        std::pair<int, int> Kernel::getVerticalRange() const
        {
            return std::make_pair(-static_cast<int>(std::get<1>(m_extents)), static_cast<int>(std::get<1>(m_extents)));
        }

        void Kernel::setValue(int x, int y, float v)
        {
            m_data[getDataIndex(x, y)] = v;
        }

        size_t Kernel::getDataIndex(int x, int y) const
        {
            x += std::get<0>(m_extents);
            y += std::get<1>(m_extents);

            return y * (std::get<0>(m_extents) * 2 + 1) + x;
        }


        Kernel build2DGaussianKernel(std::pair<unsigned int, unsigned int> extents, float sigma)
        {
            Kernel k(extents);

            setGaussianValues(k, sigma);

            return k;
        }

        Kernel build1DHorizontalGaussianKernel(unsigned int extent, float sigma)
        {
            Kernel k(std::make_pair(extent, 0));

            setGaussianValues(k, sigma);

            return k;
        }

        Kernel build1DVerticalGaussianKernel(unsigned int extent, float sigma)
        {
            Kernel k(std::make_pair(0, extent));

            setGaussianValues(k, sigma);

            return k;
        }

        Kernel buildEdgeDetectionKernel()
        {
            Kernel k(std::make_pair(1, 1));

            ///////
            // TODO
            // Construct an edge detection kernel
            k.setValue(-1, -1, 0.0f);
            k.setValue(1, 1, 0.0f);
            k.setValue(-1, 1, 0.0f);
            k.setValue(1, -1, 0.0f);

            k.setValue(0, -1, -1.0f);
            k.setValue(-1, 0, -1.0f);
            k.setValue(0, 1, -1.0f);
            k.setValue(1, 0, -1.0f);

            k.setValue(0, 0, 4.0f);
            // ...

            return k;
        }
    }
}
