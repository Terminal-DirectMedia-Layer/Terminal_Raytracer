#pragma once

#include "core/math/Vector.hpp"
#include "core/math/Tuple.hpp"

#include "core/math/SquareMatrix.hpp"
#include "core/math/UnitConverter.hpp"

#include <algorithm>
#include <stack>

namespace RayTracer
{
    template<typename T>
    class Transformation3
    {    
    public:
        using AffineMatrix = SquareMatrix<T, 4>;

        using Translation = Vector<T, 3>;
        using Scaling = Tuple<T, 3>;
        using Rotation = Tuple<T, 3>;

        Transformation3(const Translation &translation, const Scaling &scale, const Rotation &rotation)
        {
            this->setTranslation(translation);
            this->setScale(scale);
            this->setRotation(rotation);
        }

        Transformation3() :
            Transformation3(Translation(), Scaling(1.0), Rotation())
        {}

        template<typename U>
        Transformation3(const Transformation3<U> &other) :
            Transformation3(
                Translation(other.translation()),
                Scaling(other.scale()),
                Rotation(other.rotation())
            )
        {}

        Transformation3(const AffineMatrix &matrix)
        {
            this->_matrix = matrix;

            if (matrix.determinant() == 0)
                throw MathError(MathError::Type::INVALID_MATRIX_DETERMINANT);

            this->_translation = Translation(
                matrix[0][3],
                matrix[1][3],
                matrix[2][3]
            );

            this->_scale = Scaling(
                std::sqrt(matrix[0][0] * matrix[0][0] + matrix[0][1] * matrix[0][1] + matrix[0][2] * matrix[0][2]),
                std::sqrt(matrix[1][0] * matrix[1][0] + matrix[1][1] * matrix[1][1] + matrix[1][2] * matrix[1][2]),
                std::sqrt(matrix[2][0] * matrix[2][0] + matrix[2][1] * matrix[2][1] + matrix[2][2] * matrix[2][2])
            );

            this->_rotation = Rotation(
                UnitConverter<T>::toDegrees(std::atan2(matrix[2][1], matrix[2][2])),
                UnitConverter<T>::toDegrees(std::asin(-matrix[2][0])),
                UnitConverter<T>::toDegrees(std::atan2(matrix[1][0], matrix[0][0]))
            );
        }

        void load(const libconfig::Setting &node)
        {
            try {
                if (node.exists("position")) {
                    Translation translation;
                    translation.load(node["position"]);
                    this->setTranslation(translation);
                }
                if (node.exists("scale")) {
                    Scaling scale;
                    scale.load(node["scale"]);
                    this->setScale(scale);
                }
                if (node.exists("rotation")) {
                    Rotation rotation;
                    rotation.load(node["rotation"]);
                    this->setRotation(rotation);
                }
            } catch (const libconfig::SettingNotFoundException &e) {
                throw MathRepresentationError("Invalid Transformation3 description");
            }
        }

        bool tryLoad(const libconfig::Setting &node)
        {
            try {
                this->load(node);
            } catch (const libconfig::SettingNotFoundException &e) {
                return false;
            }

            return true;
        }

        Transformation3(const libconfig::Setting &node)
        {
            this->load(node);
        }

        Transformation3<T> operator+(const Transformation3<T> &other) const
        {
            return {this->matrix() * other.matrix()};
        }

        void operator+=(const Transformation3<T> &other)
        {
            this->setTranslation(this->_translation + other._translation);
            this->setScale(this->_scale * other._scale);
            this->setRotation(this->_rotation + other._rotation);
        }

    protected:
        void updateMatrix()
        {
            this->_matrix = this->_scaleMatrix * this->_rotationMatrix * this->_translationMatrix;
        }

    public:

        /* Translation */

        const Translation & translation() const
        {
            return this->_translation;
        }

        void setTranslation(const Translation &translation)
        {
            this->_translation = translation;

            for (int i = 0; i < 3; i++)
                this->_translationMatrix[i][3] = this->_translation[i];

            this->updateMatrix();
        }

        void setTranslation(T x, T y, T z)
        {
            this->setTranslation(Translation(x, y, z));
        }

        /* Scaling */

