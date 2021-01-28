
project(qtUI)

FILE(GLOB files "*.cpp" "*.h" "*.ui" "*.qrc")

add_executable(${PROJECT_NAME} 
		${files}
		${QM_FILES}
)

qt5_use_modules(${PROJECT_NAME} 
  Core 
  Gui 
  Widgets
  Multimedia
  Network
	Concurrent
)

target_link_libraries(${PROJECT_NAME}
	components
)