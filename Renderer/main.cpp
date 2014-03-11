#include <algorithm>
#include <cstdio>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <GLFW/glfw3.h>

#include <unistd.h>

#include "glfwContext.hpp" 
#include "common/glfwHints.hpp"
#include "LoadShaders.hpp"
#include "FractalCanopy.hpp"

int initContext(glfwContext &mainContext) { 

    // load default glfwHints from common/glfwHints
    mainContext.setHint(defaultHints);
    (void)mainContext.createWindow(std::pair<int, int>(768, 1024), "glfw window");
}

static const GLfloat g_vertex_buffer_data[] = {
    0.0f, 0.0f, 0.0f,
    0.0f, 0.5f, 0.0f
};


int main() {
    // init glfw
    glfwContext mainContext;
    initContext(mainContext);
    glfwContext::makeContextCurrent(mainContext);

    // init glew
    glewExperimental=GL_TRUE;
    GLenum err = glewInit();
    if(err != GLEW_OK) {
        fprintf(stderr, "GLEW NOT OKAY:%s\n", glewGetErrorString(err));
        return -1;
    }

    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 View = glm::lookAt(
            glm::vec3(0, 0, -5),
            glm::vec3(0, 0.5, 0),
            glm::vec3(0, 1, 0));

    glm::vec3 position = glm::vec3(0, 0, 5);
    float horizontalAngle = 3.14f;
    float verticalAngle = 0.0f;
    float initialFoV = 20.0f;

    glm::quat Quaternion;
    glm::vec3 EulerAngles(0, 0, 0);
    Quaternion = glm::quat(EulerAngles);
    glm::mat4 Model = glm::mat4(1.0f); 
    glm::mat4 ScaleMatrix = glm::scale(1.0f, 1.0f, 1.0f);
    glm::mat4 RotationMatrix = glm::toMat4(Quaternion);
    glm::mat4 TranslationMatrix = glm::translate(0.0f, 0.0f, 0.0f);
    Model = Model * TranslationMatrix * RotationMatrix;
    glm::mat4 MVP = Projection * View * Model;


    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, 
                 sizeof(g_vertex_buffer_data), 
                 g_vertex_buffer_data, 
                 GL_DYNAMIC_DRAW);

    GLuint programID = LoadShaders("VertexShader1.vertexshader", "FragmentShader1.fragmentshader");
    GLuint matrixID = glGetUniformLocation(programID, "MVP");
    GLuint timeID = glGetUniformLocation(programID, "time");
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    GL_LINES_CanopyFractal frac;
    frac.startnode = new CanopyNode();
    frac.programID = programID;
    frac.matrixID = matrixID;
    frac.timeID = timeID;
    frac.vertexBuffer = vertexbuffer;
    float angle = 90;
    frac.generateFractal(frac.startnode, 6, 0.5f, angle);

    while(true){
        if(mainContext.getKey(GLFW_KEY_UP, GLFW_PRESS)){
            angle += 1;        
            frac.generateFractal(frac.startnode, 6, 0.5f, angle);
        }
        if(mainContext.getKey(GLFW_KEY_DOWN, GLFW_PRESS)){
            angle -= 1;        
            frac.generateFractal(frac.startnode, 6, 0.5f, angle);
        }
        //float FoV = initialFoV - 5 * glfwGetMouseWheel();
        Projection = glm::perspective(initialFoV, 4.0f/3.0f, 0.1f, 100.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);
        /*
        glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
        // DRAW A GORRAM TRIANGLE
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(0,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (void*)0);
        glDrawArrays(GL_LINES, 0, 2);
        glDisableVertexAttribArray(0);
        */
        //frac.drawRecursive(frac.startnode, ScaleMatrix, TranslationMatrix, RotationMatrix);
        frac.View = View;
        frac.Projection = Projection;
        frac.drawRecursive(frac.startnode, Model, ScaleMatrix);
        mainContext.swapBuffers();
        glfwPollEvents();
        //sleep(100);
    }
}
