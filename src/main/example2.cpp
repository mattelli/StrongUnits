/**
 * @file example2.cpp
 * @author Massimo Mattelliano (mattemax@yahoo.com)
 * @brief
 * Basic usage of SIBaseUnits header with literals only
 * @copyright Copyright (c) 2022
 * MIT License
 */

#include "src/lib/StrongTypeDefinition.h"
#include "src/lib/SIBaseUnits.h"

using namespace stu::literals;

/**
 * More customized quantities and units in addition to SIBaseUnits
 */
namespace stu
{
    DEF_QUANTITY(area, std::ratio<0>, std::ratio<2>)
    DEF_QUANTITY(velocity, std::ratio<-1>, std::ratio<1>)
    DEF_QUANTITY(acceleration, std::ratio<-2>, std::ratio<1>)
    DEF_QUANTITY(volume, std::ratio<0>, std::ratio<3>)

    DEF_UNIT(area, meter_sq, double, _m2, scale::unity)
    DEF_UNIT(velocity, metre_per_second, double, _mps, scale::unity)
    DEF_UNIT(acceleration, metre_per_second_sq, double, _mps2, scale::unity)
    DEF_UNIT(volume, meter_cube, double, _m3, stu::scale::unity)
} // namespace stu

int main()
{
    std::cout << "  \nExample2\n";

    stu::meter a = 1.0_m;
    a = 2.0_m;
    std::cout << "\n a = ";
    a.print();

    auto a2 = 4.0_m2;
    std::cout << "\n a^2 = ";
    a2.print();

    auto aa = a * a;
    std::cout << "\n a*a = ";
    aa.print();

    auto a3 = 8.0_m3;
    std::cout << "\n a^3 = ";
    a3.print();

    auto aaa = a * a * a;
    std::cout << "\n a*a*a = ";
    aaa.print();

    auto f = 2.5 / 1000000.0_s;
    std::cout << "\n f = ";
    f.print();

    stu::kelvin const T0 = 273.15_K;
    auto g = 300.0_K - T0;
    std::cout << "\n T-273.15_K = ";
    g.print();

    auto akilogram = 1000.0_g;
    std::cout << "\n a kg = ";
    akilogram.print();
}