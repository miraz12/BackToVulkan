#--------------------------------------------------------------------------
# example project
#--------------------------------------------------------------------------

PROJECT(example)

FILE(GLOB project_headers *.h)
FILE(GLOB project_sources *.cpp)

SET(files_project ${project_headers} ${project_sources} )
source_group("header" FILES ${project_headers})
source_group("source" FILES ${project_sources})

ADD_EXECUTABLE(example ${files_project})

TARGET_LINK_LIBRARIES(example PUBLIC render core)
ADD_DEPENDENCIES(example render core)

# Pre build command, compile shaders
if(WIN32)
  add_custom_command(TARGET example
                    PRE_BUILD COMMAND cmd /c ${CMAKE_SOURCE_DIR}/resources/shaders/compile.bat
                    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/resources/shaders/)
  SET_TARGET_PROPERTIES(example PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
endif()



