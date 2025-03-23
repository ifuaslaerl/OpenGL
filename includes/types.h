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
        friend std::ostream& operator<<(std::ostream&, const Vector&);
        void draw();
        ld x, y;
};

class Point{
    public:
        Point();
        Point(ld, ld);
        Point(Vector);
        Point operator+(const Vector&) const;
        friend std::ostream& operator<<(std::ostream&, const Point&);
        void draw();
        ld x, y;
};

class Particle{
    public:
        Particle(Point, ld);
        Particle(Point, ld, int);
        Particle operator+(const Vector&) const;
        void draw();
        void set_speed(Vector);
        void update_pos();
        Point center;
        Vector velocity=Vector(0, 0);
        ld mass=0, charge=0;
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