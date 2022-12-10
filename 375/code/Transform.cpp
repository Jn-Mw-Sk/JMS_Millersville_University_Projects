/// \file Transform.cpp
/// \brief Declaration of Transform class and any associated global functions.
/// \author Gary M. Zoppetti, Ph.D. & Chad Hogg, John Shenk
/// \version A06

/// \brief A 4x4 matrix of floats with the requirement that the bottom row
///   must be 0, 0, 0, 1.  This type of matrix can be used to represent any
///   affine transformation.
/// The matrix is interpreted thus:
///   [ rx ux bx px ]
///   [ ry uy by py ]
///   [ rz uz bz pz ]
///   [  0  0  0  1 ] 
/// 'r', 'u', 'b', and 'p' are the right, up, back,
///   and position vectors, respectively. 
/// The last row is not explicitly stored since it is always
///    [  0  0  0  1 ].
#include "Transform.hpp"
#include <iomanip>

/// \brief Initializes a new transform to the identity transform: one that
///   represents no scale, rotation, shear, reflection, translation, or
///   other change.
/// \post The Matrix3 component is the identity matrix, while the Vector3
///   component is the zero vector.
Transform::Transform ()
{
	m_rotScale.setToIdentity();
	m_position.set(0.0f, 0.0f, 0.0f);
}

/// \brief Initializes a new transform from its orientation and position.
/// \param[in] orientation The orientation of the new transform.
/// \param[in] position The position of the new transform.
/// \post The components have been copied from the parameters.
Transform::Transform (const Matrix3& orientation, const Vector3& position)
{
	m_rotScale.setRight(orientation.getRight());
	m_rotScale.setUp(orientation.getUp());
	m_rotScale.setBack(orientation.getBack());

	m_position.set(position.m_x, position.m_y, position.m_z);
}
  
/// \brief Orthonormalizes the Matrix3 component.
/// \post The Matrix3 component contains three perpendicular unit vectors.
void
Transform::orthonormalize ()
{
	m_rotScale.orthonormalize();
}
  
/// \brief Resets to the identity transform.
/// \post The Matrix3 component is the identity matrix, while the Vector3
///   component is the zero vector.
void
Transform::reset ()
{
	m_rotScale.setToIdentity();
	m_position.set(0.0f, 0.0f, 0.0f);
}
  
/// \brief Converts this to a 4x4 GLM matrix, so that it can be passed to our
///   shader program.
/// \return A glm::mat4 containing the numbers of this matrix.
Matrix4
Transform::getTransform () const
{
	Matrix4 m4(Vector4(m_rotScale.getRight().m_x, m_rotScale.getRight().m_y, m_rotScale.getRight().m_z,  0.0f),
			   Vector4(m_rotScale.getUp().m_x, m_rotScale.getUp().m_y, m_rotScale.getUp().m_z,  0.0f),
			   Vector4(m_rotScale.getBack().m_x, m_rotScale.getBack().m_y, m_rotScale.getBack().m_z,  0.0f),
			   Vector4(m_position.m_x, m_position.m_y, m_position.m_z, 1.0f));

	return m4;
}
  
/// \brief Copies the elements of this transform into an array, in column-
///   major order.
/// \param[out] array The array to fill up.
/// \post The array contains rx, ry, rz, 0, ux, ... px, py, pz, 1.
void
Transform::getTransform (float array[16]) const
{
	array[0] = m_rotScale.getRight().m_x;
	array[1] = m_rotScale.getRight().m_y;
	array[2] = m_rotScale.getRight().m_z;
	array[3] = 0.0f;

	array[4] = m_rotScale.getUp().m_x;
	array[5] = m_rotScale.getUp().m_y;
	array[6] = m_rotScale.getUp().m_z;
	array[7] = 0.0f;

	array[8] = m_rotScale.getBack().m_x;
	array[9] = m_rotScale.getBack().m_y;
	array[10] = m_rotScale.getBack().m_z;
	array[11] = 0.0f;

	array[12] = m_position.m_x;
	array[13] = m_position.m_y;
	array[14] = m_position.m_z;
	array[15] = 1.0f;
}

