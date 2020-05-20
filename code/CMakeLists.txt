#--------------------------------------------------------------------------
# example project
#--------------------------------------------------------------------------

PROJECT(example)
FILE(GLOB project_headers *.h)
FILE(GLOB project_sources *.cpp)

SET(files_project ${project_headers} ${project_sources} )
SOURCE_GROUP("example" FILES ${files_project})

ADD_EXECUTABLE(example ${files_project})

ADD_DEPENDENCIES(example exts)
TARGET_LINK_LIBRARIES(example PUBLIC exts)
