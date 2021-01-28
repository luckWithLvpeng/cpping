
project(components)

LIST(APPEND header_files "components_export_global.h")

LIST (APPEND DIR_LIST "CMaskWidget")
LIST (APPEND DIR_LIST "CWidget")

FOREACH(dir IN LISTS DIR_LIST)
	include_directories(${dir})
	FILE(GLOB source "${dir}/*.cpp")
	LIST(APPEND source_files ${source})
	FILE(GLOB header "${dir}/*.h*" )
	LIST(APPEND header_files ${header})
	FILE(GLOB resource "${dir}/*.ui")
	LIST(APPEND resource_files ${resource})
	FILE(GLOB qrc "${dir}/*.qrc")
	LIST(APPEND qrc_files ${qrc})
	source_group(${dir}
		FILES
		${source}
		${header}
		${resource}
		${qrc}
	)
ENDFOREACH()

qt5_wrap_cpp(${PROJECT_NAME}_MOC_CXX ${header_files})
qt5_wrap_ui(${PROJECT_NAME}_UI_CXX ${resource_files})
qt5_add_resources(${PROJECT_NAME}_RCC_CXX ${qrc_files})

# Group files

source_group("Generated Files"
	 FILES
  	${${PROJECT_NAME}_MOC_CXX}
  	${${PROJECT_NAME}_UI_CXX}
  	${${PROJECT_NAME}_RCC_CXX}
)

add_library(${PROJECT_NAME} 
	SHARED
	${resource_files}
	${header_files}
	${source_files}
  ${${PROJECT_NAME}_UI_CXX}
	${${PROJECT_NAME}_RCC_CXX}
)
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME}  
INTERFACE 
${CMAKE_CURRENT_SOURCE_DIR}
${CMAKE_CURRENT_BINARY_DIR}
${DIR_LIST}
)

TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} PRIVATE "COMPONENTS_LIBRARY")

qt5_use_modules(${PROJECT_NAME} 
	Core 
	Gui 
	Widgets
	Multimedia
	Network
	Concurrent
)

target_link_libraries(${PROJECT_NAME}
)