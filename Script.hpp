#ifndef __prog_Script_hpp__
#define __prog_Script_hpp__

#include <string>
#include <fstream>
#include "Image.hpp"

namespace prog
{
    // Representation of a commands manipulated on an image.
    class Script
    {
    public:
        Script(const std::string &filename);
        ~Script();
        void run();

    private:
        // Current image.
        Image *image;
        // Input stream for reading script commands.
        std::ifstream input;

    private:
        // Private functions
        void clear_image_if_any();
        void open();
        void blank();
        void save();
        // void function to invert each pixel in the image.
        void invert();
        // void function to transform the color of the image into grey.
        void to_gray_scale();
        //void function to switch the color of the image.
        void replace();
        // void function to fill the area with the specific color.
        void fill();
        // void function to invert the pictire horizontally.
        void h_mirror();
        // void function to invert the pictire vertically.
        void v_mirror();
        // void function to add the file image to a certain position(x,y).
        void add();
        // void function to reduce the size of the image.
        void crop();
        // void function to rotate the image to the left.
        void rotate_left();
        // void function to rotate the image to the right.
        void rotate_right();
    };
}
#endif
