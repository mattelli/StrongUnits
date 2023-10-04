/**
 * @file StrongCUnit_test.cpp
 * @author Massimo Mattelliano (mattemax@yahoo.com)
 * @brief
 * A set of tests for StrongCUnit
 * @copyright Copyright (c) 2022
 * MIT License
 */
#include "gtest/gtest.h"
#include "src/lib/StrongTypeDefinition.h"
#include "src/lib/StrongCUnit.h"

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

/*///Unallowed wrapped types
template class stu::CUnit<float>;
template class stu::CUnit<double>;
template class stu::CUnit<long double>;
template class stu::CUnit<long>;
template class stu::CUnit<short>;
template class stu::CUnit<int>;
template class stu::CUnit<unsigned int>;
template class stu::CUnit<size_t>; //*/

TEST(StrongCUnit, Implicit_conversion_conjugate_time)
{
    stu::CUnit<stu::minute> a{1.0_min, 1.0_s};
    stu::CUnit<stu::second> b{1.0_min, -1 * 1.0_s};
    EXPECT_EQ(b, a.conj());
}

TEST(StrongCUnit, norm_time)
{
    stu::CUnit<stu::second> a{1.0_s, 1.0_s};
    EXPECT_EQ(a.norm(), 2 * 1.0_s * 1.0_s);
}

TEST(StrongCUnit, Implicit_conversion_length)
{
    stu::CUnit<stu::meter> a{10.0_m, 1.0_km};
    stu::CUnit<stu::kilometer> b{};
    b = a;
    EXPECT_EQ(b, a);
    EXPECT_EQ(b.real()() - 0.01, 0.0);
    EXPECT_EQ(b.imag()(), 1.0);
}

TEST(StrongCUnit, Addition_compound_time)
{
    stu::CUnit<stu::second> a{10.0_s, 1.0_s};
    a += stu::CUnit<stu::second>{5.0_s};
    EXPECT_EQ(a, (stu::CUnit<stu::second>{15.0_s, 1.0_s}));
    EXPECT_EQ(a.real()(), 15.0);
    EXPECT_EQ(a.imag()(), 1.0);
}

TEST(StrongCUnit, Subtraction_compound_length)
{
    stu::CUnit<stu::meter> a{10.0_m};
    a -= stu::CUnit<stu::meter>{5.0_m, 1.0_m};
    EXPECT_EQ(a, (stu::CUnit<stu::meter>{5.0_m, -1 * 1.0_m}));
    EXPECT_EQ(a.real()(), 5.0);
    EXPECT_EQ(a.imag()(), -1.0);
}

TEST(StrongCUnit, Implicit_conversion_addition_compound_length)
{
    stu::CUnit<stu::meter> a{10.0_m};
    a += stu::CUnit<stu::kilometer>{5.0_km, 0.5_km};
    EXPECT_EQ(a, (stu::CUnit<stu::meter>{5010.0_m, 500.0_m}));
    EXPECT_EQ(a.real()(), 5010.0);
    EXPECT_EQ(a.imag()(), 500.0);
}

TEST(StrongCUnit, Implicit_conversion_subtraction_compound_length)
{
    stu::CUnit<stu::meter> a{10.0_m};
    a -= stu::CUnit<stu::kilometer>{5.0_km, 0.5_km};
    EXPECT_EQ(a, (stu::CUnit<stu::meter>{-1 * 4990.0_m, -1 * 500.0_m}));
    EXPECT_EQ(a.real()(), -4990.0);
    EXPECT_EQ(a.imag()(), -500.0);
}

TEST(StrongCUnit, Addition_two_length)
{
    stu::CUnit<stu::meter> a{10.0_m, 5.0_m};
    stu::CUnit<stu::meter> b{20.0_m, 10.0_m};
    EXPECT_EQ((a + b), (stu::CUnit<stu::meter>{30.0_m, 15.0_m}));
    EXPECT_EQ((a + b).real()(), 30.0);
    EXPECT_EQ((a + b).imag()(), 15.0);
    EXPECT_EQ((b + a), (stu::CUnit<stu::meter>{30.0_m, 15.0_m}));
    EXPECT_EQ((b + a).real()(), 30.0);
    EXPECT_EQ((b + a).imag()(), 15.0);
}

