#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"

namespace prog
{
    /*
    Represents an image using a bidirectional array, where each 
    pixel is represented as a Color object (previously implemented).
    */
    class Image
    {
    private:
        // Image width variable.
        int w;
        // Image height variable.
        int h;
        // Pointer to a bidirectional array of colors (the image itself).
        Color **img;

    public:
        // Constructor with arguments (an image width, height and a color to fill).
        Image(int w, int h, const Color &fill = {255, 255, 255});
        // Destructor.
        ~Image();
        // Returns the image width.
        int width() const;
        // Returns the image height.
        int height() const;
        // Returns the color at a certain pixel (coordinate).
        Color &at(int x, int y);
        // Modifies the color at a certain pixel (coordinate).
        const Color &at(int x, int y) const; 
    };
}
#endif
