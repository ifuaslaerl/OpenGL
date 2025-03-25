#include <cassert>
#include <algorithm>
#include <cmath>
#include <GL/glew.h>
#include "../includes/types.h"

Particle::Particle(Point center_, ld radius_):
    center(center_), radius(radius_){
        static int id_count=0;
        RGB white = {1, 1, 1};
        center.set_colour(white);
        resolution = 20;
        id = ++id_count;
        set_name("Unnamed");
}

void Particle::draw(){
    ld ang=0;
    const ld step = 2*PI/resolution;

    glBegin(GL_TRIANGLES);
    for(int i=0; i<resolution; i++){

        Point p(center.x + radius*cos(ang),
                center.y + radius*sin(ang));
        p.set_colour(center.colour);

        Point q(center.x + radius*cos(ang+step),
                center.y + radius*sin(ang+step));
        q.set_colour(center.colour);

        ang += step;

        center.draw();
        p.draw();
        q.draw();
    }
    glEnd();

}

void Particle::set_speed(Vector v){velocity=v;}

void Particle::set_color(RGB c){
    center.set_colour(c);
}

void Particle::set_name(std::string s){
    int n = s.size();
    n = std::min(n, 10);
    std::string to_complete = "";
    for(int i=0; i<10-n; i++) to_complete += "_";
    name = s.substr(0,n) + to_complete;
}

void Particle::update_pos(){center.update_pos(velocity);}

void Particle::check_colision_with_boundaries(){
    if(center.x - radius < -WIDTH || center.x + radius > WIDTH){
        velocity.x *=-1;
        center.x = std::clamp(center.x, radius-WIDTH, WIDTH-radius);
    }
    if(center.y - radius < -HEIGHT || center.y + radius > HEIGHT){
        velocity.y *=-1;
        center.y = std::clamp(center.y, radius-HEIGHT, HEIGHT-radius);
    }
}

void Particle::check_colision_with_particle(Particle &p){
    Vector diference = (center-p.center);
    if(diference.module() > radius + p.radius) return; // nao existe colisao

    Vector direction = diference*(1/diference.module()); // TODO verificar se divide por zero
    Vector rel_speed = (velocity-p.velocity);

    ld speed = rel_speed * direction;

    if(speed>0) return; // Não sei pq preciso verificar isso

    ld impulse = 2*speed/(mass + p.mass);

    // não entendi esse final
    velocity = velocity - direction * (impulse * p.mass);
    p.velocity = p.velocity + direction * (impulse * mass);
}

