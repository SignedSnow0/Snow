#pragma once
#include <vector>
#include <vulkan/vulkan.h>
#include "Core/Types.h"

namespace SnowEngine {
    class VulkanSystem {
    public:
        static b8 Initialize();
        static void Shutdown();
        
        static const VulkanSystem* const GetInstance();

    private:
        VulkanSystem();

        static std::vector<const char*> GetExtensions();
        static std::vector<const char*> GetLayers();
        
        void CreateInstance(); 
        void CreateDebugMessenger();

        VkInstance mInstance;
#ifdef DEBUG
        VkDebugUtilsMessengerEXT mMessenger;
#endif
    };
}
