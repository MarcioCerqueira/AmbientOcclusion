#pragma once

#define VULKAN_HPP_NO_CONSTRUCTORS
#include <vulkan/vulkan.hpp>
#include "GraphicsPipelineCreateInfo.h"

class GraphicsPipeline
{
public:
	GraphicsPipeline(const GraphicsPipelineCreateInfo& graphicsPipelineCreateInfo);
	~GraphicsPipeline();

private:
	const vk::PipelineVertexInputStateCreateInfo buildPipelineVertexInputStateCreateInfo() const;
	const vk::PipelineInputAssemblyStateCreateInfo buildPipelineInputAssemblyStateCreateInfo() const;
	const vk::PipelineViewportStateCreateInfo buildPipelineViewportStateCreateInfo(const vk::Extent2D& swapChainExtent) const;
	const vk::Viewport buildViewport(const vk::Extent2D& swapChainExtent) const;
	const vk::Rect2D buildScissor(const vk::Extent2D& swapChainExtent) const;
	const vk::PipelineRasterizationStateCreateInfo buildPipelineRasterizationStateCreateInfo() const;
	const vk::PipelineMultisampleStateCreateInfo buildPipelineMultisampleStateCreateInfo() const;
	const vk::PipelineColorBlendStateCreateInfo buildPipelineColorBlendStateCreateInfo() const;
	const vk::PipelineColorBlendAttachmentState buildPipelineColorBlendAttachmentState() const;
	const vk::PipelineDynamicStateCreateInfo buildPipelineDynamicStateCreateInfo() const;
	const vk::PipelineLayoutCreateInfo buildPipelineLayoutCreateInfo() const;
	
	const vk::Device vulkanLogicalDevice;
	vk::PipelineLayout pipelineLayout;
	vk::Pipeline pipeline;
};