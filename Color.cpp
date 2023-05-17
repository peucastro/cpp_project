#include "Color.hpp"

namespace prog
{
    Color::Color() // Default constructor implementation.
    {
        r = 0; // Sets the red (r) data member to 0.
        g = 0; // Sets the green (g) data member to 0.
        b = 0; // Sets the blue (b) data member to 0.
    }
    Color::Color(const Color &other) // Copy constructor implementation.
    {
        r = other.r; // Sets the red (r) data member with the copied color's ref value (other.r).
        g = other.g; // Sets the green (g) data member with the copied color's green value (other.g).
        b = other.b; // Sets the blue (b) data member with the copied color's blue value (other.r).
    }
    Color::Color(rgb_value red, rgb_value green, rgb_value blue) // Constructor with arguments implementation.
    {
        r = red; // Sets the red (r) data member with the function argument red.
        g = green; // Sets the green (g) data member with the function argument green.
        b = blue; // Sets the blue (b) data member with the function argument blue.
    }
    
    rgb_value Color::red() const // Red value's accessor implementation.
    {
        return r; // Returns data member r (red RGB channel).
    }
    rgb_value Color::green() const // Green value's accessor implementation.
    {
        return g; // Returns data member g (green RGB channel).
    }
    rgb_value Color::blue() const // Blue value's accessor implementation.
    {
        return b; // Returns data member b (blue RGB channel).
    }
    
    rgb_value &Color::red() // Red value's modifier implementation.
    {
        return r; // Returns a reference to the data member r (red RGB channel).
    }
    rgb_value &Color::green() // Green value's modifier implementation.
    {
        return g; // Returns a reference to the data member g (green RGB channel).
    }
    rgb_value &Color::blue() // Blue value's modifier implementation.
    {
        return b; // Returns a reference to the data member b (blue RGB channel).
    }
    
    bool Color::operator==(const Color &other) const // Equality operator implementation
    {
        if (r == other.r && g == other.g && b == other.b) // Checks if all the channels have equal RGB values.
            return true; // If the condition satisfies, returns true.
        return false; // Otherwise, returns false.
    }
    bool Color::operator!=(const Color &other) const // Difference operator implementation.
    {
        if (r != other.r || g != other.g || b != other.b) // Checks if any of the channels differs.
            return true; // If the condition satisfies, returns true.
        return false; // Otherwise, returns false.
    }
}
