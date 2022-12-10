/// \file Matrix3.hpp
/// \brief Implementation of Matrix3 class and any associated global functions.
/// \author John Shenk
/// \version A05

#include "Matrix3.hpp"
#include <iomanip>
#include <cmath>
#include <glm/gtx/rotate_vector.hpp>

/// \brief Initializes a new matrix to the identity matrix.
/// \post rx, uy, and bz are 1.0f while all other elements are 0.0f.
Matrix3::Matrix3 ()
{
        m_right.set(1.0f, 0.0f, 0.0f);
        m_up.set(0.0f, 1.0f, 0.0f);
        m_back.set(0.0f, 0.0f, 1.0f);
}

/// \brief Initializes a new matrix from its 9 elements.
/// \param[in] rx The first column, first row.
/// \param[in] ry The first column, second row.
/// \param[in] rz The first column, third row.
/// \param[in] ux The second column, first row.
/// \param[in] uy The second column, second row.
/// \param[in] uz The second column, third row.
/// \param[in] bx The third column, first row.
/// \param[in] by The third column, second row.
/// \param[in] bz The third column, third row.
/// \post Each element has the value of its matching parameter.
Matrix3::Matrix3 (float rx, float ry, float rz,
        float ux, float uy, float uz,
        float bx, float by, float bz)
{
        m_right.m_x = rx;
        m_right.m_y = ry;
        m_right.m_z = rz;

        m_up.m_x = ux;
        m_up.m_y = uy;
        m_up.m_z = uz;

        m_back.m_x = bx;
        m_back.m_y = by;
        m_back.m_z = bz;
}
  
/// \brief Initializes a new matrix from three basis vectors.
/// \param[in] right The first column of the matrix.
/// \param[in] up The second column of the matrix.
/// \param[in] back The third column of the matrix.
/// \post Each column vector has the value of its matching parameter.
Matrix3::Matrix3 (const Vector3& right, const Vector3& up,
         const Vector3& back)
{
        m_right = right;
        m_up = up;
        m_back = back;
}
  
/// \brief Initializes a new matrix from two basis vectors, computing the third.
/// \param[in] up The second column of the matrix.
/// \param[in] back The third column of the matrix.
/// \param[in] makeOrthonormal Whether or not to orthonormalize the vectors.
/// \post The up and back vectors have the value of their matching parameters.
/// \post The right vector is the cross product of the up and bac vectors.
/// \post If makeOrthonormal is true, the vectors have been orthonormalized.
Matrix3::Matrix3 (const Vector3& up, const Vector3& back,
        bool makeOrthonormal)
{
    m_up = up;
    m_back = back;
    m_right = up.cross(back);
    if(makeOrthonormal == true)
    {
        this->orthonormalize();   
    }

}

/// \brief Destructs a matrix.
Matrix3::~Matrix3 ()
{
        //Nothing
}
  
/// \brief Sets this to the identity matrix.
/// \post rx, uy, and bz are 1.0f while all other elements are 0.0f.
void
Matrix3::setToIdentity ()
{
        m_right.set(1.0f, 0.0f, 0.0f);
        m_up.set(0.0f, 1.0f, 0.0f);
        m_back.set(0.0f, 0.0f, 1.0f);
}

/// \brief Sets this to the zero matrix.
/// \post All elements are 0.0f.
void
Matrix3::setToZero ()
{
        m_right.set(0.0f, 0.0f, 0.0f);
        m_up.set(0.0f, 0.0f, 0.0f);
        m_back.set(0.0f, 0.0f, 0.0f);
}


/// \brief Retrieves a pointer to the first column, first row.
/// \return A pointer to the beginning of the data.
/// Because of the way our data is stored, you can use pointer arithmetic to
///   get to the first column second row, first column third row, second
///   column first row, and so forth.
float*
Matrix3::data ()
{
        return &m_right.m_x;
}

/// \brief Retrieves a constant pointer to the first column, first row.
/// \return A constant pointer to the beginning of the data.
/// Because of the way our data is stored, you can use pointer arithmetic to
///   get to the first column second row, first column third row, second
///   column first row, and so forth.  
const float*
Matrix3::data () const
{
        return &m_right.m_x;
}

/// \brief Sets the right vector.
/// \param[in] right The new value for the first column.
/// \post The first column is a copy of the parameter.
void
Matrix3::setRight (const Vector3& right)
{
        m_right = right;
}

/// \brief Gets the right vector.
/// \return A copy of the first column.
Vector3
Matrix3::getRight () const
{
        return m_right;
}

