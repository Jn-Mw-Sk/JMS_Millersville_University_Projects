// Filename:    triangle.cpp
// Assignment:  Lab_1_Triangle_Class
// Author:      John M Shenk
// Date:        August 31, 2021
//Description:  A program used to test out the capabilities of triangle class.

#include "triangle.h"
#include <iostream>

int main () {

    triangle t1 (3, 4, 5); //create a triangle of sides 3, 4, 5
    triangle t2;
    std::cout<<"Is t1 a right triangle? "<<t1.is_right()<<std::endl;
    std::cout<<"Is t2 a right triangle? "<<t2.is_right()<<std::endl;
    std::cout<<"The perimeter of t1 is "<<t1.perimeter()<<std::endl;
    std::cout<<"The perimeter of t2 is "<<t2.perimeter()<<std::endl<<std::endl;

    //Create pointers for the triangle objects. 
    triangle* p1 = &t1;
    triangle* p2 = &t2;
    std::cout<<"Is t1 a right triangle? "<<p1->is_right()<<std::endl;
    std::cout<<"Is t2 a right triangle? "<<p2->is_right()<<std::endl;
    std::cout<<"The perimeter of t1 is "<<p1->perimeter()<<std::endl;
    std::cout<<"The perimeter of t2 is "<<p2->perimeter()<<std::endl;
   


}