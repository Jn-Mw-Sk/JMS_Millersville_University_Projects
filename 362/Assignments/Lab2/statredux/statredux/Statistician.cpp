/***************************************************
 Name: John Shenk
 Course: CSCI 362: Data Structures
 Date: September 10, 2021
 Assignment: Statistician Redux
 Description: A class the takes a vector and performs various operations with the vector. 
 
 ***************************************************/

#include "Statistician.h"
#include <iostream>
#include <algorithm>

// Function Implementations
// **************************************************

// Finds the largest value in the passed vector
// Assumes nums is not empty
float
maximum (const std::vector<float>& nums)
{
	return *std::max_element(nums.begin(), nums.end());
}


// Finds the smallest value in the passed vector
// Assumes nums is not empty
float
minimum (const std::vector<float>& nums)
{
	return *std::min_element(nums.begin(), nums.end());
}


// Finds the sum of values from the passed vector
// Should return zero if the vector is empty
float
sumOfValues (const std::vector<float>& nums)
{
	float sum = 0;

	auto iter = nums.begin();

	while(iter != nums.end())
	{
		sum += *iter;
		++iter;
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

	if(count <= 0)
	{
		return result;
	}

	float num; 

	while( count > 0 )
	{ 
		std::cout<<"Enter value ==> ";
		std::cin>>num;
		result.push_back(num);
		count--;
	}

	return result;
}
