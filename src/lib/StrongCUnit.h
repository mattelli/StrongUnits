/**
 * @file StrongCUnit.h
 * @author Massimo Mattelliano (mattemax@yahoo.com)
 * @brief
 * Complex Strong Unit implementation
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

#ifndef STRONGCOMPLEXUNIT_H
#define STRONGCOMPLEXUNIT_H

#include <complex>
#include "StrongUnit.h"

namespace stu
{
    /**
     * @brief
     * Class template representing a complex strong unit type
     * @tparam UNIT a strong unit type
     */
    template <typename UNIT>
    class CUnit final
    {
#ifdef __linux__
        static_assert(std::is_compound<UNIT>::value &&
                          not std::is_same<UNIT, char>::value &&
                          not std::is_same<UNIT, bool>::value,
                      "==>> NOT ALLOWED WRAPPED TYPE! <<==");
#elif _WIN32
        static_assert(std::is_compound_v<UNIT> &&
                          !(std::is_same_v<UNIT, char>)&&!(std::is_same_v<UNIT, bool>),
                      "==>> NOT ALLOWED WRAPPED TYPE! <<==");
#endif
    private:
        UNIT real_{};
        UNIT imag_{};

    public:
        constexpr explicit CUnit(UNIT real = UNIT{}, UNIT imag = UNIT{})
            : real_{real}, imag_{imag} {}
        CUnit(CUnit const &other) = default;
        CUnit(CUnit &&other) noexcept = default;
        ~CUnit() = default;

        CUnit &operator=(CUnit other) noexcept
        {
            real_ = other.real_;
            imag_ = other.imag_;
            return *this;
        }

        UNIT real() const { return real_; }
        UNIT imag() const { return imag_; }

        CUnit conj() const
        {
            CUnit res{};
            res.real_ = real_;
            res.imag_ = UNIT{} - imag_;
            return res;
        }

        auto norm() const
        {
            return (real_ * real_ + imag_ * imag_);
        }

        void print() const
        {
            std::cout << "Re: ";
            (*this).real().print();
            std::cout << "Im: ";
            (*this).imag().print();
        }

        template <typename UN>
        friend std::istream &operator>>(std::istream &is, CUnit<UN> &a_cunit);

        template <typename OTHER_UNIT>
        operator CUnit<OTHER_UNIT>() const
        {
            return CUnit<OTHER_UNIT>{real_, imag_};
        }

        CUnit &operator+=(CUnit const &other)
        {
            real_ += other.real_;
            imag_ += other.imag_;
            return *this;
        }

        CUnit &operator-=(CUnit const &other)
        {
            real_ -= other.real_;
            imag_ -= other.imag_;
            return *this;
        }

        // prefix increment
        CUnit &operator++()
        {
            ++real_;
            ++imag_++;
            return *this;
        }

        // postfix increment
        CUnit operator++(int)
        {
            CUnit old = *this;
            operator++();
            return old;
        }

        // prefix decrement
        CUnit &operator--()
        {
            --real_;
            --imag_;
            return *this;
        }

        // postfix decrement
        CUnit operator--(int)
        {
            CUnit old = *this;
            operator--();
            return old;
        }

    }; // CUnit

    template <typename TY, typename LA = stu::tag::numeral_label>
    using numeral_cunity = stu::CUnit<stu::numeral_unit<TY, LA>>;
#ifdef STU_UNIT_TYPE
    using cunit = stu::numeral_cunity<STU_UNIT_TYPE>;
