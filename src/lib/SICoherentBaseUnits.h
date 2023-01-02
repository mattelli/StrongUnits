/**
 * @file SICoherentBaseUnits.h
 * @author Massimo Mattelliano (mattemax@yahoo.com)
 * @brief
 * International System coherent base units in terms of base units
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

#ifndef SICOHERENTBASEUNITS_H
#define SICOHERENTBASEUNITS_H

#include "SIBaseUnits.h"

namespace stu
{
    /**
     * SI Coherent Base Quantities
     */
    namespace quantity
    {
        /// @cond
        DEF_QUANTITY(area, std::ratio<0>, std::ratio<2>)
        DEF_QUANTITY(volume, std::ratio<0>, std::ratio<3>)
        DEF_QUANTITY(velocity, std::ratio<-1>, std::ratio<1>)
        DEF_QUANTITY(acceleration, std::ratio<-2>, std::ratio<1>)
        DEF_QUANTITY(wavenumber, std::ratio<0>, std::ratio<-1>)
        DEF_QUANTITY(density, std::ratio<0>, std::ratio<-3>, std::ratio<1>)
        DEF_QUANTITY(surface_density, std::ratio<0>, std::ratio<-2>, std::ratio<1>)
        DEF_QUANTITY(specific_volume, std::ratio<0>, std::ratio<3>, std::ratio<-1>)
        DEF_QUANTITY(current_density, std::ratio<0>, std::ratio<-2>, std::ratio<0>, std::ratio<1>)
        DEF_QUANTITY(magnetic_field_strength, std::ratio<0>, std::ratio<1>, std::ratio<0>, std::ratio<1>)
        DEF_QUANTITY(concentration, std::ratio<0>, std::ratio<-3>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>)
        DEF_QUANTITY(luminance, std::ratio<0>, std::ratio<-2>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>)
        ///@endcond
    } // namespace quantity

    /**
     * SI Coherent Base Units
     */
    DEF_UNIT(quantity::area, square_meter, STU_UNIT_TYPE, _m2, scale::unity)
    DEF_UNIT(quantity::volume, cubic_meter, STU_UNIT_TYPE, _m3, scale::unity)
    DEF_UNIT(quantity::velocity, meter_per_second, STU_UNIT_TYPE, _mps, scale::unity)
    DEF_UNIT(quantity::acceleration, meter_per_second_squared, STU_UNIT_TYPE, _mps2, scale::unity)
    DEF_UNIT(quantity::wavenumber, reciprocal_meter, STU_UNIT_TYPE, _m_1, scale::unity)
    DEF_UNIT(quantity::density, gram_per_cubic_meter, STU_UNIT_TYPE, _gpm3, scale::unity)
    DEF_UNIT(quantity::surface_density, gram_per_square_meter, STU_UNIT_TYPE, _gpm2, scale::unity)
    DEF_UNIT(quantity::density, kilogram_per_cubic_meter, STU_UNIT_TYPE, _kgpm3, scale::kilo)
    DEF_UNIT(quantity::surface_density, kilogram_per_square_meter, STU_UNIT_TYPE, _kgpm2, scale::kilo)
    DEF_UNIT(quantity::specific_volume, cubic_meter_per_gram, STU_UNIT_TYPE, _m3pg, scale::unity)
    DEF_UNIT(quantity::magnetic_field_strength, ampere_per_meter, STU_UNIT_TYPE, _Apm, scale::unity)
    DEF_UNIT(quantity::concentration, mole_per_cubic_meter, STU_UNIT_TYPE, _molpm3, scale::unity)
    DEF_UNIT(quantity::luminance, candela_per_square_meter, STU_UNIT_TYPE, _cdpm2, scale::unity)

} // namespace stu

#endif // SICOHERENTBASEUNITS_H