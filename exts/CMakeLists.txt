#--------------------------------------------------------------------------
# exts
#--------------------------------------------------------------------------

ADD_LIBRARY(exts INTERFACE)

if(MSVC)
    add_compile_options(/W0)
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-w)
endif()

find_package(Vulkan REQUIRED)

SET(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
SET(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs")
SET(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
SET(GLFW_INSTALL OFF CACHE BOOL "Generate installation target")		  

ADD_SUBDIRECTORY(glfw)
SET_TARGET_PROPERTIES(glfw PROPERTIES FOLDER "exts/glfw")
TARGET_INCLUDE_DIRECTORIES(exts SYSTEM INTERFACE glfw/include)

#ADD_SUBDIRECTORY(yaml-cpp)
#SET_TARGET_PROPERTIES(yaml-cpp PROPERTIES FOLDER "exts/yaml-cpp")
#TARGET_INCLUDE_DIRECTORIES(exts INTERFACE yaml-cpp/include)

#ADD_SUBDIRECTORY(tinygltf)
TARGET_INCLUDE_DIRECTORIES(exts SYSTEM INTERFACE tinygltf)

#ADD_SUBDIRECTORY(tinyobjloader)
TARGET_INCLUDE_DIRECTORIES(exts SYSTEM INTERFACE tinyobjloader)

TARGET_LINK_LIBRARIES(exts INTERFACE Vulkan::Vulkan glfw)