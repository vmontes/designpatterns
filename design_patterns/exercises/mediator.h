#pragma once
#include <vector>

namespace mediator
{
struct IParticipant
{
    virtual void say(int value) = 0;
    virtual void listen(int value) = 0;
};

struct Mediator
{
    std::vector<IParticipant*> participants;

    void broadcast(IParticipant* p, int n)
    {
        for (auto& i : participants)
        {
            if (i != p)
                i->listen(n);
        }
    }
};

struct Participant : IParticipant
{
    int value{ 0 };
    Mediator& mediator;

    Participant(Mediator& mediator) : mediator(mediator)
    {
        mediator.participants.push_back(this);
    }

    void say(int value)
    {
        // todo
        mediator.broadcast(this, value);
    }

    void listen(int value)
    {
        // todo
        this->value += value;
    }
};
}