/// \brief Sets the up vector.
/// \param[in] up The new value for the second column.
/// \post The second column is a copy of the parameter.
void
Matrix3::setUp (const Vector3& up)
{
        m_up = up;
}

/// \brief Gets the up vector.
/// \return A copy of the second column.
Vector3
Matrix3::getUp () const
{
        return m_up;
}

/// \brief Sets the back vector.
/// \param[in] back The new value for the third column.
/// \post The third column is a copy of the parameter.
void
Matrix3::setBack (const Vector3& back)
{
        m_back = back;
}
 
/// \brief Gets the back vector.
/// \return A copy of the third column.
Vector3
Matrix3::getBack () const
{
        return m_back;
}

/// \brief Sets the forward (opposite of back) vector.
/// \param[in] forward The new forward vector.
/// \post The third column is the negation of the parameter.
void
Matrix3::setForward (const Vector3& forward)
{
        m_back = -forward;
}

/// \brief Gets the forward (opposite of back) vector.
/// \return A copy of the negation of the third column.
Vector3
Matrix3::getForward () const
{
        return -m_back;
}

/// \brief Inverts this matrix, using an fast algorithm that will only work for rotations.
/// \pre This matrix represents a pure rotation.
/// \post This matrix has been replaced with its inversion.
void
Matrix3::invertRotation ()
{
        this->transpose();
}

/// \brief Inverts this matrix, using an expensive algorithm.
/// \post This matrix has been replaced with its inversion.
void
Matrix3::invert ()
{
        float determinant = this->determinant();

        // New right vector
        Vector3 invR ((m_up.m_y * m_back.m_z - m_back.m_y * m_up.m_z),
        (m_back.m_y * m_right.m_z - m_right.m_y * m_back.m_z),
        (m_right.m_y * m_up.m_z - m_up.m_y * m_right.m_z));

        // New up vector
        Vector3 invU ((m_back.m_x * m_up.m_z - m_up.m_x * m_back.m_z),
        (m_right.m_x * m_back.m_z - m_back.m_x * m_right.m_z),
        (m_up.m_x * m_right.m_z - m_right.m_x * m_up.m_z));

        // New back vector 
        Vector3 invB ((m_up.m_x * m_back.m_y - m_back.m_x * m_up.m_y),
        (m_back.m_x * m_right.m_y - m_right.m_x * m_back.m_y),
        (m_right.m_x * m_up.m_y - m_up.m_x * m_right.m_y));

        //Set vectors using new vectors
        m_right = invR;
        m_up = invU;
        m_back = invB;

        //Multiply by determinant
        *this *= 1/determinant;
}

/// \brief Calculates the determinant of this matrix.
/// \return The determinant.
float
Matrix3::determinant () const
{
        float determinant = m_right.m_x * (m_up.m_y * m_back.m_z - m_back.m_y * m_up.m_z)
                - m_right.m_y * (m_up.m_x * m_back.m_z - m_back.m_x * m_up.m_z)
                + m_right.m_z * (m_up.m_x * m_back.m_y - m_back.m_x * m_up.m_y);
        return determinant;
}

/// \brief Transposes this matrix.
/// \post The first column has become the first row, etc.
void
Matrix3::transpose ()
{
        Vector3 r = m_right;
        Vector3 u = m_up;
        Vector3 b = m_back;

        m_right.m_x = r.m_x;
        m_up.m_x = r.m_y;
        m_back.m_x = r.m_z;

        m_right.m_y = u.m_x;
        m_up.m_y = u.m_y;
        m_back.m_y = u.m_z;

        m_right.m_z = b.m_x;
        m_up.m_z = b.m_y;
        m_back.m_z = b.m_z;
}

/// \brief Makes the basis vectors orthonormal to each other.
/// Starts by assuming that the back vector is pointing in the correct
///   direction.  Normalizes the back vector.  Computes the right vector by
///   crossing up with back, and then normalizes it.  Computes the up vector
///   by crossing back with right, and then normalizes it.
/// \post All columns have a length of 1 and are mutually perpendicular.
/// \post The back vector points in the same direction that it did before.
void
Matrix3::orthonormalize ()
{
        m_back.normalize();

        m_right = m_up.cross(m_back);
        m_right.normalize();

        m_up = m_back.cross(m_right);
        m_up.normalize();
}

/// \brief Makes this into a uniform scale matrix.
/// \param[in] scale The amount to scale up (or down).
/// \post This is a matrix that scales vectors by the specified factor.
void
Matrix3::setToScale (float scale)
{
        m_right.set(scale, 0.0f, 0.0f);
        m_up.set(0.0f, scale, 0.0f);
        m_back.set(0.0f, 0.0f, scale);
}

