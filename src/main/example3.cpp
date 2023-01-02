/**
 * @file example3.cpp
 * @author Massimo Mattelliano (mattemax@yahoo.com)
 * @brief
 * Basic usage of SIDerivedUnits header with symbols only
 * @copyright Copyright (c) 2022
 * MIT License
 */

#include "src/lib/StrongTypeDefinition.h"
#include "src/lib/SIDerivedUnits.h"

using namespace stu::symbols;
using namespace stu::prefixes;

/**
 *  Quantity and unit definitios only from SIDerivedUnits header
 **/
int main()
{
    std::cout << "  \nExample3\n";

    stu::meter a = 1*_m;
    a = 2*_m;
    std::cout << "\n a = ";
    a.print();

    auto a2 = 4*_m*_m;
    std::cout << "\n a^2 = ";
    a2.print();

    auto aa = a*a;
    std::cout << "\n a*a = ";
    aa.print();

    auto a3 = 8.0*_m*_m*_m;
    std::cout << "\n a^3 = ";
    a3.print();

    auto aaa = a*a*a;
    std::cout << "\n a*a*a = ";
    aaa.print();

    auto f = 2.5 / (M_*_s); // usege of prefix mega allows automatic scale conversion 
    std::cout << "\n f = ";
    f.print();

    stu::kelvin const T0 = 273.15*_K;
    stu::celsius g = 300.0*_K - T0;
    std::cout << "\n celsius t = ";
    g.print();

    auto akilogram = k_*_g ; // usege of prefix kilo allows automatic scale conversion
    std::cout << "\n a kg = ";
    akilogram.print();
}