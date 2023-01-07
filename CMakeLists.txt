cmake_minimum_required (VERSION 3.24.2 FATAL_ERROR)
set(PN OpenGL)
project(${PN})

add_executable(${PN} 
	src/main.cpp 
	src/Shaders/Shader.cpp 
	src/Shaders/Shader.h
	src/Resources/ResourceManager.cpp
	src/Resources/ResourceManager.h
	src/EngineObjects/EnginePrimitives.cpp
	src/EngineObjects/EnginePrimitives.h)

target_compile_features(${PN} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw)

add_subdirectory(glad)
target_link_libraries(${PN} PRIVATE glad glfw)