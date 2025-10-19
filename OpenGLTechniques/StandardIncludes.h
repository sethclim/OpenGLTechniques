#ifndef STANDARDINCLUDES_H
#define STANDARDINCLUDES_H

#define GLM_ENABLE_EXPERIMENTAL

// Include standard headers
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <functional>
#include <chrono>

// Windows Specific includes and defines
#ifdef _WIN32
#include <Windows.h>
#define M_ASSERT(_cond, _msg)     \
	if (!(_cond))                 \
	{                             \
		OutputDebugStringA(_msg); \
		std::abort();             \
		glfwTerminate();          \
	}
#endif // _WIN32

// OpenGL/Helpers headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/ext/matrix_projection.hpp>

// font
#define generic GenericFromFreeTypeLibrary
#include <ft2build.h>
#include FT_FREETYPE_H
#undef generic

#include "Resolution.h"
#include "Singleton.h"

static void Log(std::string _msg)
{
	std::cout << _msg << std::endl;
}

#endif // !STANDARDINCLUDES_H
