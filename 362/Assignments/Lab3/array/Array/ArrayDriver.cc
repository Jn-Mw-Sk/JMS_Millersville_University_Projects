/*
  Filename   : ArrayDriver.cc
  Author     : Gary M. Zoppetti
  Course     : CSCI 362-01
  Assignment : N/A
  Description: Test some, but NOT ALL, methods of the Array class.
*/   

/************************************************************/
// System includes

#include <cstdlib>
#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <cassert>

/************************************************************/
// Local includes

#include "Array.hpp"

/************************************************************/
// Using declarations

using std::cin;
using std::cout;
using std::endl;
using std::ostream_iterator;
using std::string;
using std::ostringstream;

/************************************************************/
// Function prototypes/global vars/typedefs

void
printTestResult (const string& test,
		 const string& expected,
		 const ostringstream& actual);

/************************************************************/

int      
main (int argc, char* argv[]) 
{        
  Array<int> A;

  // For holding the actual result
  ostringstream output;
  // Put the actual result into the output stream
  output << A;
  printTestResult ("no-arg ctor", "[ ]", output);

  // Must clear the output stream each time
  output.str ("");
  output << A.empty ();
  // "1" for true, "0" for false
  printTestResult ("empty", "1", output);
  
  A.push_back (5);
  A.push_back (10);
  A.push_back (15);

  output.str ("");
  output << A;
  printTestResult ("push_back", "[ 5 10 15 ]", output);

  output.str ("");
  output << A.size ();
  printTestResult ("size", "3", output);
  
  A.pop_back ();
  A.pop_back ();

  output.str ("");
  output << A;
  printTestResult ("pop_back", "[ 5 ]", output);

  /************************************************************/
  // Convert the following tests to use printTestResult
  /************************************************************/
  
  for (int i = 0; i < 10; ++i)
    A.insert (A.begin (), i);

  output.str("");
  output << A;
  printTestResult ("Inserted 9 8 ... 0 at beginning\n", "[ 9 8 7 6 5 4 3 2 1 0 5 ]", output);
  
  for (Array<int>::iterator i = A.begin (); i != A.end (); )
    i = A.erase (i);

  output.str("");
  output << A;
  printTestResult ("Erased all elements in A\n", "[ ]", output);

  // Size ctor, with a fill value. 
  Array<int> B (3, 9);
  
  output.str("");
  output << B;
  printTestResult ("Created a vector with 3 nines...\n", "[ 9 9 9 ]", output);

  // Range ctor. 
  Array<int> C (B.begin (), B.begin () + 2);
  
  output.str("");
  output << C;
  printTestResult ("Created a new vector using the the first and third elements of another vector.\n", "[ 9 9 ]", output);

  // Assignment operator. 
  B = A;
  
  output.str("");
  output<<B;
  printTestResult ("Assigned vector B to vector A (which should be empty).\n", "[ ]", output);

  for (int i = 0; i < 5; ++i)
    B.insert (B.begin (), i);
  
  output.str("");
  output<<B;
  printTestResult ("Inserting 0, 1, 2, 3, 4 at beginning of B\n", "[ 4 3 2 1 0 ]", output);

  /************************************************************/
  // START WRITING YOUR TESTS HERE
  /************************************************************/

  // Test range ctor (a different case than I test above)

  // Test copy ctor

  Array<int> D (B);

  output.str("");
  output << D; 
  printTestResult ("Create a new array which is a copy of array B.\n", "[ 4 3 2 1 0 ]", output);


  // Test capacity
  output.str("");
  output << D.capacity();
  printTestResult ("Return the capacity of array D.\n", "6", output);

  // ...
  
  return EXIT_SUCCESS;
}

/************************************************************/

void
printTestResult (const string& test,
		 const string& expected,
		 const ostringstream& actual)
{
  cout << "Test: " << test << endl;
  cout << "==========================" << endl;
  cout << "Expected: " << expected << endl;
  cout << "Actual  : " << actual.str () << endl;
  cout << "==========================" << endl << endl;

  // Ensure the two results are the same
  assert (expected == actual.str ());
}

/************************************************************/
