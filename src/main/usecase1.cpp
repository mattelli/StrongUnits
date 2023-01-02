/**
 * @file usecase1.cpp
 * @author Massimo Mattelliano (mattemax@yahoo.com)
 * @brief
 * In this use-case the range of a bullet is computed having its inital velocity module and angle.
 * @copyright Copyright (c) 2022
 * MIT License
 */

#include "src/lib/StrongTypeDefinition.h"
#include "src/lib/NonSIBaseUnits.h"

using namespace stu::literals;
using namespace stu::symbols;
using namespace stu::prefixes;
using namespace stu::constants;

namespace stu
{
    DEF_UNIT(quantity::length, kilometer, STU_UNIT_TYPE, _km, scale::kilo)
    DEF_UNIT(quantity::velocity, kilometer_per_hour, STU_UNIT_TYPE, _kmph, scale::kilo)
}

stu::meter computeBulletRange(stu::radian const &angle, stu::meter_per_second const &init_speed)
{
    return stu::pow<2>(init_speed) * stu::sin(2 * angle) / 9.81_mps2;
}

int main()
{
    std::cout << "  \nUseCase1\n\nCompute bullet range ...\n";

    stu::degree alpa;
    std::cout << "\n insert bullet angle referred to the ground (degree) >> ";
    std::cin >> alpa;
    stu::radian alpa_rad{alpa};
    std::cout << alpa << " (" << alpa_rad << ")" << std::endl;

    stu::meter_per_second v0;
    std::cout << "\n insert bullet initial speed (mps) >> ";
    std::cin >> v0;
    stu::kilometer_per_hour v0_kph{v0};
    std::cout << v0 << " (" << v0_kph << ")" << std::endl;

    auto range = computeBulletRange(alpa_rad, v0);
    std::cout << "\n bullet range = " << range << " ("
              << static_cast<stu::kilometer>(range) << ")\n" << std::endl;
}
