/**
 * @file StrongUnit.h
 * @author Massimo Mattelliano (mattemax@yahoo.com)
 * @brief
 * Strong Unit implementation
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

#ifndef STRONGUNIT_H
#define STRONGUNIT_H

/**
 * @brief
 * It enables iostream support for strong units
 */

#include <type_traits>
#include <ratio>
#include <cmath>
#include <string>
#include <iostream>

/**
 * @brief
 * Namespace in which strong unit types are defined.
 */
namespace stu
{
    /**
     * @brief
     * Namespace in which strong unit literals are defefined (labels format is identical).
     */
    namespace literals
    {
    }

    /**
     * @brief
     * Namespace in which strong unit symbols are defined (symbols are strong unit constants having same format as literals and labels)
     */
    namespace symbols
    {
    }

    /**
     * @brief
     * Namespace in which strong unit prefixes are defefined (prefixes are numeral units constants).
     */
    namespace prefixes
    {
    }
} // namespace std

/**
 * @brief
 * Defines a rational `scale=up/dn` used for unit linear conversion.
 * @note it should be called before DEF_UNIT.
 * @note down default value (`dn=1`).
 */
#define DEF_SCALE(scale, up, ...) \
    using scale = stu::Scale<up, ##__VA_ARGS__>;

/**
 * @brief
 * Defines a quantity used by a strong unit.
 * @note it should be called before DEF_UNIT.
 */
#define DEF_QUANTITY(quantity, ...) \
    using quantity = stu::Quantity<__VA_ARGS__>;

/**
 * @brief
 * Defines a strong unit prefix.
 */
