/// \file Matrix4.hpp
/// \brief Implementation of Matrix4 class and any associated global functions.
/// \author John Shenk
/// \version A07

#include "Matrix4.hpp"
#include <iomanip>
#include <math.h>
#include <glm/gtx/rotate_vector.hpp>

/// \brief Initializes to the identity matrix.
/// \post rx, uy, bz, and tw are 1.0f while all other elements are 0.0f.
Matrix4::Matrix4 ()
{
    m_right.set(1.0f, 0.0f, 0.0f, 0.0f);
    m_up.set(0.0f, 1.0f, 0.0f, 0.0f);
    m_back.set(0.0f, 0.0f, 1.0f, 0.0f);
    m_translation.set(0.0f, 0.0f, 0.0f, 1.0f);
}

/// \brief Initializes a ne matrix from the four basis vectors.
/// \param[in] right The first column of the new matrix.
/// \param[in] up The second column of the new matrix.
/// \param[in] back The third column of the new matrix.
/// \param[in] translation The fourth column of the new matrix.
Matrix4::Matrix4 (const Vector4& right, const Vector4& up,
	const Vector4& back, const Vector4& translation)
{
    m_right.set(right.m_x, right.m_y, right.m_z, right.m_w);
    m_up.set(up.m_x, up.m_y, up.m_z, up.m_w);
    m_back.set(back.m_x, back.m_y, back.m_z, back.m_w);
    m_translation.set(translation.m_x, translation.m_y, translation.m_z, translation.m_w);
}

/// \brief Gets the right vector.
/// \return A copy of the first column.
Vector4
Matrix4::getRight () const
{
    return m_right;
}

/// \brief Gets the up vector.
/// \return A copy of the second column.
Vector4
Matrix4::getUp () const
{
    return m_up;
}

/// \brief Gets the back vector.
/// \return A copy of the third column.
Vector4
Matrix4::getBack () const
{
    return m_back;
}

/// \brief Gets the translation vector.
/// \return A copy of the fourth column.
Vector4
Matrix4::getTranslation () const
{
    return m_translation;
}

/// \brief Sets this to the identity matrix.
/// \post The elements along the main diagonal are 1.0f while all others are
///   0.0f.
void
Matrix4::setToIdentity ()
{
    m_right.set(1.0f, 0.0f, 0.0f, 0.0f);
    m_up.set(0.0f, 1.0f, 0.0f, 0.0f);
    m_back.set(0.0f, 0.0f, 1.0f, 0.0f);
    m_translation.set(0.0f, 0.0f, 0.0f, 1.0f);
}

/// \brief Sets this to the zero matrix.
/// \post All elements are 0.0f.
void
Matrix4::setToZero ()
{
    m_right.set(0.0f, 0.0f, 0.0f, 0.0f);
    m_up.set(0.0f, 0.0f, 0.0f, 0.0f);
    m_back.set(0.0f, 0.0f, 0.0f, 0.0f);
    m_translation.set(0.0f, 0.0f, 0.0f, 0.0f);
}
    
/// \brief Gets a const pointer to the first element.
/// \return A pointer to rx.
const float*
Matrix4::data () const
{
    return &m_right.m_x;
}

// For the projection methods, do all computations using
//   double-s and only cast to float when NECESSARY. 

/// \brief Sets this to a symmetric perspective projection matrix.
/// \param[in] fovYDegrees The vertical field of view angle, in degrees.
/// \param[in] aspectRatio The ratio of width to height.
/// \param[in] nearPlaneZ The distance to the near clip plane.
/// \param[in] farPlaneZ The distance to the far clip plane.
/// \post This has been set to a symmetric perspective projection.
void
Matrix4::setToPerspectiveProjection (double fovYDegrees, double aspectRatio,
	double nearPlaneZ, double farPlaneZ)
{
    m_right.set(1.0 / (aspectRatio * tan(glm::radians(fovYDegrees / 2.0))), 0.0, 0.0, 0.0);
    m_up.set(0.0, 1.0 / tan(glm::radians(fovYDegrees / 2.0)), 0.0, 0.0);
    m_back.set(0.0, 0.0, (nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ), -1.0);
    m_translation.set(0.0, 0.0, (2 * farPlaneZ * nearPlaneZ) / (nearPlaneZ - farPlaneZ), 0.0);
}

