#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

using namespace glm;

int main() {
    if(!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* glfwHandle;
    if(!(glfwHandle = glfwCreateWindow(1024, 768, "GLFW3", 0, 0)))
    {
        fprintf(stderr, "Failed to create GLFW window\n");
        return -1;
    }

    glfwMakeContextCurrent(glfwHandle);
    glfwSetInputMode(glfwHandle, GLFW_STICKY_KEYS, GL_TRUE);

    do{
        glfwPollEvents();
        glfwSwapBuffers(glfwHandle);
    } while(glfwGetKey(glfwHandle ,GLFW_KEY_ESCAPE) != GLFW_PRESS);

    glfwTerminate();
}