/// \brief Makes this into a non-uniform scale matrix.
/// \param[in] scaleX The scale factor for the X direction.
/// \param[in] scaleY The scale factor for the Y direction.
/// \param[in] scaleZ The scale factor for the Z direction.
/// \post This is a matrix that scales vectors by the specified factors.
void
Matrix3::setToScale (float scaleX, float scaleY, float scaleZ)
{
        m_right.set(scaleX, 0.0f, 0.0f);
        m_up.set(0.0f, scaleY, 0.0f);
        m_back.set(0.0f, 0.0f, scaleZ);
}

/// \brief Makes this into a matrix that shears X values.
/// \param[in] shearY The amount to shear by Y.
/// \param[in] shearZ The amount to shear by Z.
/// \post This is a matrix that shears X by the specified factors of Y and Z.
void
Matrix3::setToShearXByYz (float shearY, float shearZ)
{
        m_right.set(1.0f, 0.0f, 0.0f);
        m_up.set(shearY, 1.0f, 0.0f);
        m_back.set(shearZ, 0.0f, 1.0f);
}

/// \brief Makes this into a matrix that shears Y values.
/// \param[in] shearX The amount to shear by X.
/// \param[in] shearZ The amount to shear by Z.
/// \post This is a matrix that shears Y by the specified factors of X and Z.
void
Matrix3::setToShearYByXz (float shearX, float shearZ)
{
        m_right.set(1.0f, shearX, 0.0f);
        m_up.set(0.0f, 1.0f, 0.0f);
        m_back.set(0.0f, shearZ, 1.0f);
}

/// \brief Makes this into a matrix that shears Z values.
/// \param[in] shearX The amount to shear by X.
/// \param[in] shearY The amount to shear by Y.
/// \post This is a matrix that shears Z by the specified factors of X and Y.
void
Matrix3::setToShearZByXy (float shearX, float shearY)
{
        m_right.set(1.0f, 0.0f, shearX);
        m_up.set(0.0f, 1.0f, shearY);
        m_back.set(0.0f, 0.0f, 1.0f);
}

/// \brief Makes this into a matrix that rotates around the X-axis.
/// \param[in] angleDegrees How much to rotate.
/// \post This is a matrix that rotates around the X-axis by the specified angle.
void
Matrix3::setToRotationX (float angleDegrees)
{
        m_right.set(1.0f, 0.0f, 0.0f);
        m_up.set(0.0f, cos(glm::radians(angleDegrees)), sin(glm::radians(angleDegrees)));
        m_back.set(0.0f, (-1.0f * sin(glm::radians(angleDegrees))), cos(glm::radians(angleDegrees)));
}

/// \brief Makes this into a matrix that rotates around the Y-axis.
/// \param[in] angleDegrees How much to rotate.
/// \post This is a matrix that rotates around the Y-axis by the specified angle.
void
Matrix3::setToRotationY (float angleDegrees)
{
        m_right.set(cos(glm::radians(angleDegrees)), 0.0f, (-1.0f * sin(glm::radians(angleDegrees))));
        m_up.set(0.0f, 1.0f, 0.0f);
        m_back.set(sin(glm::radians(angleDegrees)), 0.0f, cos(glm::radians(angleDegrees)));
}

/// \brief Makes this into a matrix that rotates around the Z-axis.
/// \param[in] angleDegrees How much to rotate.
/// \post This is a matrix that roates around the Z-axis by the specified angle.
void
Matrix3::setToRotationZ (float angleDegrees)
{
        m_right.set(cos(glm::radians(angleDegrees)), sin(glm::radians(angleDegrees)), 0.0f);
        m_up .set((-1.0f * sin(glm::radians(angleDegrees))), cos(glm::radians(angleDegrees)), 0.0f);
        m_back.set(0.0f, 0.0f, 1.0f);
}

