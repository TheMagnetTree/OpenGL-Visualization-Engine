#ifndef _GLFWCONTEXT_HPP
#define _GLFWCONTEXT_HPP

#include <string>
#include <vector>
#include <utility>
#include <map>

#include <GLFW/glfw3.h>

using std::string;
using std::vector;
using std::pair;
using std::make_pair;
using std::map;

class glfwContext {
  private:
    GLFWwindow* _windowHandle;

    // Window Settings
    map<int, int> _windowHints;
    int _width;
    int _height;
    string _title;
    GLFWmonitor* _monitor;
    glfwContext* _sharedContext;

    // Helper Functions
    void assignAllHints();

  public:
    glfwContext();
    ~glfwContext();

    GLFWwindow* createWindow();
    void swapBuffers();

    // Getters
    GLFWwindow* windowHandle();
    int height();
    int width();

    // Setters
    void setHint(int target, int hint);
    void setHint(const map<int, int> &hintMap);
    void setHeight(int height);
    void setWidth(int width);
    void setTitle(string title);

};

#endif //_CONTEXT_HPP
