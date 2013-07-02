#include <iterator>
#include "glfwContext.hpp"

// constructors
glfwContext::glfwContext() {
    if(!glfwInit()) {
        // Throw GLFW error
    }
}

// destructors
glfwContext::~glfwContext() {
    glfwTerminate();
}

// Stuff
GLFWwindow* glfwContext::createWindow() {
    assignAllHints();

    _windowHandle = glfwCreateWindow(_width, _height, _title.c_str(), NULL , NULL);
    return windowHandle();
}

void glfwContext::swapBuffers() {
    glfwSwapBuffers(_windowHandle);
}

// Getters
GLFWwindow* glfwContext::windowHandle() {
    return _windowHandle;
}

int glfwContext::height() {
    int height;
    glfwGetWindowSize(_windowHandle, NULL, &height);
    return height;
}

int glfwContext::width() {
    int width;
    glfwGetWindowSize(_windowHandle, &width, NULL);
    return width;
}

// Setters
void glfwContext::setHint(int target, int hint) {
    map<int, int>::iterator it;
    it = _windowHints.find(target);
    if(it != _windowHints.end()) {
        _windowHints.erase(it);
    }
    _windowHints.insert(make_pair(target, hint));
}

void glfwContext::setHint(const map<int, int> &hintMap) {
    _windowHints = hintMap;
}

void glfwContext::setHeight(int height) {
    _height = height;
}

void glfwContext::setWidth(int width) {
    _width = width;
}

void glfwContext::setTitle(string title) {
    _title = title;
}

// Helpers
void glfwContext::assignAllHints() {
    glfwDefaultWindowHints();
    for(pair<int, int> hint : _windowHints) {
        glfwWindowHint(hint.first, hint.second);
    }
}