/// \brief Makes this into a matrix that rotates around an arbitrary vector.
/// \param[in] angleDegrees How much to rotate.
/// \param[in] axis The vector to rotate around.
/// \post This is a matrix that rotates around the specified vector by the specified angle.
void
Matrix3::setFromAngleAxis (float angleDegrees, const Vector3& axis)
{
      Vector3 copy = axis;
      copy.normalize();  

      m_right.set(pow(copy.m_x, 2.0f) + cos(glm::radians(angleDegrees)) * (1 - pow(copy.m_x, 2.0f)), 
      copy.m_x * copy.m_y * (1.0f - cos(glm::radians(angleDegrees))) + copy.m_z * sin(glm::radians(angleDegrees)), 
      copy.m_x * copy.m_z * (1.0f - cos(glm::radians(angleDegrees))) - copy.m_y * sin(glm::radians(angleDegrees)));

      m_up.set(copy.m_x * copy.m_y * (1.0f - cos(glm::radians(angleDegrees))) - copy.m_z * sin(glm::radians(angleDegrees)),
      pow(copy.m_y, 2.0f) + cos(glm::radians(angleDegrees)) * (1.0f - pow(copy.m_y, 2.0f)),
      copy.m_y * copy.m_z * (1.0f - cos(glm::radians(angleDegrees))) + copy.m_x * sin(glm::radians(angleDegrees)));

      m_back.set(copy.m_x *  copy.m_z * (1.0f - cos(glm::radians(angleDegrees))) + copy.m_y * sin(glm::radians(angleDegrees)),
      copy.m_y * copy.m_z * (1.0f - cos(glm::radians(angleDegrees))) - copy.m_x * sin(glm::radians(angleDegrees)),
      pow(copy.m_z, 2.0f) + cos(glm::radians(angleDegrees)) * (1.0f - pow(copy.m_z, 2.0f)));
}

/// \brief Negates this matrix.
/// \post Every element has been replaced by its negation.
void
Matrix3::negate ()
{
        m_right *= -1;
        m_up *= -1;
        m_back *= -1;
}

/// \brief Transforms a vector, computing *this * v.
/// \param[in] v The vector to multiply by this matrix.
/// \return The result of the multiplication.
Vector3
Matrix3::transform (const Vector3& v) const
{
        Vector3 newVect((v.m_x * m_right.m_x + v.m_y * m_up.m_x + v.m_z * m_back.m_x),
        (v.m_x * m_right.m_y + v.m_y * m_up.m_y + v.m_z * m_back.m_y),
        (v.m_x * m_right.m_z + v.m_y * m_up.m_z + v.m_z * m_back.m_z));

        return newVect;
}

/// \brief Adds another matrix to this.
/// \param[in] m The other matrix.
/// \return This matrix.
/// \post Every element of this matrix has its sum with the equivalent element in the other.
Matrix3&
Matrix3::operator+= (const Matrix3& m)
{
        m_right += m.m_right;
        m_up += m.m_up;
        m_back += m.m_back;

        return *this;
}

/// \brief Subtracts another matrix from this.
/// \param[in] m The other matrix.
/// \return This matrix.
/// \post Every element of this matrix has the difference of it and the equivalent element in the other.
Matrix3&
Matrix3::operator-= (const Matrix3& m)
{
        m_right -= m.m_right;
        m_up -= m.m_up;
        m_back -= m.m_back;

        return *this;
}

/// \brief Multiplies this matrix by a scalar.
/// \param[in] scalar The number to multiply by.
/// \return This matrix.
/// \post Every element of this matrix has the product of it and the scalar.
Matrix3&
Matrix3::operator*= (float scalar)
{
        m_right *= scalar;
        m_up *= scalar;
        m_back *= scalar;

        return *this;
}

/// \brief Multiplies this matrix by another matrix.
/// \param[in] m The matrix to multiply by.
/// \return This matrix.
/// \post This matrix contains the product of itself with m.
Matrix3&
Matrix3::operator*= (const Matrix3& m)
{
        Matrix3 t = *this;

        m_right.m_x = t.m_right.m_x * m.m_right.m_x + t.m_up.m_x * m.m_right.m_y + t.m_back.m_x * m.m_right.m_z;
        m_up.m_x = t.m_right.m_x * m.m_up.m_x + t.m_up.m_x * m.m_up.m_y + t.m_back.m_x * m.m_up.m_z;
        m_back.m_x = t.m_right.m_x * m.m_back.m_x + t.m_up.m_x * m.m_back.m_y + t.m_back.m_x * m.m_back.m_z;

        m_right.m_y =  t.m_right.m_y * m.m_right.m_x + t.m_up.m_y * m.m_right.m_y + t.m_back.m_y * m.m_right.m_z;
        m_up.m_y =  t.m_right.m_y * m.m_up.m_x + t.m_up.m_y * m.m_up.m_y + t.m_back.m_y * m.m_up.m_z;
        m_back.m_y =  t.m_right.m_y * m.m_back.m_x + t.m_up.m_y * m.m_back.m_y + t.m_back.m_y * m.m_back.m_z;

        m_right.m_z = t.m_right.m_z * m.m_right.m_x + t.m_up.m_z * m.m_right.m_y + t.m_back.m_z * m.m_right.m_z;
        m_up.m_z = t.m_right.m_z * m.m_up.m_x + t.m_up.m_z * m.m_up.m_y + t.m_back.m_z * m.m_up.m_z;
        m_back.m_z = t.m_right.m_z * m.m_back.m_x + t.m_up.m_z * m.m_back.m_y + t.m_back.m_z * m.m_back.m_z;
        
        return *this;
}

