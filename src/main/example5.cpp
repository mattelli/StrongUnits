/**
 * @file example5.cpp
 * @author Massimo Mattelliano (mattemax@yahoo.com)
 * @brief
 * Basic usage of StrongCUnit and NonSIBaseUnits headers
 * @copyright Copyright (c) 2022
 * MIT License
 */

#include "src/lib/StrongTypeDefinition.h"
#include "src/lib/NonSIBaseUnits.h"
#include "src/lib/StrongCUnit.h"

using namespace stu::literals;
using namespace stu::symbols;
using namespace stu::prefixes;
using namespace stu::constants;

/**
 *  Quantity and unit definitios only from headers
 **/

int main()
{
    std::cout << "  \nExample5\n\n";

    stu::CUnit<stu::ampere> I;
    std::cout << "Insert CUnit (ampere) >> ";
    std::cin >> I;
    std::cout << I << std::endl;

    std::cout << "Conjugate = ";
    std::cout << I.conj() << std::endl;

    auto abs_I = stu::abs(I);
    std::cout << "abs(I) = ";
    abs_I.print();

    auto arg_I = stu::arg(I);
    std::cout << "arg(I) radiants = ";
    arg_I.print();

    stu::degree arg_deg_I = arg_I;
    std::cout << "arg(I) deg = ";
    arg_deg_I.print();

    stu::numeral_unity arg_num_I = arg_I;
    std::cout << "arg(I) numeric = ";
    arg_num_I.print();

    auto s1 = stu::sin(arg_I);
    std::cout << "sin[arg(I) radiants] =\n";
    s1.print();
    
    auto c1 = stu::cos(arg_I);
    std::cout << "cos[arg(I) radiants] =\n";
    c1.print();

    auto s2 = stu::sin(2*PI*arg_num_I + j*_0);
    std::cout << "sin[arg(I) numeric + j0] =\n";
    s2.print();
    
    auto c2 = stu::cos(2*PI*arg_num_I + j*_0);
    std::cout << "cos[arg(I) numeric + j0] =\n";
    c2.print();

    auto I2 = stu::pow<2>(I);
    std::cout << "I^2 =\n";
    I2.print();

    auto I2_sqrt = stu::sqrt(I2);
    std::cout << "sqrt(I^2) =\n";
    I2_sqrt.print();

    std::cout << "j*j =\n";
    (j * j).print();

    auto I0 = 1.0_A + j * 1.0_A;
    std::cout << "I0 =\n";
    I0.print();

    auto I1 = (_1+j)*_A;
    std::cout << "I1 =\n";
    I1.print();

    auto I00 = I0-I;
    std::cout << "I0-I =\n";
    I00.print();

    auto I11 = I1+I;
    std::cout << "I1+I =\n";
    I11.print();

    auto e = stu::exp(_1+j*_0);
    std::cout << "RE{e^(1+j0)}-e =\n";
    std::cout << e.real() - E << std::endl;

    auto ac = stu::acos(-1*_1 + j*0);
    std::cout << "Re{acos^(-1+j0)}-PI =\n";
    std::cout << ac.real() - PI << std::endl;
}