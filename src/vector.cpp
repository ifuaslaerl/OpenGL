#include "../includes/types.h"

Vector::Vector() : x(0), y(0) {}
Vector::Vector(ld x, ld y) : x(x), y(y) {}

Vector Vector::operator+(const Vector &v) const {
    return Vector(x+v.x, y+v.y);
}

Vector Vector::operator-(const Vector &v) const{
    return Vector(x-v.x, y-v.y);
}

std::ostream& operator<<(std::ostream& out, const Vector& v){
    return out << "[" << v.x << ", " << v.y << "]";
}


void Vector::draw(){ // TODO
}