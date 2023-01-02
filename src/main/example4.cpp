/**
 * @file example4.cpp
 * @author Massimo Mattelliano (mattemax@yahoo.com)
 * @brief
 * Basic usage of NonSIBaseUnits and SISpecialDerivedUnits headers
 * @copyright Copyright (c) 2022
 * MIT License
 */

#include "src/lib/StrongTypeDefinition.h"
#include "src/lib/NonSIBaseUnits.h"
#include "src/lib/SISpecialDerivedUnits.h"

using namespace stu::literals;
using namespace stu::symbols;
using namespace stu::prefixes;

/**
 *  Quantity and unit definitios only from headers
 **/

void computeImpedence()
{
    std::cout << "ComputeImpedence\n";
    auto I = 2.0*m_*_A;
    std::cout << " I = ";
    I.print();

    auto V = 3.0_V;
    std::cout << " V = ";
    V.print();

    stu::ohm Z = V / I;
    std::cout << " Z = ";
    Z.print();

    stu::watt P = V * I;
    std::cout << " V*I = ";
    P.print();

    auto PP = Z*stu::pow<2>(I);
    std::cout << " Z*I^2 = ";
    PP.print();
}

void computeNonSIunit()
{
    std::cout << "ComputeNonSIunit\n";
    stu::second t1 = _min;
    std::cout << "1 min as seconds : ";
    t1.print();

    stu::second t2 = _h;
    std::cout << "1 hour as seconds : ";
    t2.print();

    stu::second t3 = _d;
    std::cout << "1 day as seconds : ";
    t3.print();

    stu::radian angle = 360 * _deg;
    std::cout << "360° as radiants : ";
    angle.print();

    stu::square_meter a = _ha;
    std::cout << "1 hectare as m^2 : ";
    a.print();

    stu::cubic_meter l = _L;
    std::cout << " 1 Liter as m^3 : ";
    l.print();

    stu::kilogram ww = _t;
    std::cout << " 1 tonne as kg : ";
    ww.print();
}

int main()
{
    std::cout << "  \nExample4\n";

    computeNonSIunit();
    computeImpedence();

    auto w1 = 1.0_kg;
    auto w2 = 1 * k_ * _g;
    auto d1 = 1 * k_ * _gpm3;
    auto d2 = 1.0_kgpm3;
    auto dd1 = 1 * k_ * _gpm2;
    auto dd2 = 1.0_kgpm2;

    std::cout << "Compute others\n";
    stu::meter_per_second speed = 3.6*k_*_m/_h;
    std::cout << " 3.6kph as mps : ";
    speed.print();

    auto f1 = _rad / _s;
    std::cout << " 1 rad/s : ";
    f1.print();

    stu::radian_per_second f2 = 1 / _s;
    std::cout << " 1 Hz as rad/s : ";
    f2.print();

    auto t_sqrt = stu::sqrt(2*_s);
    std::cout << " sqrt(2s) = ";
    t_sqrt.print();

    auto t = stu::pow<2>(t_sqrt);
    std::cout << " [sqrt(2s)]^2 = ";
    t.print();
}