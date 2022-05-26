#include "PhysicalDeviceSuitabilityRater.h"

int PhysicalDeviceSuitabilityRater::rate(const PhysicalDeviceSuitabilityRaterInfo& physicalDeviceSuitabilityRaterInfo) const
{
	int score{ 0 };
	score += rateByPhysicalDeviceType(physicalDeviceSuitabilityRaterInfo);
	score += rateByQueueFamilyProperties(physicalDeviceSuitabilityRaterInfo);
	score *= rateByDeviceExtensionSupport(physicalDeviceSuitabilityRaterInfo);
	score *= rateBySwapChainProperties(physicalDeviceSuitabilityRaterInfo);
	return score;
}

int PhysicalDeviceSuitabilityRater::rateByPhysicalDeviceType(const PhysicalDeviceSuitabilityRaterInfo& physicalDeviceSuitabilityRaterInfo) const
{
	int score{ 0 };
	switch (physicalDeviceSuitabilityRaterInfo.vulkanPhysicalDevice.getProperties().deviceType)
	{
	case vk::PhysicalDeviceType::eDiscreteGpu:
		score = 1000;
		break;
	case vk::PhysicalDeviceType::eIntegratedGpu:
		score = 500;
		break;
	case vk::PhysicalDeviceType::eCpu:
		score = 100;
		break;
	default:
		score = 0;
		break;
	}
	return score;
}

int PhysicalDeviceSuitabilityRater::rateByQueueFamilyProperties(const PhysicalDeviceSuitabilityRaterInfo& physicalDeviceSuitabilityRaterInfo) const
{
	int score{ 0 };
	const QueueFamilyIndices queueFamilyIndices{ 
		physicalDeviceSuitabilityRaterInfo.vulkanPhysicalDevice, 
		physicalDeviceSuitabilityRaterInfo.vulkanWindowSurface 
	};
	score += 1000 * static_cast<int>(queueFamilyIndices.getGraphicsFamilyIndex().has_value());
	score += 1000 * static_cast<int>(queueFamilyIndices.getPresentFamilyIndex().has_value());
	return score;
}

int PhysicalDeviceSuitabilityRater::rateByDeviceExtensionSupport(const PhysicalDeviceSuitabilityRaterInfo& physicalDeviceSuitabilityRaterInfo) const
{
	const std::vector<vk::ExtensionProperties> availableExtensions = physicalDeviceSuitabilityRaterInfo.vulkanPhysicalDevice.enumerateDeviceExtensionProperties();
	std::set<std::string> requiredExtensions(physicalDeviceSuitabilityRaterInfo.vulkanDeviceExtensions.begin(), physicalDeviceSuitabilityRaterInfo.vulkanDeviceExtensions.end());
	for (const auto& extension : availableExtensions)
	{
		requiredExtensions.erase(extension.extensionName);
	}
	return static_cast<int>(requiredExtensions.empty());
}

int PhysicalDeviceSuitabilityRater::rateBySwapChainProperties(const PhysicalDeviceSuitabilityRaterInfo& physicalDeviceSuitabilityRaterInfo) const
{
	ValidationLayer validationLayer;
	LogicalDeviceInfo logicalDeviceInfo{
		.queueFamilyIndices = physicalDeviceSuitabilityRaterInfo.queueFamilyIndices,
		.vulkanPhysicalDevice = physicalDeviceSuitabilityRaterInfo.vulkanPhysicalDevice,
		.vulkanDeviceExtensions = physicalDeviceSuitabilityRaterInfo.vulkanDeviceExtensions,
		.enabledLayerCount = validationLayer.getEnabledLayerCount(),
		.enabledLayerNames = validationLayer.getEnabledLayerNames()
	};
	LogicalDevice logicalDevice(logicalDeviceInfo);
	SwapChainInfo swapChainInfo{
		.vulkanPhysicalDevice = physicalDeviceSuitabilityRaterInfo.vulkanPhysicalDevice,
		.vulkanWindowSurface = physicalDeviceSuitabilityRaterInfo.vulkanWindowSurface,
		.framebufferSize = physicalDeviceSuitabilityRaterInfo.framebufferSize,
		.queueFamilyIndices = physicalDeviceSuitabilityRaterInfo.queueFamilyIndices
	};
	return static_cast<int>(logicalDevice.createSwapChain(swapChainInfo).isValid());
}