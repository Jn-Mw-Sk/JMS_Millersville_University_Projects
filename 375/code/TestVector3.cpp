/// \file TestVector3.cpp
/// \brief A collection of Catch2 unit tests for the Vector3 class.
/// \author Chad Hogg, John Shenk
/// \version A04

#include <sstream>

#include "Vector3.hpp"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>


// Note: I included just a few representative / unusually tricky test cases here.  You should write the others, for every function declared in Vector3.hpp.

SCENARIO ("Vector3 constructors.", "[Vector3][A04]") {
  GIVEN ("Nothing at all.") {
    WHEN ("I use the default Vector3 constructor.") {
      Vector3 v;
      THEN ("All components should be 0.0f.") {
	REQUIRE (0.0f == Approx (v.m_x));
	REQUIRE (0.0f == Approx (v.m_y));
	REQUIRE (0.0f == Approx (v.m_z));
      }
    }

    WHEN ("I pass 5.3f to the constructor with one parameter.") {
      Vector3 v (5.3f);
      THEN ("All components should be 5.3f.") {
	REQUIRE (5.3f == Approx (v.m_x));
	REQUIRE (5.3f == Approx (v.m_y));
	REQUIRE (5.3f == Approx (v.m_z));
      }
    }

    WHEN ("I pass 3.4f, 9.1f, and -2.4f to the constructor with three parameters.") {
      Vector3 v (3.4f, 9.1f, -2.4f);
      THEN ("The components should be 3.4f, 9.1f, and -2.4f respectively.") {
	REQUIRE (3.4f == Approx (v.m_x));
	REQUIRE (9.1f == Approx (v.m_y));
	REQUIRE (-2.4f == Approx (v.m_z));
      }
    }
  }
}

////////////////John's Tests////////////////
SCENARIO ("Vector3 set function.", "[Vector3][A04]")
{
  GIVEN("A vector initialized with (1.0f, 2.0f, 3.0f).")
  {
    Vector3 v1 (1.0f, 2.0f, 3.0f);
    WHEN("I call set on this vector with a parameter of 5.0f.")
    {
      v1.set(5.0);
      THEN("Each element in the vector should be set to 5.0f."){
        REQUIRE (5.0f == Approx (v1.m_x));
        REQUIRE (5.0f == Approx (v1.m_y));
        REQUIRE (5.0f == Approx (v1.m_z));
      }
    }   
  }
}

SCENARIO ("Vector3 negate function", "[Vector3][A04]")
{
  GIVEN ("A vector initialized with (6.5f, -2.5f, 0.0f")
  {
    Vector3 v (6.5f, -2.5f, 0.0f);
    WHEN("I call negate on this vector.")
    {
      v.negate();
      THEN("The elements in the vector should be negated (i.e. (-6.5f, 2.5f, 0.0f))")
      {
        REQUIRE (-6.5f == Approx(v.m_x));
        REQUIRE (2.5f == Approx(v.m_y));
        REQUIRE (0.0f == Approx(v.m_z));
      }
    }
  }
}



///////////////////////////////////////////

SCENARIO ("Vector3 dot product.", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to (1.1f, 2.2f, 3.3f) and (0.1f, -2.0f, 8.0f).") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    Vector3 v2 (0.1f, -2.0f, 8.0f);
    WHEN ("I find the dot product of the vectors.") 
    {
      float dot = v1.dot (v2);
      THEN ("The dot product should be the sum of the element-wise products.") {
	      // Source: typed "dot product of (1.1, 2.2, 3.3) and (0.1, -2.0, 8.0)" into Wolfram Alpha
	      REQUIRE (22.11f == Approx (dot));
      }
    }
  }
}

////////////////John's Tests////////////////

