// Copyright John Maddock 2006.
// Copyright Paul A. Bristow 2007, 2009
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifdef _MSC_VER
#  pragma warning (disable : 4756) // overflow in constant arithmetic
#endif

#include <boost/math/concepts/real_concept.hpp>
#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <boost/math/special_functions/math_fwd.hpp>
#include <boost/math/special_functions/legendre.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/array.hpp>
#include "functor.hpp"

#include "handle_test_result.hpp"
#include "table_type.hpp"

#ifndef SC_
#define SC_(x) static_cast<typename table_type<T>::type>(BOOST_JOIN(x, L))
#endif

template <class Real, class T>
void do_test_legendre_p(const T& data, const char* type_name, const char* test_name)
{
   typedef Real                   value_type;

   typedef value_type (*pg)(int, value_type);
   pg funcp;

#if !(defined(ERROR_REPORTING_MODE) && !defined(LEGENDRE_P_FUNCTION_TO_TEST))
#ifdef LEGENDRE_P_FUNCTION_TO_TEST
   funcp = LEGENDRE_P_FUNCTION_TO_TEST;
#elif defined(BOOST_MATH_NO_DEDUCED_FUNCTION_POINTERS)
   funcp = boost::math::legendre_p<value_type>;
#else
   funcp = boost::math::legendre_p;
#endif

   boost::math::tools::test_result<value_type> result;

   std::cout << "Testing " << test_name << " with type " << type_name
      << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

   //
   // test legendre_p against data:
   //
   result = boost::math::tools::test_hetero<Real>(
      data,
      bind_func_int1<Real>(funcp, 0, 1),
      extract_result<Real>(2));
   handle_test_result(result, data[result.worst()], result.worst(), type_name, "legendre_p", test_name);
#endif

   typedef value_type (*pg2)(unsigned, value_type);
#if !(defined(ERROR_REPORTING_MODE) && !defined(LEGENDRE_Q_FUNCTION_TO_TEST))
#ifdef LEGENDRE_Q_FUNCTION_TO_TEST
   pg2 funcp2 = LEGENDRE_Q_FUNCTION_TO_TEST;
#elif defined(BOOST_MATH_NO_DEDUCED_FUNCTION_POINTERS)
   pg2 funcp2 = boost::math::legendre_q<value_type>;
#else
   pg2 funcp2 = boost::math::legendre_q;
#endif

   //
   // test legendre_q against data:
   //
   result = boost::math::tools::test_hetero<Real>(
      data,
      bind_func_int1<Real>(funcp2, 0, 1),
      extract_result<Real>(3));
   handle_test_result(result, data[result.worst()], result.worst(), type_name, "legendre_q", test_name);

   std::cout << std::endl;
#endif
}

template <class Real, class T>
void do_test_assoc_legendre_p(const T& data, const char* type_name, const char* test_name)
{
#if !(defined(ERROR_REPORTING_MODE) && !defined(LEGENDRE_PA_FUNCTION_TO_TEST))
   typedef Real                   value_type;

   typedef value_type (*pg)(int, int, value_type);
#ifdef LEGENDRE_PA_FUNCTION_TO_TEST
   pg funcp = LEGENDRE_PA_FUNCTION_TO_TEST;
#elif defined(BOOST_MATH_NO_DEDUCED_FUNCTION_POINTERS)
   pg funcp = boost::math::legendre_p<value_type>;
#else
   pg funcp = boost::math::legendre_p;
#endif

   boost::math::tools::test_result<value_type> result;

   std::cout << "Testing " << test_name << " with type " << type_name
      << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

   //
   // test legendre_p against data:
   //
   result = boost::math::tools::test_hetero<Real>(
      data,
      bind_func_int2<Real>(funcp, 0, 1, 2),
      extract_result<Real>(3));
   handle_test_result(result, data[result.worst()], result.worst(), type_name, "legendre_p (associated)", test_name);
   std::cout << std::endl;
#endif
}

