#include <algorithm>
#include <GL/glew.h>

#include "glfwContext.hpp" 
#include "common/glfwHints.hpp"
#include <GL/gl.h>

int initContext(glfwContext &mainContext) { 

    // load default glfwHints from common/glfwHints
    mainContext.setHint(defaultHints);
    mainContext.setHeight(768);
    mainContext.setWidth(1024);
    mainContext.setTitle("glfw window");
    (void)mainContext.createWindow();
}

int main() {
    glfwContext mainContext;
    initContext(mainContext);
    while(true){
        mainContext.swapBuffers();
    }
}
