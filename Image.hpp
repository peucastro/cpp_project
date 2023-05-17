#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"

namespace prog
{
    /*
    represents an image using a bidirectional array, where each 
    pixel is represented as a Color object (previously implemented)
    */
    class Image
    {
    private:
        int w; //image width variable
        int h; //image height variable
        Color **img; //pointer to a bidirectional array of colors (the image itself)

    public:
        Image(int w, int h, const Color &fill = {255, 255, 255}); //constructor with arguments
        ~Image(); //destructor
        int width() const; //returns the image width
        int height() const; //returns the image height
        Color &at(int x, int y); //returns the color at a certain pixel (coordinate)
        const Color &at(int x, int y) const; //modifies the color at a certain pixel (coordinate)
    };
}
#endif
