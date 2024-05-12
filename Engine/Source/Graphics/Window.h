#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "Core/Types.h"

namespace SnowEngine {
    class Window {
    public:
        static b8 Initialize();
        static void Shutdown();
        static Window* CreateWindow(const std::string& title, u32 width, u32 height);

        b8 IsClosing() const;

    private:
        Window(GLFWwindow* handle);

        GLFWwindow* mWindow{ nullptr };
    };
}
