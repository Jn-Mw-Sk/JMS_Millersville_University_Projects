/*
  Filename:   driver.cpp
  Author:     John Shenk 
  Course:     CSCI 362: Data Structures
  Date:       February 14, 2021
  Assignment: Elementary Sorts - Assignment 3
  
  Description: This program requests from the user a number of elements to popualte a vector,
    a type of sort to perform on the elements in the vector, and a sequence type ('a' for ascending, 'd' for descending, and 'r' for random).
    If the sequence type 'r' was chosen, the program asks for a seed for the random number generator.
    The program the performs the selected sort on the vector and displays the # of compares, # of swaps, and a yes or a no,
    depending on if the sorted vector matches a vector sorted with std::sort.
*/

/**********************************************************/
// System includes

#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

/**********************************************************/
// Local includes

#include "sort.hpp"

/**********************************************************/
// Using declarations
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::srand;
using std::rand;
using std::vector;
using std::sort;

/**********************************************************/
// Function prototypes/global vars/typedefs

std::vector<int>
populate (int count, char type);

/**********************************************************/

int
main (int argc, char* argv[])
{
  cout << "N         ==> ";
  int num;
  cin >> num;

  cout << "Algorithm ==> ";
  string algType;
  cin >> algType;

  cout << "Type      ==> ";
  char seqType;
  cin >> seqType;

  vector<int> A = populate(num, seqType);
  vector<int> ACopy = A;

  Statistics s;

  if (algType  == "bubble")
  {
    
    bubbleSort (A, s);
   
  }
  else if (algType == "insertion")
  {
    insertionSort (A, s);
  }
  else if (algType == "selection")
  {
    selectionSort (A, s);
  }

  cout << endl << "# Compares: " << s.numCompares << endl;
  cout << "# Swaps   : " << s.numSwaps << endl;

  sort (ACopy.begin(), ACopy.end());

  cout << "Sort ok?    ";
  if(A == ACopy)
  {
      cout << "yes" << endl;;
  }
  else
  {
    cout << "no" << endl;;
  }
  
  return EXIT_SUCCESS;
}

/**********************************************************/
// Function implementations

std::vector<int>
populate(int count, char type)
{
  std::vector<int> result;

  if (count <= 0)
  {
    return result;
  } 
  else 
  {
    if (type == 'a') //Ascending order
    {
      for (int i = 1; i <= count; i++)
      {
        result.push_back(i);
      }
    }
    else if (type == 'd') //Descending order
    {
      for (int i = count; i >= 1; i--)
      {
        result.push_back(i);
      }
    }
    else if (type == 'r') //Random order
    {
      cout << endl << "Seed      ==> ";
      int seed;
      cin >> seed;
      cout << endl;

      srand(seed);

      for(int i = 0; i <= count; i++)
      {
        result.push_back ( rand() );
      }
    }
  }
  return result;
}