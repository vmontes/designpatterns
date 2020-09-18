#pragma once
#include <map>
#include <string>

namespace interpreter
{
using namespace std;

struct ExpressionProcessor
{
    enum op_t {none, sum, sub, num};
    map<char, int> variables;

    int calculate(const string& expression)
    {
        // TODO
        int value = 0;
        op_t op = none;
        for (int i = 0; i < expression.size(); i++)
        {
            char c = expression[i];
            switch (expression[i])
            {
                case '+':
                    if (op != sum)
                        op = sum;
                    else
                        return 0;
                break;
                case '-':
                    if (op != sub)
                        op = sub;
                    else
                        return 0;
                break;
                default:
                {
                    if (op == num)
                        return 0;
                    op = num;
                    int dval;
                    int k;
                    const auto& it = variables.find(c);
                    if (it != variables.end())
                    {
                        dval = it->second;
                        k = i + 1;
                    }
                    else
                    {
                        k = i;
                        for (; k < expression.size(); k++)
                        {
                            if (!isdigit(expression[k]))
                                break;
                        }

                        string tmp(&expression[i], &expression[k]);
                        dval = atoi(tmp.c_str());
                    }
                    if (op == sum)
                    {
                        value += dval;
                    }
                    else if (op == sub)
                    {
                        value -= dval;
                    }
                    else
                    {
                        value += dval;
                    }
                    i = k-1;
                }
            }
        }
        return value;
    }
};
}