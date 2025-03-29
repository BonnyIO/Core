cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

project("Core")

add_executable(Core "src/Core.cpp" "src/h/Program.hpp" "src/c/Program.cpp" "src/c/Window.cpp" "src/h/Window.hpp"
					#"src/c/VertexArr.cpp" "src/c/VertexBuf.cpp" "src/c/IndexBuf.cpp" "src/c/Camera.cpp" "src/h/VertexBuf.hpp" "src/h/VertexArr.hpp"
					#"src/c/Shader.cpp" "src/c/Texture.cpp" "src/c/Resource.cpp" "src/h/Resource.hpp" "src/h/IndexBuf.hpp"   
)

add_subdirectory(external/glfw)
target_link_libraries(Core glfw)

add_subdirectory(external/glad)
target_link_libraries(Core glad)

add_subdirectory(external/spdlog)
target_link_libraries(Core spdlog)

include_directories(external/glm)

set(IMGUI_INCLUDES external/imgui/imgui.h external/imgui/backends/imgui_impl_glfw.h external/imgui/backends/imgui_impl_opengl3.h)

set(IMGUI_SOURCES external/imgui/imgui.cpp external/imgui/backends/imgui_impl_glfw.cpp external/imgui/backends/imgui_impl_opengl3.cpp
				  external/imgui/imgui_demo.cpp external/imgui/imgui_draw.cpp external/imgui/imgui_tables.cpp external/imgui/imgui_widgets.cpp )

add_library(imgui STATIC ${IMGUI_INCLUDES} ${IMGUI_SOURCES})

target_include_directories(imgui PUBLIC external)
target_include_directories(imgui PUBLIC external/imgui)

target_link_libraries(imgui PRIVATE glad glfw)

target_link_libraries(Core imgui)