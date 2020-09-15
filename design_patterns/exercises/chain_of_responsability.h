#pragma once
#include <vector>
#include <assert.h>
#include <iostream>
#include <string>

namespace chain
{
using namespace std;

struct Creature;
struct Game
{
    vector<Creature*> creatures;
};

struct StatQuery
{
    enum Statistic { attack, defense } statistic;
    int result;
};

struct Creature
{
protected:
    Game& game;
    int base_attack, base_defense;

public:
    Creature(Game& game, int base_attack, int base_defense) : game(game), base_attack(base_attack),
        base_defense(base_defense) {}
    virtual int get_attack() = 0;
    virtual int get_defense() = 0;
    virtual void UpdateStat(StatQuery& q) = 0;
};

class Goblin : public Creature
{
public:
    Goblin(Game& game, int base_attack, int base_defense) : Creature(game, base_attack, base_defense) {}

    Goblin(Game& game) : Creature(game, 1, 1) {}

    virtual void UpdateStat(StatQuery& q)
    {
        if (q.statistic == StatQuery::defense)
        {
            q.result++;
        }
    }

    int get_attack() override {
        // todo
        StatQuery q;
        q.result = base_attack;
        q.statistic = StatQuery::attack;
        for (auto& c : game.creatures)
        {
            if (c != this)
            {
                c->UpdateStat(q);
            }
        }

        return q.result;

    }

    int get_defense() override {
        // todo
        StatQuery q;
        q.result = base_defense;
        q.statistic = StatQuery::defense;
        for (auto& c : game.creatures)
        {
            if (c != this)
            {
                UpdateStat(q);
            }
        }
        return q.result;
    }
};

class GoblinKing : public Goblin
{
public:
    GoblinKing(Game& game) : Goblin(game, 3, 3) {}

    // todo

    virtual void UpdateStat(StatQuery& q)
    {
        if (q.statistic == StatQuery::attack)
        {
            q.result++;
        }

        Goblin::UpdateStat(q);
    }
};
}

