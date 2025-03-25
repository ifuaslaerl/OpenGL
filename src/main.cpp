#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <math.h>
#include <iostream>
#include <iomanip>

#include "../includes/types.h"

Vector gravity(Particle p){
    Vector v = p.velocity + Vector(0,-1);
    return v;
}

void escape_exit(GLFWwindow* window, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}

void check_colision(std::vector<Particle> &objects){ // TODO Optmize this
    // Check with Rectangular boundaries  
    
    const int n = objects.size();
    
    for(Particle& p : objects){
        p.check_colision_with_boundaries();
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i==j) continue;
            Particle &p1 = objects[i];
            Particle &p2 = objects[j];
            p1.check_colision_with_particle(p2);
        }
    }

}

void pipeline(std::vector<Particle> &objects, std::vector<Field> &forces){ // TODO is this optmizable?

    check_colision(objects);
    for(Particle &p : objects) for(Field &f : forces) p.set_speed(f.apply(p));
    for(Particle &p : objects) p.update_pos();
    for(Particle &p : objects) p.draw();

    // TODO save data in a csv to analyse in python 
    // (in order to do this, please create a directory "data", fix .gitignore and makefile to adapt this)

    #ifdef DEBUG
        std::cout << std::fixed << std::setprecision(0);
        for(Particle &p: objects){
            std::cout << "Particle " << p.id << " - " << p.name << ":\t";
        }
        std::cout << std::endl;
        for(Particle &p: objects){
            std::cout << "\tPosition: " << p.center << "\t";
        }
        std::cout << std::endl;
        for(Particle &p: objects){
            std::cout << "\tVelocity: " << p.velocity << "\t";
        }
        std::cout << std::endl;
    #endif
}

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

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, escape_exit);

    Field g(gravity);
    Particle p1(Point(100, 0), 50), p2(Point(-100, 0), 50);
    RGB red = {1.0f, 0.0f, 0.0f}, blue = {0.0f, 0.0f, 1.0f};

    p1.set_speed(Vector(10, 30));
    p1.set_color(red);
    p1.set_name("Vermelho");

    p2.set_speed(Vector(-30, 10));
    p2.set_color(blue);
    p2.set_name("Azul");

    std::vector<Field> forces = {g};
    std::vector<Particle> objects = {p1, p2};

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);

        pipeline(objects, forces);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}