/// \brief Sets this to an assymetric perspective projection matrix.
/// \param[in] left The x-value of the left side of the projection plane.
/// \param[in] right The x-value of the right side of the projection plane.
/// \param[in] bottom The y-value of the bottom of the projection plane.
/// \param[in] top The y-value of the top of the projection plane.
/// \param[in] nearPlaneZ The distance to the near clip plane.
/// \param[in] farPlaneZ The distance to the far clip plane.
/// \post This has been set to an asymmetric perspective projection.
void
Matrix4::setToPerspectiveProjection (double left, double right,
	double bottom, double top,
	double nearPlaneZ, double farPlaneZ)
{
    m_right.set(2.0 * nearPlaneZ / (right - left), 0.0, 0.0, 0.0);
    m_up.set(0.0, 2.0 * nearPlaneZ / (top - bottom), 0.0, 0.0);
    m_back.set((right + left) / (right - left), (top + bottom) / (top - bottom), (nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ), -1.0);
    m_translation.set(0.0, 0.0, (2 * nearPlaneZ * farPlaneZ) / (nearPlaneZ - farPlaneZ), 0.0);
}

/// \brief Sets this to an orthographic projection matrix.
/// \param[in] left The x-value of the left plane.
/// \param[in] right The x-value of the right plane.
/// \param[in] bottom The y-value of the bottom plane.
/// \param[in] top The y-value of the top plane.
/// \param[in] nearPlaneZ The distance to the near clip plane.
/// \param[in] farPlaneZ The distance to the far clip plane.
/// \post This has been set to an orthographic projection.
void
Matrix4::setToOrthographicProjection (double left, double right,
	double bottom, double top,
    double nearPlaneZ, double farPlaneZ)
{
    m_right.set(2.0 / (right - left), 0.0, 0.0, 0.0);
    m_up.set(0.0f, 2.0 / (top - bottom), 0.0, 0.0);
    m_back.set(0.0, 0.0, 2.0 / (nearPlaneZ - farPlaneZ), 0.0);
    m_translation.set((right + left) / -(right - left), (top + bottom) / -(top - bottom), (nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ), 1.0);
}

/// \brief Inserts a matrix into an output stream.
/// Each element of the matrix should have 2 digits of precision and a field
///   width of 10.  Elements should be in this order:
///     rx ux bx tx
///     ry uy by ty
///     rz uz bz tz
///     rw uw bw tw
/// \param[inout] out An output stream.
/// \param[in] m A matrix.
/// \return The output stream.
/// \post The matrix has been inserted into the output stream.
std::ostream&
operator<< (std::ostream& out, const Matrix4& m)
{
    Vector4 r = m.getRight();
	Vector4 u = m.getUp();
	Vector4 b = m.getBack();
	Vector4 t = m.getTranslation();

	out << std::setw(10) << std::setprecision(2) << std::fixed  << r.m_x;
    out << std::setw(10) << u.m_x;
    out << std::setw(10) << b.m_x; 
	out << std::setw(10) << t.m_x << std::endl;

	out << std::setw(10) << r.m_y;
    out << std::setw(10) << u.m_y;
    out << std::setw(10) << b.m_y;
	out << std::setw(10) << t.m_y << std::endl;

    out << std::setw(10) << r.m_z;
    out << std::setw(10) << u.m_z;
    out << std::setw(10) << b.m_z;
	out << std::setw(10) << t.m_z << std::endl;

	out << std::setw(10) << r.m_w;
	out << std::setw(10) << u.m_w;
	out << std::setw(10) << b.m_w;
	out << std::setw(10) << t.m_w << std::endl;

	return out;
}

/// \brief Checks whether or not two matrices are equal.
/// Matrices are equal if each of their respective elements are within
///   0.00001f of each other due to floating-point imprecision.
/// \param[in] m1 A matrix.
/// \param[in] m2 Another matrix.
/// \return Whether or not m1 and m2 are equal.
bool
operator== (const Matrix4& m1, const Matrix4& m2)
{
    return m1.getRight() == m2.getRight() &&
           m1.getUp() == m2.getUp() &&
           m1.getBack() == m2.getBack() &&
           m1.getTranslation() == m2.getTranslation();

}