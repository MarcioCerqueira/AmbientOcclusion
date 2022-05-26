#include "SwapChain.h"

SwapChain::SwapChain(const SwapChainInfo& swapChainInfo)
{
    vk::SurfaceCapabilitiesKHR capabilities{ swapChainInfo.vulkanPhysicalDevice.getSurfaceCapabilitiesKHR(swapChainInfo.vulkanWindowSurface) };
    const std::vector<vk::SurfaceFormatKHR> availableFormats{ swapChainInfo.vulkanPhysicalDevice.getSurfaceFormatsKHR(swapChainInfo.vulkanWindowSurface) };
    std::vector<vk::PresentModeKHR> availablePresentModes{ swapChainInfo.vulkanPhysicalDevice.getSurfacePresentModesKHR(swapChainInfo.vulkanWindowSurface) };

    checkSwapChainValidity(availableFormats, availablePresentModes);
    chooseSwapSurfaceFormat(availableFormats);
    chooseSwapPresentMode(availablePresentModes);
    chooseSwapExtent(capabilities, swapChainInfo.framebufferSize);
    setImageCount(capabilities);
    createVulkanSwapChainInfo(swapChainInfo, capabilities);
}

void SwapChain::checkSwapChainValidity(const std::vector<vk::SurfaceFormatKHR>& availableFormats, const std::vector<vk::PresentModeKHR>& availablePresentModes)
{
    valid = !availableFormats.empty() && !availablePresentModes.empty();
}

void SwapChain::chooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats)
{
    surfaceFormat = availableFormats[0];
    for (const auto& availableFormat : availableFormats) 
    {
        if (availableFormat.format == vk::Format::eB8G8R8A8Srgb && availableFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) 
        {
            surfaceFormat = availableFormat;
            return;
        }
    }
}

void SwapChain::chooseSwapPresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes)
{
    presentMode = vk::PresentModeKHR::eFifo;
    for (const auto& availablePresentMode : availablePresentModes) 
    {
        if (availablePresentMode == vk::PresentModeKHR::eMailbox) 
        {
            presentMode = availablePresentMode;
            return;
        }
    }
}

void SwapChain::chooseSwapExtent(const vk::SurfaceCapabilitiesKHR& capabilities, const WindowSize& framebufferSize)
{
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
    {
        extent = capabilities.currentExtent;
    }
    else
    {
        extent = vk::Extent2D{ static_cast<uint32_t>(framebufferSize.width), static_cast<uint32_t>(framebufferSize.height) };
        extent.width = std::clamp(extent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        extent.height = std::clamp(extent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
    }
}

void SwapChain::setImageCount(const vk::SurfaceCapabilitiesKHR& capabilities)
{
    imageCount = capabilities.minImageCount + 1;
    if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount) 
    {
        imageCount = capabilities.maxImageCount;
    }
}

bool SwapChain::isValid() const noexcept
{
    return valid;
}

void SwapChain::createVulkanSwapChainInfo(const SwapChainInfo& swapChainInfo, const vk::SurfaceCapabilitiesKHR& capabilities)
{
    std::optional<uint32_t> graphicsFamilyIndex{ swapChainInfo.queueFamilyIndices.getGraphicsFamilyIndex() };
    std::optional<uint32_t> presentFamilyIndex{ swapChainInfo.queueFamilyIndices.getPresentFamilyIndex() };
    uint32_t queueFamilyIndices[] = { graphicsFamilyIndex.value(), presentFamilyIndex.value() };
    vk::SwapchainCreateInfoKHR swapChainCreateInfoKHR{
        .flags = {},
        .surface = swapChainInfo.vulkanWindowSurface,
        .minImageCount = imageCount,
        .imageFormat = surfaceFormat.format,
        .imageColorSpace = surfaceFormat.colorSpace,
        .imageExtent = extent,
        .imageArrayLayers = 1,
        .imageUsage = vk::ImageUsageFlagBits::eColorAttachment,
        .imageSharingMode = (graphicsFamilyIndex != presentFamilyIndex) ? vk::SharingMode::eConcurrent : vk::SharingMode::eExclusive,
        .queueFamilyIndexCount = (graphicsFamilyIndex != presentFamilyIndex) ? static_cast<uint32_t>(2) : static_cast<uint32_t>(0),
        .pQueueFamilyIndices = (graphicsFamilyIndex != presentFamilyIndex) ? queueFamilyIndices : nullptr,
        .preTransform = capabilities.currentTransform,
        .compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque,
        .presentMode = presentMode
    };
    vulkanSwapChain = swapChainInfo.vulkanLogicalDevice.createSwapchainKHR(swapChainCreateInfoKHR);
    swapChainImages = swapChainInfo.vulkanLogicalDevice.getSwapchainImagesKHR(vulkanSwapChain);
}
