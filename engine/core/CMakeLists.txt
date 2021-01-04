#--------------------------------------------------------------------------
# core
#--------------------------------------------------------------------------

SET(files_core
	app.h
	app.cc)
SOURCE_GROUP("core" FILES ${files_core})

FILE(GLOB math_headers math/*.h)
SET(files_math 
	${math_headers})
SOURCE_GROUP("math" FILES ${files_math})

FILE(GLOB input_headers input/*.h)
FILE(GLOB input_sources input/*.cpp)
SET(files_input
	${input_headers}
	${input_sources})
SOURCE_GROUP("input" FILES ${files_input})

# Renderinterface
FILE(GLOB renderinterface_headers renderinterface/*.h)
FILE(GLOB renderinterface_sources renderinterface/*.cpp)
SET(files_renderinterface
	${renderinterface_headers}
	${renderinterface_sources})
SOURCE_GROUP("renderinterface" FILES ${files_renderinterface})

ADD_LIBRARY(core STATIC 
			${files_core} 
			${files_math} 
			${files_input}
			${files_renderinterface})

ADD_DEPENDENCIES(core exts)
TARGET_LINK_LIBRARIES(core PUBLIC engine exts)
