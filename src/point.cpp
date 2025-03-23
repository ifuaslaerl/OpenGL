#include <cassert>
#include <GL/glew.h>
#include "../includes/types.h"


Point::Point(): x(0), y(0) {}
Point::Point(Vector v): x(v.x), y(v.y) {}
Point::Point(ld x, ld y): x(x), y(y) {}

Vector Point::operator-(const Point &p) const{
    return Vector(x-p.x, y-p.y);
}

std::ostream& operator<<(std::ostream& out, const Point& p){
    return out << "(" << p.x << ", " << p.y << ")";
}

void Point::draw(){
    glColor3f(colour[0], colour[1], colour[2]);
    glVertex2f(x/WIDTH, y/HEIGHT);
}

void Point::set_colour(RGB c){
    colour[0] = c[0];
    colour[1] = c[1];
    colour[2] = c[2];
}

void Point::update_pos(Vector v){
    x += v.x;
    y += v.y;
}