TEST(StrongCUnit, Subtraction_two_length)
{
    stu::CUnit<stu::meter> a{10.0_m, 5.0_m};
    stu::CUnit<stu::meter> b{20.0_m, 10.0_m};
    EXPECT_EQ((a - b), (stu::CUnit<stu::meter>{-1 * 10.0_m, -1 * 5.0_m}));
    EXPECT_EQ((a - b).real()(), -10.0);
    EXPECT_EQ((a - b).imag()(), -5.0);
    EXPECT_EQ((b - a), (stu::CUnit<stu::meter>{10.0_m, 5.0_m}));
    EXPECT_EQ((b - a).real()(), 10.0);
    EXPECT_EQ((b - a).imag()(), 5.0);
}

TEST(StrongCUnit, Addition_three_length)
{
    stu::CUnit<stu::meter> a{10.0_m, 5.0_m};
    stu::CUnit<stu::meter> b{20.0_m, 10.0_m};
    stu::CUnit<stu::meter> c{5.0_m, 1.0_m};
    EXPECT_EQ((a + b + c), (stu::CUnit<stu::meter>{35.0_m, 16.0_m}));
    EXPECT_EQ((a + b + c).real()(), 35.0);
    EXPECT_EQ((a + b + c).imag()(), 16.0);
    EXPECT_EQ((c + b + a), (stu::CUnit<stu::meter>{35.0_m, 16.0_m}));
    EXPECT_EQ((c + b + a).real()(), 35.0);
    EXPECT_EQ((c + b + a).imag()(), 16.0);
}

TEST(StrongCUnit, Subtraction_three_length)
{
    stu::CUnit<stu::meter> a{10.0_m, 5.0_m};
    stu::CUnit<stu::meter> b{20.0_m, 10.0_m};
    stu::CUnit<stu::meter> c{5.0_m, 1.0_m};
    EXPECT_EQ((a - b - c), (stu::CUnit<stu::meter>{-1 * 15.0_m, -1 * 6.0_m}));
    EXPECT_EQ((a - b - c).real()(), -15.0);
    EXPECT_EQ((a - b - c).imag()(), -6.0);
    EXPECT_EQ((c - b - a), (stu::CUnit<stu::meter>{-1 * 25.0_m, -1 * 14.0_m}));
    EXPECT_EQ((c - b - a).real()(), -25.0);
    EXPECT_EQ((c - b - a).imag()(), -14.0);
}

TEST(StrongCUnit, Addition_conversion_two_length)
{
    stu::CUnit<stu::meter> a{10.0_m, 5.0_m};
    stu::CUnit<stu::kilometer> b{0.5_km, 0.1_km};
    auto c = a + b;
    auto d = b + a;
    EXPECT_EQ(c.real()(), 510.0);
    EXPECT_EQ(c.imag()(), 105.0);
    EXPECT_EQ(d.real()() - 0.51, 0.0);
    EXPECT_FLOAT_EQ(d.imag()(), 0.105);
}

TEST(StrongCUnit, Subtraction_conversion_two_length)
{
    stu::CUnit<stu::meter> a{10.0_m, 5.0_m};
    stu::CUnit<stu::kilometer> b{0.5_km, 0.1_km};
    auto c = a - b;
    auto d = b - a;
    EXPECT_EQ(c.real()(), -490.0);
    EXPECT_EQ(c.imag()(), -95.0);
    EXPECT_EQ(d.real()() - 0.49, 0.0);
    EXPECT_EQ(d.imag()() - 0.095, 0.0);
}

TEST(StrongCUnit, Addition_conversion_three_length)
{
    stu::CUnit<stu::meter> a{10.0_m, 1.0_m};
    stu::CUnit<stu::meter> b{20.0_m, 2.0_m};
    stu::CUnit<stu::kilometer> c{500.0_m, 50.0_m};
    auto d = a + b + c; // d and a same unity
    EXPECT_EQ(d.real()(), 530.0);
    EXPECT_EQ(d.imag()(), 53.0);
    auto e = c + b + a; // e and c same unity
    EXPECT_EQ(e.real()() - 0.530, 0.0);
    EXPECT_NEAR(e.imag()() - 0.053, 0.0, 6.94e-18);
}

TEST(StrongCUnit, Subtraction_conversion_three_length)
{
    stu::CUnit<stu::kilometer> a{10.0_m, 1.0_m};
    stu::CUnit<stu::meter> b{20.0_m, 2.0_m};
    stu::CUnit<stu::meter> c{5.0_m, 0.5_m};
    auto d = a - b - c; // d and a same unity
    EXPECT_EQ(d.real()() + 0.015, 0.0);
    EXPECT_EQ(d.imag()() + 0.0015, 0.0);
    auto e = b - c - a; // e and b same unity
    EXPECT_EQ(e.real()(), 5.0);
    EXPECT_EQ(e.imag()() - 0.5, 0.0);
}

