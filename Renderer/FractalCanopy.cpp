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

void GL_LINES_CanopyFractal::drawRecursive(CanopyNode *node, glm::mat4 scale, glm::mat4 translation, glm::mat4 rotation) {
    glm::mat4 nextTranslation = glm::translate(0.0f, (float)node->length, 0.0f);
    glm::mat4 nextScale       = glm::scale(0.5f, 0.5f, 0.5f);
    glm::vec3 eulerAngles(0, 0, glm::radians((float)node->angle_degrees));
    glm::quat Quaternion(eulerAngles);
    glm::mat4 nextRotation    = glm::toMat4(Quaternion);

    translation = nextTranslation + translation;
    scale = nextScale * scale;
    rotation = nextRotation * rotation;

    glm::mat4 currentModel = translation * rotation * scale;
    glm::mat4 MVP = Projection * View * currentModel;
    glUseProgram(programID);
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
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

void GL_LINES_CanopyFractal::drawRecursive(CanopyNode *node, glm::mat4 pos, glm::mat4 scale) {
    glm::vec3 eulerAngles(0, 0, glm::radians((float)node->angle_degrees));
    glm::quat Quaternion(eulerAngles);
    glm::mat4 rotation = glm::toMat4(Quaternion);

    pos = pos * rotation;
    glm::mat4 model = pos * scale;
    glm::mat4 MVP = Projection * View * model;
    GLfloat mytime = time(NULL);
    
    glUseProgram(programID);
    glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniform1f(timeID, mytime);
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
    glm::mat4 translation = glm::translate(0.0f, (float)node->length, 0.0f);
    glm::mat4 s = glm::scale(0.5f, 0.5f, 0.5f);
    scale = scale * s;
    pos = pos * translation;
    if(node->rnode) {
        drawRecursive(node->rnode, pos, scale);
    }
    if(node->lnode) {
        drawRecursive(node->lnode, pos, scale);
    }
}
