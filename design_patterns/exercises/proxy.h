#pragma once
#include <string>

namespace proxy
{
using namespace std;

class Person
{
    friend class ResponsiblePerson;
    int age;
public:
    Person(int age) : age(age) {}

    int get_age() const { return age; }
    void set_age(int age) { this->age = age; }

    string drink() const { return "drinking"; }
    string drive() const { return "driving"; }
    string drink_and_drive() const { return "driving while drunk"; }
};

class ResponsiblePerson
{
public:

    ResponsiblePerson(const Person& person) : person(person) {}
    // todo

    int get_age() const { return person.age; }
    void set_age(int age) { person.age = age; }

    string too_young() const
    {
        return "too young";
    }

    string dead() const
    {
        return "dead";
    }

    string drink() const
    {
        if (person.age >= 18)
            return person.drink();
        else
            return too_young();

    }
    string drive() const
    {
        if (person.age >= 16)
            return person.drive();
        else
            return too_young();
    }

    string drink_and_drive() const
    {
        return dead();
    }
private:
    Person person;
};
}