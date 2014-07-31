#include "FractalCanopy.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <ctime>

CanopyFractal::CanopyFractal() {
    double startx = 0;
    double starty = 0;
    CanopyNode *startNode = NULL;
};

CanopyFractal::CanopyFractal(int iterations, double x, double y, double start_length, double angle_degrees) {
    setStart(x, y);
    startnode = new CanopyNode();
    generateFractal(startnode, iterations, start_length, angle_degrees);
};

void CanopyFractal::setStart(double x, double y) {
    startx = x;
    starty = y;
};

void CanopyFractal::generateFractal(CanopyNode *node, int iterations, double length, double angle_degrees) {
    node->angle_degrees = angle_degrees;
    node->length = length;
    if(iterations <= 0) {
        return;
    }
    node->rnode = new CanopyNode();
    node->lnode = new CanopyNode();
    generateFractal(node->rnode, iterations - 1, length/2, (int)angle_degrees % 360 + angle_degrees - (int)angle_degrees);
    generateFractal(node->lnode, iterations - 1, length/2, (-(int)angle_degrees % 360 - angle_degrees + (int)angle_degrees));
    startnode->angle_degrees = 0;
};

void GL_LINES_CanopyFractal::drawRecursive(CanopyNode *node, glm::dmat4 scale, glm::dmat4 translation, glm::dmat4 rotation) {
    glm::dmat4 nextTranslation = glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, (double)node->length, 0.0));
    glm::dmat4 nextScale       = glm::scale(glm::dmat4(10) ,glm::dvec3(0.5, 0.5, 0.5));
    glm::dvec3 eulerAngles(0.0, 0.0, (double)node->angle_degrees);
    glm::dquat Quaternion(eulerAngles);
    glm::dmat4 nextRotation    = glm::mat4_cast(Quaternion);

    translation = nextTranslation + translation;
    scale = nextScale * scale;
    rotation = nextRotation * rotation;

    glm::dmat4 currentModel = translation * rotation * scale;
    glm::dmat4 MVP = Projection * View * currentModel;
    glUseProgram(programID);
    glUniformMatrix4dv(matrixID, 1, GL_FALSE, &MVP[0][0]);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          (void*)0);
    glDrawArrays(GL_LINES, 0, 2);
    glDisableVertexAttribArray(0);
    if(node->rnode) {
        drawRecursive(node->rnode, scale, translation, rotation);
    }
    if(node->lnode) {
        drawRecursive(node->lnode, scale, translation, rotation);
    }
}

void GL_LINES_CanopyFractal::drawRecursive(CanopyNode *node, glm::dmat4 pos, glm::dmat4 scale) {
    glm::dvec3 eulerAngles(0.0, 0.0, (double)node->angle_degrees);
    glm::dquat Quaternion(eulerAngles);
    glm::dmat4 rotation = glm::mat4_cast(Quaternion);

    pos = pos * rotation;
    glm::dmat4 model = pos * scale;
    glm::dmat4 MVP = Projection * View * model;
    GLfloat mytime = time(NULL);
    
    glUseProgram(programID);
    glUniformMatrix4dv(matrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniform1d(timeID, mytime);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          (void*)0);
    glDrawArrays(GL_LINES, 0, 2);
    glDisableVertexAttribArray(0);
    glm::dmat4 translation = glm::translate(glm::dmat4(1.0), glm::dvec3(0.0, (double)node->length, 0.0));
    glm::dmat4 s = glm::scale(glm::dmat4(1.0), glm::dvec3(0.5, 0.5, 0.5));
    scale = scale * s;
    pos = pos * translation;
    if(node->rnode) {
        drawRecursive(node->rnode, pos, scale);
    }
    if(node->lnode) {
        drawRecursive(node->lnode, pos, scale);
    }
}
