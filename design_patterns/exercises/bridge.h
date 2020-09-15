#pragma once
#include <string>

namespace bridge
{
using namespace std;

struct Renderer
{
    virtual string what_to_render_as() const = 0;
};

struct RasterRenderer : Renderer
{
    virtual string what_to_render_as() const { return string(" as pixels"); };
};

struct VectorRenderer : Renderer
{
    virtual string what_to_render_as() const { return string(" as lines"); };
};

struct Shape
{
    Shape(const Renderer& rend) : renderer(rend) {};
    string name;

    string str() const
    {
        return "Drawing " + name + renderer.what_to_render_as();
    };

    const Renderer& renderer;
};

struct Circle : Shape
{
    Circle(const Renderer& rend) : Shape(rend)
    {
        name = "Circle";
    };
};

struct Square : Shape
{
    Square(const Renderer& rend) : Shape(rend)
    {
        name = "Square";
    };
};

struct Triangle : Shape
{
    Triangle(const Renderer& rend) : Shape(rend)
    {
        name = "Triangle";
    };
};
}


// imagine e.g. VectorTriangle/RasterTriangle etc. here