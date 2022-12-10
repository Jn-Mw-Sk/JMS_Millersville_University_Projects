/*
 Filename   : Driver.cpp
 Author     : John Shenk
 Course     : CSCI 340 -Data Structures
 Date       : February 4, 2021
 Assignment : Lab 02
 Description: This program accepts a count of numbers from the user, populates a vector with the values entered by the user,
                  then reports the sum, average, min, max of those values.
*/ 

// Include Directives
// **************************************************
#include <iostream>
#include <cstdlib>


#include "Statistician.h"

// Using declarations
// **************************************************
using std::cout;
using std::cin;
using std::endl;
using std::vector;

// Forward Declarations
// **************************************************

// Main
// **************************************************

int
main (int argc, char* argv[])
{
  
  cout << "Enter number of values ==> ";
  int numValues;
  cin >> numValues;

  vector<float> values = populate(numValues);

  cout << endl;
  cout << "The statistics of all " << numValues << " values are:" << endl;
  cout << "  Sum: " << sumOfValues(values) << endl;
  cout << "  Avg: " << average(values) << endl;
  cout << "  Min: " << minimum(values) << endl;
  cout << "  Max: " << maximum(values) << endl;

  
  return EXIT_SUCCESS;
}


// Function Implementations
// **************************************************