/// \brief Gets the position component.
/// \return A copy of the position in this transformation.
Vector3
Transform::getPosition () const
{
	return m_position;
}
  
/// \brief Sets the position component.
/// \param[in] position The new position component.
/// \post The position in this transformation has been set to position.
void
Transform::setPosition (const Vector3& position)
{
	m_position.set(position.m_x, position.m_y, position.m_z);
}

/// \brief Sets the position component.
/// \param[in] x The new x-coordinate of the position.
/// \param[in] y The new y-coordinate of the position.
/// \param[in] z The new z-coordinate of the position.
/// \post The position in this transformation has been set to [x, y, z].
void
Transform::setPosition (float x, float y, float z)
{
	m_position.set(x, y, z);
}

/// \brief Gets the right basis vector.
/// \return A copy of the right basis vector.
Vector3
Transform::getRight () const
{
	return m_rotScale.getRight();
}
  
/// \brief Gets the up basis vector.
/// \return A copy of the up basis vector.
Vector3
Transform::getUp () const
{
	return m_rotScale.getUp();
}
  
/// \brief Gets the back basis vector.
/// \return A copy of the back basis vector.
Vector3
Transform::getBack () const
{
	return m_rotScale.getBack();
}

/// \brief Gets the orientation/scale matrix.
/// \return A copy of the orientation/scale matrix.
Matrix3
Transform::getOrientation () const
{
	return m_rotScale;
}

/// \brief Sets the orientation/scale matrix.
/// \param[in] orientation The new orientation/scale matrix.
/// \post The orientation/scale matrix has been set to the parameter.
void
Transform::setOrientation (const Matrix3& orientation)
{
	m_rotScale.setRight(orientation.getRight());
	m_rotScale.setUp(orientation.getUp());
	m_rotScale.setBack(orientation.getBack());
}

/// \brief Sets the orientation/scale matrix.
/// \param[in] right The new right vector.
/// \param[in] up The new up vector.
/// \param[in] The new back vector.
/// \post The orientation/scale matrix has been set to [right, up, back].
void
Transform::setOrientation (const Vector3& right, const Vector3& up,
	  const Vector3& back)
{
	m_rotScale.setRight(right);
	m_rotScale.setUp(up);
	m_rotScale.setBack(back);
}

/// \brief Moves "distance" units along the right vector.
/// \param[in] distance How far to move.
/// \post The position has been moved that far in the local right direction.
void
Transform::moveRight (float distance)
{
	m_position += m_rotScale.getRight() * distance;
}

/// \brief Moves "distance" units along the up vector.
/// \param[in] distance How far to move.
/// \post The position has been moved that far in the local up direction.
void
Transform::moveUp (float distance)
{
	m_position += m_rotScale.getUp() * distance;
}

/// \brief Moves "distance" units along the back vector.
/// \param[in] distance How far to move.
/// \post The position has been moved that far in the local back direction.
void
Transform::moveBack (float distance)
{
	m_position += m_rotScale.getBack() * distance;
}

/// \brief Moves "distance" units in "localDirection", which is relative
///   to the coordinate system defined by this transform.
/// \param[in] distance How far to move.
/// \param[in] localDirection The (local) direction to move in.
/// \post The position has been moved that far in that direction.
void
Transform::moveLocal (float distance, const Vector3& localDirection)
{
	Vector3 c = localDirection;
	c *= distance;

	m_position += m_rotScale * c;
}

/// \brief Moves "distance" units in "worldDirection", which is relative
///   to the world coordinate system.
/// \param[in] distance How far to move.
/// \param[in] worldDirection The (world) direction to move in.
/// \post The position has been moved that far in that direction.
void
Transform::moveWorld (float distance, const Vector3& worldDirection)
{
	Vector3 c = worldDirection;
	c *= distance;

	m_position += c;
}

