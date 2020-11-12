#pragma once
#include <iostream>
#include <vector>
#include <complex>
#include <tuple>

namespace template_method
{
using namespace std;

struct Creature
{
    int attack, health;

    Creature(int attack, int health) : attack(attack), health(health) {}
};

struct CardGame
{
    vector<Creature> creatures;

    CardGame(const vector<Creature>& creatures) : creatures(creatures) {}

    // return the index of the creature that won (is a live)
    // example:
    // - creature1 alive, creature2 dead, return creature1
    // - creature1 dead, creature2 alive, return creature2
    // - no clear winner: return -1
    int combat(int creature1, int creature2)
    {
        // todo
        Creature& c1 = creatures[creature1];
        Creature& c2 = creatures[creature2];
        hit(c1, c2);
        hit(c2, c1);

        if ((c1.health > 0) || (c2.health > 0))
        {
            if (c1.health <= 0)
                return creature2;
            else if (c2.health <= 0)
                return creature1;
            else
                return -1;
        }
        
        return -1;
    }

    virtual void hit(Creature& attacker, Creature& other) = 0;
};

struct TemporaryCardDamageGame : CardGame
{
    TemporaryCardDamageGame(const vector<Creature>& creatures) : CardGame(creatures) {}

    void hit(Creature& attacker, Creature& other) override 
    {
        // todo
        int health = other.health;
        other.health -= attacker.attack;
        if (other.health > 0)
            other.health = health;
    }
};

struct PermanentCardDamageGame : CardGame
{
    PermanentCardDamageGame(const vector<Creature>& creatures) : CardGame(creatures) {}

    void hit(Creature& attacker, Creature& other) override
    {
        // todo
        other.health -= attacker.attack;
    }
};
}