SCENARIO ("Vector3 angleBetween:", "[Vector3][A04]")
{
  GIVEN("A vector initialized to (7.6, 4.5, 67.8) and a vector initialized to (6.5, 4.9, 9.3)")
  {
    Vector3 v1 (7.6f, 4.5f, 67.8f);
    Vector3 v2 (6.5f, 4.9f, 9.3f);
    WHEN("angleBetween is called on v1 with v2 as a parameter")
    {
      float angle = v1.angleBetween(v2);
      THEN("The angle between the two vector should equal 0.59039")
      {
        // Source: entered both vectors into an angle calculator on Wolfram Alpha
        REQUIRE (0.59039 == Approx(angle));
      }
    }
  }
}

SCENARIO("Vector 3 cross product", "[Vector3][A04]")
{
  GIVEN("A vector initialized to (2.0, 3.0, -1.0) and a vector initialized to (4.0, 5.0, 1.0)")
  {
    Vector3 v1 (2.0f, 3.0f, -1.0f);
    Vector3 v2 (4.0f, 5.0f, 1.0f);
    WHEN("The cross method is called on v1 with v2 as a paremeter")
    {
      THEN("The cross product should be (8.0, -6.0, -2.0")
      {
        Vector3 crossProduct = v1.cross(v2);
        // Source: Example taken from the lecture slides
        REQUIRE(8.0f == Approx(crossProduct.m_x));
        REQUIRE(-6.0f == Approx(crossProduct.m_y));
        REQUIRE(-2.0f == Approx(crossProduct.m_z));
      }
    }
  }
}

SCENARIO("Vector3 length", "[Vector3][A04]")
{
  GIVEN("A vector intialized to (8.8, 4.3, 6.5)")
  {
    Vector3 v (8.8f, 4.3f, 6.5f);
    WHEN("length is called on v")
    {
      float l = v.length();
      THEN("The length should be 11.755")
      {
        // Source: vector length {8.8, 4.3, 6.5} typed into Wolfram Alpha
        REQUIRE(11.755 == Approx(l));
      }
    }
  }
}

SCENARIO("Vector3 normalize", "[Vector3][A04]")
{
  GIVEN("A vector initialized to (7.6, 5.9, 11.0)")
  {
    Vector3 v (7.6f, 5.9f, 11.0f);
    WHEN("'normalize' is called on v")
    {
      v.normalize();
      THEN("The resulting vector should be ((0.520048, 0.403722, 0.752701))")
      {
        REQUIRE(0.520048f == Approx(v.m_x));
        REQUIRE(0.403722f == Approx(v.m_y));
        REQUIRE(0.752701f == Approx(v.m_z));
      }
    }
  }
}

SCENARIO("Vector3 += operator", "[Vector3][A04]")
{
  GIVEN("A vector intialized to (5.0, 7.9, 5.3) and a vector initialized to (6.4, 9.8, 1.0)")
  {
    Vector3 v1 (5.0f, 7.9f, 5.3f);
    Vector3 v2 (6.4f, 9.8f, 1.0f); 
    WHEN("The '+=' operator is used to add v1 and v2")
    {
      v1 += v2;
      THEN("The vector v1 should now equal (11.4, 17.7, 6.3)")
      {
        // Source: (5.0, 7.9, 5.3) + (6.4, 9.8, 1.0) typed into Wolfram Alpha
        REQUIRE(11.4f == Approx(v1.m_x));
        REQUIRE(17.7f == Approx(v1.m_y));
        REQUIRE(6.3f == Approx(v1.m_z));
      }
    }
  }
}

SCENARIO("Vector3 -= operator", "[Vector3][A04]")
{
  GIVEN("A vector initialized to (6.76, 4.59, 4.32) and a vector intialized to (3.22, 6.98, 5.67)")
  {
    Vector3 v1 (6.76f, 4.59f, 4.32f);
    Vector3 v2 (3.22f, 6.98f, 5.67f);
    WHEN("The '-=' operator is used to subtract v2 from v1.")
    {
      v1 -= v2;
      THEN("The vector v1 should be the difference between v1 ad v2.")
      {
        // Source: Typed calculations in graphing calculator
        REQUIRE(3.54 == Approx (v1.m_x));
        REQUIRE(-2.39 == Approx (v1.m_y));
        REQUIRE(-1.35 == Approx (v1.m_z));
      }
    }
  }
}