TEST(StrongCUnit, Prefix_increment_decrement)
{
    stu::CUnit<stu::meter> a{1.0_m, 1.0_m};
    EXPECT_EQ(++a, (stu::CUnit<stu::meter>{2.0_m, 2.0_m}));
    EXPECT_EQ(a, (stu::CUnit<stu::meter>{2.0_m, 2.0_m}));

    stu::CUnit<stu::second> s{2.0_s, 2.0_s};
    EXPECT_EQ(--s,(stu::CUnit<stu::second>{1.0_s, 1.0_s}));
    EXPECT_EQ(s, (stu::CUnit<stu::second>{1.0_s, 1.0_s}));
}

TEST(StrongCUnit, Postfix_increment_decrement)
{
    stu::CUnit<stu::meter> a{1.0_m, 1.0_m};
    EXPECT_EQ(a++, (stu::CUnit<stu::meter>{1.0_m, 1.0_m}));
    EXPECT_EQ(a, (stu::CUnit<stu::meter>{2.0_m, 2.0_m}));

    stu::CUnit<stu::second> s{2.0_s, 2.0_s};
    EXPECT_EQ(s--, (stu::CUnit<stu::second>{2.0_s, 2.0_s}));
    EXPECT_EQ(s, (stu::CUnit<stu::second>{1.0_s, 1.0_s}));
}

TEST(StrongCUnit, Comparision_operators)
{
    stu::CUnit<stu::meter> a{1.0_m, 5.0_m};
    auto b = a;
    b += a;
    EXPECT_EQ((a == a), true);
    EXPECT_EQ((b != a), true);
}

TEST(StrongCUnit, Comparision_operators_conversion)
{
    stu::CUnit<stu::kilometer> b{0.5_km};
    stu::CUnit<stu::meter> c{100.0_m};
    stu::CUnit<stu::kilometer> d{0.1_km};
    EXPECT_EQ((c == d), true);
    EXPECT_EQ((c != b), true);
}

TEST(StrongCUnit, Hybrid_addition_two_length)
{
    stu::CUnit<stu::meter> a{10.0_m, 5.0_m};
    EXPECT_EQ((a + 20.0_m), (stu::CUnit<stu::meter>{30.0_m, 5.0_m}));
    EXPECT_EQ((a + 20.0_m).real()(), 30.0);
    EXPECT_EQ((a + 20.0_m).imag()(), 5.0);
    EXPECT_EQ((20.0_m + a), (stu::CUnit<stu::meter>{30.0_m, 5.0_m}));
    EXPECT_EQ((20.0_m + a).real()(), 30.0);
    EXPECT_EQ((20.0_m + a).imag()(), 5.0);
}

TEST(StrongCUnit, Hybrid_subtraction_two_length)
{
    stu::CUnit<stu::meter> a{10.0_m, 5.0_m};
    EXPECT_EQ((a - 20.0_m), (stu::CUnit<stu::meter>{-1 * 10.0_m, 5.0_m}));
    EXPECT_EQ((a - 20.0_m).real()(), -10.0);
    EXPECT_EQ((a - 20.0_m).imag()(), 5.0);
    EXPECT_EQ((20.0_m - a), (stu::CUnit<stu::meter>{10.0_m, -1 * 5.0_m}));
    EXPECT_EQ((20.0_m - a).real()(), 10.0);
    EXPECT_EQ((20.0_m - a).imag()(), -5.0);
}

TEST(StrongCUnit, Hybrid_addition_three_length_conversion)
{
    stu::CUnit<stu::meter> a{10.0_m, 1.0_m};
    stu::CUnit<stu::kilometer> c{500.0_m, 1.0_m};
    EXPECT_EQ((a + 100.0_m + c), (stu::CUnit<stu::meter>{610.0_m, 2.0_m}));
    EXPECT_EQ((a + 100.0_m + c).real()(), 610.0);
    EXPECT_EQ((a + 100.0_m + c).imag()(), 2.0);
    EXPECT_EQ((c + 100.0_m + a), (stu::CUnit<stu::kilometer>{0.610_km, 0.002_km}));
    EXPECT_EQ((c + 100.0_m + a).real()() - 0.610, 0.0);
    EXPECT_EQ((c + 100.0_m + a).imag()() - 0.002, 0.0);
}

