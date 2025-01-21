/*
** EPITECH PROJECT, 2024
** MathError
** File description:
** file for MathError functions
*/


#pragma once

#include <exception>

namespace RayTracer
{
    class MathError : public std::exception
    {
    public:
        enum class Type {
            DIVIDE_BY_ZERO,
            INVALID_MATRIX_SIZE,
            INVALID_VECTOR_SIZE,
            INVALID_MATRIX_MULTIPLICATION,
            INVALID_VECTOR_MULTIPLICATION,
            INVALID_MATRIX_ADDITION,
            INVALID_VECTOR_ADDITION,
            INVALID_MATRIX_SUBTRACTION,
            INVALID_VECTOR_SUBTRACTION,
            INVALID_MATRIX_INVERSION,
            INVALID_VECTOR_INVERSION,
            INVALID_MATRIX_DETERMINANT
        };
        explicit MathError(Type type) : _type(type) {}

        [[nodiscard]] const char *what() const noexcept override
        {
            switch (_type) {
                case Type::DIVIDE_BY_ZERO:
                    return "Divide by zero";
                case Type::INVALID_MATRIX_SIZE:
                    return "Invalid matrix size";
                case Type::INVALID_VECTOR_SIZE:
                    return "Invalid vector size";
                case Type::INVALID_MATRIX_MULTIPLICATION:
                    return "Invalid matrix multiplication";
                case Type::INVALID_VECTOR_MULTIPLICATION:
                    return "Invalid vector multiplication";
                case Type::INVALID_MATRIX_ADDITION:
                    return "Invalid matrix addition";
                case Type::INVALID_VECTOR_ADDITION:
                    return "Invalid vector addition";
                case Type::INVALID_MATRIX_SUBTRACTION:
                    return "Invalid matrix subtraction";
                case Type::INVALID_VECTOR_SUBTRACTION:
                    return "Invalid vector subtraction";
                case Type::INVALID_MATRIX_INVERSION:
                    return "Invalid matrix inversion";
                case Type::INVALID_VECTOR_INVERSION:
                    return "Invalid vector inversion";
                case Type::INVALID_MATRIX_DETERMINANT:
                    return "Invalid matrix determinant";
            }

            return "Unknown error";
        }

    protected:
        const Type _type;
    };
} // RayTracer
