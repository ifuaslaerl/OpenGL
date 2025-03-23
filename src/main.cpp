#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <math.h>
#include <iostream>

#include "../includes/types.h"

Vector gravity(Particle p){
    Vector v = p.velocity + Vector(0,-1);
    return v;
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

    glfwMakeContextCurrent(window); // Não sei oq faz ainda

    Field field(gravity);
    Particle p(Point(0, 0), 50);
    p.set_speed(Vector(0, 100));

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);

        p.draw();
        p.update_pos();
        p.set_speed(field.apply(p));

        std::cout << "speed: " << p.velocity << std::endl;
        std::cout << "pos: " << p.center << std::endl;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}