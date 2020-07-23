#--------------------------------------------------------------------------
# render
#--------------------------------------------------------------------------

FILE(GLOB project_headers *.h)
FILE(GLOB project_sources *.cpp)

SET(files_project ${project_headers} ${project_sources} )
source_group("header" FILES ${project_headers})
source_group("source" FILES ${project_sources})

ADD_LIBRARY(render STATIC ${files_project})
ADD_DEPENDENCIES(render exts)
TARGET_LINK_LIBRARIES(render PUBLIC engine exts)