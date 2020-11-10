#pragma once
#include <iostream>
#include <iostream>
#include <vector>
#include <string>

namespace state
{
using namespace std;

class CombinationLock
{
    enum STATE
    {
        LOCKED,
        OPEN,
        ERROR
    };

    vector<int> combination;

public:

    string status;

    CombinationLock(const vector<int>& combination) : combination(combination) 
    {
        set_state(LOCKED);
    }

    void set_state(STATE state)
    {
        switch (state)
        {
            case CombinationLock::LOCKED:
                status = "LOCKED";
                break;
            case CombinationLock::OPEN:
                status = "OPEN";
                break;
            case CombinationLock::ERROR:
                status = "ERROR";
                break;
            default:
                break;
        }
    }

    bool compare_combination()
    {
        if (combination.size() != status.size())
            return false;
        else
        {
            for (int i = 0; i < combination.size(); i++)
            {
                int k = status[i] - 48;
                if (combination[i] != k)
                    return false;
            }       
        }
        return true;
    }

    void enter_digit(int digit)
    {
        // TODO
        if (status == "LOCKED")
            status.clear();

        status += to_string(digit);
        if (compare_combination())
        {
            set_state(OPEN);
        }
        else if (status.size() >= combination.size())
        {
            set_state(ERROR);
        }
    }
};


}
