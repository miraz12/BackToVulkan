#--------------------------------------------------------------------------
# render
#--------------------------------------------------------------------------

# Display
FILE(GLOB display_headers display/*.h)
FILE(GLOB display_sources display/*.cpp)
SET(files_display 
	${display_headers}
	${display_sources})
SOURCE_GROUP("display" FILES ${files_display})

# Properties
FILE(GLOB properties_headers properties/*.h)
FILE(GLOB properties_sources properties/*.cpp)
SET(files_properties 
	${properties_headers}
	${properties_sources})
SOURCE_GROUP("properties" FILES ${files_properties})

# Resources
FILE(GLOB resources_headers resources/*.h)
FILE(GLOB resources_sources resources/*.cpp)
SET(files_resources 
	${resources_headers}
	${resources_sources})
SOURCE_GROUP("resources" FILES ${files_resources})

# Servers
FILE(GLOB servers_headers servers/*.h)
FILE(GLOB servers_sources servers/*.cpp)
SET(files_servers 
	${servers_headers}
	${servers_sources})
SOURCE_GROUP("servers" FILES ${files_servers})

SET(files_render
	${files_display}
    ${files_properties}
    ${files_resources}
	${files_servers})

ADD_LIBRARY(render STATIC ${files_render})
ADD_DEPENDENCIES(render exts)
TARGET_LINK_LIBRARIES(render PUBLIC engine exts)