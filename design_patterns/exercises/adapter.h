#pragma once

namespace adapter
{

struct Square
{
    int side{ 0 };


    explicit Square(const int side)
        : side(side)
    {
    }
};

struct Rectangle
{
    virtual int width() const = 0;
    virtual int height() const = 0;

    int area() const
    {
        return width() * height();
    }
};

struct SquareToRectangleAdapter : Rectangle
{
    SquareToRectangleAdapter(const Square& square)
    {
        // todo
        _width = square.side;
        _height = square.side;
    }

    // todo
    int _width, _height;

    int width() const { return _width; };
    int height() const { return _height; };
};

}