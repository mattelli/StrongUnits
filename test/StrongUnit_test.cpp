/**
 * @file StrongUnit_test.cpp
 * @author Massimo Mattelliano (mattemax@yahoo.com)
 * @brief
 * A set of tests for StrongUnit
 * @copyright Copyright (c) 2022
 * MIT License
 */
#include "gtest/gtest.h"
#include "src/lib/StrongTypeDefinition.h"
#include "src/lib/StrongUnit.h"

using namespace stu::literals;
using namespace stu::symbols;
using namespace stu::constants;

namespace stu
{
    DEF_QUANTITY(Numeral)
    DEF_QUANTITY(Time, std::ratio<1>)
    DEF_QUANTITY(Length, std::ratio<0>, std::ratio<1>)
    DEF_QUANTITY(Velocity, std::ratio<-1>, std::ratio<1>)

    DEF_SCALE(unity, 1U)
    DEF_SCALE(kilo, 1000U)
    DEF_SCALE(s2min, 60U)

    DEF_UNIT(Length, meter, STU_UNIT_TYPE, _m, unity)
    DEF_UNIT(Length, kilometer, STU_UNIT_TYPE, _km, kilo)
    DEF_UNIT(Time, second, STU_UNIT_TYPE, _s, unity)
    DEF_UNIT(Time, minute, STU_UNIT_TYPE, _min, s2min)
    DEF_UNIT(Velocity, meter_per_second, STU_UNIT_TYPE, _mps, unity)
}

// Allowed wrapped types
template class stu::Unit<float, stu::Numeral, stu::unity, stu::tag::numeral_label>;
template class stu::Unit<double, stu::Numeral, stu::unity, stu::tag::numeral_label>;
template class stu::Unit<long double, stu::Numeral, stu::unity, stu::tag::numeral_label>;

TEST(StrongUnit, Implicit_conversion_length)
{
    stu::meter a = 10.0_m;
    stu::kilometer b{0.0};
    b = a;
    EXPECT_EQ(b() - 0.01, 0.0);
}

TEST(StrongUnit, Implicit_conversion_Time)
{
    stu::second s = 30.0_s;
    stu::minute m = 0.0_min;
    m = s;
    EXPECT_EQ(m(), 0.5);
}

TEST(StrongUnit, Addition_compound_length)
{
    stu::meter a = 10.0_m;
    a += 5.0_m;
    EXPECT_EQ(a(), 15.0);
}

TEST(StrongUnit, Subtraction_compound_length)
{
    stu::meter a = 10.0_m;
    a -= 5.0_m;
    EXPECT_EQ(a(), 5.0);
}

TEST(StrongUnit, Implicit_conversion_addition_compound_length)
{
    stu::meter a = 10.0_m;
    a += 0.5_km;
    EXPECT_EQ(a(), 510.0);
}

TEST(StrongUnit, Implicit_conversion_subtraction_compound_length)
{
    stu::kilometer a = 10.0_km;
    a -= 500.0_m;
    EXPECT_EQ(a(), 9.5);
}

TEST(StrongUnit, Addition_two_length)
{
    stu::meter a = 10.0_m;
    stu::meter b{20.0};
    EXPECT_EQ((a + b)(), 30.0);
    EXPECT_EQ((b + a)(), 30.0);
}

TEST(StrongUnit, Subtraction_two_length)
{
    stu::meter a = 10.0_m;
    stu::meter b{20.0};
    EXPECT_EQ((a - b)(), -10.0);
    EXPECT_EQ((b - a)(), 10.0);
}

TEST(StrongUnit, Addition_three_length)
{
    stu::meter a = 10.0_m;
    stu::meter b{20.0};
    stu::meter c = 5.0_m;
    EXPECT_EQ((a + b + c)(), 35.0);
    EXPECT_EQ((c + b + a)(), 35.0);
}

TEST(StrongUnit, Subtraction_three_length)
{
    stu::meter a = 10.0_m;
    stu::meter b{20.0};
    stu::meter c = 5.0_m;
    EXPECT_EQ((a - b - c)(), -15.0);
    EXPECT_EQ((c - b - a)(), -25.0);
}

