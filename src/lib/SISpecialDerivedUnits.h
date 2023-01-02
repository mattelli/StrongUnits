/**
 * @file SISpecialDerivedUnits.h
 * @author Massimo Mattelliano (mattemax@yahoo.com)
 * @brief
 * International System some special derived units in terms of base units
 * @copyright Copyright (c) 2022
 * MIT License
 * 
 * Copyright (c) 2022 Massimo Mattelliano
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef SISPECIALDERIVEDUNITS_H
#define SISPECIALDERIVEDUNITS_H

#include "SIDerivedUnits.h"

namespace stu
{
    /**
     * SI Special Derived Quantities
     */
    namespace quantity
    {
        /// @cond
        DEF_QUANTITY(dynamic_viscosity, std::ratio<-1>, std::ratio<-1>, std::ratio<1>)
        DEF_QUANTITY(angular_velocity, std::ratio<-1>)
        DEF_QUANTITY(angular_acceleration, std::ratio<-2>)
        DEF_QUANTITY(irradiance, std::ratio<-3>, std::ratio<0>, std::ratio<1>)
        DEF_QUANTITY(electric_field, std::ratio<-2>, std::ratio<1>, std::ratio<1>, std::ratio<-1>)
        DEF_QUANTITY(electric_permittivity, std::ratio<4>, std::ratio<-3>, std::ratio<-1>, std::ratio<2>)
        DEF_QUANTITY(magnetic_permeability, std::ratio<-2>, std::ratio<1>, std::ratio<1>, std::ratio<-2>)
        DEF_QUANTITY(molar_energy, std::ratio<-2>, std::ratio<2>, std::ratio<1>, std::ratio<0>, std::ratio<0>, std::ratio<-1>)
        ///@endcond
    } // namespace quantity

    /**
     * SI Special Derived Units
     */
    DEF_UNIT(quantity::dynamic_viscosity, pascal_second, STU_UNIT_TYPE, _Pas, scale::unity)
    DEF_UNIT(quantity::angular_velocity, radian_per_second, STU_UNIT_TYPE, _radps, scale::num2rad)
    DEF_UNIT(quantity::angular_acceleration, radian_per_second_squared, STU_UNIT_TYPE, _radps2, scale::num2rad)
    DEF_UNIT(quantity::irradiance, watt_per_square_meter, STU_UNIT_TYPE, _Wpm2, scale::unity)
    DEF_UNIT(quantity::electric_field, volt_per_meter, STU_UNIT_TYPE, _Vpm, scale::unity)
    DEF_UNIT(quantity::electric_permittivity, farad_per_meter, STU_UNIT_TYPE, _Fpm, scale::unity)
    DEF_UNIT(quantity::magnetic_permeability, henry_per_meter, STU_UNIT_TYPE, _Hpm, scale::unity)
    DEF_UNIT(quantity::molar_energy, joule_per_mole, STU_UNIT_TYPE, _Jpmol, scale::kilo)

} // namespace stu

#endif // SISPECIALDERIVEDUNITS_H