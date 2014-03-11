#ifndef _FRACTALCANOPY_HPP
#define _FRACTALCANOPY_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

class CanopyNode {
  public:
    CanopyNode(double l, double ang) { length = l; angle_degrees = ang; rnode = NULL; lnode = NULL; };
    CanopyNode() { length = 0; angle_degrees = 0; rnode = NULL; lnode = NULL; };
    ~CanopyNode() {};

    double angle_degrees;
    double length;

    CanopyNode *rnode;
    CanopyNode *lnode;
};

class CanopyFractal {
  public:
    CanopyFractal();
    CanopyFractal(int iterations, double x, double y, double start_length, double angle_degrees);
    ~CanopyFractal(){ };

    void setStart(double x, double y);
    void generateFractal(CanopyNode *node, int iterations, double length, double angle_degrees);

    double startx;
    double starty;
    CanopyNode *startnode;
};

class GL_LINES_CanopyFractal : public CanopyFractal {
  public:
    GLuint programID;
    GLuint matrixID;
    GLuint timeID;
    GLuint vertexBuffer; 

    glm::mat4 Model, View, Projection;

    void drawRecursive(CanopyNode *node, glm::mat4 scale, glm::mat4 translation, glm::mat4 rotation);
    void drawRecursive(CanopyNode *node, glm::mat4 pos, glm::mat4 scale);
};

#endif // _FRACTALCANOPY_HPP