TEST(StrongUnit, Addition_conversion_two_length)
{
    stu::meter a = 10.0_m;
    stu::kilometer b{0.5};
    stu::meter c = a + b;
    stu::kilometer d = b + a;
    EXPECT_EQ(c(), 510.0);
    EXPECT_EQ(d() - 0.51, 0.0);
}

TEST(StrongUnit, Subtraction_conversion_two_length)
{
    stu::meter a = 10.0_m;
    stu::kilometer b{0.5};
    stu::meter c = a - b;
    stu::kilometer d = b - a;
    EXPECT_EQ(c(), -490.0);
    EXPECT_EQ(d() - 0.49, 0.0);
}

TEST(StrongUnit, Addition_conversion_three_length)
{
    stu::meter a = 10.0_m;
    stu::meter b{20.0};
    stu::kilometer c = 500.0_m;
    auto d = a + b + c; // d and a same unity
    EXPECT_EQ(d(), 530.0);
    auto e = c + b + a; // e and c same unity
    EXPECT_EQ(e() - 0.53, 0.0);
}

TEST(StrongUnit, Subtraction_conversion_three_length)
{
    stu::kilometer a = 10.0_m;
    stu::meter b{20.0};
    stu::meter c = 5.0_m;
    auto d = a - b - c; // d and a same unity
    EXPECT_EQ(d() + 0.015, 0.0);
    auto e = b - c - a; // e and b same unity
    EXPECT_EQ(e(), 5.0);
}

TEST(StrongUnit, Prefix_increment_decrement)
{
    stu::meter a = 1.0_m;
    stu::meter b = ++a;
    EXPECT_EQ(b, a);

    auto s = 1.0_s;
    auto w = --s;
    EXPECT_EQ(w, s);
}

TEST(StrongUnit, Postfix_increment_decrement)
{
    stu::meter a = 1.0_m;
    stu::meter b = a++;
    EXPECT_EQ((b + 1.0_m), a);

    auto s = 1.0_s;
    auto w = s--;
    EXPECT_EQ((w - 1.0_s), s);
}

TEST(StrongUnit, Comparision_operators)
{
    stu::meter a = 1.0_m;
    stu::meter b = a;
    b += a;
    EXPECT_EQ((a < b), true);
    EXPECT_EQ((a <= a), true);
    EXPECT_EQ((b > a), true);
    EXPECT_EQ((b >= b), true);
    EXPECT_EQ((a == a), true);
    EXPECT_EQ((b != a), true);
}

TEST(StrongUnit, Comparision_operators_conversion)
{
    stu::meter a = 1.0_m;
    stu::kilometer b = 0.5_km;
    EXPECT_EQ((a < b), true);
    EXPECT_EQ((a <= a), true);
    EXPECT_EQ((b > a), true);
    EXPECT_EQ((b >= b), true);

    stu::meter c = 100.0_m;
    stu::kilometer d = 0.1_km;
    EXPECT_EQ((c == d), true);
    EXPECT_EQ((c != b), true);
}

TEST(StrongUnit, multiply_division_operators_conversion)
{
    stu::meter a = 1.0_m;
    stu::kilometer b = 2.0 * a * 2.0;
    EXPECT_EQ(b, 4.0_m);
    EXPECT_EQ(b / 4.0, 1.0_m);

    a = 5.0_m;
    stu::meter c = 2.0 * a + b;
    EXPECT_EQ(c, 14.0_m);

    c = 2 * a - b;
    EXPECT_EQ(c, 6.0_m);
    EXPECT_EQ(6 / c, 1.0 / 1.0_m);

    EXPECT_EQ(2.0 * a + b, a * 2.0 + b);
    EXPECT_EQ(2 * a + b, b + a * 2.0);
}

TEST(StrongUnit, units_multiplication_operator_conversion)
{
    auto a = 10.0_mps;
    auto b = 2.0_s;
    EXPECT_EQ(a * b, 20.0_m);
    EXPECT_EQ(b * a, 20.0_m);
}

TEST(StrongUnit, units_division_operator_conversion)
{
    auto a = 10.0_km;
    auto b = 2.0_s;
    EXPECT_EQ(a / b, 5000.0_mps);
}

