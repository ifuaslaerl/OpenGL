#include <GL/glew.h>
#include "../includes/types.h"

Point::Point(Vector v): x(v.x), y(v.y) {}
Point::Point(ld x, ld y): x(x), y(y) {}

Point Point::operator+(const Vector &v) const {
    return Point(x+v.x, y+v.y);
}

std::ostream& operator<<(std::ostream& out, const Point& p){
    return out << "(" << p.x << ", " << p.y << ")";
}

void Point::draw(){
    glVertex2f(x/WIDTH, y/HEIGHT);
}