TEST(StrongCUnit, Hybrid_subtraction_three_length_conversion)
{
    stu::CUnit<stu::meter> a{10.0_m, 1.0_m};
    stu::CUnit<stu::kilometer> c{500.0_m, 1.0_m};
    EXPECT_EQ((a - 100.0_m - c), (stu::CUnit<stu::meter>{-1 * 590.0_m, 0.0_m}));
    EXPECT_EQ((a - 100.0_m - c).real()(), -590.0);
    EXPECT_EQ((a - 100.0_m - c).imag()(), 0.0);
    // EXPECT_EQ((c - 100.0_m - a)-(stu::CUnit<stu::kilometer>{0.39_km, 0.0_km}), stu::CUnit<stu::kilometer>{});
    // Test fails :  2.98023e-08+j0 VS 0+j0 !!!
    EXPECT_EQ((c - 100.0_m - a).real()() - 0.39, 0.0);
    EXPECT_EQ((c - 100.0_m - a).imag()(), 0.0);
}

TEST(StrongCUnit, floatingpoints_multiply_operators_conversion)
{
    stu::CUnit<stu::meter> a{10.0_m, 1.0_m};
    stu::CUnit<stu::kilometer> b = 2.0 * a * 2.0;
    EXPECT_EQ(b, (stu::CUnit<stu::meter>{40.0_m, 4.0_m}));
    EXPECT_EQ(b.real()() - 0.04, 0.0);
    EXPECT_EQ(b.imag()() - 0.004, 0.0);

    auto c = 2 * a + b;
    EXPECT_EQ(c, (stu::CUnit<stu::meter>{60.0_m, 6.0_m}));
    EXPECT_EQ(c.real()(), 60.0);
    EXPECT_EQ(c.imag()(), 6.0);

    auto d = b - 2 * a;
    EXPECT_EQ(d, (stu::CUnit<stu::meter>{20.0_m, 2.0_m}));
    EXPECT_EQ(d.real()() - 0.02, 0.0);
    EXPECT_EQ(d.imag()() - 0.002, 0.0);
}

TEST(StrongCUnit, units_multiply_operators_conversion)
{
    stu::CUnit<stu::meter> a{0.01_km, 0.001_km};
    auto b = 2 * a * 2.0_m;
    EXPECT_EQ(b.real(), 40.0_m * 1.0_m);
    EXPECT_EQ(b.imag()() - (4.0_m * 1.0_m)(), 0.0);

    auto c = 2.0_m * a + b;
    EXPECT_EQ(c.real(), 60.0_m * 1.0_m);
    EXPECT_EQ(c.imag()() - (6.0_m * 1.0_m)(), 0.0);

    auto d = b - 2.0_m * a;
    EXPECT_EQ(d.real(), 20.0_m * 1.0_m);
    EXPECT_EQ(d.imag()() - (2.0_m * 1.0_m)(), 0.0);

    auto e = 2.0_m * a * 2;
    EXPECT_EQ(e.real(), 40.0_m * 1.0_m);
    EXPECT_EQ(e.imag()() - (4.0_m * 1.0_m)(), 0.0);
}

TEST(StrongCUnit, complex_units_multiplication_operator_conversion)
{
    stu::CUnit<stu::second> a{1.0_s, 2.0_s};
    stu::CUnit<stu::second> b{3.0_s, 1.0_s};
    auto c = a * b;
    EXPECT_EQ(c.real(), 1 * 1.0_s * 1.0_s);
    EXPECT_EQ(c.imag(), 7 * 1.0_s * 1.0_s);
    auto d = b * a;
    EXPECT_EQ(d.real(), 1 * 1.0_s * 1.0_s);
    EXPECT_EQ(d.imag(), 7 * 1.0_s * 1.0_s);

    stu::CUnit<stu::meter> e{5.0_m, 3.0_m};
    auto f = e * a;
    EXPECT_EQ(f.real(), -1 * 1.0_m * 1.0_s);
    EXPECT_EQ(f.imag(), 13 * 1.0_m * 1.0_s);

    stu::CUnit<stu::kilometer> g{1.0_m, 3.0_m};
    auto h = g * e;
    EXPECT_NEAR(h.real()() - (-0.004 * 1.0_km * 1.0_m)(), 0.0, 8.68e-19);
    EXPECT_EQ(h.imag()() - (0.018 * 1.0_km * 1.0_m)(), 0.0);
}