TEST(StrongUnit, units_modulo_conversion)
{
    auto sec = 130.9_s;
    auto sec1 = 60.1_s;
    sec %= sec1; // 130.0_s and 60.0_s are actually considered (floating point to integer conversion)
    EXPECT_EQ(sec, 10.0_s);

    sec = 130.0_s;
    auto min = 1.0_min;
    sec %= min;
    EXPECT_EQ(sec, 10.0_s);

    sec = 130.0_s % 60.0_s;
    EXPECT_EQ(sec, 10.0_s);

    sec = 130.0_s % 1.0_min;
    EXPECT_EQ(sec, 10.0_s);
}

TEST(StrongUnit, max_min_conversion)
{
    stu::meter a = 1.0_m;
    stu::meter b = 2.0_m;
    EXPECT_EQ(stu::max(a, b), b);
    EXPECT_EQ(stu::max(b, a), b);
    EXPECT_EQ(stu::min(a, b), a);
    EXPECT_EQ(stu::min(b, a), a);

    stu::meter c = 10.0_m;
    stu::kilometer d = 3.0_m;
    EXPECT_EQ(d, 0.003_km);
    EXPECT_EQ(stu::max(c, d), c);
    EXPECT_EQ(stu::max(d, c), c);
    EXPECT_EQ(stu::min(c, d), d);
    EXPECT_EQ(stu::min(d, c), d);

    stu::meter e = stu::max(a, b);
    stu::meter f = stu::min(c, d);
    EXPECT_EQ(stu::max(e, f), f);
    EXPECT_EQ(stu::max(f, e), f);
    EXPECT_EQ(stu::min(e, f), e);
    EXPECT_EQ(stu::min(f, e), e);
}

TEST(StrongUnit, units_abs_conversion)
{
    stu::meter a = 1000.0_m;
    stu::kilometer b = 2.0_km;
    EXPECT_EQ(stu::abs(a - b), 1.0_km);
    EXPECT_EQ(stu::abs(b - a), 1000.0_m);

    stu::meter c = stu::abs(a - b);
    EXPECT_EQ(c, 1.0_km);

    stu::kilometer d = stu::abs(b - a);
    EXPECT_EQ(d, 1000.0_m);
}

TEST(StrongUnit, units_ceil_conversion)
{
    stu::kilometer a{2.7};
    EXPECT_EQ(stu::ceil(a), 3 * _km);

    stu::kilometer b{-2.7};
    EXPECT_EQ(stu::ceil(b), -1.0 * 2 * _km);
}

TEST(StrongUnit, units_floor_conversion)
{
    stu::kilometer a{2.7};
    EXPECT_EQ(stu::floor(a), 2 * _km);

    stu::kilometer b{-2.7};
    EXPECT_EQ(stu::floor(b), -1.0 * 3 * _km);
}

TEST(StrongUnit, units_round_conversion)
{
    stu::kilometer a{2.5};
    EXPECT_EQ(stu::round(a), 3 * _km);

    stu::meter b{2.4};
    EXPECT_EQ(stu::round(b), 2.0_m);

    stu::kilometer c{-2.5};
    EXPECT_EQ(stu::round(c), -1 * 3 * _km);

    stu::meter d{-2.3};
    EXPECT_EQ(stu::round(d), -1 * 2.0_m);
}

TEST(StrongUnit, units_exp_conversion)
{
    stu::meter b = 0.002_km;
    auto d = stu::exp(b / 1.0_m);
    auto dd = std::exp(b());

    EXPECT_EQ(d(), dd);

    auto e = stu::exp(_1);
    EXPECT_EQ(e, E);
}

TEST(StrongUnit, units_log_conversion)
{
    stu::meter b = 0.002_km;
    auto d = stu::log(b / 1.0_m);
    auto dd = std::log(b());

    EXPECT_EQ(d(), dd);
}

TEST(StrongUnit, units_log10_conversion)
{
    stu::meter b = 0.002_km;
    auto d = stu::log10(b / 1.0_m);
    auto dd = std::log10(b());

    EXPECT_EQ(d(), dd);
}

