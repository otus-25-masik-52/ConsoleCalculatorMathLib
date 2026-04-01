#pragma once

#include <climits>

namespace CalculatorMath {
#if defined(__GNUC__) || defined(__clang__)
#define CALCULATOR_MATH_HAS_BUILTIN_OVERFLOW 1
#else
#define CALCULATOR_MATH_HAS_BUILTIN_OVERFLOW 0
#endif

  enum ErrorCode {
    ERR_NONE = 0,
    ERR_INVALID_ARGUMENTS,
    ERR_OVERFLOW,
    ERR_DIV_ZERO,
    ERR_UNSUPPORTED_METHOD
  };

  namespace detail {
    inline ErrorCode addition_impl(const int a, const int b, int *result) {
#if CALCULATOR_MATH_HAS_BUILTIN_OVERFLOW
      return __builtin_add_overflow(a, b, result) ? ERR_OVERFLOW : ERR_NONE;
#else
      if ((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b)) {
        return ERR_OVERFLOW;
      }
      *result = a + b;
      return ERR_NONE;
#endif
    }

    inline ErrorCode subtraction_impl(const int a, const int b, int *result) {
#if CALCULATOR_MATH_HAS_BUILTIN_OVERFLOW
      return __builtin_sub_overflow(a, b, result) ? ERR_OVERFLOW : ERR_NONE;
#else
      if (b == INT_MIN && a > 0) {
        return ERR_OVERFLOW;
      }
      return addition_impl(a, -b, result);
#endif
    }

    inline ErrorCode multiplication_impl(const int a, const int b, int *result) {
#if CALCULATOR_MATH_HAS_BUILTIN_OVERFLOW
      return __builtin_mul_overflow(a, b, result) ? ERR_OVERFLOW : ERR_NONE;
#else
      if (a == 0 || b == 0) {
        *result = 0;
        return ERR_NONE;
      }
      if ((a == INT_MIN && b == -1) || (b == INT_MIN && a == -1)) {
        return ERR_OVERFLOW;
      }
      if (a > 0 && ((b > 0 && a > INT_MAX / b) || (b < 0 && b < INT_MIN / a))) {
        return ERR_OVERFLOW;
      }
      if (a < 0 && ((b > 0 && a < INT_MIN / b) || (b < 0 && a < INT_MAX / b))) {
        return ERR_OVERFLOW;
      }
      *result = a * b;
      return ERR_NONE;
#endif
    }

    inline ErrorCode division_impl(const int a, const int b, int *result) {
      if (b == 0) {
        return ERR_DIV_ZERO;
      }
      if (a == INT_MIN && b == -1) {
        return ERR_OVERFLOW;
      }
      *result = a / b;
      return ERR_NONE;
    }

    inline ErrorCode exponentiation_impl(const int base, const int exp, int *result) {
      int res = 1;
      int i = 0;
      int temp = 0;

      if (exp < 0) {
        return ERR_INVALID_ARGUMENTS;
      }

      while (i < exp) {
        if (multiplication_impl(res, base, &temp) != ERR_NONE) {
          return ERR_OVERFLOW;
        }

        res = temp;
        i = i + 1;
      }

      *result = res;
      return ERR_NONE;
    }

    inline ErrorCode factorial_impl(const int n, int *result) {
      int sub_result = 0;

      if (n < 0) {
        return ERR_INVALID_ARGUMENTS;
      }

      if (n == 0 || n == 1) {
        *result = 1;
        return ERR_NONE;
      }

      if (factorial_impl(n - 1, &sub_result) != ERR_NONE) {
        return ERR_OVERFLOW;
      }

      return multiplication_impl(n, sub_result, result);
    }
  }

  template<typename Impl, typename... Args>
  ErrorCode call_with_precheck(Impl impl, int *result, Args... args) {
    if (!result) {
      return ERR_INVALID_ARGUMENTS;
    }
    return impl(args..., result);
  }

  inline ErrorCode addition(const int a, const int b, int *result) {
    return call_with_precheck(detail::addition_impl, result, a, b);
  }

  inline ErrorCode subtraction(const int a, const int b, int *result) {
    return call_with_precheck(detail::subtraction_impl, result, a, b);
  }

  inline ErrorCode multiplication(const int a, const int b, int *result) {
    return call_with_precheck(detail::multiplication_impl, result, a, b);
  }

  inline ErrorCode division(const int a, const int b, int *result) {
    return call_with_precheck(detail::division_impl, result, a, b);
  }

  inline ErrorCode exponentiation(const int base, const int exp, int *result) {
    return call_with_precheck(detail::exponentiation_impl, result, base, exp);
  }

  inline ErrorCode factorial(const int n, int *result) {
    return call_with_precheck(detail::factorial_impl, result, n);
  }
} // CalculatorMath