/// \brief Rotates about the local X axis.
/// \param[in] angleDegrees how much to rotate.
/// \post The orientation/scale matrix includes this rotation before whatever
///   transformations it already encoded.
void
Transform::pitch (float angleDegrees)
{
	Matrix3 rotX;
	rotX.setToRotationX(angleDegrees);

	m_rotScale *= rotX;
}

/// \brief Rotates about the local Y axis.
/// \param[in] angleDegrees How much to rotate.
/// \post The orientation/scale matrix includes this rotation before whatever
///   transformations it already encoded.
void
Transform::yaw (float angleDegrees)
{
	Matrix3 rotY;
	rotY.setToRotationY(angleDegrees);

	m_rotScale *= rotY;
}

/// \brief Rotates about the local Z axis.
/// \param[in] angleDegrees How much to rotate.
/// \post The orientation/scale matrix includes this rotation before whatever
///   transformations it already encoded.
void
Transform::roll (float angleDegrees)
{
	Matrix3 rotZ;
	rotZ.setToRotationZ(angleDegrees);

	m_rotScale *= rotZ;
}

/// \brief Rotates locally about an arbitrary local unit vector "axis".
/// \param[in] angleDegrees How much to rotate.
/// \param[in] axis The (local) vector to rotate around.
/// \post The orientation/scale matrix includes this rotation before whatever
///   transformations it already encoded.
void
Transform::rotateLocal (float angleDegrees, const Vector3& axis)
{
	Matrix3 rotateLocally;
	rotateLocally.setFromAngleAxis(angleDegrees, axis);

	m_rotScale *= rotateLocally;
}

/// \brief Sets "up" to world Y, and adjusts "back" and "right"
///   to ensure the matrix is orthogonal.
/// If "back" is pointing in the Y or -Y direction,
///   make it [ 0 0 1 ].
/// This will override any scaling, shearing, pitching,
///   or rolling that existed, while leaving yawing and
///   movement.
/// \post The up vector in the orientation/scale matrix is [0, 1, 0].
/// \post The right and back vectors in the orientation/scale matrix are
///   perpendicular to the up vector and each other.
void
Transform::alignWithWorldY ()
{
	m_rotScale.setUp(Vector3(0.0f, 1.0f, 0.0f));

	m_rotScale.setBack(m_rotScale.getRight().cross(m_rotScale.getUp()));
	Vector3 b = m_rotScale.getBack();
	b.normalize();
	m_rotScale.setBack(b);

	m_rotScale.setRight(m_rotScale.getUp().cross(m_rotScale.getBack()));
	Vector3 r = m_rotScale.getRight();
	r.normalize();
	m_rotScale.setRight(r);
	
}

/// \brief Rotates around the world unit vector "axis".
/// \param[in] angleDegrees How much to rotate.
/// \param[in] axis The (world) vector to rotate around.
/// \post The orientation/scale matrix includes this rotation after whatever
///   transformations it already encoded.
void
Transform::rotateWorld (float angleDegrees, const Vector3& axis)
{
	Matrix3 rotWorld;
	rotWorld.setFromAngleAxis(angleDegrees, axis);

	m_position.set((rotWorld.getRight().m_x  * m_position.m_x + rotWorld.getUp().m_x * m_position.m_y + rotWorld.getBack().m_x * m_position.m_z),
	(rotWorld.getRight().m_y  * m_position.m_x + rotWorld.getUp().m_y * m_position.m_y + rotWorld.getBack().m_y * m_position.m_z),
	(rotWorld.getRight().m_z  * m_position.m_x + rotWorld.getUp().m_z * m_position.m_y + rotWorld.getBack().m_z * m_position.m_z));
	
	rotWorld *= m_rotScale;

	m_rotScale.setRight(rotWorld.getRight());
	m_rotScale.setUp(rotWorld.getUp());
	m_rotScale.setBack(rotWorld.getBack());
}

