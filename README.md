# AmbientOcclusion

## Overview

This repository contains several ambient occlusion algorithms implemented in C++ using the Vulkan library.

## Requirements

The provided source codes were tested in Windows 10 using the following libraries:
- Vulkan SDK 1.3.211.0;
- glfw3 3.3.7;
- glm 0.9.9.8;
- rapidjson;

To run the application, you need to pass the `config.json` file path as an argument to it (_e.g._ `main.exe config.json`). Also, we suggest you to move the `shaders` folder to the same folder where the executable is located.

If you want to recompile the shaders, please update the `compileShaders.bat` file (Windows) or create a new one following this [tutorial](https://vulkan-tutorial.com/Drawing_a_triangle/Graphics_pipeline_basics/Shader_modules#page_Compiling-the-shaders).
 
## Compilation/Building for Windows 

To compile the source code and build the application for Windows, you may need to:
 - Install [Visual Studio](https://docs.microsoft.com/en-us/visualstudio/install/install-visual-studio) (>= 2019);
 - Install [vcpkg](https://vcpkg.io/en/index.html):
	- **Note**: By default, vcpkg install x86 libraries. If you use a 64-bit version of Windows, you [need to add the following environment variable](https://github.com/microsoft/vcpkg/issues/1254): `VCPKG_DEFAULT_TRIPLET = x64-windows` before installing the vcpkg libraries;
 - Install [Vulkan SDK](https://vulkan.lunarg.com/sdk/home);
 - Run the following vcpkg commands in the command prompt:
   - vcpkg install vulkan-headers;
   - vcpkg install glfw3;
   - vcpkg install glm;
   - vcpkg install rapidjson;
   - vcpkg integrate install;
   
Then, you can create a new, empty Visual Studio project, add the source codes, and you may need to change the following properties of the project:
 - `Configuration Properties -> General -> C++ Language Standard:` to `ISO C++17 Standard (/std:c++17)`;
 - `Configuration Properties -> C/C++ -> General -> Additional Include Directories:` to `<AMBIENT_OCCLUSION_PATH>\include;%(AdditionalIncludeDirectories)`;
 - `Configuration Properties -> Linker -> General ->  Additional Library Directories:` to `<VULKAN_SDK_PATH>\Lib;%(AdditionalLibraryDirectories)`;
 - `Configuration Properties -> Linker -> Input -> Additional Dependencies:` add `vulkan-1.lib`,

where:
- `<AMBIENT_OCCLUSION_PATH>` is the path where the repository is stored;
- `<VULKAN_SDK_PATH>` is the path where the Vulkan SDK is installed;
