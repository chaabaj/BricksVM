#ifndef __BRICKSVM_CORE_COMPUTATION_HPP__
# define __BRICKSVM_CORE_COMPUTATION_HPP__

# include "exception/InvalidOperationException.hpp"

namespace bricksvm
{
    namespace core
    {
        template<typename T>
        struct Add
        {
            inline static T compute(T const a, T const b)
            {
                return a + b;
            }
        };

        template<typename T>
        struct Substract
        {
            inline static T compute(T const a, T const b)
            {
                return a - b;
            }
        };

        template<typename T>
        struct Divide
        {
            inline static T compute(T const a, T const b)
            {
                if (b > 0)
                {
                    return a / b;
                }
                throw bricksvm::exception::InvalidOperationException("Floating point exception");
            }
        };

        template<typename T>
        struct Multiply
        {
            inline static T compute(T const a, T const b)
            {
                return a * b;
            }
        };

        template<typename T>
        struct Modulo
        {
            inline static T compute(T const a, T const b)
            {
                return a % b;
            }
        };

        template<>
        struct Modulo< float >
        {
            inline static float compute(float const a, float const b)
            {
                throw bricksvm::exception::InvalidOperationException("Cannot compute modulo of float values");
            }
        };

        template<>
        struct Modulo< double >
        {
            inline static double compute(double const a, double const b)
            {
                throw bricksvm::exception::InvalidOperationException("Cannot compute modulo of double values");
            }
        };

        template<typename T>
        struct BinaryOr
        {
            inline static T compute(T const a, T const b)
            {
                return a | b;
            }
        };

        template<>
        struct BinaryOr< float >
        {
            inline static float compute(float const a, float const b)
            {
                throw bricksvm::exception::InvalidOperationException("Cannot do binary operation on float values");
            }
        };

        template<>
        struct BinaryOr< double >
        {
            inline static double compute(double const a, double const b)
            {
                throw bricksvm::exception::InvalidOperationException("Cannot do binary operation on double values");
            }
        };

        template<typename T>
        struct BinaryAnd
        {
            inline static T compute(T const a, T const b)
            {
                return a & b;
            }
        };


        template<>
        struct BinaryAnd< float >
        {
            inline static float compute(float const a, float const b)
            {
                throw bricksvm::exception::InvalidOperationException("Cannot do binary operation on float values");
            }
        };

        template<>
        struct BinaryAnd< double >
        {
            inline static double compute(double const a, double const b)
            {
                throw bricksvm::exception::InvalidOperationException("Cannot do binary operation on double values");
            }
        };



        template<typename T>
        struct BinaryLeftShift
        {
            inline static T compute(T const a, T const b)
            {
                return a << b;
            }
        };


        template<>
        struct BinaryLeftShift< float >
        {
            inline static float compute(float const a, float const b)
            {
                throw bricksvm::exception::InvalidOperationException("Cannot do binary operation on float values");
            }
        };

        template<>
        struct BinaryLeftShift< double >
        {
            inline static double compute(double const a, double const b)
            {
                throw bricksvm::exception::InvalidOperationException("Cannot do binary operation on double values");
            }
        };


        template<typename T>
        struct BinaryRightShift
        {
            inline static T compute(T const a, T const b)
            {
                return a >> b;
            }
        };


        template<>
        struct BinaryRightShift< float >
        {
            inline static float compute(float const a, float const b)
            {
                throw bricksvm::exception::InvalidOperationException("Cannot do binary operation on float values");
            }
        };

        template<>
        struct BinaryRightShift< double >
        {
            inline static double compute(double const a, double const b)
            {
                throw bricksvm::exception::InvalidOperationException("Cannot do binary operation on double values");
            }
        };


        template<typename T>
        struct BinaryXor
        {
            inline static T compute(T const a, T const b)
            {
                return a ^ b;
            }
        };


        template<>
        struct BinaryXor< float >
        {
            inline static float compute(float const a, float const b)
            {
                throw bricksvm::exception::InvalidOperationException("Cannot do binary operation on float values");
            }
        };

        template<>
        struct BinaryXor< double >
        {
            inline static double compute(double const a, double const b)
            {
                throw bricksvm::exception::InvalidOperationException("Cannot do binary operation on double values");
            }
        };


        template<typename T>
        struct Equal
        {
            inline static bool compute(T const a, T const b)
            {
                return a == b;
            }
        };

        template<typename T>
        struct GreaterThan
        {
            inline static bool compute(T const a, T const b)
            {
                return a > b;
            }
        };

        template<typename T>
        struct NotEqual
        {
            inline static bool compute(T const a, T const b)
            {
                return a != b;
            }
        };

        template<typename T>
        struct GreaterOrEqualThan
        {
            inline static bool compute(T const a, T const b)
            {
                return a >= b;
            }
        };

        template<typename T>
        struct LowerOrEqualThan
        {
            inline static bool compute(T const a, T const b)
            {
                return a <= b;
            }
        };

        template<typename T>
        struct LowerThan
        {
            inline static bool compute(T const a, T const b)
            {
                return a < b;
            }
        };
    }
}

#endif