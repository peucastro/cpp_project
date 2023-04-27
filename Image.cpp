#include "Image.hpp"

namespace prog
{
    Image::Image(int w, int h, const Color &fill)
    {
        this->w = w;
        this->h = h;
        img = new Color *[w];

        for (int i = 0; i < w; i++)
        {
            Color *column = new Color[h];
            for (int j = 0; j < h; j++)
            {
                column[j] = fill;
            }
            img[i] = column;
        }
    }
    Image::~Image()
    {
        for (int i = 0; i < w; i++)
        {
            delete[] img[i];
        }
        delete[] img;
    }
    int Image::width() const
    {
        return this->w;
    }
    int Image::height() const
    {
        return this->h;
    }

    Color &Image::at(int x, int y)
    {
        return img[x][y];
    }

    const Color &Image::at(int x, int y) const
    {
        return img[x][y];
    }
}