#endif

    template <typename UN>
    std::ostream &operator<<(std::ostream &os, CUnit<UN> const &a_cunit)
    {
        if (a_cunit.imag()() >= 0)
            os << a_cunit.real() << "+j" << a_cunit.imag();
        else
            os << a_cunit.real() << "-j" << -1.0 * a_cunit.imag();
        return os;
    }

    template <typename UN>
    std::istream &operator>>(std::istream &is, CUnit<UN> &a_cunit)
    {
        is >> a_cunit.real_ >> a_cunit.imag_;
        return is;
    }

    template <typename UN1, typename UN2>
    bool operator==(CUnit<UN1> const &left, CUnit<UN2> const &right)
    {
        return ((left.real() == right.real()) && (left.imag() == right.imag()));
    }

    template <typename UN1, typename UN2>
    bool operator!=(CUnit<UN1> const &left, CUnit<UN2> const &right)
    {
        return (!(left == right));
    }

    // OPE+
    template <typename UN1, typename UN2>
    CUnit<UN1> operator+(CUnit<UN1> first, CUnit<UN2> const &second)
    {
        first += second;
        return first;
    }

    template <typename UN1, typename UN2>
    CUnit<UN1> operator+(CUnit<UN1> first, UN2 const &second)
    {
        first += CUnit<UN2>{second};
        return first;
    }

    template <typename UN1, typename UN2>
    CUnit<UN1> operator+(UN1 const &first, CUnit<UN2> const &second)
    {
        CUnit<UN1> cfirst{first};
        cfirst += second;
        return cfirst;
    }

    // OPE-
    template <typename UN1, typename UN2>
    CUnit<UN1> operator-(CUnit<UN1> first, CUnit<UN2> const &second)
    {
        first -= second;
        return first;
    }

    template <typename UN1, typename UN2>
    CUnit<UN1> operator-(CUnit<UN1> first, UN2 const &second)
    {
        first -= CUnit<UN2>{second};
        return first;
    }

    template <typename UN1, typename UN2>
    CUnit<UN1> operator-(UN1 const &first, CUnit<UN2> const &second)
    {
        CUnit<UN1> cfirst{first};
        cfirst -= second;
        return cfirst;
    }

    // OPE*
    template <typename UN>
    CUnit<UN> operator*(long double const &first, CUnit<UN> const &second)
    {
        return CUnit<UN>{first * second.real(), first * second.imag()};
    }

    template <typename UN>
    CUnit<UN> operator*(CUnit<UN> const &first, long double const &second)
    {
        return CUnit<UN>{first.real() * second, first.imag() * second};
    }

    template <typename UN1, typename UN2>
    auto operator*(UN1 const &first, CUnit<UN2> const &second)
    {
        auto unit_real = first * second.real();
        using unnamed_unit = decltype(unit_real);
        return CUnit<unnamed_unit>{unit_real, first * second.imag()};
    }

    template <typename UN1, typename UN2>
    auto operator*(CUnit<UN1> const &first, UN2 const &second)
    {
        auto unit_real = first.real() * second;
        using unnamed_unit = decltype(unit_real);
        return CUnit<unnamed_unit>{unit_real, first.imag() * second};
    }

    template <typename UN1, typename UN2>
    auto operator*(CUnit<UN1> const &first, CUnit<UN2> const &second)
    {
        auto unit_real = first.real() * second.real();
        using unnamed_unit = decltype(unit_real);
        return CUnit<unnamed_unit>{(unit_real - first.imag() * second.imag()),
                                   (first.real() * second.imag() + second.real() * first.imag())};
    }

    // OPE/
    template <typename UN>
    CUnit<UN> operator/(CUnit<UN> const &numerator, long double const &denominator)
    {
        return CUnit<UN>{numerator.real() / denominator, numerator.imag() / denominator};
    }

    template <typename UN1, typename UN2>
    auto operator/(CUnit<UN1> const &numerator, UN2 const &denominator)
    {
        auto unit_real = numerator.real() / denominator;
        using unnamed_unit = decltype(unit_real);
        return CUnit<unnamed_unit>{unit_real, numerator.imag() / denominator};
    }

    template <typename UN1, typename UN2>
    auto operator/(CUnit<UN1> const &numerator, CUnit<UN2> const &denominator)
    {
        auto norm = denominator.norm();
        auto unit = numerator.real() / denominator.real();
        using unnamed_unit = decltype(unit);
        return CUnit<unnamed_unit>{(numerator.real() * denominator.real() + numerator.imag() * denominator.imag()) / norm,
                                   (denominator.real() * numerator.imag() - numerator.real() * denominator.imag()) / norm};
    }

    template <typename UN>
    auto operator/(long double const &numerator, CUnit<UN> const &denominator)
    {
        using TY = decltype(denominator.real()());
        stu::numeral_unit<TY> num_unit{static_cast<TY>(numerator)};
        stu::numeral_cunity<TY> num_cunit{num_unit};
        return (num_cunit / denominator);
    }

    template <typename UN1, typename UN2>
    auto operator/(UN1 const &numerator, CUnit<UN2> const &denominator)
    {
        CUnit<decltype(numerator)> num_cunit{numerator};
        return (num_cunit / denominator);
    }

    // MATH FUNCTIONS
    template <typename UN>
    auto getComplex(CUnit<UN> const &value)
    {
        using TY = decltype(value.real()());
        return std::complex<TY>{value.real()(), value.imag()()};
    }

    template <typename UN, typename TY>
    CUnit<UN> setComplex(std::complex<TY> const &value)
    {
        UN re_value{value.real()};
        UN im_value{value.imag()};
        return CUnit<UN>{re_value, im_value};
    }

    namespace /*Utilities*/
    {
        template <typename TY>
        using complex_function = std::complex<TY> (*)(std::complex<TY> const &);

        template <typename TY, typename LA>
        stu::numeral_cunity<TY> compute_complex_function(stu::numeral_cunity<TY, LA> const &value,
                                                         complex_function<TY> c_fun)
        {
            std::complex<TY> c{c_fun(getComplex(value))};
            return setComplex<stu::numeral_unit<TY>>(c);
        }
    }

    template <typename UN>
    UN abs(CUnit<UN> const &value)
    {
        return UN{std::abs(getComplex(value))};
    }

    template <typename UN>
    auto arg(CUnit<UN> const &value)
    {
        using TY = decltype(value.real()());
        return stu::numeral_rad<TY, stu::tag::numeral_rad_label>{std::arg(getComplex(value))};
    }

    template <typename UN, typename TY, typename LA>
    CUnit<UN> polar(UN const &rho, stu::numeral_rad<TY, LA> const &theta)
    {
        std::complex<TY> c{std::polar(rho(), theta())};
        return setComplex<UN>(c);
    }

    template <typename TY, typename LA>
    stu::numeral_cunity<TY> exp(stu::numeral_cunity<TY, LA> const &value)
    {
        return compute_complex_function(value, std::exp<TY>);
    }

    template <typename TY, typename LA>
    stu::numeral_cunity<TY> log(stu::numeral_cunity<TY, LA> const &value)
    {
        return compute_complex_function(value, std::log<TY>);
    }

    template <typename TY, typename LA>
    stu::numeral_cunity<TY> log10(stu::numeral_cunity<TY, LA> const &value)
    {
        return compute_complex_function(value, std::log10<TY>);
    }

    template <typename TY, typename LA>
    stu::numeral_cunity<TY> sin(stu::numeral_cunity<TY, LA> const &value)
    {
        return compute_complex_function(value, std::sin<TY>);
    }

    template <typename TY, typename LA>
    stu::numeral_cunity<TY> cos(stu::numeral_cunity<TY, LA> const &value)
    {
        return compute_complex_function(value, std::cos<TY>);
    }

    template <typename TY, typename LA>
    stu::numeral_cunity<TY> tan(stu::numeral_cunity<TY, LA> const &value)
    {
        return compute_complex_function(value, std::tan<TY>);
    }

    template <typename TY, typename LA>
    stu::numeral_cunity<TY> asin(stu::numeral_cunity<TY, LA> const &value)
    {
        return compute_complex_function(value, std::asin<TY>);
    }

    template <typename TY, typename LA>
    stu::numeral_cunity<TY> acos(stu::numeral_cunity<TY, LA> const &value)
    {
        return compute_complex_function(value, std::acos<TY>);
    }

    template <typename TY, typename LA>
    stu::numeral_cunity<TY> atan(stu::numeral_cunity<TY, LA> const &value)
    {
        return compute_complex_function(value, std::atan<TY>);
    }

    template <typename TY, typename LA>
    stu::numeral_cunity<TY> sinh(stu::numeral_cunity<TY, LA> const &value)
    {
        return compute_complex_function(value, std::sinh<TY>);
    }

    template <typename TY, typename LA>
    stu::numeral_cunity<TY> cosh(stu::numeral_cunity<TY, LA> const &value)
    {
        return compute_complex_function(value, std::cosh<TY>);
    }

    template <typename TY, typename LA>
    stu::numeral_cunity<TY> tanh(stu::numeral_cunity<TY, LA> const &value)
    {
        return compute_complex_function(value, std::tanh<TY>);
    }

    template <typename TY, typename LA>
    stu::numeral_cunity<TY> asinh(stu::numeral_cunity<TY, LA> const &value)
    {
        return compute_complex_function(value, std::asinh<TY>);
    }

    template <typename TY, typename LA>
    stu::numeral_cunity<TY> acosh(stu::numeral_cunity<TY, LA> const &value)
    {
        return compute_complex_function(value, std::acosh<TY>);
    }

    template <typename TY, typename LA>
    stu::numeral_cunity<TY> atanh(stu::numeral_cunity<TY, LA> const &value)
    {
        return compute_complex_function(value, std::atanh<TY>);
    }

    template <typename TY, typename LA>
    stu::numeral_cunity<TY> pow(stu::numeral_cunity<TY, LA> const &base,
                                std::complex<long double> const &exponent)
    {
        auto c_exp = static_cast<std::complex<TY>>(exponent);
        std::complex<TY> c{std::pow(getComplex(base), c_exp)};
        return setComplex<stu::numeral_unit<TY>>(c);
    }

    template <typename TY, typename LA>
    stu::numeral_cunity<TY> pow(stu::numeral_cunity<TY, LA> const &base,
                                stu::numeral_cunity<TY, LA> const &exponent)
    {
        return stu::pow(base, getComplex(exponent));
    }

    template <typename TY, typename LA>
    stu::numeral_cunity<TY> pow(stu::numeral_cunity<TY, LA> const &base,
                                long double const &exponent)
    {
        auto ty_exp = static_cast<TY>(exponent);
        std::complex<TY> c{std::pow(getComplex(base), ty_exp)};
        return setComplex<stu::numeral_unit<TY>>(c);
    }

    template <typename TY, typename LA>
    stu::numeral_cunity<TY> pow(stu::numeral_cunity<TY, LA> const &base,
                                stu::numeral_unit<TY, LA> const &exponent)
    {
        return stu::pow(base, exponent());
    }

    template <std::intmax_t exponent, typename UN>
    auto pow(CUnit<UN> const &base)
    {
        using TY = decltype(base.real()());
        using unnamed_unit = decltype(stu::pow<exponent>(base.real()));
        std::complex<TY> c{std::pow(getComplex(base), static_cast<long double>(exponent))};

        return setComplex<unnamed_unit>(c);
    }

    template <typename TY, typename LA>
    stu::numeral_cunity<TY> sqrt(stu::numeral_cunity<TY, LA> const &value)
    {
        return compute_complex_function(value, std::sqrt<TY>);
    }

    template <typename UN>
    auto sqrt(CUnit<UN> const &value)
    {
        using TY = decltype(value.real()());
        using unnamed_unit = decltype(stu::sqrt(value.real()));
        std::complex<TY> c{std::sqrt(getComplex(value))};

        return setComplex<unnamed_unit>(c);
    }

    namespace constants
    {
#ifdef STU_UNIT_TYPE
        static constexpr const cunit j{_0, _1};
#endif
    } // namespace constants

} // namespace stu

#endif // STRONGCOMPLEXUNIT_H