#include "ImageView.h"

ImageView::ImageView(const vk::Device& vulkanLogicalDevice, const vk::Image& image, const vk::SurfaceFormatKHR& surfaceFormat) : vulkanLogicalDevice(vulkanLogicalDevice)
{
    vk::ImageViewCreateInfo imageViewCreateInfo{ buildImageViewCreateInfo(image, surfaceFormat) };
    vulkanImageView = vulkanLogicalDevice.createImageView(imageViewCreateInfo);
}

ImageView::~ImageView()
{
    vulkanLogicalDevice.destroyImageView(vulkanImageView);
}

const vk::ImageViewCreateInfo ImageView::buildImageViewCreateInfo(const vk::Image& image, const vk::SurfaceFormatKHR& surfaceFormat) const
{
    return vk::ImageViewCreateInfo{
        .image = image,
        .viewType = vk::ImageViewType::e2D,
        .format = surfaceFormat.format,
        .components = vk::ComponentSwizzle::eIdentity,
        .subresourceRange = createImageSubresourceRange()
    };
}

const vk::ImageSubresourceRange ImageView::createImageSubresourceRange() const
{
    return vk::ImageSubresourceRange{
        .aspectMask = vk::ImageAspectFlagBits::eColor,
        .baseMipLevel = 0,
        .levelCount = 1,
        .baseArrayLayer = 0,
        .layerCount = 1
    };
}

vk::ImageView ImageView::getVulkanImageView() const
{
    return vulkanImageView;
}
