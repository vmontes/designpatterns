#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <numeric>

namespace composite
{
using namespace std;

struct ContainsIntegers
{
    virtual int sum() = 0;
};

struct SingleValue : ContainsIntegers
{
    int value{ 0 };

    SingleValue() = default;

    explicit SingleValue(const int value)
        : value{ value }
    {
    }

    // TODO
    int sum() { return value; };
};

struct ManyValues : vector<int>, ContainsIntegers
{
    void add(const int value)
    {
        push_back(value);
    }

    int sum()
    {
        return std::accumulate(begin(), end(), 0);
    }
};

int sum(const vector<ContainsIntegers*> items)
{
    // TODO
    int r = 0;
    for (const auto& it : items)
    {
        r += it->sum();
    }
    return r;
}
}