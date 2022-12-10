/// \file TestVector3.cpp
/// \brief A collection of Catch2 unit tests for the Matrix3 class.
/// \author Chad Hogg, John Shenk
/// \version A05

#include <sstream>

#include "Matrix3.hpp"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <bits/stdc++.h>
#include <glm/gtx/rotate_vector.hpp>

SCENARIO("Matrix3 default constructor", "[Matrix3][A05]")
{
  GIVEN("Nothing at all.")
  {
    WHEN("We call the default constructor for Matrix3")
    {
      Matrix3 newMatrix; 
      THEN("The resulting matrix should be the identity matrix.")
      {
        Vector3 right(1.0f, 0.0f, 0.0f); 
        Vector3 up(0.0f, 1.0f, 0.0f);
        Vector3 back(0.0f, 0.0f, 1.0f);
        REQUIRE(right == newMatrix.getRight());
        REQUIRE(up == newMatrix.getUp());
        REQUIRE(back == newMatrix.getBack());
      }
    }
  }
}


SCENARIO("Matrix3 element-wise constructor", "[Matrix3][A05]")
{
  GIVEN("Nothing at all.")
  {
    WHEN("We call the Matrix3 constructor with nine parameters (5.4, 6.5, 7.8, 3.2, 4.5, 9.8, 0.0, 2.1, 3.4)")
    {
      Matrix3 newMatrix(5.4f, 6.5f, 7.8f, 3.2f, 4.5f, 9.8f, 0.0f, 2.1f, 3.4f);
      THEN("We should get a matrix composed of the parameters passed in.")
      {
        REQUIRE(Vector3(5.4f, 6.5f, 7.8f) == newMatrix.getRight());
        REQUIRE(Vector3(3.2f, 4.5f, 9.8f) == newMatrix.getUp());
        REQUIRE(Vector3(0.0f, 2.1f, 3.4f) == newMatrix.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 Vector-wise constructor", "[Matrix3][A05]")
{
  GIVEN("Three vectors")
  {
    Vector3 vec1(8.7f, 4.3f, 5.4f);
    Vector3 vec2(5.4f, 3.2f, 1.2f);
    Vector3 vec3(8.7f, 9.0f, 1.0f);
    WHEN("We call the Matrix3 constructor with the three vectors as parameters")
    {
      Matrix3 newMatrix(vec1, vec2, vec3);
      THEN("We should get a matrix with the three vectors as columns")
      {
        REQUIRE(vec1 == newMatrix.getRight());
        REQUIRE(vec2 == newMatrix.getUp());
        REQUIRE(vec3 == newMatrix.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 Orthogonalizing Constructor", "[Matrix3][A05]")
{
  GIVEN("Two vectors inititalized as (4.0, 8.0, 2.0) and (2.0, 7.0, 2.0)")
  {
    Vector3 vec1 (4.0f, 8.0f, 2.0f);
    Vector3 vec2 (2.0f, 7.0f, 2.0f);
    WHEN("We call the Matrix3 constructor passing only vec1 and vec2.")
    {
      Matrix3 newMatrix(vec1, vec2);
      THEN("The resuliting matrix's right vector should equal the cross product of the two vectors passed in.")
      {
        REQUIRE(vec1 == newMatrix.getUp());
        REQUIRE(vec2 == newMatrix.getBack());
        // Source: Cross((4.0, 8.0, 2.0), (2.0, 7.0, 2.0)) typed into Wolfram Alpha
        REQUIRE(Vector3(2.0f, -4.0f, 12.0f) == newMatrix.getRight());
      }
    }
  }
}

SCENARIO("Matrix3 setToIdentity", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized as (4.0, 4.0, 5.0, 6.0, 3.0, 4.0, 3.0, 4.0, 9.0)")
  {
    Matrix3 m (4.0f, 4.0f, 5.0f, 6.0f, 3.0f, 4.0f, 3.0f, 4.0f, 9.0f);
    WHEN("We call set to identity on the matrix")
    {
      m.setToIdentity();
      THEN("We should get the identity matrix back")
      {
        REQUIRE(Vector3(1.0f, 0.0f, 0.0f) == m.getRight());
        REQUIRE(Vector3(0.0f, 1.0f, 0.0f) == m.getUp());
        REQUIRE(Vector3(0.0f, 0.0f, 1.0f) == m.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 setToZero", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (4.0, 4.0, 5.0, 6.0, 3.0, 4.0, 3.0, 4.0, 9.0)")
  {
    Matrix3 m (4.0f, 4.0f, 5.0f, 6.0f, 3.0f, 4.0f, 3.0f, 4.0f, 9.0f);
    WHEN("We call setToZero on the matrix")
    {
      m.setToZero();
      THEN("We should get the zero matrix back.")
      {
        REQUIRE(Vector3(0.0f, 0.0f, 0.0f) == m.getRight());
        REQUIRE(Vector3(0.0f, 0.0f, 0.0f) == m.getUp());
        REQUIRE(Vector3(0.0f, 0.0f, 0.0f) == m.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 data function", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (4.0, 4.0, 5.0, 6.0, 3.0, 4.0, 3.0, 4.0, 9.0)")
  {
    Matrix3 m (4.0f, 4.0f, 5.0f, 6.0f, 3.0f, 4.0f, 3.0f, 4.0f, 9.0f);
    WHEN("We create a float pointer and set it equal to m.data()")
    {
      float* data = m.data();
      THEN("We should get a pointer pointing to the first element in the matrix (4.0f)")
      {
        REQUIRE(*data == 4.0f);
      }
    }
  }
}                                                                      

SCENARIO("Matrix3 setRight", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (4.0, 4.0, 5.0, 6.0, 3.0, 4.0, 3.0, 4.0, 9.0 and a vector initialized to (8.0, 5.0, 1.0)")
  {
    Matrix3 m (4.0f, 4.0f, 5.0f, 6.0f, 3.0f, 4.0f, 3.0f, 4.0f, 9.0f);
    Vector3 v (8.0f, 5.0f, 1.0f);
    WHEN("We call setRight with the vector as a parameter.")
    {
      m.setRight(v);
      THEN("The right vector should equal (8.0, 5.0, 1.0)")
      {
        REQUIRE(v == m.getRight());
      }
    }
  }
}

SCENARIO("Matrix3 getRight", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (4.0, 4.0, 5.0, 6.0, 3.0, 4.0, 3.0, 4.0, 9.0)")
  {
    Matrix3 m (4.0f, 4.0f, 5.0f, 6.0f, 3.0f, 4.0f, 3.0f, 4.0f, 9.0f);
    WHEN("We call getRight")
    {
      THEN("We should get the right vector (4.0, 4.0, 5.0)")
      {
        REQUIRE(Vector3(4.0f, 4.0f, 5.0f) == m.getRight());
      }
    }
  }
}

SCENARIO("Matrix3 setUp", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (4.0, 4.0, 5.0, 6.0, 3.0, 4.0, 3.0, 4.0, 9.0 and a vector initialized to (8.0, 5.0, 1.0)")
  {
    Matrix3 m (4.0f, 4.0f, 5.0f, 6.0f, 3.0f, 4.0f, 3.0f, 4.0f, 9.0f);
    Vector3 v (8.0f, 5.0f, 1.0f);
    WHEN("We call setUp with the vector as a parameter.")
    {
      m.setUp(v);
      THEN("The up vector should equal (8.0, 5.0, 1.0)")
      {
        REQUIRE(v == m.getUp());
      }
    }
  }
}

SCENARIO("Matrix3 getUp", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (4.0, 4.0, 5.0, 6.0, 3.0, 4.0, 3.0, 4.0, 9.0)")
  {
    Matrix3 m (4.0f, 4.0f, 5.0f, 6.0f, 3.0f, 4.0f, 3.0f, 4.0f, 9.0f);
    WHEN("We call getUp with the vector as a parameter.")
    {
      THEN("We should get the up vector (6.0, 3.0, 4.0)")
      {
        REQUIRE(Vector3(6.0f, 3.0f, 4.0f) == m.getUp());
      }
    }
  }
}



SCENARIO("Matrix3 setBack", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (4.0, 4.0, 5.0, 6.0, 3.0, 4.0, 3.0, 4.0, 9.0 and a vector initialized to (8.0, 5.0, 1.0)")
  {
    Matrix3 m (4.0f, 4.0f, 5.0f, 6.0f, 3.0f, 4.0f, 3.0f, 4.0f, 9.0f);
    Vector3 v (8.0f, 5.0f, 1.0f);
    WHEN("We call setBack with the vector as a parameter.")
    {
      m.setBack(v);
      THEN("The back vector should equal (8.0, 5.0, 1.0)")
      {
        REQUIRE(v == m.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 getBack", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (4.0, 4.0, 5.0, 6.0, 3.0, 4.0, 3.0, 4.0, 9.0)")
  {
    Matrix3 m (4.0f, 4.0f, 5.0f, 6.0f, 3.0f, 4.0f, 3.0f, 4.0f, 9.0f);
    WHEN("We call getBack with the vector as a parameter.")
    {
      THEN("We should get the back vector (3.0, 4.0, 9.0)")
      {
        REQUIRE(Vector3(3.0f, 4.0f, 9.0f) == m.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 setForward", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (4.0, 4.0, 5.0, 6.0, 3.0, 4.0, 3.0, 4.0, 9.0) and a vector initialized to (5.0, -10.0, 4.0)")
  {
    Matrix3 m (4.0f, 4.0f, 5.0f, 6.0f, 3.0f, 4.0f, 3.0f, 4.0f, 9.0f);\
    Vector3 v (5.0f, -10.0f, 4.0f);
    WHEN("We call setForward with the vector as a parameter.")
    {
      m.setForward(v);
      THEN("The back vector should now be the negation of the vector passed in.")
      {
        REQUIRE(Vector3(-5.0f, 10.0f, -4.0f) == m.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 getForward", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (4.0, 4.0, 5.0, 6.0, 3.0, 4.0, 3.0, 4.0, 9.0)")
  {
    Matrix3 m (4.0f, 4.0f, 5.0f, 6.0f, 3.0f, 4.0f, 3.0f, 4.0f, 9.0f);
    WHEN("We call getForward")
    {
      THEN("We should get the negation of the back vector. THe back vector itself should not be changed")
      {
        REQUIRE(Vector3(-3.0f, -4.0f, -9.0f) == m.getForward());
        //Checks if the back vector stayed the same
        REQUIRE(Vector3(3.0f, 4.0f, 9.0f) == m.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 invertRotation", "[Matrix3][A05]")
{
  GIVEN("A rotation matrix (rotationX in this example) with 90.0 as a parameter")
  {
    Matrix3 m;
    m.setToRotationX(90.0f);
    WHEN("We call invertRotation on the matrix")
    {
      m.invertRotation();
      THEN("The resulting matrix should be the inverse of the original")
      {
        REQUIRE(Vector3(1.0f, 0.0f, 0.0f) == m.getRight());
        REQUIRE(Vector3(0.0f, 0.0f, -1.0f) == m.getUp());
        REQUIRE(Vector3(0.0f, 1.0f, 0.0f) == m.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 Invert", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (4.0, 4.0, 5.0, 6.0, 3.0, 4.0, 3.0, 4.0, 9.0)")
  {
    Matrix3 m (4.0f, 4.0f, 5.0f, 6.0f, 3.0f, 4.0f, 3.0f, 4.0f, 9.0f);
    WHEN("We call the invert function on this matrix")
    {
      Matrix3 identity;
      identity.setToIdentity();
      Matrix3 m2 = m;
      m.invert();
      THEN("When we multiply the matrices together, we should get the identity matrix")
      {
        REQUIRE (identity == m2 * m);
      }
    }
  }
}

SCENARIO("Matrix3 determinant", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (4.0, 4.0, 5.0, 6.0, 3.0, 4.0, 3.0, 4.0, 9.0)")
  {
    Matrix3 m (4.0f, 4.0f, 5.0f, 6.0f, 3.0f, 4.0f, 3.0f, 4.0f, 9.0f);
    WHEN("We call the determinant function on this matrix")
    {
      float det = m.determinant();
      THEN("The resulting value should be the determinant")
      {
        REQUIRE(Approx(-49.0f) == det);
      }
    }
  }
}



SCENARIO("Matrix3 transpose", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (4.0, 2.0, 8.0, 4.0, 5.0, 7.0, 2.0, 0.0, 1.0)")
  {
    Matrix3 m (4.0f, 2.0f, 8.0f, 4.0f, 5.0f, 7.0f, 2.0f, 0.0f, 1.0f);
    WHEN("We call transpose")
    {
      m.transpose();
      THEN("The matrix should now be its transpose")
      {
        REQUIRE(Vector3(4.0f, 2.0f, 8.0f) == m.getRight());
        REQUIRE(Vector3(4.0f, 5.0f, 7.0f) == m.getUp());
        REQUIRE(Vector3(2.0f, 0.0f, 1.0f) == m.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 orthonormalize", "[Matrix3][A05]")
{
  GIVEN("A Matrix initialized to (2.0f, 6.0f, 8.0f, 8.0f, 6.0f, 6.0f, 2.0f, 4.0f, 0.0f)")
  {
    Matrix3 m (2.0f, 6.0f, 8.0f, 8.0f, 6.0f, 6.0f, 2.0f, 4.0f, 0.0f);
    WHEN("We call orthonormalize on the matrix.")
    {
      m.orthonormalize();
      THEN("The matrix should now be orthonormalized.")
      {
        REQUIRE(Vector3(0.196116f, 0.962699f, -0.186411f) == m.getRight());
        REQUIRE(Vector3(0.588348f, 0.0365582f, 0.807781) == m.getUp());
        REQUIRE(Vector3(0.784465f, -0.268093f, -0.559233f) == m.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 setToSclae - uniform", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f)")
  {
    Matrix3 m (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f);
    WHEN("We call setToScale on the matrix with 5.0f as a parameter")
    {
      m.setToScale(5.0f);
      THEN("The matrix should now be a uniform scale matrix")
      {
        REQUIRE(Vector3(5.0f, 0.0f, 0.0f) == m.getRight());
        REQUIRE(Vector3(0.0f, 5.0f, 0.0f) == m.getUp());
        REQUIRE(Vector3(0.0f, 0.0f, 5.0f) == m.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 setToScale - non-uniform", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (6.0f, 2.0f, 5.0f, 1.0f, 4.0f, 9.0f, 4.0f, 5.0f, 3.0f)")
  {
    Matrix3 m (6.0f, 2.0f, 5.0f, 1.0f, 4.0f, 9.0f, 4.0f, 5.0f, 3.0f);
    WHEN("We call setToScale on the matrix with the parameters (7.0f, 5.0f, 2.0f)")
    {
      m.setToScale(7.0f, 5.0f, 2.0f);
      THEN("The matrix should now be a non-uniform scale matrix")
      {
        REQUIRE(Vector3(7.0f, 0.0f, 0.0f) == m.getRight());
        REQUIRE(Vector3(0.0f, 5.0f, 0.0f) == m.getUp());
        REQUIRE(Vector3(0.0f, 0.0f, 2.0f) == m.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 setToShearXByYz", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (0.0f, 3.0f, 2.0f, 1.0f, 6.0f, 5.0f, 4.0f, 5.0f, 3.0f)")
  {
    Matrix3 m (0.0f, 3.0f, 2.0f, 1.0f, 6.0f, 5.0f, 4.0f, 5.0f, 3.0f);
    WHEN("We call setToShearXByYz on the matrix with the parameters (5.0f, 6.0f)")
    {
      m.setToShearXByYz(5.0f, 6.0f);
      THEN("The matrix should now be a shearing matrix")
      {
        REQUIRE(Vector3 (1.0f, 0.0f, 0.0f) == m.getRight());
        REQUIRE(Vector3 (5.0f, 1.0f, 0.0f) == m.getUp());
        REQUIRE(Vector3 (6.0f, 0.0f, 1.0f) == m.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 setToShearYByXz", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f)")
  {
    Matrix3 m (0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f);
    WHEN("We call setToShearYByXz on the matrix with the parameters (9.0f, 4.0f)")
    {
      THEN("The matrix should now be a shearing matrix")
      {
        REQUIRE(Vector3(1.0f, 9.0f, 0.0f) == m.getRight());
        REQUIRE(Vector3(0.0f, 1.0f, 0.0f) == m.getUp());
        REQUIRE(Vector3(0.0f, 4.0f, 1.0f) == m.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 setToShearZByXy", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (9.0f, 2.0f, 5.0f, 6.0f, 3.0f, 1.0f, 5.0f, 4.0f, 7.0f)")
  {
    Matrix3 m (9.0f, 2.0f, 5.0f, 6.0f, 3.0f, 1.0f, 5.0f, 4.0f, 7.0f);
    WHEN("We call setToShearZByXy on the matrix with the parameters (4.0f, -8.0f)")
    {
      m.setToShearZByXy(4.0f, -8.0f);
      THEN("The matrix should now be a shearing matrix")
      {
        REQUIRE(Vector3(1.0f, 0.0f, 4.0f) == m.getRight());
        REQUIRE(Vector3(0.0f, 1.0f, -8.0f) == m.getUp());
        REQUIRE(Vector3(0.0f, 0.0f, 1.0f) == m.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 setToRotationX", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (9.0f, 2.0f, 5.0f, 6.0f, 3.0f, 1.0f, 5.0f, 4.0f, 7.0f)")
  {
    Matrix3 m (9.0f, 2.0f, 5.0f, 6.0f, 3.0f, 1.0f, 5.0f, 4.0f, 7.0f);
    WHEN("We call setRotationX on the matrix with the parameter with the parameter 90")
    {
      m.setToRotationX(90.0f);
      THEN("The matrix should be a rotation about x matrix")
      {
        REQUIRE(Vector3(1.0f, 0.0f, 0.0f) == m.getRight());
        REQUIRE(Vector3(0.0f, cos(glm::radians(90.0f)), sin(glm::radians(90.0f))) == m.getUp());
        REQUIRE(Vector3(0.0f, -sin(glm::radians(90.0f)), cos(glm::radians(90.0f))) == m.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 setToRotationY", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (9.0f, 2.0f, 5.0f, 6.0f, 3.0f, 1.0f, 5.0f, 4.0f, 7.0f)")
  {
    Matrix3 m (9.0f, 2.0f, 5.0f, 6.0f, 3.0f, 1.0f, 5.0f, 4.0f, 7.0f);
    WHEN("We call setRotationY on the matrix with the parameter with the parameter 90")
    {
      m.setToRotationY(90);
      THEN("The matrix should be a rotation about y axis")
      {
        REQUIRE(Vector3(cos(glm::radians(90.0f)), 0.0f, sin(glm::radians(90.0f))) == m.getRight());
        REQUIRE(Vector3(0.0f, 1.0f, 0.0f) == m.getUp());
        REQUIRE(Vector3(-sin(glm::radians(90.0f)), 0.0f, cos(glm::radians(90.0f))) == m.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 setToRotationZ", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (9.0f, 2.0f, 5.0f, 6.0f, 3.0f, 1.0f, 5.0f, 4.0f, 7.0f)")
  {
    Matrix3 m (9.0f, 2.0f, 5.0f, 6.0f, 3.0f, 1.0f, 5.0f, 4.0f, 7.0f);
    WHEN("We call setRotationZ on the matrix with the parameter with the parameter 90")
    {
      m.setToRotationZ(90);
      THEN("The matrix should be a rotation about z axis")
      {
        REQUIRE(Vector3(cos(glm::radians(90.0f)), sin(glm::radians(90.0f)), 0.0f) == m.getRight());
        REQUIRE(Vector3(-sin(glm::radians(90.0f)), cos(glm::radians(90.0f)), 0.0f) == m.getBack());
        REQUIRE(Vector3(0.0f, 0.0f, 1.0f) == m.getUp());
      }
    }
  }
}



SCENARIO("Matrix3 setFromAngleAxis", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (9.0f, 2.0f, 5.0f, 6.0f, 3.0f, 1.0f, 5.0f, 4.0f, 7.0f)")
  {
    Matrix3 m (9.0f, 2.0f, 5.0f, 6.0f, 3.0f, 1.0f, 5.0f, 4.0f, 7.0f);
    WHEN("We call setFromAngleAxis on the matrix with the parameter with the parameter 45 and the vector (1, 2, 3)")
    {
      m.setFromAngleAxis(45.0f, Vector3(1.0f, 2.0f, 3.0f));
      THEN("The matrix should be det to rotate around the given axis")
      {
         REQUIRE( true == true );
      }
    }
  }
}

SCENARIO("Matrix3 Negate", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (3.0f, 5.0f, 6.0f, -2.0f, 6.0f, -1.0f, -5.0f, -8.0f, -2.0f)")
  {
    Matrix3 m (3.0f, 5.0f, 6.0f, -2.0f, 6.0f, -1.0f, -5.0f, -8.0f, -2.0f);
    WHEN("We call negate on this matrix")
    {
      m.negate();
      THEN("The matrix should now be its negation")
      {
        REQUIRE(Vector3(-3.0f, -5.0f, -6.0f) == m.getRight());
        REQUIRE(Vector3(2.0f, -6.0f, 1.0f) == m.getUp());
        REQUIRE(Vector3(5.0f, 8.0f, 2.0f) == m.getBack());
      }
    }
  }
}


SCENARIO("Matrix3 transform", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f) and a vector initalized to (1.0f, 2.0f, 3.0f)")
  {
    Matrix3 m (8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f);
    Vector3 v (3.0f, 2.0f, 1.0f);
    WHEN("We call transform on the matrix with the vector as a parameter")
    {
      THEN("The vector should now be matrix * vector")
      {
        REQUIRE(Vector3(36.0f, 30.0f, 24.0f) == m.transform(v));
      }
    }
  }
}

SCENARIO("Matrix3 operator+=", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 9.0f, 8.0f) and a matrix initialized to (9.0f, 7.0f, 5.0f, 3.0f, 1.0f, 9.0f, 4.0f, 6.0f, 2.0f)")
  {
    Matrix3 m1 (6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 9.0f, 8.0f);
    Matrix3 m2 (9.0f, 7.0f, 5.0f, 3.0f, 1.0f, 9.0f, 4.0f, 6.0f, 2.0f);
    WHEN("We add m2 to m1 using +=")
    {
      m1 += m2;
      THEN("m1 should now be m1 + m2")
      {
        REQUIRE(Vector3(15.0f, 12.0f, 9.0f) == m1.getRight());
        REQUIRE(Vector3(6.0f, 3.0f, 10.0f) == m1.getUp());
        REQUIRE(Vector3(4.0f, 15.0f, 10.0f) == m1.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 operator-=", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 9.0f, 8.0f) and a matrix initialized to (9.0f, 7.0f, 5.0f, 3.0f, 1.0f, 9.0f, 4.0f, 6.0f, 2.0f)")
  {
    Matrix3 m1 (6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 9.0f, 8.0f);
    Matrix3 m2 (9.0f, 7.0f, 5.0f, 3.0f, 1.0f, 9.0f, 4.0f, 6.0f, 2.0f);
    WHEN("We add m2 to m1 using -=")
    {
      m1 -= m2;
      THEN("m1 should now be m1 - m2")
      {
        REQUIRE(Vector3(-3.0f, -2.0f, -1.0f) == m1.getRight());
        REQUIRE(Vector3(0.0f, 1.0f, -8.0f) == m1.getUp());
        REQUIRE(Vector3(-4.0f, 3.0f, 6.0f) == m1.getBack());
      }
    }
  }
}





SCENARIO("Matrix3 operator*= matrix x matrix", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 9.0f, 8.0f) and a matrix initialized to (9.0f, 7.0f, 5.0f, 3.0f, 1.0f, 9.0f, 4.0f, 6.0f, 2.0f)")
  {
    Matrix3 m1 (6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 9.0f, 8.0f);
    Matrix3 m2 (9.0f, 7.0f, 5.0f, 3.0f, 1.0f, 9.0f, 4.0f, 6.0f, 2.0f);
    WHEN("We add m2 to m1 using +=")
    {
      m1 *= m2;
      THEN("m1 should now be m1 * m2")
      {
        // Source: matrices multiplied on Wolfram Alpha
        REQUIRE(Vector3(75.0f, 104.0f, 83.0f) == m1.getRight());
        REQUIRE(Vector3(21.0f, 98.0f, 85.0f) == m1.getUp());
        REQUIRE(Vector3(42.0f, 50.0f, 38.0f) == m1.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 operator+", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 9.0f, 8.0f) and a matrix initialized to (9.0f, 7.0f, 5.0f, 3.0f, 1.0f, 9.0f, 4.0f, 6.0f, 2.0f)")
  {
    Matrix3 m1 (6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 9.0f, 8.0f);
    Matrix3 m2 (9.0f, 7.0f, 5.0f, 3.0f, 1.0f, 9.0f, 4.0f, 6.0f, 2.0f);
    WHEN("We add m2 to m1 using +")
    {
      m1 =  m1 + m2;
      THEN("m1 should now be m1 + m2")
      {
        REQUIRE(Vector3(15.0f, 12.0f, 9.0f) == m1.getRight());
        REQUIRE(Vector3(6.0f, 3.0f, 10.0f) == m1.getUp());
        REQUIRE(Vector3(4.0f, 15.0f, 10.0f) == m1.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 operator-", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 9.0f, 8.0f) and a matrix initialized to (9.0f, 7.0f, 5.0f, 3.0f, 1.0f, 9.0f, 4.0f, 6.0f, 2.0f)")
  {
    Matrix3 m1 (6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 9.0f, 8.0f);
    Matrix3 m2 (9.0f, 7.0f, 5.0f, 3.0f, 1.0f, 9.0f, 4.0f, 6.0f, 2.0f);
    WHEN("We add m2 to m1 using -")
    {
      m1 = m1 - m2;
      THEN("m1 should now be m1 - m2")
      {
        REQUIRE(Vector3(-3.0f, -2.0f, -1.0f) == m1.getRight());
        REQUIRE(Vector3(0.0f, 1.0f, -8.0f) == m1.getUp());
        REQUIRE(Vector3(-4.0f, 3.0f, 6.0f) == m1.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 operator* matrix * scalar", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 9.0f, 8.0f) and a matrix initialized to (9.0f, 7.0f, 5.0f, 3.0f, 1.0f, 9.0f, 4.0f, 6.0f, 2.0f)")
  {
    Matrix3 m1 (6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 9.0f, 8.0f);
    
    WHEN("We multiply the matrix by a scalar 3.0f")
    {
      m1 = m1 * 3.0f;
      THEN("m1's elements should have all been multiplied by the scalar")
      {
        REQUIRE(Vector3(18.0f, 15.0f, 12.0f) == m1.getRight());
        REQUIRE(Vector3(9.0f, 6.0f, 3.0f) == m1.getUp());
        REQUIRE(Vector3(0.0f, 27.0f, 24.0f) == m1.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 operator* scalar * matrix", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 9.0f, 8.0f) and a matrix initialized to (9.0f, 7.0f, 5.0f, 3.0f, 1.0f, 9.0f, 4.0f, 6.0f, 2.0f)")
  {
    Matrix3 m1 (6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 9.0f, 8.0f);
    
    WHEN("We multiply the matrix by a scalar 3.0f")
    {
      m1 = 3.0f * m1;
      THEN("m1's elements should have all been multiplied by the scalar")
      {
        REQUIRE(Vector3(18.0f, 15.0f, 12.0f) == m1.getRight());
        REQUIRE(Vector3(9.0f, 6.0f, 3.0f) == m1.getUp());
        REQUIRE(Vector3(0.0f, 27.0f, 24.0f) == m1.getBack());
      }
    }
  }
}


SCENARIO("Matrix3 operator* matrix x matrix", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 9.0f, 8.0f) and a matrix initialized to (9.0f, 7.0f, 5.0f, 3.0f, 1.0f, 9.0f, 4.0f, 6.0f, 2.0f)")
  {
    Matrix3 m1 (6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 9.0f, 8.0f);
    Matrix3 m2 (9.0f, 7.0f, 5.0f, 3.0f, 1.0f, 9.0f, 4.0f, 6.0f, 2.0f);
    WHEN("We add m2 to m1 using *")
    {
      m1 = m1 * m2;
      THEN("m1 should now be m1 * m2")
      {
        // Source: matrices multiplied on Wolfram Alpha
        REQUIRE(Vector3(75.0f, 104.0f, 83.0f) == m1.getRight());
        REQUIRE(Vector3(21.0f, 98.0f, 85.0f) == m1.getUp());
        REQUIRE(Vector3(42.0f, 50.0f, 38.0f) == m1.getBack());
      }
    }
  }
}

SCENARIO("Matrix3 operator* matrix * vector", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f) and a vector initalized to (1.0f, 2.0f, 3.0f)")
  {
    Matrix3 m (8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f);
    Vector3 v (3.0f, 2.0f, 1.0f);
    WHEN("We multiply the matrix by the vector using *")
    {
      v = m * v;
      THEN("The vector should now be matrix * vector")
      {
        REQUIRE(Vector3(36.0f, 30.0f, 24.0f) == v);
      }
    }
  }
}

SCENARIO("Matrix3 output operator", "[Matrix3][A05]")
{
  GIVEN("A matrix initialized to (1.0f, 1.0f, 2.0f, 3.0f, 5.0f, 8.0f, 13.0f, 21.0f, 34.0f)")
  {
    Matrix3 m (1.0f, 1.0f, 2.0f, 3.0f, 5.0f, 8.0f, 13.0f, 21.0f, 34.0f);
    WHEN("We put this matrix into an output stream")
    {
      std::stringstream out;
       std::ostream& r = out << m;
      THEN("It should have included each component with a precision of 2 and field width of 10.")
      {
        REQUIRE( ("      1.00      1.00      2.00\n" "      3.00      5.00      8.00\n" "      13.00      21.00      34.00\n") == out.str () );
      }
    }
  }
}

SCENARIO("Matrix3 operator==", "[Matrix3][A05]")
{
  GIVEN("A matrix intialized to (6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 9.0f, 8.0f) and a matrix initialized to (6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 9.0f, 8.0f)")
  {
    Matrix3 m1 (6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 9.0f, 8.0f);
    Matrix3 m2 (6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f, 0.0f, 9.0f, 8.0f);
    WHEN("We compare the two matrices")
    {
      THEN("The matrices should be equivalent")
      {
        REQUIRE(m1 == m2);
      }
    }
  }
}

/*
SKELETON OF TEST CODE TO GET STARTED ON A NEW ONE
=================================================

SCENARIO("", "[Matrix3][A05]")
{
  GIVEN("")
  {
    WHEN("")
    {
      THEN("")
      {
        REQUIRE(true == true);
      }
    }
  }
}


*/