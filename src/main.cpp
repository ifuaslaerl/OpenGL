#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <math.h>
#include <iostream>

#define WIDTH 1000
#define HEIGHT 500
#define TITLE "Simulador"

typedef Vector(*FieldFunction)(Point);
typedef long double ld;

const ld PI = acos(-1);

class Vector{

    public:

    ld x, y;

    Vector(ld x, ld y) : x(x), y(y) {}

    void draw(){ // TODO
    }

    Vector operator+(const Vector &v) const {
        return Vector(x+v.x, y+v.y);
    }

};

class Point: public Vector{

    public:

    Vector p;

    Point(ld x, ld y): p(x, y) { // TODO RESOLVER

    }

    void draw(){
        glVertex2f(x/WIDTH, y/HEIGHT);
    }

    Point operator+(const Vector &v) const {
        return Point(x+v.x, y+v.y);
    }

};

class Particle{

    public:

    Point center;
    ld radius;
    int resolution;

    Particle(Point center, ld radius, int resolution=100):
        center(center), radius(radius), resolution(resolution) {}

    void draw(){
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

    Particle operator+(const Vector &v) const {
        return Particle(center+v, radius);
    }

};

class Field{

    Field() {}

    Vector map(Point p){}

};

int main(){

    if(!glfwInit()){
        std::cerr << "Falha ao Inicializar Biblioteca GLFW3" 
            << std::endl;
        return -1;
    }

    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT,
        TITLE, NULL, NULL);

    if(!window){
        std::cerr << "Falha ao Inicializar Janela de execução"
            << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // Não sei oq faz ainda

    Particle p(Point(0, 0), 50);
    Vector velocity(0, 10), aceleration(0, -0.1);

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);

        p = p+velocity;
        p.draw();
        velocity = velocity + aceleration;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}