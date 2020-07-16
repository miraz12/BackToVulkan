#--------------------------------------------------------------------------
# example project
#--------------------------------------------------------------------------

PROJECT(example)


FILE(GLOB project_headers *.h math/*.h IO/*.h)
FILE(GLOB project_sources *.cpp)

SET(files_project ${project_headers} ${project_sources} )
source_group("header" FILES ${project_headers})
source_group("source" FILES ${project_sources})

if(MSVC)
  add_compile_options(/W4 /wd26812)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  add_compile_options(-Wall -Wno-long-long -pedantic /w26812)
endif()

ADD_EXECUTABLE(example ${files_project})

ADD_DEPENDENCIES(example exts)
TARGET_LINK_LIBRARIES(example PUBLIC exts)
SET_PROPERTY(TARGET example PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

# Pre build command, compile shaders
if(WIN32)
  add_custom_command(TARGET example
                    PRE_BUILD COMMAND cmd /c ${CMAKE_SOURCE_DIR}/resources/shaders/compile.bat
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/resources/shaders/)
endif()



