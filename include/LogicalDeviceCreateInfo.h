#pragma once

#define VULKAN_HPP_NO_CONSTRUCTORS
#include <vulkan/vulkan.hpp>
#include <optional>

#include "QueueFamilyIndices.h"
#include "WindowSize.h"

struct LogicalDeviceCreateInfo
{
	QueueFamilyIndices queueFamilyIndices;
	vk::PhysicalDevice vulkanPhysicalDevice;
	vk::SurfaceKHR vulkanWindowSurface;
	std::vector<const char*> vulkanDeviceExtensions;
	WindowSize framebufferSize;
	uint32_t enabledLayerCount;
	char* const* enabledLayerNames;
};