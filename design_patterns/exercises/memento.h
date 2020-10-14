#pragma once
#include <iostream>
#include <vector>
#include <memory>

namespace memento
{
using namespace std;

struct Token
{
    int value;

    Token(int value) : value(value) {}
};

struct Memento
{
    vector<shared_ptr<Token>> tokens;
};

struct TokenMachine
{
    vector<shared_ptr<Token>> tokens;

    Memento add_token(int value)
    {
        return add_token(make_shared<Token>(value));
    }

    // adds the token to the set of tokens and returns the
    // snapshot of the entire system
    Memento add_token(const shared_ptr<Token>& token)
    {
        // todo
        auto p = token;
        tokens.push_back(p);
        Memento m;
        for (const auto& it : tokens)
        {
            m.tokens.push_back(make_shared<Token>(it->value));
        }
        return m;
    }

    // reverts the system to a state represented by the token
    void revert(const Memento& m)
    {
        // todo
        tokens.clear();
        for (auto& it : m.tokens)
        {
            tokens.push_back(it);
        }
    }
};
}