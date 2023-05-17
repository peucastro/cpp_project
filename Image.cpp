#include "Image.hpp"

namespace prog
{
    Image::Image(int w, int h, const Color &fill) // Constructor with arguments implementation.
    {
        this->w = w; // Sets the image width (data member this->w) with the constructor parameter w.
        this->h = h; // Sets the image height (data member this->h) with the constructor parameter h.
        img = new Color *[w]; // Creates the image first row with the size of the image width (w).

        for (int i = 0; i < w; i++) // One cycle to go through all pixels in width.
        {
            Color *column = new Color[h]; // Creates an array of colors (column) with the size of the image height (h) using dynamic memory.
            for (int j = 0; j < h; j++) // One cycle to go through all pixels in height.
            {
                column[j] = fill; // Sets all pixels in the array with the color provided in the constructor (fill).
            }
            img[i] = column; // Sets the image currnt column with the array column.
        }
    }
    Image::~Image()
    {
        for (int i = 0; i < w; i++) // Iterates through all the image columns. 
        {
            delete[] img[i]; // Deletes the columns each at a time.
        }
        delete[] img; // Deletes the image first row.
    }
    int Image::width() const
    {
        return this->w; // Returns the image width (data member w).
    }
    int Image::height() const
    {
        return this->h; // Returns the image height (data member h).
    }
    Color &Image::at(int x, int y)
    {
        return img[x][y]; // Modifies the color of the image in a certain position (x is used for the width coordinate and y for the height).
    }
    const Color &Image::at(int x, int y) const
    {
        return img[x][y]; // Returns the color of the image in a certain position (x is used for the width coordinate and y for the height).
    }
}
