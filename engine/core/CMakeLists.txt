#--------------------------------------------------------------------------
# core
#--------------------------------------------------------------------------

SET(files_core
	app.h
	app.cc)
SOURCE_GROUP("core" FILES ${files_core})

FILE(GLOB math_headers math/*.h)
FILE(GLOB math_sources math/*.cc)
SET(files_math 
	${math_headers}
	${math_sources})
SOURCE_GROUP("math" FILES ${files_math})

ADD_LIBRARY(core STATIC ${files_core} ${files_math} )
ADD_DEPENDENCIES(core exts)
TARGET_LINK_LIBRARIES(core PUBLIC engine exts)
