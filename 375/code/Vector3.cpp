/// \file Vector3.hpp
/// \brief Implementation of Vector class.
/// \author John Shenk
/// \version A04

#include "Vector3.hpp"
#include <cmath>
#include <iomanip>
#include <bits/stdc++.h>

/// \brief Initializes a new vector to have all coefficients 0.0f.
/// \post All coefficients are 0.0f.
Vector3::Vector3 ()
{
    m_x = m_y = m_z = 0.0f;
}

/// \brief Initializes a new vector to have all coefficients identical.
/// \param[in] xyz The value that should be used for all three coefficients.
/// \post All coefficients are equal to xyz.
Vector3::Vector3 (float xyz)
{
    m_x = m_y = m_z = xyz;
}


/// \brief Initializes a new vector with custom coefficients.
/// \param[in] x The coefficient for the basis vector i.
/// \param[in] y The coefficient for the basis vector j.
/// \param[in] z The coefficient for the basis vector k.
/// \post The coefficients are equal to x, y, and z respectively.
Vector3::Vector3 (float x, float y, float z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

/// \brief Sets each coefficient to the same value.
/// \param[in] xyz The value that should be used for all three coefficients.
/// \post All coefficients are equal to xyz.
void
Vector3::set (float xyz)
{
    m_x = m_y = m_z = xyz;
}

/// \brief Sets each coefficient to (potentially) different values.
/// \param[in] x The new coefficient for the basis vector i.
/// \param[in] y The new coefficient for the basis vector j.
/// \param[in] z The new coefficient for the basis vector k.
/// \post The coefficients are equal to x, y, and z respectively.
void
Vector3::set (float x, float y, float z)
{
    m_x = x;
    m_y = y;
    m_z = z;
}

/// \brief Replaces the direction of this vector to its exact opposite.
/// \post The vector has been negated.
void
Vector3::negate ()
{
    m_x = -m_x;
    m_y = -m_y;
    m_z = -m_z;
}

/// \brief Compute the dot product of this with another vector.
/// \param[in] v The other vector.
/// \return The dot product of this and v.
float
Vector3::dot (const Vector3& v) const
{
    return (m_x * v.m_x) + (m_y * v.m_y) + (m_z * v.m_z);
}

/// \brief Computes the angle (in radians) between this and another vector.
/// \param[in] v The other vector.
/// \return The angle between this and v, expressed in radians.
float
Vector3::angleBetween (const Vector3& v) const
{
    return acos((this->dot(v))/(this->length() * v.length()));
}

/// \brief Computes the cross product between this and another vector.
/// \param[in] v The other vector.
/// \return The cross product of this vector with v.
Vector3
Vector3::cross (const Vector3& v) const
{
    Vector3 xProduct ((m_y * v.m_z - m_z * v.m_y), (m_z * v.m_x - m_x * v.m_z), (m_x * v.m_y - m_y * v.m_x));
    return xProduct;
}

/// \brief Computes the length of this vector.
/// \return The length of this vector.
float
Vector3::length () const
{
    return sqrt(pow(m_x, 2) + pow(m_y, 2) + pow(m_z, 2));
}

/// \brief Normalizes this vector.
/// \post This vector points in the same direction, but has a length of 1.
void
Vector3::normalize ()
{
    float l = length();
    m_x /= l;
    m_y /= l;
    m_z /= l;
}

const float*
Vector3::data()
{
    return &m_x;
}

/// \brief Adds another vector to this one.
/// \param[in] v Another vector.
/// \post This vector has been replaced by itself plus v.
/// \return This vector.
Vector3&
Vector3::operator+= (const Vector3& v)
{
    this->set((m_x + v.m_x), (m_y + v.m_y), (m_z + v.m_z));
    return *this;
}

/// \brief Subtracts another vector from this one.
/// \param[in] v Another vector.
/// \post This vector has been replaced by itself minus v.
/// \return This vector.
Vector3&
Vector3::operator-= (const Vector3& v)
{
    this->set((m_x - v.m_x), (m_y - v.m_y), (m_z - v.m_z));
    return *this;
}

/// \brief Multiplies this vector by a scalar.
/// \param[in] s A scalar.
/// \post This vector has been replaced with itself times s.
/// \return This vector.
Vector3&
Vector3::operator*= (float s)
{
    this->set((m_x * s), (m_y * s), (m_z * s));
    return *this;
}

/// \brief Divies this vector by a scalar.
/// \param[in] s A scalar.
/// \post This vector has been replaced with itself divided by s.
/// \return This vector.
Vector3&
Vector3::operator/= (float s)
{
    this->set((m_x / s), (m_y / s), (m_z / s));
    return *this;
}

/// \brief Adds two vectors.
/// \param[in] v1 The first addend.
/// \param[in] v2 The second addend.
/// \return A new vector that is v1 + v2.
Vector3
operator+ (const Vector3& v1, const Vector3& v2)
{
    Vector3 v1Copy = v1;
    v1Copy += v2;
    return v1Copy;
}

/// \brief Subtracts two vectors.
/// \param[in] v1 The minuend.
/// \param[in] v2 The subtrahend.
/// \return A new vector that is v1 - v2.
Vector3
operator- (const Vector3& v1, const Vector3& v2)
{
    Vector3 v1Copy = v1;
    v1Copy -= v2;
    return v1Copy;
}

/// \brief Negates a vector.
/// \param[in] v A vector.
/// \return A new vector that is the negation of v.
Vector3
operator- (const Vector3& v)
{
    Vector3 negativeVec (-v.m_x, -v.m_y, -v.m_z);
    return negativeVec;
}

/// \brief Multiplies a scalar by a vector.
/// \param[in] s A scalar.
/// \param[in] v A vector.
/// \return A new vector that is s * v.
Vector3
operator* (float s, const Vector3& v)
{
    Vector3 vCopy = v;
    vCopy *= s;
    return vCopy;
}

/// \brief Multiplies a vector by a scalar.
/// \param[in] v A vector.
/// \param[in] s A scalar.
/// \return A new vector that is v * s.
Vector3
operator* (const Vector3& v, float s)
{
    Vector3 vCopy = v;
    vCopy *= s;
    return vCopy;
}

/// \brief Divides a vector by a scalar.
/// \param[in] v A vector.
/// \param[in] s A scalar.
/// \return A new vector that is v / s.
Vector3
operator/ (const Vector3& v, float s)
{
    Vector3 vCopy = v;
    vCopy /= s;
    return vCopy;
}

/// \brief Inserts a vector into an output stream.
/// Each component of the vector should have 2 digits of precision and a field
///   width of 10.
/// \param[in] out An output stream.
/// \param[in] v A vector.
/// \return The output stream.
/// \post The vector has been inserted into the output stream.
std::ostream&
operator<< (std::ostream& out, const Vector3& v)
{
    out << std::setw(10) << std::setprecision(2) << std::fixed  << v.m_x;
    out << std::setw(10) << v.m_y;
    out << std::setw(10) << v.m_z;
    return out;
}

/// \brief Checks whether or not two vectors are equal.
/// Vectors are equal if each of their respective components are within
///   0.00001f of each other due to floating-point imprecision.
/// \param[in] v1 A vector.
/// \param[in] v2 Another vector.
/// \return Whether or not v1 and v2 are equal.
bool
operator== (const Vector3& v1, const Vector3& v2)
{
    if (fabs(v1.m_x - v2.m_x) > 0.00001f)
        return false;
    else if (fabs(v1.m_y - v2.m_y) > 0.00001f)
        return false;
    else if (fabs(v1.m_z - v2.m_z) > 0.00001f)
        return false; 

    return true;
}

