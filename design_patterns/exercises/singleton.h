#pragma once
#include <functional>

namespace singleton
{
using namespace std;

struct SingletonTester
{
    template <typename T>
    bool is_singleton(function<T* ()> factory)
    {
        // TODO
        T* i1 = factory();
        T* i2 = factory();
        return (i1 == i2);
    }
};
}