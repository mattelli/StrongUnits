/**
 * @file usecase2.cpp
 * @author Massimo Mattelliano (mattemax@yahoo.com)
 * @brief
 * In this use-case a RLC series circuit is considered.
 * It is computed its elctric impedence at given frequency and its resonance frequency.
 * @copyright Copyright (c) 2022
 * MIT License
 */

#include "src/lib/StrongTypeDefinition.h"
#include "src/lib/SISpecialDerivedUnits.h"
#include "src/lib/StrongCUnit.h"

using namespace stu::literals;
using namespace stu::symbols;
using namespace stu::prefixes;
using namespace stu::constants;

int main()
{
    std::cout << "  \nUseCase2\n\nRLC series circuit ...\n";

    auto R = 12.0_ohm;
    auto L = 0.025_H;
    auto C = 312*mc_*_F;
    std::cout << "  having: R=" << R << "; L=" << L << "; C=" << C << std::endl;

    stu::hertz f0 = 1/(2*PI*stu::sqrt(L*C));
    std::cout << "  resonance frequency f0 = " << f0 << std::endl;

    stu::hertz f;
    std::cout << "\n insert electric current frequency (hertz) >> ";
    std::cin >> f;
    auto w = 2*PI*f;
    std::cout << f << " (w = " << w << ")" << std::endl;

    auto Z = R + j*w*L - j/(w*C);
    std::cout << "\n Z = " << stu::abs(Z) << std::endl;
}
