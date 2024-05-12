#include "Graphics/Vulkan/Core.h"
#include "Graphics/Window.h"
#include <SnowEngine.h>

void Initialize() {
    SnowEngine::Window::Initialize();
    SnowEngine::VulkanSystem::Initialize();
}

void Shutdown() {
    SnowEngine::VulkanSystem::Shutdown();
    SnowEngine::Window::Shutdown();
}

int main() {
    Initialize();

    SnowEngine::Window* window = SnowEngine::Window::CreateWindow("SnowEngine", 1280, 720);

    while (!window->IsClosing()) {
        SnowEngine::Window::PollEvents();
    }

    delete window;

    Shutdown();

    return 0;
}
