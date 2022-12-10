#include "circle.h"
#include <iostream>

const double PI = 3.141592653;

double circle::perimeter() const{

    return 2*PI*m_radius;
}

double circle::area() const{
    return PI*m_radius*m_radius;
}

int main(){

    circle c1;
    c1.set_radius(20);
    std::cout << "c1's perimeter is " << c1.perimeter() <<std::endl;
    circle c2(30);
    std::cout << "c2's area is " << c2.area() <<std::endl;
    circle* ptr1 = &c1;
    std::cout << "c1's perimeter is " << ptr1->perimeter() <<std::endl;
    circle* ptr2 = &c2;
    std::cout << "c2's area is " << ptr2->area() <<std::endl;
}