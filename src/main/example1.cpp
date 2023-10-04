/**
 * @file example1.cpp
 * @author Massimo Mattelliano (mattemax@yahoo.com)
 * @brief
 * Basic usage of StrongUnit header.
 * @copyright Copyright (c) 2022
 * MIT License
 */

#include "src/lib/StrongUnit.h"
#include <vector>

using namespace stu::literals;
using namespace stu::symbols;

/**
 *  Customized quantity and unit definitions without additional headers
 **/
namespace stu
{
    DEF_SCALE(unity, 1U)
    DEF_SCALE(kilo, 1000U)
    DEF_SCALE(s2min, 60U)
    DEF_SCALE(kmph2mps, 1000U, 3600U)

    DEF_QUANTITY(Number) // each quantity is ideally defined by base numbers with rational exponents,
                         // Number must be represented by (b0^0)*...*(b9^0)
    DEF_UNIT(Number, number, float, _, unity)

    DEF_QUANTITY(Time, std::ratio<1>) // Time can be represented by (b0^1)*(b1^0)*...*(b9^0), only the first ratio needs to be inputted
    DEF_UNIT(Time, second, float, _s, unity)
    DEF_UNIT(Time, minute, float, _min, s2min)

    DEF_QUANTITY(Length, std::ratio<0>, std::ratio<1>) // Length can be represented by (b0^0)*(b1^1)*(b2^0)*...*(b9^0), only the first two ratios need to be inputted
    DEF_UNIT(Length, meter, float, _m, unity)
    DEF_UNIT(Length, kilometer, float, _km, kilo)

    DEF_QUANTITY(Velocity, std::ratio<-1>, std::ratio<1>) // this defines a derived quantity, i.e. combination of other quantities
    DEF_UNIT(Velocity, meter_second, float, _mps, unity)
    DEF_UNIT(Velocity, kilometer_hour, float, _kmph, kmph2mps)

    DEF_QUANTITY(Acceleration, std::ratio<-2>, std::ratio<1>) // this defines a derived quantity, i.e. combination of other quantities
    DEF_UNIT(Acceleration, meter_per_second_sq, float, _mps2, unity)
}

const auto gravityAcceleration = 9.81_mps2; // using literals
const float greek_pi = 3.14159;

stu::second getPendulumPeriod_std(const stu::meter &length); // computes simple pendulum period using std math function
stu::second getPendulumPeriod_stu(const stu::meter &length); // computes simple pendulum period using stu math function

void computeVelocityExample()
{
    stu::meter s;
    std::cout << "\n Compute velocity ... ";
    std::cout << "\n insert space (meters) : ";
    std::cin >> s;
    s.print();

    stu::second t;
    std::cout << "\n insert time (seconds) : ";
    std::cin >> t;
    t.print();

    std::cout << "\n The velocity is : \n";
    auto v = s / t;
    stu::kilometer_hour w = v;
    v.print();
    w.print();
}

void ComputePendulumPeriodExample()
{
    stu::meter l;
    std::cout << "\n Compute the period of a pendulum ... ";
    std::cout << "\n insert pendulum length (meters) : ";
    std::cin >> l;
    l.print();

    auto t = getPendulumPeriod_std(l);
    std::cout << "\n The period of the pendulum is (seconds) : \n";
    t.print();

    t = getPendulumPeriod_stu(l);
    std::cout << "\n The new period of the pendulum is (seconds) : \n";
    t.print();

    std::cout << "\n The period (minutes) : \n";
    stu::minute m = t;
    m.print();
    std::cout << "\n";
}

/**
 * @brief Basic example of strong units
 */
int main()
{
    std::cout << "  \nExample1\n\n";

    computeVelocityExample();
    ComputePendulumPeriodExample();

    stu::kilometer space = 3.0_mps * 2.0_s; // using strong unit literals
    std::cout << "space: ";
    space.print();

    stu::kilometer_hour vel = 2 * _m / _s; // using strong unit symbols
    std::cout << "vel: ";
    vel.print();

    auto numb = 2.0_km / (1 * _m); // using strong unit  literals and symbols
    std::cout << "numb: ";
    numb.print();

    auto new_quantity = 1.0_mps2 * 2.0_m;
    std::cout << "new_quantity: ";
    new_quantity.print();

    std::cout << "\n Vector of meters: \n";
    std::vector<stu::meter> lung{1.0_km, 2.0_m, 3.0_m};
    for (auto const &m : lung)
        m.print();

    std::cout << "\n Increments: \n";
    stu::meter s{1.0};
    stu::meter sa{0.0};
    auto velox = 50.0_kmph;
    for (stu::second t{}; t < 10.0_s; ++t)
    {
        s += (velox + 10.0_kmph) * t;
        sa += gravityAcceleration * stu::pow<2>(t);

        std::cout << "\n ------ \n";
        s.print();
        sa.print();
    }
}

stu::second getPendulumPeriod_std(const stu::meter &length)
{
    auto sec_squared_res = length / gravityAcceleration;             // this returns second squared automatically defined unit
    stu::second res{2.0f * greek_pi * std::sqrt(sec_squared_res())}; // operator() returns the wrapped type
    return res;
}

stu::second getPendulumPeriod_stu(const stu::meter &length)
{
    return 2.0f * greek_pi * stu::sqrt(length / gravityAcceleration); // using stu function
}