#define DEF_PREFIX(quantity, a_unit, type, label, scale)         \
    namespace tag                                                \
    {                                                            \
        struct label                                             \
        {                                                        \
            label(){};                                           \
            std::string label_{#label};                          \
        };                                                       \
    }                                                            \
    using a_unit = stu::Unit<type, quantity, scale, tag::label>; \
    namespace prefixes                                           \
    {                                                            \
        static constexpr a_unit label{1};                        \
    }

/**
 * @brief
 * Defines a strong unit.
 */
#define DEF_UNIT(quantity, a_unit, type, label, scale)           \
    namespace tag                                                \
    {                                                            \
        struct label                                             \
        {                                                        \
            label(){};                                           \
            std::string label_{#label};                          \
        };                                                       \
    }                                                            \
    using a_unit = stu::Unit<type, quantity, scale, tag::label>; \
    namespace literals                                           \
    {                                                            \
        a_unit operator"" label(long double val)                 \
        {                                                        \
            return a_unit{static_cast<type>(val)};               \
        }                                                        \
    }                                                            \
    namespace symbols                                            \
    {                                                            \
        static constexpr a_unit label{1};                        \
    }

namespace stu
{
    /// @cond
    namespace utils /* Utilities to compute derived quantities */
    {
        template <std::uintmax_t a, std::uintmax_t b>
        struct mcd
        {
            static constexpr std::uintmax_t value = mcd<b, a % b>::value;
        };
        template <std::uintmax_t a>
        struct mcd<a, 0>
        {
            static constexpr std::uintmax_t value = a;
        };

        /**
         * Scale
         * Struct template representing a rational scale for unit linear conversion.
         *
         * tparam UP scale numerator
         * tparam DN scale denominator
         */
        template <std::uintmax_t UP, std::uintmax_t DN>
        struct ScaleBase
        {
            static_assert((UP > 0 && UP <= UINTMAX_MAX), "==>> UNVALID SCALE UP! <<==");
            static_assert((DN > 0 && DN <= UINTMAX_MAX), "==>> UNVALID SCALE DN! <<==");
            static constexpr std::uintmax_t up_ = UP;
            static constexpr std::uintmax_t dn_ = DN;
        };

        template <std::uintmax_t UP, std::uintmax_t DN>
        struct simplified_scale
        {
            using type = ScaleBase<UP / mcd<UP, DN>::value, DN / mcd<UP, DN>::value>;
        };
    } // namespace utils
    ///@endcond

    template <std::uintmax_t UP, std::uintmax_t DN = 1>
    using Scale = typename utils::simplified_scale<UP, DN>::type;

    /**
     * @brief
     * Struct template representing a quantity for automatic derived unit conversion.
     * @note Each quantity is ideally represented by QU = Base0^(Exp0)*Base1^(Exp1)*...*Base9^(Exp9)
     *       where the rational exponents Exps are represented by std::ratio
     *
     * @tparam BASEiEXP quantity's rational exponents (std::ratio)
     */
    template <class BASE0EXP = std::ratio<0>,
              class BASE1EXP = std::ratio<0>,
              class BASE2EXP = std::ratio<0>,
              class BASE3EXP = std::ratio<0>,
              class BASE4EXP = std::ratio<0>,
              class BASE5EXP = std::ratio<0>,
              class BASE6EXP = std::ratio<0>,
              class BASE7EXP = std::ratio<0>,
              class BASE8EXP = std::ratio<0>,
              class BASE9EXP = std::ratio<0>>
    /* Add here more ratios if needed*/
    struct Quantity
    {
        static constexpr BASE0EXP b0e{};
        static constexpr BASE1EXP b1e{};
        static constexpr BASE2EXP b2e{};
        static constexpr BASE3EXP b3e{};
        static constexpr BASE4EXP b4e{};
        static constexpr BASE5EXP b5e{};
        static constexpr BASE6EXP b6e{};
        static constexpr BASE7EXP b7e{};
        static constexpr BASE8EXP b8e{};
        static constexpr BASE9EXP b9e{};
        /* Add here more ratios if needed*/
    };

    /// @cond
    namespace utils /* Utilities to compute derived quantities */
    {
        template <class, class>
        struct mul_quantities;
        template <class... BEs1, class... BEs2>
        struct mul_quantities<Quantity<BEs1...>, Quantity<BEs2...>>
        {
            using type_quantity = Quantity<std::ratio_add<BEs1, BEs2>...>;
        };
        template <class QU1, class QU2>
        using mul_quantities_t = typename mul_quantities<QU1, QU2>::type_quantity;

        template <class, class>
        struct div_quantities;
        template <class... BEs1, class... BEs2>
        struct div_quantities<Quantity<BEs1...>, Quantity<BEs2...>>
        {
            using type_quantity = Quantity<std::ratio_subtract<BEs1, BEs2>...>;
        };
        template <class QU1, class QU2>
        using div_quantities_t = typename div_quantities<QU1, QU2>::type_quantity;

        template <class, class>
        struct pow_quantities;
        template <class... BEs1, class EXP>
        struct pow_quantities<Quantity<BEs1...>, EXP>
        {
            using type_quantity = Quantity<std::ratio_multiply<BEs1, EXP>...>;
        };
        template <class QU1, class QU2>
        using pow_quantities_t = typename pow_quantities<QU1, QU2>::type_quantity;

        constexpr std::uintmax_t isqrt(std::uintmax_t value)
        {
            for (std::uintmax_t i{1}; i <= (value + 1) / 2; ++i)
            {
                if ((value % i == 0) && (i * i == value))
                    return i;
            }
            return 0;
        }

        constexpr std::uintmax_t ipow(std::uintmax_t base, std::intmax_t exponent)
        {
            if (exponent > 0)
                return (base * ipow(base, exponent - 1));
            else
                return 1UL;
        }

    } // namespace utils
    ///@endcond

    /**
     * @brief
     * Class template representing a strong unit type
     * @tparam TYPE     type wrapped by this class
     * @tparam QUANTITY      parameter type to specify the quantity representing the wrapped type
     * @tparam SCALE    scale type for linear conversion
     * @tparam LABEL    label type for tagging printed units
     */
    template <typename TYPE, typename QUANTITY, typename SCALE, typename LABEL>
    class Unit final
    {

#ifdef __linux__
        static_assert(std::is_same<TYPE, float>::value ||
                          std::is_same<TYPE, double>::value ||
                          std::is_same<TYPE, long double>::value,
                      "==>> NOT ALLOWED WRAPPED TYPE! <<==");
#elif _WIN32
        static_assert(std::is_same_v<TYPE, float> ||
                          std::is_same_v<TYPE, double> ||
                          std::is_same_v<TYPE, long double>,
                      "==>> NOT ALLOWED WRAPPED TYPE! <<==");
#endif

    private:
        TYPE value_{};

    public:
        constexpr explicit Unit(TYPE value = 0) : value_{value} {}
        Unit(Unit const &other) = default;
        Unit(Unit &&other) noexcept = default;
        ~Unit() = default;

        Unit &operator=(Unit other) noexcept
        {
            std::swap(value_, other.value_);
            return *this;
        }

        /**
         * @brief `operator()`.
         * It returns the type wrapped by this class
         */
        TYPE operator()() const { return value_; }

        /**
         * @brief Prints a unit information.
         * It streams value, quantity, and scale information to the standard output.
         */
        void print() const
        {
            std::cout << (*this) << " ["
                      << "<" << QUANTITY::b0e.num << ":" << QUANTITY::b0e.den << ">"
                      << "<" << QUANTITY::b1e.num << ":" << QUANTITY::b1e.den << ">"
                      << "<" << QUANTITY::b2e.num << ":" << QUANTITY::b2e.den << ">"
                      << "<" << QUANTITY::b3e.num << ":" << QUANTITY::b3e.den << ">"
                      << "<" << QUANTITY::b4e.num << ":" << QUANTITY::b4e.den << ">"
                      << "<" << QUANTITY::b5e.num << ":" << QUANTITY::b5e.den << ">"
                      << "<" << QUANTITY::b6e.num << ":" << QUANTITY::b6e.den << ">"
                      << "<" << QUANTITY::b7e.num << ":" << QUANTITY::b7e.den << ">"
                      << "<" << QUANTITY::b8e.num << ":" << QUANTITY::b8e.den << ">"
                      << "<" << QUANTITY::b9e.num << ":" << QUANTITY::b9e.den << ">"
                      << " ; S=" << 1.0 * SCALE::up_ / SCALE::dn_ << "]\n";
        }

        template <typename TY, typename QU, typename SC, typename LA>
        friend std::istream &operator>>(std::istream &is, Unit<TY, QU, SC, LA> &a_unit);

        /**
         * @brief
         * Implicit linear conversion member function "operator type ()" from a unit to another of the same quantity
         * @tparam OTHER_SCALE scale type for unit linear conversion
         * @tparam OTHER_LABEL label type for tagging printed units
         * @return Unit<TYPE, QUANTITY, OTHER_SCALE, OTHER_LABEL>
         */
        template <typename OTHER_SCALE, typename OTHER_LABEL>
        operator Unit<TYPE, QUANTITY, OTHER_SCALE, OTHER_LABEL>() const
        {
            return Unit<TYPE, QUANTITY, OTHER_SCALE, OTHER_LABEL>{
                static_cast<TYPE>(1.0 * value_ * SCALE::up_ / SCALE::dn_ *
                                  OTHER_SCALE::dn_ / OTHER_SCALE::up_)};
        }

        Unit &operator+=(Unit const &other)
        {
            value_ += other.value_;
            return *this;
        }

        Unit &operator-=(Unit const &other)
        {
            value_ -= other.value_;
            return *this;
        }

        /**
         * @brief
         * @note `floating point` to `integer` conversion
         */
        Unit &operator%=(Unit const &other)
        {
            value_ = static_cast<int>(value_) % static_cast<int>(other.value_);
            return *this;
        }

        // prefix increment
        Unit &operator++()
        {
            value_++;
            return *this;
        }

        // postfix increment
        Unit operator++(int)
        {
            Unit old = *this;
            operator++();
            return old;
        }

        // prefix decrement
        Unit &operator--()
        {
            value_--;
            return *this;
        }

        // postfix decrement
        Unit operator--(int)
        {
            Unit old = *this;
            operator--();
            return old;
        }

    }; // Unit

    /// @cond
    namespace tag
    {
        struct numeral_label
        {
            numeral_label(){};
            std::string label_{"u_"};
        };

        struct numeral_rad_label
        {
            numeral_rad_label(){};
            std::string label_{"rad_"};
        };

        struct numeral_sr_label
        {
            numeral_sr_label(){};
            std::string label_{"sr_"};
        };
    } // namespace tag
    ///@endcond

    template <typename TY, typename LA = stu::tag::numeral_label>
    using numeral_unit = stu::Unit<TY, stu::Quantity<>,
                                   stu::Scale<1UL>,
                                   LA>;

    template <typename TY, class LA = stu::tag::numeral_rad_label>
    using numeral_rad = stu::Unit<TY, stu::Quantity<>,
                                  stu::Scale<50000000000000000UL,
                                             314159265358979323UL>,
                                  LA>;

    template <typename TY, typename LA = stu::tag::numeral_sr_label>
    using numeral_sr = stu::Unit<TY, stu::Quantity<>,
                                 stu::Scale<25000000000000000UL,
                                            314159265358979323UL>,
                                 LA>;

#ifdef STU_UNIT_TYPE
    using rad = stu::numeral_rad<STU_UNIT_TYPE>;
    using sr = stu::numeral_sr<STU_UNIT_TYPE>;
    using unit = stu::numeral_unit<STU_UNIT_TYPE>;
#endif

    /**
     * @brief It streams out the value of a unit.
     */
    template <typename TY, typename QU, typename SC, typename LA>
    std::ostream &operator<<(std::ostream &os, Unit<TY, QU, SC, LA> const &a_unit)
    {
        os << a_unit() << "*" << LA{}.label_;
        return os;
    }

    /**
     * @brief It streams in a numeric value to a unit.
     * @note It throws an instance of `std::invalid_argument` if the argument is not a number.
     */
    template <typename TY, typename QU, typename SC, typename LA>
    std::istream &operator>>(std::istream &is, Unit<TY, QU, SC, LA> &a_unit)
    {
        std::string data;
        is >> data;
        if (data.empty())
            is.setstate(std::ios::failbit);
        else
            a_unit.value_ = static_cast<TY>(std::stold(data));
        return is;
    }

    template <typename TY, typename QU, typename SC1, typename SC2, typename LA1, typename LA2>
    bool operator<(Unit<TY, QU, SC1, LA1> const &left, Unit<TY, QU, SC2, LA2> const &right)
    {
        return (left() < (static_cast<Unit<TY, QU, SC1, LA1>>(right))());
    }

    template <typename TY, typename QU, typename SC1, typename SC2, typename LA1, typename LA2>
    bool operator>(Unit<TY, QU, SC1, LA1> const &left, Unit<TY, QU, SC2, LA2> const &right)
    {
        return (right < left);
    }

    template <typename TY, typename QU, typename SC1, typename SC2, typename LA1, typename LA2>
    bool operator<=(Unit<TY, QU, SC1, LA1> const &left, Unit<TY, QU, SC2, LA2> const &right)
    {
        return (!(left > right));
    }

    template <typename TY, typename QU, typename SC1, typename SC2, typename LA1, typename LA2>
    bool operator>=(Unit<TY, QU, SC1, LA1> const &left, Unit<TY, QU, SC2, LA2> const &right)
    {
        return (!(left < right));
    }

    template <typename TY, typename QU, typename SC1, typename SC2, typename LA1, typename LA2>
    bool operator==(Unit<TY, QU, SC1, LA1> const &left, Unit<TY, QU, SC2, LA2> const &right)
    {
        return (!(left < right) && !(left > right));
    }

    template <typename TY, typename QU, typename SC1, typename SC2, typename LA1, typename LA2>
    bool operator!=(Unit<TY, QU, SC1, LA1> const &left, Unit<TY, QU, SC2, LA2> const &right)
    {
        return ((left < right) || (left > right));
    }

    template <typename TY, typename QU, typename SC1, typename SC2, typename LA1, typename LA2>
    Unit<TY, QU, SC1, LA1> operator+(Unit<TY, QU, SC1, LA1> first, Unit<TY, QU, SC2, LA2> const &second)
    {
        first += static_cast<Unit<TY, QU, SC1, LA1>>(second);
        return first;
    }

    template <typename TY, typename QU, typename SC1, typename SC2, typename LA1, typename LA2>
    Unit<TY, QU, SC1, LA1> operator-(Unit<TY, QU, SC1, LA1> first, Unit<TY, QU, SC2, LA2> const &second)
    {
        first -= static_cast<Unit<TY, QU, SC1, LA1>>(second);
        return first;
    }

    /**
     * @brief `floating point` to `integer` conversion
     */
    template <typename TY, typename QU, typename SC1, typename SC2, typename LA1, typename LA2>
    Unit<TY, QU, SC1, LA1> operator%(Unit<TY, QU, SC1, LA1> first, Unit<TY, QU, SC2, LA2> const &second)
    {
        first %= static_cast<Unit<TY, QU, SC1, LA1>>(second);
        return first;
    }

    /**
     * @brief It allows double*Unit.
     */
    template <typename TY, typename QU, typename SC, typename LA>
    auto operator*(long double const &first, Unit<TY, QU, SC, LA> const &second)
    {
        return Unit<TY, QU, SC, LA>{static_cast<TY>(first * second())};
    }

    /**
     * @brief It allows Unit*double.
     */
    template <typename TY, typename QU, typename SC, typename LA>
    auto operator*(Unit<TY, QU, SC, LA> const &first, long double const &second)
    {
        return Unit<TY, QU, SC, LA>{static_cast<TY>(first() * second)};
    }

    /**
     * @brief It allows Unit*Unit.
     */
    template <typename TY, typename QU1, typename SC1, typename QU2, typename SC2, typename LA1, typename LA2>
    auto operator*(Unit<TY, QU1, SC1, LA1> const &first, Unit<TY, QU2, SC2, LA2> const &second)
    {
        static constexpr auto sc_up{SC1::up_ * SC2::up_};
        static constexpr auto sc_dn{SC1::dn_ * SC2::dn_};

        struct combined_label
        {
            combined_label(){};
            std::string label_ = LA1{}.label_ + "*" + LA2{}.label_;
        };

        return Unit<TY,
                    utils::mul_quantities_t<QU1, QU2>,
                    Scale<sc_up, sc_dn>,
                    combined_label>{first() * second()};
    }

    /**
     * @brief It allows Unit/double.
     */
    template <typename TY, typename QU, typename SC, typename LA>
    auto operator/(Unit<TY, QU, SC, LA> const &numerator, long double const &denominator)
    {
        return Unit<TY, QU, SC, LA>{static_cast<TY>(numerator() / denominator)};
    }

    /**
     * @brief It allows double/Unit.
     */
    template <typename TY, typename QU, typename SC, typename LA>
    auto operator/(long double const &numerator, Unit<TY, QU, SC, LA> const &denominator)
    {
        stu::numeral_unit<TY> num_unit{static_cast<TY>(numerator)};
        return (num_unit / denominator);
    }

    /**
     * @brief It allows Unit/Unit.
     */
    template <typename TY, typename QU1, typename SC1, typename QU2, typename SC2, typename LA1, typename LA2>
    auto operator/(Unit<TY, QU1, SC1, LA1> const &numerator, Unit<TY, QU2, SC2, LA2> const &denominator)
    {
        static constexpr auto sc_up{SC1::up_ * SC2::dn_};
        static constexpr auto sc_dn{SC1::dn_ * SC2::up_};

        struct combined_label
        {
            combined_label(){};
            std::string label_ = LA1{}.label_ + "*(" + LA2{}.label_ + ")^-1";
        };

        return Unit<TY,
                    utils::div_quantities_t<QU1, QU2>,
                    Scale<sc_up, sc_dn>,
                    combined_label>{numerator() / denominator()};
    }

    // MATH FUNCTIONS
    template <typename TY, typename QU, typename SC1, typename SC2, typename LA1, typename LA2>
    Unit<TY, QU, SC1, LA1> max(Unit<TY, QU, SC1, LA1> first, Unit<TY, QU, SC2, LA2> second)
    {
        return (first > second) ? first : static_cast<Unit<TY, QU, SC1, LA1>>(second);
    }

    template <typename TY, typename QU, typename SC1, typename SC2, typename LA1, typename LA2>
    Unit<TY, QU, SC1, LA1> min(Unit<TY, QU, SC1, LA1> first, Unit<TY, QU, SC2, LA2> second)
    {
        return (first < second) ? first : static_cast<Unit<TY, QU, SC1, LA1>>(second);
    }

    template <typename TY, typename QU, typename SC, typename LA>
    auto abs(Unit<TY, QU, SC, LA> const &value)
    {
        return Unit<TY, QU, SC, LA>{std::abs(value())};
    }

    template <typename TY, typename QU, typename SC, typename LA>
    auto ceil(Unit<TY, QU, SC, LA> const &value)
    {
        return Unit<TY, QU, SC, LA>{std::ceil(value())};
    }

    template <typename TY, typename QU, typename SC, typename LA>
    auto floor(Unit<TY, QU, SC, LA> const &value)
    {
        return Unit<TY, QU, SC, LA>{std::floor(value())};
    }

    template <typename TY, typename QU, typename SC, typename LA>
    auto round(Unit<TY, QU, SC, LA> const &value)
    {
        return Unit<TY, QU, SC, LA>{std::round(value())};
    }

    template <typename TY, typename LA>
    auto exp(stu::numeral_unit<TY, LA> const &value)
    {
        return stu::numeral_unit<TY>{std::exp(value())};
    }

    template <typename TY, typename LA>
    auto log(stu::numeral_unit<TY, LA> const &value)
    {
        return stu::numeral_unit<TY>{std::log(value())};
    }

    template <typename TY, typename LA>
    auto log10(stu::numeral_unit<TY, LA> const &value)
    {
        return stu::numeral_unit<TY>{std::log10(value())};
    }

    template <typename TY, typename LA>
    auto sin(stu::numeral_rad<TY, LA> const &value)
    {
        return stu::numeral_unit<TY>{std::sin(value())};
    }

    template <typename TY, typename LA>
    auto cos(stu::numeral_rad<TY, LA> const &value)
    {
        return stu::numeral_unit<TY>{std::cos(value())};
    }

    template <typename TY, typename LA>
    auto tan(stu::numeral_rad<TY, LA> const &value)
    {
        return stu::numeral_unit<TY>{std::tan(value())};
    }

    template <typename TY, typename LA>
    auto asin(stu::numeral_unit<TY, LA> const &value)
    {
        return stu::numeral_unit<TY>{std::asin(value())};
    }

    template <typename TY, typename LA>
    auto acos(stu::numeral_unit<TY, LA> const &value)
    {
        return stu::numeral_unit<TY>{std::acos(value())};
    }

    template <typename TY, typename LA>
    auto atan(stu::numeral_unit<TY, LA> const &value)
    {
        return stu::numeral_unit<TY>{std::atan(value())};
    }

    template <typename TY, typename LA>
    auto sinh(stu::numeral_unit<TY, LA> const &value)
    {
        return stu::numeral_unit<TY>{std::sinh(value())};
    }

    template <typename TY, typename LA>
    auto cosh(stu::numeral_unit<TY, LA> const &value)
    {
        return stu::numeral_unit<TY>{std::cosh(value())};
    }

    template <typename TY, typename LA>
    auto tanh(stu::numeral_unit<TY, LA> const &value)
    {
        return stu::numeral_unit<TY>{std::tanh(value())};
    }

    template <typename TY, typename LA>
    auto asinh(stu::numeral_unit<TY, LA> const &value)
    {
        return stu::numeral_unit<TY>{std::asinh(value())};
    }

    template <typename TY, typename LA>
    auto acosh(stu::numeral_unit<TY, LA> const &value)
    {
        return stu::numeral_unit<TY>{std::acosh(value())};
    }

    template <typename TY, typename LA>
    auto atanh(stu::numeral_unit<TY, LA> const &value)
    {
        return stu::numeral_unit<TY>{std::atanh(value())};
    }

    template <typename TY, typename LA>
    auto pow(stu::numeral_unit<TY, LA> const &base,
             long double const &exponent)
    {
        return stu::numeral_unit<TY>{std::pow(base(), static_cast<TY>(exponent))};
    }

    template <typename TY, typename LA>
    auto pow(stu::numeral_unit<TY, LA> const &base,
             stu::numeral_unit<TY, LA> const &exponent)
    {
        return stu::numeral_unit<TY>{std::pow(base(), exponent())};
    }

    template <std::intmax_t exponent, typename TY, typename QU, typename SC, typename LA>
    auto pow(Unit<TY, QU, SC, LA> const &base)
    {
        static constexpr auto p_sc_up{utils::ipow(SC::up_, exponent)};
        static constexpr auto p_sc_dn{utils::ipow(SC::dn_, exponent)};
        static constexpr auto n_sc_up{utils::ipow(SC::dn_, 0 - exponent)};
        static constexpr auto n_sc_dn{utils::ipow(SC::up_, 0 - exponent)};

        struct combined_label
        {
            combined_label(){};
            std::string label_ = "(" + LA{}.label_ + ")^" + std::to_string(exponent);
        };

        return Unit<TY,
                    utils::pow_quantities_t<QU, std::ratio<exponent>>,
                    std::conditional_t<(exponent >= 0),
                                       Scale<p_sc_up, p_sc_dn>,
                                       Scale<n_sc_up, n_sc_dn>>,
                    combined_label>{static_cast<TY>(std::pow(base(), exponent))};
    }

    template <typename TY, typename LA>
    auto sqrt(stu::numeral_unit<TY, LA> const &value)
    {
        return stu::numeral_unit<TY>{std::sqrt(value())};
    }

    template <typename TY, typename QU, typename SC, typename LA>
    auto sqrt(Unit<TY, QU, SC, LA> const &value)
    {
        constexpr auto sc_up{utils::isqrt(SC::up_)};
        constexpr auto sc_dn{utils::isqrt(SC::dn_)};
        static_assert(sc_up > 0 && sc_dn > 0, "==>> UNVALID SCALE! <<==");

        struct combined_label
        {
            combined_label(){};
            std::string label_ = "(" + LA{}.label_ + ")^1/2";
        };

        return Unit<TY,
                    utils::pow_quantities_t<QU, std::ratio<1, 2>>,
                    Scale<sc_up, sc_dn>,
                    combined_label>{std::sqrt(value())};
    }

    /**
     * @brief
     * Namespace in which strong unit constants are defined.
     * Namely : numeral unit zero (`_0`), one (`_1`), π number (`PI`),
     * Euler's number (`E`) and complex imaginary unit (`j`)
     */
    namespace constants
    {
#ifdef STU_UNIT_TYPE
        static constexpr const unit PI{3.14159265358979323};
        static constexpr const unit E{2.71828182845904523};
        static constexpr const unit _0{0};
        static constexpr const unit _1{1};
#endif
    } // namespace constants

} // namespace stu

#endif // STRONGUNIT_H