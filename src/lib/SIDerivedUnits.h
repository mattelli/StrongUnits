/**
 * @file SIDerivedUnits.h
 * @author Massimo Mattelliano (mattemax@yahoo.com)
 * @brief
 * International System Derived Units
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

#ifndef SIDERIVEDUNITS_H
#define SIDERIVEDUNITS_H

#include "SIBaseUnits.h"

namespace stu
{
    /**
     * SI Derived Quantities
     */
    namespace quantity
    {
        /// @cond
        DEF_QUANTITY(frequency, std::ratio<-1>)
        DEF_QUANTITY(force, std::ratio<-2>, std::ratio<1>, std::ratio<1>)
        DEF_QUANTITY(pressure, std::ratio<-2>, std::ratio<-1>, std::ratio<1>)
        DEF_QUANTITY(energy, std::ratio<-2>, std::ratio<2>, std::ratio<1>)
        DEF_QUANTITY(power, std::ratio<-3>, std::ratio<2>, std::ratio<1>)
        DEF_QUANTITY(electric_charge, std::ratio<1>, std::ratio<0>, std::ratio<0>, std::ratio<1>)
        DEF_QUANTITY(voltage, std::ratio<-3>, std::ratio<2>, std::ratio<1>, std::ratio<-1>)
        DEF_QUANTITY(electrical_capacitance, std::ratio<4>, std::ratio<-2>, std::ratio<-1>, std::ratio<2>)
        DEF_QUANTITY(electrical_impedance, std::ratio<-3>, std::ratio<2>, std::ratio<1>, std::ratio<-2>)
        DEF_QUANTITY(electrical_conductance, std::ratio<3>, std::ratio<-2>, std::ratio<-1>, std::ratio<2>)
        DEF_QUANTITY(magnetic_flux, std::ratio<-2>, std::ratio<2>, std::ratio<1>, std::ratio<-1>)
        DEF_QUANTITY(magnetic_field, std::ratio<-2>, std::ratio<0>, std::ratio<1>, std::ratio<-1>)
        DEF_QUANTITY(inductance, std::ratio<-2>, std::ratio<2>, std::ratio<1>, std::ratio<-2>)
        DEF_QUANTITY(luminous_flux, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>)
        DEF_QUANTITY(illuminance, std::ratio<0>, std::ratio<-2>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>)
        DEF_QUANTITY(radioactivity, std::ratio<-1>)
        DEF_QUANTITY(absorbed_dose, std::ratio<-2>, std::ratio<2>)
        DEF_QUANTITY(equivalent_dose, std::ratio<-2>, std::ratio<2>)
        DEF_QUANTITY(catalytic_activity, std::ratio<-1>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>)
        ///@endcond
    } // namespace quantity

    /**
     * SI Derived Units
     */
    DEF_UNIT(quantity::frequency, hertz, STU_UNIT_TYPE, _Hz, scale::unity)
    DEF_UNIT(quantity::force, newton, STU_UNIT_TYPE, _N, scale::unity)
    DEF_UNIT(quantity::pressure, pascal, STU_UNIT_TYPE, _Pa, scale::unity)
    DEF_UNIT(quantity::energy, joule, STU_UNIT_TYPE, _J, scale::unity)
    DEF_UNIT(quantity::power, watt, STU_UNIT_TYPE, _W, scale::unity)
    DEF_UNIT(quantity::electric_charge, coulomb, STU_UNIT_TYPE, _C, scale::unity)
    DEF_UNIT(quantity::voltage, volt, STU_UNIT_TYPE, _V, scale::unity)
    DEF_UNIT(quantity::electrical_capacitance, farad, STU_UNIT_TYPE, _F, scale::unity)
    DEF_UNIT(quantity::electrical_impedance, ohm, STU_UNIT_TYPE, _ohm, scale::unity)
    DEF_UNIT(quantity::electrical_conductance, siemens, STU_UNIT_TYPE, _S, scale::unity)
    DEF_UNIT(quantity::magnetic_flux, weber, STU_UNIT_TYPE, _Wb, scale::unity)
    DEF_UNIT(quantity::magnetic_field, tesla, STU_UNIT_TYPE, _T, scale::unity)
    DEF_UNIT(quantity::inductance, henry, STU_UNIT_TYPE, _H, scale::unity)
    DEF_UNIT(quantity::temperature, celsius, STU_UNIT_TYPE, _Cdeg, scale::unity)
    DEF_UNIT(quantity::luminous_flux, lumen, STU_UNIT_TYPE, _lm, scale::unity)
    DEF_UNIT(quantity::illuminance, lux, STU_UNIT_TYPE, _lx, scale::unity)
    DEF_UNIT(quantity::radioactivity, becquerel, STU_UNIT_TYPE, _Bq, scale::unity)
    DEF_UNIT(quantity::absorbed_dose, gray, STU_UNIT_TYPE, _Gy, scale::unity)
    DEF_UNIT(quantity::equivalent_dose, sievert, STU_UNIT_TYPE, _Sv, scale::unity)
    DEF_UNIT(quantity::catalytic_activity, katal, STU_UNIT_TYPE, _kat, scale::unity)

} // namespace stu

#endif // SIDERIVEDUNITS_H