// \brief Scales locally using a uniform scale.
/// \param[in] scale The scaling factor.
/// \post The orientation/scale matrix includes this scale before whatever
///   transformations it already encoded.
void
Transform::scaleLocal (float scale)
{
	Matrix3 localScale;
	localScale.setToScale(scale);

	m_rotScale *= localScale;
}

/// \brief Scales locally using a non-uniform scale.
/// \param[in] scaleX The scaling factor for the X direction.
/// \param[in] scaleY The scaling factor for the Y direction.
/// \param[in] scaleZ The scaling factor for the Z direction.
/// \post The orientation/scale matrix includes this scale before whatever
///   transformations it already encoded.
void
Transform::scaleLocal (float scaleX, float scaleY, float scaleZ)
{
	Matrix3 scaleLocal;
	scaleLocal.setToScale(scaleX, scaleY, scaleZ);

	m_rotScale *= scaleLocal;
}
    
/// \brief Scales with regard to world using a uniform scale.
/// \param[in] scale The scaling factor.
/// \post The orientation/scale matrix includes this scale after whatever
///   transformations it already encoded.
void
Transform::scaleWorld (float scale)
{
	Matrix3 scaleWorld;
	scaleWorld.setToScale(scale);

	m_position.set((scaleWorld.getRight().m_x  * m_position.m_x), (scaleWorld.getUp().m_y * m_position.m_y), (scaleWorld.getBack().m_z * m_position.m_z));

	scaleWorld *= m_rotScale;

	m_rotScale.setRight(scaleWorld.getRight());
	m_rotScale.setUp(scaleWorld.getUp());
	m_rotScale.setBack(scaleWorld.getBack());

	
}

/// \brief Scales with regard to world using a non-uniform scale.
/// \param[in] scaleX The scaling factor for the X direction.
/// \param[in] scaleY The scaling factor for the Y direction.
/// \param[in] scaleZ The scaling factor for the Z direction.
/// \post The orientation/scale matrix includes this scale after whatever
///   transformations it already encoded.
void
Transform::scaleWorld (float scaleX, float scaleY, float scaleZ)
{
	Matrix3 scaleWorld;
	scaleWorld.setToScale(scaleX, scaleY, scaleZ);

	m_position.set((scaleWorld.getRight().m_x  * m_position.m_x), (scaleWorld.getUp().m_y * m_position.m_y), (scaleWorld.getBack().m_z * m_position.m_z));

	scaleWorld *= m_rotScale;

	m_rotScale.setRight(scaleWorld.getRight());
	m_rotScale.setUp(scaleWorld.getUp());
	m_rotScale.setBack(scaleWorld.getBack());
}

/// \brief Shears local X by Y and Z.
/// \param[in] shearY The factor of Y to shear X by.
/// \param[in] shearZ The factor of Z to shear X by.
/// \post The orientation/scale matrix includes this shear before whatever
///   transformations it already encoded.
void
Transform::shearLocalXByYz (float shearY, float shearZ)
{
	Matrix3 shearXYZ;
	shearXYZ.setToShearXByYz(shearY, shearZ);

	m_rotScale *= shearXYZ;
}

/// \brief Shears local Y by X and Z.
/// \param[in] shearX The factor of X to shear Y by.
/// \param[in] shearZ The factor of Z to shear Y by.
/// \post The orientation/scale matrix includes this shear before whatever
///   transformations it already encoded.
void
Transform::shearLocalYByXz (float shearX, float shearZ)
{
	Matrix3 shearYXZ;
	shearYXZ.setToShearYByXz(shearX, shearZ);

	m_rotScale *= shearYXZ;
}


