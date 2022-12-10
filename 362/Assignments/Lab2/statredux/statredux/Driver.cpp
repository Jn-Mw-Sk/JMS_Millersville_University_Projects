/***************************************************
 Name: John Shenk
 Course: CSCI 362: Data Structures
 Date: September 10, 2021
 Assignment: Statistician Redux
 Description: A program the takes multiple numbers from the user and reports the  maximum, minimum, sum, 
    and average of those numbers. 
 
 ***************************************************/

// Include Directives
// **************************************************
#include <iostream>
#include <vector>

#include "Statistician.h"


// Using Statements
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
main(int argc, char* argv[])
{

    int num;

    cout<<"Enter number of values ==> "; //Ask for number of elements
    cin>>num;

    const vector<float> vec = populate(num); //Populate our vector

    cout<<endl<<"The statistics of all "<<num<< " values are:"<<endl;
    cout<<"  Sum: "<<sumOfValues(vec)<<endl;;
    cout<<"  Avg: "<<average(vec)<<endl;
    cout<<"  Min: "<<minimum(vec)<<endl;
    cout<<"  Max: "<<maximum(vec)<<endl;
    
}


// Function Implementations
// **************************************************

// TODO: any functions you call within main that are a part of this
// file must be implemented AFTER main
