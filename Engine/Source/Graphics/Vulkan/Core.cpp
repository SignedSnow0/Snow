#include "Core.h"
#include <string.h>
#include <iostream>
#include "GLFW/glfw3.h"

namespace SnowEngine {
    static VulkanSystem* sSystem{ nullptr };

    static VKAPI_ATTR VkBool32 VKAPI_CALL PrintDebugMessage(VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT type, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
        std::cerr << "Validation layer: " << pCallbackData->pMessage << std::endl;

        return VK_FALSE;
    }

    static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr)
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr)
            func(instance, debugMessenger, pAllocator);
    }

    b8 VulkanSystem::Initialize() {
        sSystem = new VulkanSystem(); 

        return true;
    }

    void VulkanSystem::Shutdown() {
        if (!sSystem)
            return;

#ifdef DEBUG
        DestroyDebugUtilsMessengerEXT(sSystem->mInstance, sSystem->mMessenger, nullptr);
#endif
        
        vkDestroyInstance(sSystem->mInstance, nullptr);
    }

    const VulkanSystem* const VulkanSystem::GetInstance() { return sSystem; }

    VulkanSystem::VulkanSystem() {
        CreateInstance();
    }

    void VulkanSystem::CreateInstance() {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "SnowEngine App";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "SnowEngine";
        appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
        appInfo.apiVersion = VK_API_VERSION_1_3;

        std::vector<const char*> extensions = GetExtensions();
        std::vector<const char*> layers = GetLayers();

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = extensions.size();
        createInfo.ppEnabledExtensionNames = extensions.data();
        createInfo.enabledLayerCount = layers.size();
        createInfo.ppEnabledLayerNames = layers.data();

        vkCreateInstance(&createInfo, nullptr, &mInstance);
    }

    void VulkanSystem::CreateDebugMessenger() {
        VkDebugUtilsMessengerCreateInfoEXT createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        createInfo.pfnUserCallback = PrintDebugMessage;
        createInfo.pUserData = nullptr;

        CreateDebugUtilsMessengerEXT(mInstance, &createInfo, nullptr, &mMessenger);
    }

    std::vector<const char*> VulkanSystem::GetExtensions() {
        u32 count{ 0 };
        const char** extensions{ nullptr };
        extensions = glfwGetRequiredInstanceExtensions(&count);

        return std::vector(count, *extensions);
    }

    std::vector<const char*> VulkanSystem::GetLayers() {
        std::vector<const char*> layers{};
#ifdef DEBUG
        layers.push_back("VK_LAYER_KHRONOS_validation");
#endif

        u32 layerCount{ 0 };
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (u32 i = 0; i < layers.size(); i++) {
            const char* layer = layers.at(i);
            b8 found{ false };

            for (const auto availableLayer : availableLayers) {
                if (strcmp(layer, availableLayer.layerName) == 0) {
                    found = true;
                    break;
                }
            } 

            if (!found) {
                layers.erase(layers.begin() + i);
            }
        }

        return layers;
    }
}
