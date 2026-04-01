# ConsoleCalculatorMathLib
A C++ header-only library for working with mathematical functions.

![Static Badge](https://img.shields.io/badge/otus--25--masik--52-ConsoleCalculatorMathLib-darkblue)
![GitHub top language](https://img.shields.io/github/languages/top/otus-25-masik-52/ConsoleCalculatorMathLib)
![GitHub](https://img.shields.io/github/license/otus-25-masik-52/ConsoleCalculatorMathLib)
![GitHub Repo stars](https://img.shields.io/github/stars/otus-25-masik-52/ConsoleCalculatorMathLib)

## Documentation

### Functions overview
| Function       | Description                            | Returns   | Notes                                     |
|----------------| -------------------------------------- | --------- |-------------------------------------------|
| addition       | Performs safe addition of two integers | ErrorCode | Detects overflow using selected method    |
| subtraction    | Performs safe subtraction              | ErrorCode | Same overflow strategy as add             |
| multiplication | Performs safe multiplication           | ErrorCode | Uses step-by-step overflow checks         |
| division       | Performs safe division                 | ErrorCode | Checks division by zero and edge cases    |
| exponentiation | Integer exponentiation                 | ErrorCode | Iterative, uses safe multiplication       |
| factorial      | Factorial calculation                  | ErrorCode | Recursive/iterative with overflow control |

> All functions return an ErrorCode and write the result via pointer.

### Overflow handling strategy

The library supports multiple strategies for detecting integer overflow:

- **MANUAL** — portable boundary checks using INT_MIN / INT_MAX
- **BUILTIN** — compiler-specific intrinsics (if available)

Availability of built-in overflow checks is determined at compile time:

```
#if defined(__GNUC__) || defined(__clang__)
#define CALCULATOR_MATH_HAS_BUILTIN_OVERFLOW 1
#else
#define CALCULATOR_MATH_HAS_BUILTIN_OVERFLOW 0
#endif
```

If supported, the library can use compiler intrinsics like `__builtin_func_overflow` for efficient and well-defined overflow detection. Otherwise, it falls back to fully portable methods.

## Support
If you have any difficulties or questions about using this lib, create a [discussion](https://github.com/otus-25-masik-52/ConsoleCalculatorMathLib/issues/new/choose) in this repository.

## Dependencies
This library is implemented in C++20 and does not rely on the standard library or OOP abstractions.
To use it, you only need:
- a **C++20-compatible compiler**
- **CMake**

## Description of commits 
All comments are written according to [Conventional Commits](https://www.conventionalcommits.org/en/v1.0.0/).