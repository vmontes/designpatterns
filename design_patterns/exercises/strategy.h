#pragma once
#include <iostream>
#include <vector>
#include <complex>
#include <tuple>
#include <cmath>

namespace strategy
{
using namespace std;

struct DiscriminantStrategy
{
    virtual double calculate_discriminant(double a, double b, double c) = 0;
};

struct OrdinaryDiscriminantStrategy : DiscriminantStrategy
{
    // todo

    virtual double calculate_discriminant(double a, double b, double c)
    {
        double ret = (b * b) - (4 * a * c);
        return ret;
    }
};

struct RealDiscriminantStrategy : DiscriminantStrategy
{
    // todo
    virtual double calculate_discriminant(double a, double b, double c)
    {
        double ret = (b * b) - (4 * a * c);
        if (ret < 0)
            return nan("");
        else
            return ret;
    }
};

class QuadraticEquationSolver
{
    DiscriminantStrategy& strategy;
public:
    QuadraticEquationSolver(DiscriminantStrategy& strategy) : strategy(strategy) {}

    tuple<complex<double>, complex<double>> solve(double a, double b, double c)
    {
        // todo
        double discriminant = strategy.calculate_discriminant(a, b, c);

        complex<double> tmp = { discriminant, 0 };
        complex<double> root = sqrt(tmp);
        complex<double> retp;
        complex<double> retm;
        retp = ((-b) + root) / (2 * a);
        retm = ((-b) - root) / (2 * a);
        return { retp, retm };
    }
};
}
