#include "AmbientOcclusionApplication.h"

AmbientOcclusionApplication::AmbientOcclusionApplication(const int windowWidth, const int windowHeight)
{
	const std::string applicationName{ "Ambient Occlusion Application" };
	window = std::make_unique<Window>(windowWidth, windowHeight, applicationName);
	graphicInstance = std::make_unique<GraphicInstance>(applicationName);
	windowSurface = std::make_unique<WindowSurface>(graphicInstance->getVulkanInstance(), window->getGLFWWindow());
	graphicInstance->selectPhysicalDevice(windowSurface->getVulkanWindowSurface());
	graphicInstance->createLogicalDevice(windowSurface->getVulkanWindowSurface(), window->getFramebufferSize());
	loadGraphicsPipeline();
}

void AmbientOcclusionApplication::loadGraphicsPipeline()
{
	Shader vertexShader("shaders/vert.spv", graphicInstance->getVulkanLogicalDevice(), vk::ShaderStageFlagBits::eVertex);
	Shader fragmentShader("shaders/frag.spv", graphicInstance->getVulkanLogicalDevice(), vk::ShaderStageFlagBits::eFragment);
}

void AmbientOcclusionApplication::run() const noexcept
{
	window->open();
}