/*
 Filename   : Statistician.cpp
 Author     : John Shenk
 Course     : CSCI 340 - Data Structures
 Date       : February 4, 2021
 Assignment : Lab 02
 Description: This program accepts an input of integers from user, stores those values in a vector, and returns results for the maximum,
                  minimum, sum, and average of the values.
*/ 

// ***************************************************

// TODO: other includes go here
#include <iostream>

#include "Statistician.h"

// Using declarations
// ***************************************************

using std::cout;
using std::cin;
using std::vector;
using std::endl;

// Function Implementations
// **************************************************

// Finds the largest value in the passed vector
// Assumes nums is not empty
float
maximum (const std::vector<float>& nums)
{

  float max = nums.at(0); 

  for (float number: nums){
    if (number > max){
      max = number;
    }
  }

  return max;

}


// Finds the largest value in the passed vector
// Assumes nums is not empty
float
minimum (const std::vector<float>& nums)
{ 

  float min = nums.at(0);

  for (float number : nums){
    if (number < min){
      min = number;
    }
  }

  return min;
}


// Finds the sum of values from the passed vector
// Should return zero if the vector is empty
float
sumOfValues (const std::vector<float>& nums)
{

  float sum = 0;

  for(float number : nums){

    sum += number;

  }

  return sum;
}


// Finds the average of all values from the passed vector
// assumes nums is not empty
float
average (const std::vector<float>& nums)
{

  return sumOfValues(nums) / nums.size();

}

// Creates and returns a new vector. Reads in count number
// of values from the user by prompting for each one
// should return an empty vector if count <= 0
std::vector<float>
populate (int count)
{
  std::vector<float> result;

  float value;

  if (count <= 0){

    return result;

  } else {

    while (count > 0){

        cout << "Enter value ==> ";
        cin >> value;
        result.push_back (value);
        count--;

    }

  }
  
  return result;
}
