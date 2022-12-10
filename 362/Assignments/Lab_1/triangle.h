// Filename:    triangle.h
// Assignment:  Lab_1_Triangle_Class
// Author:      John M Shenk
// Date:        August 31, 2021
//Description:  The header file containing information 
//                  of the triangle class.

//
#ifndef triangle_H
#define triangle_H

//The triangle class
class triangle{

private: 

    //Data Members
    double m_side1;
    double m_side2;
    double m_side3;

public:

    //******CONSTRUCTORS******

    //default constructor
    triangle () {
        m_side1 = 1;
        m_side2 = 1;
        m_side3 = 1;
    }

    //constructor (one number)
    triangle ( const double& x ){
        m_side1 = x;
        m_side2 = x;
        m_side3 = x;
    }

    //constructor (three numbers)
    triangle ( const double& x, const double& y, const double&z ){
        m_side1 = x;
        m_side2 = y;
        m_side3 = z;
    }

    //******ACCESSORS******

    //Return length of side 1.
    double getSide1 () const{
        return m_side1;
    }

    //Return length of side 2.
    double getSide2 () const{
        return m_side2;
    }

    //Return length of side 3.
    double getSide3 () const{
        return m_side3;
    }

    //******UPDATE FUNCTIONS******

    //Sets m_side1 to a new value.
    void set_Side1 ( const double& x ) {
        m_side1 = x;
    }

    //Sets m_side2 to a new value.
    void set_side2 ( const double& x ) {
        m_side2 = x;
    }

    //Sets m_side3 to a new value.
    void set_side3 ( const double& x ) {
        m_side3 = x;
    }


    //******OTHER MEMBER FUNCTIONS******

    //Returns the paremeter of the triangle.
    double perimeter () const { 
        return m_side1 + m_side2 + m_side3;
    }

    //Return largest side.
    double largest_side () const {

        if ( m_side1 >= m_side2 && m_side1 >= m_side3) { 
            return m_side1;
        } 
        else if ( m_side2 >= m_side1 && m_side2 >= m_side3 ) {
            return m_side2;
        } 
        else {
            return m_side3;
        }

    }

    //Returns a boolean value setermining whether the triangle is a right triangle or not.
    bool is_right () const {

        if ( m_side3 == largest_side() ) {
            return ( m_side1 * m_side1 ) + ( m_side2 * m_side2 ) == ( m_side3 * m_side3 );
        } 
        else if ( m_side2 == largest_side() ) {
            return ( m_side1 * m_side1 ) + ( m_side3 * m_side3 ) == ( m_side2 * m_side2 );
        }
        else {
            return ( m_side2 * m_side2 ) + ( m_side3 * m_side3 ) == ( m_side1 * m_side1 );
        }
        
    }

};


#endif