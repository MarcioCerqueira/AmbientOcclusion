#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <vulkan/vulkan.hpp>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "ArgumentParser.h"
#include "JSONConfigurationFileParser.h"
#include "AmbientOcclusionApplication.h"

int main(int argc, const char* argv[]) 
{
	
	try 
	{
		ArgumentParser argumentParser{ argc, argv };
		JSONConfigurationFileParser JSONConfigurationFileParser{ argumentParser.getConfigurationFile().c_str() };
		ConfigurationFileModel configurationFileModel{ JSONConfigurationFileParser.getConfigurationFileModel() };

		AmbientOcclusionApplication app{ configurationFileModel.window.width, configurationFileModel.window.height };
		app.run();
	}
	catch (const vk::SystemError& error)
	{
		std::cerr << "vk::SystemError: " << error.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (const std::exception& exception)
	{
		std::cerr << "std::exception: " << exception.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (...)
	{
		std::cerr << "Unknown error" << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;

}