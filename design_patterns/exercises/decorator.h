#pragma once
#include <iostream>
#include <string>

namespace decorator
{
using namespace std;

struct Flower
{
    bool isblue;
    bool isred;
    virtual string str() = 0;

    Flower() : isblue(false), isred(false) {};
};

struct Rose : Flower
{
    Rose() : Flower() {};
    string str() override {
        // todo
        return "A rose";
    };
};

struct RedFlower : Flower
{
    Flower& flower;
    RedFlower(Flower& _flower) : Flower(), flower(_flower)
    {
        isred = true;
        isblue = _flower.isblue;
    };

    string str() override {
        // todo
        string ret = flower.str();
        if (!flower.isred)
        {
            if (flower.isblue)
            {
                ret += " and red";
            }
            else
            {
                ret += " that is red";
            }
        }
        return ret;
    };
};

struct BlueFlower : Flower
{
    Flower& flower;
    BlueFlower(Flower& _flower) : Flower(), flower(_flower)
    {
        isblue = true;
        isred = _flower.isred;
    };
    string str() override {
        // todo
        string ret = flower.str();
        if (!flower.isblue)
        {
            if (flower.isred)
            {
                ret += " and blue";
            }
            else
            {
                ret += " that is blue";
            }
        }
        return ret;
    };
};
}