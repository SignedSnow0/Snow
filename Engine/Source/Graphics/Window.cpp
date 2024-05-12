#include "Window.h"

namespace SnowEngine {
    b8 Window::Initialize() {
         if (!glfwInit())
             return false;
                 
         return true;
    }

    void Window::Shutdown() {
        glfwTerminate();
    }

    Window* Window::CreateWindow(const std::string& title, u32 width, u32 height) {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        GLFWwindow* handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!handle)
            return nullptr;

        glfwMakeContextCurrent(handle);

        return new Window(handle);
    }

    void Window::PollEvents() { glfwPollEvents(); }

    b8 Window::IsClosing() const { return glfwWindowShouldClose(mWindow); }

    Window::Window(GLFWwindow* handle) 
        : mWindow{ handle } { }
}
