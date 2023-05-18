#include <iostream>
#include <fstream>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"

using namespace std;

namespace prog
{
    // Use to read color values from a script file.
    istream &operator>>(istream &input, Color &c)
    {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string &filename) : image(nullptr), input(filename)
    {
    }

    void Script::clear_image_if_any()
    {
        if (image != nullptr)
        {
            delete image;
            image = nullptr;
        }
    }

    Script::~Script()
    {
        clear_image_if_any();
    }

    void Script::run()
    {
        string command;
        while (input >> command)
        {
            cout << "Executing command '" << command << "' ..." << endl;
            if (command == "open")
            {
                open();
                continue;
            }
            if (command == "blank")
            {
                blank();
                continue;
            }
            // Other commands require an image to be previously loaded.
            if (command == "save")
            {
                save();
                continue;
            }
            if (command == "invert")
            {
                invert();
                continue;
            }
            if (command == "to_gray_scale")
            {
                to_gray_scale();
                continue;
            }
            if (command == "replace")
            {
                replace();
                continue;
            }
            if (command == "fill")
            {
                fill();
                continue;
            }
            if (command == "h_mirror")
            {
                h_mirror();
                continue;
            }
            if (command == "v_mirror")
            {
                v_mirror();
                continue;
            }
            if (command == "add")
            {
                add();
                continue;
            }
            if (command == "crop")
            {
                crop();
                continue;
            }
            if (command == "rotate_left")
            {
                rotate_left();
                continue;
            }
            if (command == "rotate_right")
            {
                rotate_right();
                continue;
                ;
            }
        }
    }

    void Script::open()
    {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }

    void Script::blank()
    {
        // Replace current image (if any) with blank image.
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }

    void Script::save()
    {
        // Save current image to PNG file.
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }

    void Script::invert() // Inverts the intensity of the color in the current image.
    {
        for (int i = 0; i < image->width(); i++) // One cycle to go through all pixels in width.
        {
            for (int j = 0; j < image->height(); j++) // One cycle to go through all pixels in height.
            {
                Color inv(255 - image->at(i, j).red(), 255 - image->at(i, j).green(), 255 - image->at(i, j).blue()); // Inverts all values of color in the current image.
                image->at(i, j) = inv;                                                                               // The inverted color is distributed to each pixel.
            }
        }
    }

    void Script::to_gray_scale() // Turns the current image's color into tones of gray.
    {
        for (int i = 0; i < image->width(); i++) // One cycle to go through all pixels in width.
        {
            for (int j = 0; j < image->height(); j++) // One cycle to go through all pixels in height.
            {
                // Creation of a value that corresponds to the average of the color values according to the cycles above.
                rgb_value v = (image->at(i, j).red() + image->at(i, j).green() + image->at(i, j).blue()) / 3;
                image->at(i, j) = Color(v, v, v); // Turns every pixel's color into the corresponding average.
            }
        }
    }

    void Script::replace() // Replaces one color for another.
    {
        Color c1, c2;
        input >> c1 >> c2; // Insertion of the two desired colors.

        for (int i = 0; i < image->width(); i++) // One cycle to go through all pixels in width.
        {
            for (int j = 0; j < image->height(); j++) // One cycle to go through all pixels in height.
            {
                // Verification if each pixel corresponds to the first color according to the cycles above.
                if (image->at(i, j).red() == c1.red() && image->at(i, j).green() == c1.green() && image->at(i, j).blue() == c1.blue())
                    image->at(i, j) = c2; // Replacement of the first color to the second color.
            }
        }
    }

    void Script::fill() // Fills the the desired area with a especific color.
    {
        int x, y, w, h;
        Color c;
        // Insertion of the values that determine the coordinates of the origin, the width, the height and the color that fills the desired area, respectively.
        input >> x >> y >> w >> h >> c;

        for (int i = x; i < x + w; i++) // One cycle to go through all pixels in the width of the area.
        {
            for (int j = y; j < y + h; j++) // One cycle to go through all pixels in the height of the area.
            {
                image->at(i, j) = c; // Redefinition of the color in each pixel inside the desired area.
            }
        }
    }