TEST(StrongUnit, units_sin_conversion)
{
    stu::meter b = 0.002_km;
    stu::rad arg = b / 1.0_m;
    auto d = stu::sin(arg);
    auto dd = std::sin(arg());

    EXPECT_EQ(d(), dd);
}

TEST(StrongUnit, units_cos_conversion)
{
    stu::meter b = 0.002_km;
    stu::rad arg = b / 1.0_m;
    auto d = stu::cos(arg);
    auto dd = std::cos(arg());

    EXPECT_EQ(d(), dd);
}

TEST(StrongUnit, units_tan_conversion)
{
    stu::meter b = 0.002_km;
    stu::rad arg = b / 1.0_m;
    auto d = stu::tan(arg);
    auto dd = std::tan(arg());

    EXPECT_EQ(d(), dd);
}

TEST(StrongUnit, units_asin_conversion)
{
    stu::meter b = 0.0002_km;
    auto d = stu::asin(b / 1.0_m);
    auto dd = std::asin(b());

    EXPECT_EQ(d(), dd);
}

TEST(StrongUnit, units_acos_conversion)
{
    stu::meter b = 0.0002_km;
    auto d = stu::acos(b / 1.0_m);
    auto dd = std::acos(b());

    EXPECT_EQ(d(), dd);

    auto ac = stu::acos(-1 * _1);
    EXPECT_EQ(ac, PI);
}

TEST(StrongUnit, units_atan_conversion)
{
    stu::meter b = 0.0002_km;
    auto d = stu::atan(b / 1.0_m);
    auto dd = std::atan(b());

    EXPECT_EQ(d(), dd);
}

TEST(StrongUnit, units_sinh_conversion)
{
    stu::meter b = 0.002_km;
    auto d = stu::sinh(b / 1.0_m);
    auto dd = std::sinh(b());

    EXPECT_EQ(d(), dd);
}

TEST(StrongUnit, units_cosh_conversion)
{
    stu::meter b = 0.002_km;
    auto d = stu::cosh(b / 1.0_m);
    auto dd = std::cosh(b());

    EXPECT_EQ(d(), dd);
}

TEST(StrongUnit, units_tanh_conversion)
{
    stu::meter b = 0.002_km;
    auto d = stu::tanh(b / 1.0_m);
    auto dd = std::tanh(b());

    EXPECT_EQ(d(), dd);
}

TEST(StrongUnit, units_asinh_conversion)
{
    stu::meter b = 0.002_km;
    auto d = stu::asinh(b / 1.0_m);
    auto dd = std::asinh(b());

    EXPECT_EQ(d(), dd);
}

TEST(StrongUnit, units_acosh_conversion)
{
    stu::meter b = 0.002_km;
    auto d = stu::acosh(b / 1.0_m);
    auto dd = std::acosh(b());

    EXPECT_EQ(d(), dd);
}

TEST(StrongUnit, units_atanh_conversion)
{
    stu::meter b = 0.0005_km;
    auto d = stu::atanh(b / 1.0_m);
    auto dd = std::atanh(b());

    EXPECT_EQ(d(), dd);
}

TEST(StrongUnit, units_pow_conversion)
{
    stu::meter b = 0.0005_km;
    stu::meter e = 2.0_m;
    auto d = stu::pow(b / 1.0_m, e / 1.0_m);
    auto dd = std::pow(b(), e());

    EXPECT_EQ(d(), dd);

    auto a = stu::pow(b / 1.0_m, 2.0);
    EXPECT_EQ(a(), dd);

    auto aa = stu::pow<2>(b);
    EXPECT_EQ(aa(), dd);

    auto cc = stu::pow<-2>(b);
    EXPECT_EQ(cc(), 1 / dd);
}

TEST(StrongUnit, units_sqrt_conversion)
{
    auto b = 5.0_km * 5.0_km;
    stu::meter d = stu::sqrt(b);
    auto dd = std::sqrt(b());

    EXPECT_EQ(d(), dd * 1000);

    stu::unit a = stu::sqrt(b / (_m * _m));

    EXPECT_EQ(a(), dd * 1000);
}

/*/
//*/