        const Scaling & scale() const
        {
            return this->_scale;
        }

        void setScale(const Scaling &scale)
        {
            this->_scale = scale;

            for (int i = 0; i < 3; i++)
                this->_scaleMatrix[i][i] = this->_scale[i];

            this->updateMatrix();
        }

        void setScale(T x, T y, T z)
        {
            this->setScale(Scaling(x, y, z));
        }

        /* Rotation */

        const Rotation & rotation() const
        {
            return this->_rotation;
        }

        void setRotation(const Rotation &rotation)
        {
            std::transform(rotation.values.begin(), rotation.values.end(), this->_rotation.values.begin(),
                [](T angle) {
                    return UnitConverter<T>::toRadians(angle);
                });

            AffineMatrix subRotationMatrix;
            this->_rotationMatrix = AffineMatrix();

            int i = 0;
            for (T angle : this->_rotation.values) {
                T cosAngle = std::cos(angle);
                T sinAngle = std::sin(angle);

                T x = i == 0;
                T y = i == 1;
                T z = i == 2;

                i++;

                subRotationMatrix[0][0] = cosAngle + x * x * (1 - cosAngle);
                subRotationMatrix[0][1] = x * y * (1 - cosAngle) - z * sinAngle;
                subRotationMatrix[0][2] = x * z * (1 - cosAngle) + y * sinAngle;

                subRotationMatrix[1][0] = y * x * (1 - cosAngle) + z * sinAngle;
                subRotationMatrix[1][1] = cosAngle + y * y * (1 - cosAngle);
                subRotationMatrix[1][2] = y * z * (1 - cosAngle) - x * sinAngle;

                subRotationMatrix[2][0] = z * x * (1 - cosAngle) - y * sinAngle;
                subRotationMatrix[2][1] = z * y * (1 - cosAngle) + x * sinAngle;
                subRotationMatrix[2][2] = cosAngle + z * z * (1 - cosAngle);

                this->_rotationMatrix *= subRotationMatrix;
            }
            
            this->updateMatrix();
        }

        void setRotation(T x, T y, T z)
        {
            this->setRotation(Rotation(x, y, z));
        }

        const AffineMatrix & matrix() const
        {
            return this->_matrix;
        }

        Transformation3<T> inverse() const
        {
            return {this->matrix().inverse()};
        }
        
        Translation translation()
        {
            return this->_translation;
        }

        AffineMatrix translationMatrix()
        {
            return this->_translationMatrix;
        }

        Transformation3<T> translationTransformation()
        {
            return {this->translationMatrix()};
        }
        
        Scaling scaling()
        {
            return this->_scaling;
        }

        AffineMatrix scaleMatrix()
        {
            return this->_scaleMatrix;
        }

        Transformation3<T> scaleTransformation()
        {
            return {this->scaleMatrix()};
        }

        /* Applied transformation operators */

        Tuple<T, 3> operator *(const Tuple<T, 3> &tuple) const
        {
            return {
                this->_matrix[0][0] * tuple.at(0) + this->_matrix[0][1] * tuple.at(1) + this->_matrix[0][2] * tuple.at(2) + this->_matrix[0][3],
                this->_matrix[1][0] * tuple.at(0) + this->_matrix[1][1] * tuple.at(1) + this->_matrix[1][2] * tuple.at(2) + this->_matrix[1][3],
                this->_matrix[2][0] * tuple.at(0) + this->_matrix[2][1] * tuple.at(1) + this->_matrix[2][2] * tuple.at(2) + this->_matrix[2][3]
            };
        }

    public:
        Translation rotation()
        {
            return this->_rotation;
        }

        AffineMatrix rotationMatrix()
        {
            return this->_rotationMatrix;
        }

        Transformation3<T> rotationTransformation()
        {
            return {this->rotationMatrix()};
        }

    protected:
        Translation _translation;
        Scaling _scale{1.0};
        Rotation _rotation;

        AffineMatrix _scaleMatrix;
        AffineMatrix _rotationMatrix;
        AffineMatrix _translationMatrix;
        AffineMatrix _matrix;
    };

    using Transformation3f = Transformation3<float>;
    using Transformation3d = Transformation3<double>;
};