/// \brief Shears local Z by X and Y.
/// \param[in] shearX The factor of X to shear Z by.
/// \param[in] shearY The factor of Y to shear Z by.
/// \post The orientation/scale matrix includes this shear before whatever
///   transformations it already encoded.
void
Transform::shearLocalZByXy (float shearX, float shearY)
{
	Matrix3 shearZXY;
	shearZXY.setToShearZByXy(shearX, shearY);

	m_rotScale *= shearZXY;
}


/// \brief Inverts this transform assuming it consists of a pure rotation
///   and a translation.
/// This can be used to compute the view transform.
/// \pre This transform consists of a pure rotation and translation.
/// \post This transform has been inverted.
void
Transform::invertRt ()
{
	m_rotScale.invertRotation();
	m_position.set((m_rotScale.getRight().m_x  * -m_position.m_x + m_rotScale.getUp().m_x * -m_position.m_y + m_rotScale.getBack().m_x * -m_position.m_z),
	(m_rotScale.getRight().m_y  * -m_position.m_x + m_rotScale.getUp().m_y * -m_position.m_y + m_rotScale.getBack().m_y * -m_position.m_z),
	(m_rotScale.getRight().m_z  * -m_position.m_x + m_rotScale.getUp().m_z * -m_position.m_y + m_rotScale.getBack().m_z * -m_position.m_z));
}

/// \brief Combines this with "t" in the order this * t.
/// \param[in] t Another transform that should be combined with this.
/// \post This transform consists of itself times t.
void
Transform::combine (const Transform& t)
{
	m_position += m_rotScale * t.getPosition();

	m_rotScale *= t.getOrientation();
}

/// \brief Combines two transforms into their product.
/// \param[in] t1 A transform.
/// \param[in] t2 Another transform.
/// \return A new transform that is t1 * t2.
Transform
operator* (const Transform& t1, const Transform& t2)
{
	Transform t;
	Transform c1 = t1;
	Transform c2 = t2;
	c1.combine(c2);

	t.setOrientation(c1.getOrientation());
	t.setPosition(c1.getPosition());

	return t;
}

/// \brief Prints the complete 4x4 matrix the Transform represents.
/// Each element of the matrix should have 2 digits of precision and a field
///   width of 10.  Elements should be in this order:
///      rx ux bx px
///      ry uy by py
///      rz uz bz pz
///      0  0  0  1
/// \param[inout] out An output stream.
/// \param[in] t A transform.
/// \return The output stream.
/// \post The transform has been inserted into the output stream.
std::ostream&
operator<< (std::ostream& out, const Transform& t)
{
	Vector3 r = t.getRight();
	Vector3 u = t.getUp();
	Vector3 b = t.getBack();
	Vector3 p = t.getPosition();

	out << std::setw(10) << std::setprecision(2) << std::fixed  << r.m_x;
    out << std::setw(10) << u.m_x;
    out << std::setw(10) << b.m_x; 
	out << std::setw(10) << p.m_x << std::endl;

	out << std::setw(10) << r.m_y;
    out << std::setw(10) << u.m_y;
    out << std::setw(10) << b.m_y;
	out << std::setw(10) << p.m_y << std::endl;

    out << std::setw(10) << r.m_z;
    out << std::setw(10) << u.m_z;
    out << std::setw(10) << b.m_z;
	out << std::setw(10) << p.m_z << std::endl;

	out << std::setw(10) << 0.0f;
	out << std::setw(10) << 0.0f;
	out << std::setw(10) << 0.0f;
	out << std::setw(10) << 1.0f << std::endl;

	return out;
}

/// \brief Tests whether or not two transforms are equal.
/// Transforms are equal if their matrices and vectors are equal.
/// \param[in] t1 A transform.
/// \param[in] t2 Another transform.
/// \return Whether or not t1 and t2 are equal.
bool
operator== (const Transform& t1, const Transform& t2)
{
	return t1.getOrientation() == t2.getOrientation() && t1.getPosition() == t2.getPosition();
}
