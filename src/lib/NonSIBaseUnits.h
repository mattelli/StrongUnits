/**
 * @file NonSIBaseUnits.h
 * @author Massimo Mattelliano (mattemax@yahoo.com)
 * @brief
 * Non-SI base units accepted for use with SI units
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

#ifndef NONSIBASEUNITS_H
#define NONSIBASEUNITS_H

#include "SICoherentBaseUnits.h"

namespace stu
{
    namespace scale
    {
        DEF_SCALE(s2min, 60U)
        DEF_SCALE(s2hour, 3600U)
        DEF_SCALE(s2day, 86400U)
        DEF_SCALE(num2deg, 1U, 360U)
        DEF_SCALE(sq_m2ha, 10000U)
        DEF_SCALE(cb_m2L, 1U, 1000U)
        DEF_SCALE(g2t, 1000000U)
    }

    /**
     * Non-SI base units accepted for use with SI units
     */
    DEF_UNIT(quantity::time, minute, STU_UNIT_TYPE, _min, scale::s2min)
    DEF_UNIT(quantity::time, hour, STU_UNIT_TYPE, _h, scale::s2hour)
    DEF_UNIT(quantity::time, day, STU_UNIT_TYPE, _d, scale::s2day)
    DEF_UNIT(quantity::plane_angle, degree, STU_UNIT_TYPE, _deg, scale::num2deg)
    DEF_UNIT(quantity::area, hectare, STU_UNIT_TYPE, _ha, scale::sq_m2ha)
    DEF_UNIT(quantity::volume, liter, STU_UNIT_TYPE, _L, scale::cb_m2L)
    DEF_UNIT(quantity::mass, tonne, STU_UNIT_TYPE, _t, scale::g2t)

} // namespace stu

#endif // NONSIBASEUNITS_H