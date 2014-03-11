#include "glfwContext.hpp"
#include <iterator>

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
GLFWwindow *glfwContext::createWindow(std::pair<int, int> dim, std::string title) {
    _title = title;

    assignAllHints();

    _windowHandle = glfwCreateWindow(dim.first, dim.second, _title.c_str(), NULL , NULL);
    return _windowHandle;
}

void glfwContext::swapBuffers() {
    glfwSwapBuffers(_windowHandle);
}

void glfwContext::makeContextCurrent(glfwContext &context) {
    glfwMakeContextCurrent(context.windowHandle());
}

bool glfwContext::getKey(int key, int action) {
    if(glfwGetKey(_windowHandle, key) == action) return true;
    else return false;
}

// Getters
GLFWwindow *glfwContext::windowHandle() {
    return _windowHandle;
}

int glfwContext::height() {
    int height = 0;
    glfwGetWindowSize(_windowHandle, NULL, &height);
    return height;
}

int glfwContext::width() {
    int width = 0;
    glfwGetWindowSize(_windowHandle, &width, NULL);
    return width;
}

pair<int, int> glfwContext::windowDims() {
    int width = 0, height = 0;
    glfwGetWindowSize(_windowHandle, &width, &height);
    pair<int, int> dims(width, height);
    return dims;
}

string glfwContext::title() {
    return _title;
}

pair<double, double> glfwContext::mousePos() {
    double x = 0, y = 0;
    glfwGetCursorPos(_windowHandle, &x, &y);
    pair<double, double> mousePos(x, y);
    return mousePos;
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
    glfwSetWindowSize(_windowHandle, width(), height);
}

void glfwContext::setWidth(int width) {
    glfwSetWindowSize(_windowHandle, width, height());
}

void glfwContext::setWindowDims(int width, int height) {
    glfwSetWindowSize(_windowHandle, width, height);
}

void glfwContext::setTitle(string title) {
    _title = title;
    glfwSetWindowTitle(_windowHandle, title.c_str());
}

void glfwContext::setMousePos(pair<double, double> pos) {
    glfwSetCursorPos(_windowHandle, pos.first, pos.second);
}

// Helpers
void glfwContext::assignAllHints() {
    glfwDefaultWindowHints();
    for(pair<int, int> hint : _windowHints) {
        glfwWindowHint(hint.first, hint.second);
    }
}