/// \brief Adds two matrices.
/// \param[in] m1 The first matrix to add.
/// \param[in] m2 The secondn matrix to add.
/// \return A new matrix that is m1 + m2.
Matrix3
operator+ (const Matrix3& m1, const Matrix3& m2)
{
        Matrix3 m1C = m1;
        Matrix3 m2C = m2;
        m1C += m2C;
        return m1C;
}       

/// \brief Subtracts two matrices.
/// \param[in] m1 The matrix to subtract from.
/// \param[in] m2 The matrix to subtract.
/// \return A new matrix that is m1 - m2.
Matrix3
operator- (const Matrix3& m1, const Matrix3& m2)
{
        Matrix3 m1C = m1;
        Matrix3 m2C = m2;
        m1C -= m2C;
        return m1C;
}

/// \brief Negates a matrix.
/// \param[in] m The matrix to negate.
/// \return A new matrix that is -m.
Matrix3
operator- (const Matrix3& m)
{
        Matrix3 copy = m;
        copy.negate();
        return copy;
}

/// \brief Multiplies a matrix by a scalar.
/// \param[in] m The matrix to multiply.
/// \param[in] scalar The number to multiply it by.
/// \return A new matrix that is m * scalar.
Matrix3
operator* (const Matrix3& m, float scalar)
{
        Matrix3 copy = m;
        copy *= scalar;
        return copy;
}

/// \brief Multiplies a matrix by a scalar.
/// \param[in] scalar The number to multiply it by.
/// \param[in] m The matrix to multiply.
/// \return A new matrix that is m * scalar.
Matrix3
operator* (float scalar, const Matrix3& m)
{
        Matrix3 copy = m;
        copy *= scalar;
        return copy;
}

/// \brief Multiplies a matrix by another matrix.
/// \param[in] m1 A matrix.
/// \param[in] m2 Another matrix.
/// \return A new matrix rhat is m * m.
Matrix3
operator* (const Matrix3& m1, const Matrix3& m2)
{
        Matrix3 m1C = m1;
        Matrix3 m2C = m2;

        m1C *= m2C;
        return m1C;
}

/// \brief Multiplies a matrix by a vector.
/// \param[in] m A matrix.
/// \param[in] v A vector.
/// \return A new vector that is m * v.
Vector3
operator* (const Matrix3& m, const Vector3& v)
{
        Matrix3 copyM = m;
        Vector3 copyV = v;

        copyV = copyM.transform(copyV);
        return copyV;
}

/// \brief Inserts a matrix into an output stream.
/// Each element of the matrix should have 2 digits of precision and a field
///   width of 10.  Elements should be in this order:
///      rx ux bx
///      ry uy by
///      rz uz bz
/// \param[inout] out An output stream.
/// \param[in] m A matrix.
/// \return The output stream.
/// \post The matrix has been inserted into the output stream.
std::ostream&
operator<< (std::ostream& out, const Matrix3& m)
{       Vector3 r = m.getRight();
        Vector3 u = m.getUp();
        Vector3 b = m.getBack();

        out << std::setw(10) << std::setprecision(2) << std::fixed  << r.m_x;
        out << std::setw(10) << u.m_x;
        out << std::setw(10) << b.m_x << std::endl;

        out << std::setw(10) << r.m_y;
        out << std::setw(10) << u.m_y;
        out << std::setw(10) << b.m_y << std::endl;

        out << std::setw(10) << r.m_z;
        out << std::setw(10) << u.m_z;
        out << std::setw(10) << b.m_z << std::endl;

        return out;
}

/// \brief Checks whether or not two matrices are equal.
/// matrices are equal if each of their respective elements are within
///   0.00001f of each other due to floating-point imprecision.
/// \param[in] m1 A matrix.
/// \param[in] m2 Another matrix.
/// \return Whether or not m1 and m2 are equal.
bool
operator== (const Matrix3& m1, const Matrix3& m2)
{

         return m1.getRight() == m2.getRight() && m1.getUp() == m2.getUp() && m1.getBack() == m2.getBack();
}
