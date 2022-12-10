#ifndef circle_H
#define circle_H

class circle{
private:
    double m_radius;

public:
    circle(){

    }

    circle(double r){
        m_radius = r;
    }

    //there are two types of member functions
    //1. accessor functions only read class data. The key word "const" shows this is an accessor
    double get_radius() const{
        return m_radius;
    }

    //2. update funcitons which may alter class data
    void set_radius(const double& r){
        m_radius = r;
    }

    //you can define other member functions here
    double perimeter() const;

    double area() const;

    

};

#endif