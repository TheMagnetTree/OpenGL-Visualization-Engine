#ifndef _GLFWHINTS_HPP
#define _GLFWHINTS_HPP

#include <vector>
#include <utility>
#include <map>
#include <GLFW/glfw3.h>

using std::map;
using std::make_pair;

// int hint, int value
static const map<int, int> defaultHints 
{ make_pair(GLFW_SAMPLES, 4)
, make_pair(GLFW_CONTEXT_VERSION_MAJOR, 4)
, make_pair(GLFW_CONTEXT_VERSION_MINOR, 2)
, make_pair(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE)
};

#endif //_GLFW_HINTS_HPP