TEST(StrongCUnit, floatingpoints_division_operators_conversion)
{
    stu::CUnit<stu::meter> a{20.0_m, 2.0_m};
    stu::CUnit<stu::kilometer> b = a / 2.0;
    EXPECT_EQ(b, (stu::CUnit<stu::meter>{10.0_m, 1.0_m}));
    EXPECT_EQ(b.real()() - 0.01, 0.0);
    EXPECT_EQ(b.imag()() - 0.001, 0.0);

    auto c = a / 2 + b;
    EXPECT_EQ(c, (stu::CUnit<stu::meter>{20.0_m, 2.0_m}));
    EXPECT_EQ(c.real()(), 20.0);
    EXPECT_EQ(c.imag()(), 2.0);

    auto d = 2 * b - a / 2;
    EXPECT_EQ(d, (stu::CUnit<stu::meter>{10.0_m, 1.0_m}));
    EXPECT_EQ(d.real()() - 0.01, 0.0);
    EXPECT_EQ(d.imag()() - 0.001, 0.0);

    stu::CUnit<stu::meter> e{2.0_m, 1.0_m};
    auto f = 20 / e;
    EXPECT_EQ(f.real()() - 8, 0.0);
    EXPECT_EQ(f.imag()() + 4, 0.0);
}

TEST(StrongCUnit, units_division_operators_conversion)
{
    stu::CUnit<stu::meter> a{20.0_m, 2.0_m};
    stu::CUnit<stu::kilometer> b = 1.0_m * a / 2.0_m;
    EXPECT_EQ(b, (stu::CUnit<stu::meter>{10.0_m, 1.0_m}));
    EXPECT_EQ(b.real(), 0.01_km);
    EXPECT_EQ(b.imag(), 0.001_km);

    auto c = 1.0_m * a / 2.0_m + b;
    EXPECT_EQ(c, (stu::CUnit<stu::meter>{20.0_m, 2.0_m}));
    EXPECT_EQ(c.real(), 20.0_m);
    EXPECT_EQ(c.imag(), 2.0_m);

    auto d = 2 * b - 1.0_m * a / 2.0_m;
    EXPECT_EQ(d, (stu::CUnit<stu::meter>{10.0_m, 1.0_m}));
    EXPECT_EQ(d.real(), 0.01_km);
    EXPECT_EQ(d.imag(), 0.001_km);

    stu::CUnit<stu::meter> e{2.0_m, 1.0_m};
    auto f = 20.0_m / e;
    EXPECT_EQ(f.real()() - 8, 0.0);
    EXPECT_EQ(f.imag()() + 4, 0.0);
}

TEST(StrongCUnit, complex_units_division_operator_conversion)
{
    stu::CUnit<stu::meter> a{10.0_m, 2.0_m};
    stu::CUnit<stu::second> b{2.0_s, 2.0_s};
    auto c = a / b;
    EXPECT_EQ(c.real(), 3 * 1.0_m / 1.0_s);
    EXPECT_EQ(c.imag(), -2 * 1.0_m / 1.0_s);
    auto d = b / a;
    EXPECT_EQ(d.real()() - ((3.0 / 13.0) * 1.0_s / 1.0_m)(), 0.0);
    EXPECT_EQ(d.imag()() - ((2.0 / 13.0) * 1.0_s / 1.0_m)(), 0.0);

    stu::CUnit<stu::kilometer> g = a;
    auto h = g / b;
    EXPECT_EQ(h.real()() - (3 * 0.001_km / 1.0_s)(), 0.0);
    EXPECT_EQ(h.imag()() - (-2 * 0.001_km / 1.0_s)(), 0.0);
}

TEST(StrongCUnit, cunits_abs_arg_polar_conversion)
{
    stu::meter a = 1.0_m;
    stu::kilometer b = 1.0_m;
    auto c = a + j * b;
    auto r = stu::abs(c);
    auto t = stu::arg(c);

    std::complex<STU_UNIT_TYPE> cc{1, 1};
    auto rr = std::abs(cc);
    auto tt = std::arg(cc);

    EXPECT_EQ(r(), rr);
    EXPECT_EQ(t(), tt);

    auto d = stu::polar(r, t);
    auto dd = std::polar(rr, tt);
    EXPECT_EQ(stu::getComplex(d), dd);
}

