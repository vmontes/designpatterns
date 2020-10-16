#pragma once
#include <iostream>
#include <unordered_set>
using namespace std;

namespace observer
{
class Game;
class IRat
{
    int attack{ 1 };

public:

    int GetAttack() 
    {
        return attack;
    }

    void AdjustAttack(int new_attack)
    {
        attack = new_attack;
    }
};

class Game
{
    // todo
    unordered_set<IRat*> playing_rats;

    void AdjustAtacks()
    {
        int new_attack = (int)playing_rats.size();
        for (auto& it : playing_rats)
            it->AdjustAttack(new_attack);
    }

public:

    void GetInto(IRat* rat)
    {
        playing_rats.insert(rat);
        AdjustAtacks();
    }

    void GetOut(IRat* rat)
    {
        playing_rats.erase(rat);
        AdjustAtacks();
    }
};

struct Rat : IRat
{
    Game& game;

    Rat(Game& game) : game(game)
    {
        // todo, obviously
        game.GetInto(this);
    }

    ~Rat()
    {
        // rat dies here!
        game.GetOut(this);
    }
};
}