    void Script::h_mirror() // Inverts the current image horizontally.
    {
        for (int i = 0; i < image->width() / 2; i++) // One cycle to go through all pixels in one half of the width.
        {
            for (int j = 0; j < image->height(); j++) // One cycle to go through all pixels in height.
            {
                Color *c = new Color; // Copy of the color of every pixel according to the cycles above using dinamic memory.
                *c = image->at(i, j);
                image->at(i, j) = image->at(image->width() - 1 - i, j); // Reverts the order of every pixel according to the corresponding width.
                image->at(image->width() - 1 - i, j) = *c;              // The color is distributed to each inverted pixel according to the width.
                delete c;                                               // Delete the copy.
            }
        }
    }

    void Script::v_mirror() // Inverts the current image vertically.
    {
        for (int i = 0; i < image->width(); i++) // One cycle to go through all pixels in width.
        {
            for (int j = 0; j < image->height() / 2; j++) // One cycle to go through all pixels in one half of the height.
            {
                Color *c = new Color; // Copy of the color of every pixel according to the cycles above using dinamic memory.
                *c = image->at(i, j);
                image->at(i, j) = image->at(i, image->height() - 1 - j); // Reverts the order of every pixel according to the corresponding height.
                image->at(i, image->height() - 1 - j) = *c;              // The color is distributed to each inverted pixel according to the height.
                delete c;                                                // Delete the copy.
            }
        }
    }

    void Script::add()
    {
        string filename;
        Color neutral;
        int x, y;
        input >> filename >> neutral >> x >> y;

        Image *file = loadFromPNG(filename);
        int x_file = 0;
        int y_file = 0;

        for (int i = x; i < x + file->width(); i++)
        {
            for (int j = y; j < y + file->height(); j++)
            {
                if (file->at(x_file, y_file) != neutral)
                    image->at(i, j) = file->at(x_file, y_file);
                y_file++;
            }
            y_file = 0;
            x_file++;
        }
        delete file;
    }

    void Script::crop()
    {
        int x, y, w, h;
        input >> x >> y >> w >> h;

        Image *new_image = new Image(w, h);
        int x_new = 0;
        int y_new = 0;

        for (int i = x; i < x + w; i++) // One cycle to go through all pixels in the width of the area.
        {
            for (int j = y; j < y + h; j++) // One cycle to go through all pixels in the height of the area.
            {
                new_image->at(x_new, y_new) = image->at(i, j);
                y_new++;
            }
            y_new = 0;
            x_new++;
        }

        delete image;      // Delete the current image.
        image = new_image; // The copy turns into the current image.
    }

    void Script::rotate_left() // Rotates the current image ninety degrees to the left.
    {
        Image *new_image = new Image(image->height(), image->width()); // Copy of the current image using dinamic memory.

        for (int i = 0; i < image->width(); i++) // One cycle to go through all pixels in width.
        {
            for (int j = 0; j < image->height(); j++)                       // One cycle to go through all pixels in height.
                new_image->at(j, image->width() - i - 1) = image->at(i, j); // The coordinates of every pixel invert and the height becomes dependent of the width of each pixel.
        }
        delete image;      // Delete the current image.
        image = new_image; // The copy turns into the current image.
    }

    void Script::rotate_right() // Rotates the current image ninety degrees to the right.
    {
        Image *new_image = new Image(image->height(), image->width()); // Copy of the current image using dinamic memory.

        for (int i = 0; i < image->width(); i++) // One cycle to go through all pixels in width.
        {
            for (int j = 0; j < image->height(); j++)                        // One cycle to g through all pixels in height.
                new_image->at(image->height() - j - 1, i) = image->at(i, j); // The coordinates of every pixel invert and the width becomes dependent of the height of each pixel.
        }
        delete image;      // Delete the current image.
        image = new_image; // The copy turns into the current image.
    }
}