TEST(StrongCUnit, cunits_exp_conversion)
{
    stu::meter a = 1.0_m;
    stu::kilometer b = 1.0_m;
    auto c = a + j * b;
    auto d = stu::exp(c / 1.0_m);

    std::complex<STU_UNIT_TYPE> cc{1, 1};
    auto dd = std::exp(cc);

    EXPECT_EQ(stu::getComplex(d), dd);

    auto e = stu::exp(_1 + j * _0);
    EXPECT_EQ(e.real(), E);
}

TEST(StrongCUnit, cunits_log_conversion)
{
    stu::meter a = 1.0_m;
    stu::kilometer b = 1.0_m;
    auto c = a + j * b;
    auto d = stu::log(c / 1.0_m);

    std::complex<STU_UNIT_TYPE> cc{1, 1};
    auto dd = std::log(cc);

    EXPECT_EQ(stu::getComplex(d), dd);
}

TEST(StrongCUnit, cunits_log10_conversion)
{
    stu::meter a = 1.0_m;
    stu::kilometer b = 1.0_m;
    auto c = a + j * b;
    auto d = stu::log10(c / 1.0_m);

    std::complex<STU_UNIT_TYPE> cc{1, 1};
    auto dd = std::log10(cc);

    EXPECT_EQ(stu::getComplex(d), dd);
}

TEST(StrongCUnit, cunits_sin_conversion)
{
    stu::meter a = 1.0_m;
    stu::kilometer b = 1.0_m;
    auto c = a + j * b;
    auto d = stu::sin(c / 1.0_m);

    std::complex<STU_UNIT_TYPE> cc{1, 1};
    auto dd = std::sin(cc);

    EXPECT_EQ(stu::getComplex(d), dd);
}

TEST(StrongCUnit, cunits_cos_conversion)
{
    stu::meter a = 1.0_m;
    stu::kilometer b = 1.0_m;
    auto c = a + j * b;
    auto d = stu::cos(c / 1.0_m);

    std::complex<STU_UNIT_TYPE> cc{1, 1};
    auto dd = std::cos(cc);

    EXPECT_EQ(stu::getComplex(d), dd);
}

TEST(StrongCUnit, cunits_tan_conversion)
{
    stu::meter a = 1.0_m;
    stu::kilometer b = 1.0_m;
    auto c = a + j * b;
    auto d = stu::tan(c / 1.0_m);

    std::complex<STU_UNIT_TYPE> cc{1, 1};
    auto dd = std::tan(cc);

    EXPECT_EQ(stu::getComplex(d), dd);
}

TEST(StrongCUnit, cunits_asin_conversion)
{
    stu::meter a = 1.0_m;
    stu::kilometer b = 1.0_m;
    auto c = a + j * b;
    auto d = stu::asin(c / 1.0_m);

    std::complex<STU_UNIT_TYPE> cc{1, 1};
    auto dd = std::asin(cc);

    EXPECT_EQ(stu::getComplex(d), dd);
}

TEST(StrongCUnit, cunits_acos_conversion)
{
    stu::meter a = 1.0_m;
    stu::kilometer b = 1.0_m;
    auto c = a + j * b;
    auto d = stu::acos(c / 1.0_m);

    std::complex<STU_UNIT_TYPE> cc{1, 1};
    auto dd = std::acos(cc);

    EXPECT_EQ(stu::getComplex(d), dd);

    auto ac = stu::acos(-1 * _1 + j * _0);
    EXPECT_EQ(ac.real(), PI);
}

TEST(StrongCUnit, cunits_atan_conversion)
{
    stu::meter a = 1.0_m;
    stu::kilometer b = 1.0_m;
    auto c = a + j * b;
    auto d = stu::atan(c / 1.0_m);

    std::complex<STU_UNIT_TYPE> cc{1, 1};
    auto dd = std::atan(cc);

    EXPECT_EQ(stu::getComplex(d), dd);
}

TEST(StrongCUnit, cunits_sinh_conversion)
{
    stu::meter a = 1.0_m;
    stu::kilometer b = 1.0_m;
    auto c = a + j * b;
    auto d = stu::sinh(c / 1.0_m);

    std::complex<STU_UNIT_TYPE> cc{1, 1};
    auto dd = std::sinh(cc);

    EXPECT_EQ(stu::getComplex(d), dd);
}

