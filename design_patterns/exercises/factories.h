#pragma once
#include <string>

namespace factories
{
using namespace std;

struct Person
{
    int id;
    string name;
};

class PersonFactory
{
    int last_id;

public:

    PersonFactory() : last_id(0) {};

    Person create_person(const string& name)
    {
        // todo
        return { last_id++,name };
    }
};
}
