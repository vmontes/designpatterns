#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

namespace flyweight
{
using namespace std;

struct Sentence
{
    vector<string> words;

    struct WordToken
    {
        bool capitalize;
    };

    vector<WordToken> tokens;

    Sentence(const string& text)
    {
        // todo
        istringstream f(text);
        string tmp;
        while (getline(f, tmp, ' '))
        {
            words.push_back(tmp);
            tokens.push_back({ false });
        };
    }

    WordToken& operator[](size_t index)
    {
        // todo
        return tokens[index];
    }

    string str() const
    {
        // todo
        string ret;
        for (int i = 0; i < words.size(); i++)
        {
            if (tokens[i].capitalize)
            {
                string s = words[i];
                transform(s.begin(), s.end(), s.begin(), (int(&)(int))::toupper);
                ret += s;
            }
            else
            {
                ret += words[i];
            }
            ret += " ";
        }
        ret.erase(ret.end() - 1, ret.end());
        return ret;
    }
};
}