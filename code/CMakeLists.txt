#--------------------------------------------------------------------------
# example project
#--------------------------------------------------------------------------

PROJECT(example)
FILE(GLOB project_headers *.h math/*.h IO/*.h)
FILE(GLOB project_sources *.cpp)


SET(files_project ${project_headers} ${project_sources} )
source_group("header" FILES ${project_headers})
source_group("source" FILES ${project_sources})

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