SCENARIO("Vector3 *= operator", "[Vector3][A04]")
{
  GIVEN("A vector initialized to (4.54, 6.59, 1.0) and a scalar s (2.0)")
  {
    Vector3 v (4.54f, 6.59f, 1.0f);
    float s = 2.0f;
    WHEN("We use the *= operator to multiply the vector by a scalar")
    {
      v *= s;
      THEN("The resulting vector should be the original vector multiplied by the scalar")
      {
        // Source: (4.54, 6.59, 1.0) * 2.0 typed into Wolfram Alpha
        REQUIRE(9.08f == Approx(v.m_x));
        REQUIRE(13.18f == Approx(v.m_y));
        REQUIRE(2.0f == Approx(v.m_z));
      }
    }
  }
}

SCENARIO("Vector3 /= operator", "[Vector3][A04]")
{
  GIVEN("A vector initialized to (7.0, -18.0, 66.0) and a scalar s (2.0f)")
  {
    Vector3 v (7.0f, -18.0f, 66.0f);
    float s = 2.0f;
    WHEN("We use the /= operator to divide the vector by a scalar")
    {
      v /= s;
      THEN("The resulting vector should be the original vector divided by the scalar")
      {
        // Source: (7.0, -18.0, 66.0) / 2 typed into Wolfram Alpha
        REQUIRE(3.5f == Approx(v.m_x));
        REQUIRE(-9.0f == Approx(v.m_y));
        REQUIRE(33.0f == Approx(v.m_z));
      }
    }
  }
}

SCENARIO("Vector '+' operator", "[Vector3][A04]")
{
  GIVEN("A vector initialized to (3.54, 77.9, 33.23) and a vector initialized to (66.4, 99.0, 12.76)")
  {
    Vector3 v1 (3.54f, 77.9f, 33.23f);
    Vector3 v2 (66.4f, 99.0f, 12.76f);
    WHEN("We use operator+ to add two vectors and set the result to a new vector.")
    {
      Vector3 result = v1 + v2;
      THEN("The resulting vector should be the result of the addition of the two vectors.")
      {
        // Source: (3.54, 77.9, 33.23) + (66.4, 99.0, 12.76) typed into Wolfram Alpha
        REQUIRE(69.94f == Approx(result.m_x));
        REQUIRE(176.9f == Approx(result.m_y));
        REQUIRE(45.99f == Approx(result.m_z));
      }
    }
  }
}

SCENARIO("Vector3 '-' operator (overload 1, subtraction)", "[Vector3][A04]")
{
  GIVEN("A vector initialized to (8.7, 6.543, 65.0) and a vector initialized to (4.56, 7.65, 5.0)")
  {
    Vector3 v1 (8.7f, 6.543f, 65.0f);
    Vector3 v2 (4.56f, 7.65f, 5.0f);
    WHEN("We use the - operator to subtract one vector from another and set the result to another vector.")
    {
      Vector3 result = v1 - v2;
      THEN("The resulting vector should be the result of the subtraction of the two vectors.")
      {
        // Source: (8.7, 6.543, 65.0) - (4.56, 7.65, 5.0) typed into Wolfram Alpha
        REQUIRE(4.14f == Approx(result.m_x));
        REQUIRE(-1.107f == Approx(result.m_y));
        REQUIRE(60.0f == Approx(result.m_z));
      }
    }
  }
}

SCENARIO("Vector3 '-' operator (overload 2, negation)", "[Vector3][A04]")
{
  GIVEN("A vector initialized to (9.0, -44.85, 99.2)")
  {
    Vector3 v (9.0f, -44.85f, 99.2f);
    WHEN("We set another vector equal to the negation of a vector.")
    {
      Vector3 result = -v;
      THEN("The resulting vector should be the negation of the original vector.")
      {
        REQUIRE(-9.0f == Approx(result.m_x));
        REQUIRE(44.85f == Approx(result.m_y));
        REQUIRE(-99.2f == Approx(result.m_z));
      }
    }
  }
}

