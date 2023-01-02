/**
 * @file SIBaseUnits.h
 * @author Massimo Mattelliano (mattemax@yahoo.com)
 * @brief
 * International System Base Units
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

#ifndef SIBASEUNITS_H
#define SIBASEUNITS_H

#include "StrongUnit.h"

namespace stu
{
    /**
     * @brief
     * Namespace in which SI scales for units conversion are defined
     */
    namespace scale
    {
        /// @cond
        DEF_SCALE(atto, 1, 1000000000000000000)
        DEF_SCALE(femto, 1, 1000000000000000)
        DEF_SCALE(pico, 1, 1000000000000)
        DEF_SCALE(nano, 1, 1000000000)
        DEF_SCALE(micro, 1, 1000000)
        DEF_SCALE(milli, 1, 1000)
        DEF_SCALE(centi, 1, 100)
        DEF_SCALE(deci, 1, 10)
        DEF_SCALE(unity, 1)
        DEF_SCALE(deca, 10)
        DEF_SCALE(hecto, 100)
        DEF_SCALE(kilo, 1000)
        DEF_SCALE(mega, 1000000)
        DEF_SCALE(giga, 1000000000)
        DEF_SCALE(tera, 1000000000000)
        DEF_SCALE(peta, 1000000000000000)
        DEF_SCALE(exa, 1000000000000000000)

        DEF_SCALE(num2rad,
                  50000000000000000U,
                  314159265358979323U)
        DEF_SCALE(num2sr,
                  25000000000000000U,
                  314159265358979323U)
        ///@endcond
    } // namespace scale

    /**
     * @brief
     * Namespace in which SI quantities are defined
     */
    namespace quantity
    {
        /// @cond
        DEF_QUANTITY(numeral)
        DEF_QUANTITY(plane_angle)
        DEF_QUANTITY(solid_angle)
        DEF_QUANTITY(time, std::ratio<1>)
        DEF_QUANTITY(length, std::ratio<0>, std::ratio<1>)
        DEF_QUANTITY(mass, std::ratio<0>, std::ratio<0>, std::ratio<1>)
        DEF_QUANTITY(electric_current, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>)
        DEF_QUANTITY(temperature, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>)
        DEF_QUANTITY(substance_amount, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>)
        DEF_QUANTITY(luminous_intensity, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>)
        ///@endcond
    }

    /**
     * SI Prefix numeral unit and constants are defined
     */
    DEF_PREFIX(quantity::numeral, numeral_atto, STU_UNIT_TYPE, a_, scale::atto)
    DEF_PREFIX(quantity::numeral, numeral_femto, STU_UNIT_TYPE, f_, scale::femto)
    DEF_PREFIX(quantity::numeral, numeral_pico, STU_UNIT_TYPE, p_, scale::pico)
    DEF_PREFIX(quantity::numeral, numeral_nano, STU_UNIT_TYPE, n_, scale::nano)
    DEF_PREFIX(quantity::numeral, numeral_micro, STU_UNIT_TYPE, mc_, scale::micro)
    DEF_PREFIX(quantity::numeral, numeral_milli, STU_UNIT_TYPE, m_, scale::milli)
    DEF_PREFIX(quantity::numeral, numeral_centi, STU_UNIT_TYPE, c_, scale::centi)
    DEF_PREFIX(quantity::numeral, numeral_deci, STU_UNIT_TYPE, d_, scale::deci)
    DEF_PREFIX(quantity::numeral, numeral_unity, STU_UNIT_TYPE, u_, scale::unity)
    DEF_PREFIX(quantity::numeral, numeral_deca, STU_UNIT_TYPE, da_, scale::deca)
    DEF_PREFIX(quantity::numeral, numeral_hecto, STU_UNIT_TYPE, h_, scale::hecto)
    DEF_PREFIX(quantity::numeral, numeral_kilo, STU_UNIT_TYPE, k_, scale::kilo)
    DEF_PREFIX(quantity::numeral, numeral_mega, STU_UNIT_TYPE, M_, scale::mega)
    DEF_PREFIX(quantity::numeral, numeral_giga, STU_UNIT_TYPE, G_, scale::giga)
    DEF_PREFIX(quantity::numeral, numeral_tera, STU_UNIT_TYPE, T_, scale::tera)
    DEF_PREFIX(quantity::numeral, numeral_peta, STU_UNIT_TYPE, P_, scale::peta)
    DEF_PREFIX(quantity::numeral, numeral_exa, STU_UNIT_TYPE, E_, scale::exa)

    /**
     * SI Base Units
     */
    DEF_UNIT(quantity::time, second, STU_UNIT_TYPE, _s, scale::unity)
    DEF_UNIT(quantity::length, meter, STU_UNIT_TYPE, _m, scale::unity)
    DEF_UNIT(quantity::mass, gram, STU_UNIT_TYPE, _g, scale::unity)
    DEF_UNIT(quantity::mass, kilogram, STU_UNIT_TYPE, _kg, scale::kilo)
    DEF_UNIT(quantity::electric_current, ampere, STU_UNIT_TYPE, _A, scale::unity)
    DEF_UNIT(quantity::temperature, kelvin, STU_UNIT_TYPE, _K, scale::unity)
    DEF_UNIT(quantity::substance_amount, mole, STU_UNIT_TYPE, _mol, scale::unity)
    DEF_UNIT(quantity::luminous_intensity, candela, STU_UNIT_TYPE, _cd, scale::unity)
    DEF_UNIT(quantity::plane_angle, radian, STU_UNIT_TYPE, _rad, scale::num2rad)
    DEF_UNIT(quantity::solid_angle, steradian, STU_UNIT_TYPE, _sr, scale::num2sr)
} // namespace stu

#endif // SIBASEUNITS_H