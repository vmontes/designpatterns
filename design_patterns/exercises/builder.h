#pragma once
#include <string>
#include <tuple>
#include <list>
#include <ostream>

namespace builder
{
using namespace std;

class CodeBuilder
{
public:
    CodeBuilder(const string& class_name)
    {
        _class_name = class_name;
    }

    CodeBuilder& add_field(const string& name, const string& type)
    {
        // todo
        _fields.push_back(make_pair(name, type));
        return *this;
    }

    friend ostream& operator<<(ostream& os, const CodeBuilder& obj)
    {
        // todo
        os << "class " << obj._class_name << endl << "{" << endl;
        for (auto& i : obj._fields)
        {
            os << "  " << i.second << " " << i.first << ";" << endl;
        }
        os << "};" << endl;
        return os;
    }

protected:
    string _class_name;
    list<pair<string, string>> _fields;

};
}

