#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#define WIDTH 1000
#define HEIGHT 1000
#define TITLE "Simulador"
#define PI M_PI

typedef long double ld;

class Vector{
    public:
        Vector();
        Vector(ld, ld);
        Vector operator+(const Vector&) const;
        Vector operator-(const Vector&) const;
        Vector operator*(const ld&) const;
        ld operator*(const Vector&) const;
        friend std::ostream& operator<<(std::ostream&, const Vector&);
        void draw();
        ld module();
        ld x, y;
};

typedef float RGB[3];

class Point{
    public:
        Point();
        Point(ld, ld);
        Point(Vector);
        Vector operator-(const Point&) const;
        friend std::ostream& operator<<(std::ostream&, const Point&);
        void draw();
        void set_colour(RGB);
        void update_pos(Vector);
        ld x, y;
        RGB colour;
};

class Particle{
    public:
        Particle(Point, ld);
        Particle(Point, ld, int);
        void draw();
        void set_speed(Vector);
        void set_color(RGB);
        void update_pos();
        void check_colision_with_boundaries();
        void check_colision_with_particle(Particle&);
        Point center;
        Vector velocity=Vector(0, 0);
        ld mass=1, charge=0;
    private:
        ld radius;
        int resolution;
};

typedef Vector(*FieldFunction)(Particle);

class Field{
    public:
        Field(FieldFunction);
        Vector apply(Particle);
    private:
        FieldFunction f;
};