SCENARIO("Vector 3 '*' operator", "[Vector3][A04]")
{
  // v * s form 
  GIVEN("A vector initialized to (32.6, 65.8, 23.4) and a scalar s (6.5)")
  {
    Vector3 v (32.6f, 65.8f, 23.4f);
    float s = 6.5f;
    WHEN("We multiply the vector by the scalar")
    {
      Vector3 result = v * s;
      THEN("The resulting matrix shoule be the product of a vector and a scalar")
      {
        // Source: {211.9, 427.7, 152.1}
        REQUIRE(211.9f == Approx(result.m_x));
        REQUIRE(427.7f == Approx(result.m_y));
        REQUIRE(152.1f == Approx(result.m_z));
      }
    }
  }
  // s * v form
  GIVEN("A vector initialized to (32.6, 65.8, 23.4) and a scalar s (6.5)")
  {
    Vector3 v (32.6f, 65.8f, 23.4f);
    float s = 6.5f;
    WHEN("We multiply the scalar by the vector")
    {
      Vector3 result = s * v;
      THEN("The resulting matrix shoule be the product of a vector and a scalar")
      {
        // Source: {211.9, 427.7, 152.1}
        REQUIRE(211.9f == Approx(result.m_x));
        REQUIRE(427.7f == Approx(result.m_y));
        REQUIRE(152.1f == Approx(result.m_z));
      }
    }
  }
}

SCENARIO("Vector3 '/' operator", "[Vector3][A04]")
{
  GIVEN("A vector initialized to (8.7, 3.2, 77.93) and a scalar s (4.32)")
  {
    Vector3 v (8.7f, 3.2f, 77.93f);
    float s = 4.32f;
    WHEN("We use the '/' operator to divide the vector by the scalar")
    {
      Vector3 result = v / s;
      THEN("The resulting vector should be the quotient of the vector divided by the scalar")
      {
        // Source: (8.7, 3.2, 77.93) / 4.32 typed into Wolfram Alpha
        REQUIRE(2.01389f == Approx(result.m_x));
        REQUIRE(0.740741f == Approx(result.m_y));
        REQUIRE(18.0394f == Approx(result.m_z));
      }
    }
  }
}




////////////////////////////////////////////


SCENARIO ("Vector3 stream insertion.", "[Vector3][A04]") {
  GIVEN ("A vector initialized with (4.3, 102345, and -1.2).") {
    Vector3 v(4.3f, 102345.0f, -1.2f);
    WHEN ("I insert it into an output stream.") {
      std::stringstream out;
      std::ostream& r = out << v;
      THEN ("It should have included each component with a precision of 2 and field width of 10.") {
	REQUIRE ("      4.30 102345.00     -1.20" == out.str ());
      }
      THEN ("The original stream should have been returned.") {
	REQUIRE (&out == &r);
      }
    }
  }
}

SCENARIO ("Vector3 equality.", "[Vector3][A04]") {
  GIVEN ("A vector initialized with (1.2, 3.4, and 0.1).") {
    Vector3 v1(1.2f, 3.4f, 0.1f);
    WHEN ("I compare with a vector initialized with (1.2, 3.4, and 0.1000000001).") {
      Vector3 v2(1.2f, 3.4f, 0.1000000001f);
      bool equal = v1 == v2;
      THEN ("They should be equal.") {
	REQUIRE (true == equal);
      }
    }
    WHEN ("I compare with a vector initialized with (1.2, 3.4, and 0.101).") {
      Vector3 v3(1.2f, 3.4f, 0.101f);
      bool equal = v1 == v3;
      THEN ("They should not be equal.") {
	REQUIRE (false == equal);
      }
    }
  }
  
}

/*

SKELETON OF TEST CODE TO GET STARTED ON A NEW ONE
=================================================

SCENARIO("", "[Vector3][A04]")
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