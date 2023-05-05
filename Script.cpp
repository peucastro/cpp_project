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
    void Script::invert()
    {
        for (int i = 0; i < image->width(); i++)
        {
            for (int j = 0; j < image->height(); j++)
            {
                Color inv(255 - image->at(i, j).red(), 255 - image->at(i, j).green(), 255 - image->at(i, j).blue());
                image->at(i, j) = inv;
            }
        }
    }
    void Script::to_gray_scale()
    {
        for (int i = 0; i < image->width(); i++)
        {
            for (int j = 0; j < image->height(); j++)
            {
                rgb_value v = (image->at(i, j).red() + image->at(i, j).green() + image->at(i, j).blue()) / 3;
                image->at(i, j) = Color(v, v, v);
            }
        }
    }
    void Script::replace()
    {
        Color c1, c2;
        input >> c1 >> c2;

        for (int i = 0; i < image->width(); i++)
        {
            for (int j = 0; j < image->height(); j++)
            {
                if (image->at(i, j).red() == c1.red() && image->at(i, j).green() == c1.green() && image->at(i, j).blue() == c1.blue())
                    image->at(i, j) = c2;
            }
        }
    }
    void Script::fill()
    {
        int x, y, w, h;
        Color c;
        input >> x >> y >> w >> h >> c;

        for (int i = x; i < x + w; i++)
        {
            for (int j = y; j < y + h; j++)
            {
                image->at(i, j) = c;
            }
        }
    }
    void Script::h_mirror()
    {
        for (int i = 0; i < image->width() / 2; i++)
        {
            for (int j = 0; j < image->height(); j++)
            {
                Color *c = new Color;
                *c = image->at(i, j);
                image->at(i, j) = image->at(image->width() - 1 - i, j);
                image->at(image->width() - 1 - i, j) = *c;
                delete c;
            }
        }
    }
    void Script::v_mirror()
    {
        for (int i = 0; i < image->width(); i++)
        {
            for (int j = 0; j < image->height() / 2; j++)
            {
                Color *c = new Color;
                *c = image->at(i, j);
                image->at(i, j) = image->at(i, image->height() - 1 - j);
                image->at(i, image->height() - 1 - j) = *c;
                delete c;
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

        for (int i = x; i < x + w; i++)
        {
            for (int j = y; j < y + h; j++)
            {
                new_image->at(x_new, y_new) = image->at(i, j);
                y_new++;
            }
            y_new = 0;
            x_new++;
        }

        delete image;
        image = new_image;
    }
    void Script::rotate_left()
    {
        Image *new_image = new Image(image->height(), image->width());

        for (int i = 0; i < image->width(); i++)
        {
            for (int j = 0; j < image->height(); j++)
                new_image->at(j, image->width() - i - 1) = image->at(i, j);
        }
        delete image;
        image = new_image;
    }
    void Script::rotate_right()
    {
        Image *new_image = new Image(image->height(), image->width());

        for (int i = 0; i < image->width(); i++)
        {
            for (int j = 0; j < image->height(); j++)
                new_image->at(image->height() - j - 1, i) = image->at(i, j);
        }
        delete image;
        image = new_image;
    }
}
