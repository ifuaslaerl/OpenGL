#include <cmath>
#include <GL/glew.h>
#include "../includes/types.h"

Particle::Particle(Point center, ld radius):
    center(center), radius(radius), resolution(100) {}

Particle::Particle(Point center, ld radius, int resolution):
    center(center), radius(radius), resolution(resolution) {}

void Particle::draw(){
    ld ang=0;
    const ld step = 2*PI/resolution;
    for(int i=0; i<resolution; i++){
        Point p(center.x + radius*cos(ang),
                center.y + radius*sin(ang));
        Point q(center.x + radius*cos(ang+step),
                center.y + radius*sin(ang+step));
        ang += step;

        glBegin(GL_TRIANGLES);
            center.draw();
            p.draw();
            q.draw();
        glEnd();
    }
}

void Particle::set_speed(Vector v){velocity=v;}

void Particle::update_pos(){center = center + velocity;}

Particle Particle::operator+(const Vector &v) const {
    return Particle(center+v, radius);
}