template <class T>
void test_legendre_p(T, const char* name)
{
   //
   // The actual test data is rather verbose, so it's in a separate file
   //
   // The contents are as follows, each row of data contains
   // three items, input value a, input value b and erf(a, b):
   //
#  include "legendre_p.ipp"

   do_test_legendre_p<T>(legendre_p, name, "Legendre Polynomials: Small Values");

#  include "legendre_p_large.ipp"

   do_test_legendre_p<T>(legendre_p_large, name, "Legendre Polynomials: Large Values");

#  include "assoc_legendre_p.ipp"

   do_test_assoc_legendre_p<T>(assoc_legendre_p, name, "Associated Legendre Polynomials: Small Values");

}

template <class T>
void test_spots(T, const char* t)
{
   std::cout << "Testing basic sanity checks for type " << t << std::endl;
   //
   // basic sanity checks, tolerance is 100 epsilon:
   //
   T tolerance = boost::math::tools::epsilon<T>() * 100;
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(1, static_cast<T>(0.5L)), static_cast<T>(0.5L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(-1, static_cast<T>(0.5L)), static_cast<T>(1L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(4, static_cast<T>(0.5L)), static_cast<T>(-0.2890625000000000000000000000000000000000L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(-4, static_cast<T>(0.5L)), static_cast<T>(-0.4375000000000000000000000000000000000000L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(7, static_cast<T>(0.5L)), static_cast<T>(0.2231445312500000000000000000000000000000L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(-7, static_cast<T>(0.5L)), static_cast<T>(0.3232421875000000000000000000000000000000L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(40, static_cast<T>(0.5L)), static_cast<T>(-0.09542943523261546936538467572384923220258L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(-40, static_cast<T>(0.5L)), static_cast<T>(-0.1316993126940266257030910566308990611306L), tolerance);

   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(4, 2, static_cast<T>(0.5L)), static_cast<T>(4.218750000000000000000000000000000000000L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(-4, 2, static_cast<T>(0.5L)), static_cast<T>(5.625000000000000000000000000000000000000L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(7, 5, static_cast<T>(0.5L)), static_cast<T>(-5696.789530152175143607977274672800795328L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(-7, 4, static_cast<T>(0.5L)), static_cast<T>(465.1171875000000000000000000000000000000L), tolerance);
   if(std::numeric_limits<T>::max_exponent > std::numeric_limits<float>::max_exponent)
   {
      BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(40, 30, static_cast<T>(0.5L)), static_cast<T>(-7.855722083232252643913331343916012143461e45L), tolerance);
   }
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(-40, 20, static_cast<T>(0.5L)), static_cast<T>(4.966634149702370788037088925152355134665e30L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(4, 2, static_cast<T>(-0.5L)), static_cast<T>(4.218750000000000000000000000000000000000L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(-4, 2, static_cast<T>(-0.5L)), static_cast<T>(-5.625000000000000000000000000000000000000L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(7, 5, static_cast<T>(-0.5L)), static_cast<T>(-5696.789530152175143607977274672800795328L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(-7, 4, static_cast<T>(-0.5L)), static_cast<T>(465.1171875000000000000000000000000000000L), tolerance);
   if(std::numeric_limits<T>::max_exponent > std::numeric_limits<float>::max_exponent)
   {
      BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(40, 30, static_cast<T>(-0.5L)), static_cast<T>(-7.855722083232252643913331343916012143461e45L), tolerance);
   }
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(-40, 20, static_cast<T>(-0.5L)), static_cast<T>(-4.966634149702370788037088925152355134665e30L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(4, -2, static_cast<T>(0.5L)), static_cast<T>(0.01171875000000000000000000000000000000000L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(-4, -2, static_cast<T>(0.5L)), static_cast<T>(0.04687500000000000000000000000000000000000L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(7, -5, static_cast<T>(0.5L)), static_cast<T>(0.00002378609812640364935569308025139290054701L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(-7, -4, static_cast<T>(0.5L)), static_cast<T>(0.0002563476562500000000000000000000000000000L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(40, -30, static_cast<T>(0.5L)), static_cast<T>(-2.379819988646847616996471299410611801239e-48L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p(-40, -20, static_cast<T>(0.5L)), static_cast<T>(4.356454600748202401657099008867502679122e-33L), tolerance);

   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_q(1, static_cast<T>(0.5L)), static_cast<T>(-0.7253469278329725771511886907693685738381L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_q(4, static_cast<T>(0.5L)), static_cast<T>(0.4401745259867706044988642951843745400835L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_q(7, static_cast<T>(0.5L)), static_cast<T>(-0.3439152932669753451878700644212067616780L), tolerance);
   BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_q(40, static_cast<T>(0.5L)), static_cast<T>(0.1493671665503550095010454949479907886011L), tolerance);
}

template <class T>
void test_legendre_p_prime()
{
    T tolerance = 100*boost::math::tools::epsilon<T>();
    T x = -1;
    while (x <= 1)
    {
        // P_0'(x) = 0
        BOOST_CHECK_SMALL(::boost::math::legendre_p_prime<T>(0,  x), tolerance);
        // Reflection formula for P_{-1}(x) = P_{0}(x):
        BOOST_CHECK_SMALL(::boost::math::legendre_p_prime<T>(-1,  x), tolerance);

        // P_1(x) = x, so P_1'(x) = 1:
        BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p_prime<T>(1,  x), static_cast<T>(1), tolerance);
        BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p_prime<T>(-2,  x), static_cast<T>(1), tolerance);

        // P_2(x) = 3x^2/2 + k => P_2'(x) = 3x
        BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p_prime<T>(2,  x), 3*x, tolerance);
        BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p_prime<T>(-3,  x), 3*x, tolerance);

        // P_3(x) = (5x^3 - 3x)/2 => P_3'(x) = (15x^2 - 3)/2:
        T xsq = x*x;
        BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p_prime<T>(3,  x), (15*xsq - 3)/2, tolerance);
        BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p_prime<T>(-4,  x), (15*xsq -3)/2, tolerance);

        // P_4(x) = (35x^4 - 30x^2 +3)/8 => P_4'(x) = (5x/2)*(7x^2 - 3)
        T expected = 5*x*(7*xsq - 3)/2;
        BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p_prime<T>(4,  x), expected, tolerance);
        BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p_prime<T>(-5,  x), expected, tolerance);

        // P_5(x) = (63x^5 - 70x^3 + 15x)/8 => P_5'(x) = (315*x^4 - 210*x^2 + 15)/8
        T x4 = xsq*xsq;
        expected = (315*x4 - 210*xsq + 15)/8;
        BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p_prime<T>(5,  x), expected, tolerance);
        BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p_prime<T>(-6,  x), expected, tolerance);

        // P_6(x) = (231x^6 -315*x^4 +105x^2 -5)/16 => P_6'(x) = (6*231*x^5 - 4*315*x^3 + 105x)/16
        expected = 21*x*(33*x4 - 30*xsq + 5)/8;
        BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p_prime<T>(6,  x), expected, tolerance);
        BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p_prime<T>(-7,  x), expected, tolerance);

        // Mathematica: D[LegendreP[7, x],x]
        T x6 = x4*xsq;
        expected = 7*(429*x6 -495*x4 + 135*xsq - 5)/16;
        BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p_prime<T>(7,  x), expected, tolerance);
        BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p_prime<T>(-8,  x), expected, tolerance);

        // Mathematica: D[LegendreP[8, x],x]
        // The naive polynomial evaluation algorithm is going to get worse from here out, so this will be enough.
        expected = 9*x*(715*x6 - 1001*x4 + 385*xsq - 35)/16;
        BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p_prime<T>(8,  x), expected, tolerance);
        BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p_prime<T>(-9,  x), expected, tolerance);

        x += static_cast<T>(1)/static_cast<T>(pow(2, 4));
    }

    int n = 0;
    while (n < 5000)
    {
        T expected = n*(n+1)*boost::math::constants::half<T>();
        BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p_prime<T>(n, (T) 1), expected, tolerance);
        BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p_prime<T>(-n - 1,  (T) 1), expected, tolerance);
        if (n & 1)
        {
            BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p_prime<T>(n, (T) -1), expected, tolerance);
            BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p_prime<T>(-n - 1,  (T) -1), expected, tolerance);
        }
        else
        {
            BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p_prime<T>(n, (T) -1), -expected, tolerance);
            BOOST_CHECK_CLOSE_FRACTION(::boost::math::legendre_p_prime<T>(-n - 1,  (T) -1), -expected, tolerance);
        }
        ++n;
    }
}
