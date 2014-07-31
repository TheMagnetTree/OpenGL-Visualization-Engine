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

    glm::dmat4 Model, View, Projection;

    void drawRecursive(CanopyNode *node, glm::dmat4 scale, glm::dmat4 translation, glm::dmat4 drotation);
    void drawRecursive(CanopyNode *node, glm::dmat4 pos, glm::dmat4 scale);
};

#endif // _FRACTALCANOPY_HPP