TEST(StrongCUnit, cunits_cosh_conversion)
{
    stu::meter a = 1.0_m;
    stu::kilometer b = 1.0_m;
    auto c = a + j * b;
    auto d = stu::cosh(c / 1.0_m);

    std::complex<STU_UNIT_TYPE> cc{1, 1};
    auto dd = std::cosh(cc);

    EXPECT_EQ(stu::getComplex(d), dd);
}

TEST(StrongCUnit, cunits_tanh_conversion)
{
    stu::meter a = 1.0_m;
    stu::kilometer b = 1.0_m;
    auto c = a + j * b;
    auto d = stu::tanh(c / 1.0_m);

    std::complex<STU_UNIT_TYPE> cc{1, 1};
    auto dd = std::tanh(cc);

    EXPECT_EQ(stu::getComplex(d), dd);
}

TEST(StrongCUnit, cunits_asinh_conversion)
{
    stu::meter a = 1.0_m;
    stu::kilometer b = 1.0_m;
    auto c = a + j * b;
    auto d = stu::asinh(c / 1.0_m);

    std::complex<STU_UNIT_TYPE> cc{1, 1};
    auto dd = std::asinh(cc);

    EXPECT_EQ(stu::getComplex(d), dd);
}

TEST(StrongCUnit, cunits_acosh_conversion)
{
    stu::meter a = 1.0_m;
    stu::kilometer b = 1.0_m;
    auto c = a + j * b;
    auto d = stu::acosh(c / 1.0_m);

    std::complex<STU_UNIT_TYPE> cc{1, 1};
    auto dd = std::acosh(cc);

    EXPECT_EQ(stu::getComplex(d), dd);
}

TEST(StrongCUnit, cunits_atanh_conversion)
{
    stu::meter a = 1.0_m;
    stu::kilometer b = 1.0_m;
    auto c = a + j * b;
    auto d = stu::atanh(c / 1.0_m);

    std::complex<STU_UNIT_TYPE> cc{1, 1};
    auto dd = std::atanh(cc);

    EXPECT_EQ(stu::getComplex(d), dd);
}

TEST(StrongCUnit, cunits_pow_conversion)
{
    auto b = 1.0_m + j * 0.005_km;
    auto e = 2.0_m + j * 1.0_m;
    auto d = stu::pow(b / 1.0_m, e / 1.0_m);
    std::complex<STU_UNIT_TYPE> bb{1, 5};
    std::complex<STU_UNIT_TYPE> ee{2, 1};
    auto dd = std::pow(bb, ee);
    EXPECT_EQ(stu::getComplex(d), dd);

    auto a = stu::pow(b / 1.0_m, ee);
    EXPECT_EQ(stu::getComplex(a), dd);

    auto n = stu::pow(b / 1.0_m, 2.0_m / 1.0_m);
    dd = std::pow(bb, 2.0);
    EXPECT_EQ(stu::getComplex(n), dd);

    auto f = stu::pow<2>(b);
    auto ff = std::pow(bb, 2);
    // EXPECT_EQ(stu::getComplex(f) - ff, std::complex<STU_UNIT_TYPE>{});
    EXPECT_NEAR(stu::getComplex(f).real() - ff.real(), 0.0, 7.11e-15);
    EXPECT_NEAR(stu::getComplex(f).imag() - ff.imag(), 0.0, 5.33e-15);

    auto g = stu::pow<-2>(b);
    // EXPECT_EQ(stu::getComplex(g) - (1.0/ff), std::complex<STU_UNIT_TYPE>{});
    EXPECT_NEAR(stu::getComplex(g).real() - (std::complex<STU_UNIT_TYPE>{1} / ff).real(), 0.0, 1.39e-17);
    EXPECT_NEAR(stu::getComplex(g).imag() - (std::complex<STU_UNIT_TYPE>{1} / ff).imag(), 0.0, 5.21e-18);
}

TEST(StrongCUnit, cunits_sqrt_conversion)
{
    stu::meter a = 1.0_m;
    stu::kilometer b = 1.0_m;
    auto c = a + j * b;
    auto d = stu::sqrt(c / 1.0_m);

    std::complex<STU_UNIT_TYPE> cc{1, 1};
    auto dd = std::sqrt(cc);

    EXPECT_EQ(stu::getComplex(d), dd);

    auto f = stu::sqrt(c * c);
    auto ff = std::sqrt(cc * cc);

    EXPECT_EQ(stu::getComplex(f), ff);
}

/*/
//*/