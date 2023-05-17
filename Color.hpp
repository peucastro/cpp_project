#ifndef __prog_Color_hpp__
#define __prog_Color_hpp__

namespace prog
{
    typedef unsigned char rgb_value; // Defines the type rgb_value holding values from 0 to 255 (the RGB spectrum).
    
    /*
    Represents colors using primary colors red, green and blue with 8-bits per RGB channel.
    Also implemented functions to obtain, modify and compare these values.
    */
    class Color
    {
    private:
        // Color's red rgb_value.
        rgb_value r;
        // Color's green rgb_value.
        rgb_value g;
        // Color's blue rgb_value.
        rgb_value b;

    public:
        // Default constructor, creates the color black.
        Color();
        // Copy constructor.
        Color(const Color &c);
        // Constructor with arguments (arguments red, green and blue).
        Color(rgb_value r, rgb_value g, rgb_value b);
        
        // Gets the red RGB channel value.
        rgb_value red() const;
        // Sets the red RGB channel value.
        rgb_value &red();
        
        // Gets the green RGB channel value.
        rgb_value green() const;
        // Sets the green RGB channel value.
        rgb_value &green();
        
        // Gets the blue RGB channel value.
        rgb_value blue() const;
        // Sets the green RGB channel value.
        rgb_value &blue();
           
        // Operator for equality comparison between 2 colors.
        bool operator==(const Color &other) const;
        // Operator for difference comparison between 2 colors.
        bool operator!=(const Color &other) const;
    };
}
#endif
