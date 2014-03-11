#ifndef _GLFWCONTEXT_HPP
#define _GLFWCONTEXT_HPP

#include <string>
#include <vector>
#include <utility>
#include <map>
#include <memory>

#include <GLFW/glfw3.h>

using std::string;
using std::vector;
using std::pair;
using std::make_pair;
using std::map;

class glfwContext {
  public:
    glfwContext();
    ~glfwContext();

    //GLFWwindow* createWindow();
    GLFWwindow *createWindow(pair<int, int> dim, string title);
    void swapBuffers();

    static void makeContextCurrent(glfwContext &context);

    bool getKey(int key, int action);

    // Getters
    GLFWwindow *windowHandle();
    int height();
    int width();
    string title();
    pair<double, double> mousePos();
    pair<int, int> windowDims();

    // Setters
    void setHint(int target, int hint);
    void setHint(const map<int, int> &hintMap);
    void setHeight(int height);
    void setWidth(int width);
    void setTitle(string title);
    void setMousePos(pair<double, double> pos);
    void setWindowDims(int width, int height);

  private:
    GLFWwindow *_windowHandle;

    // Window Settings
    map<int, int> _windowHints;
    string _title;
    GLFWmonitor *_monitor;
    glfwContext *_sharedContext;

    // Helper Functions
    void assignAllHints();
};

#endif //_CONTEXT_HPP
