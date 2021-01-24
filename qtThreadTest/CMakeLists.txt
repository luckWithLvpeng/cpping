
project(qtThreadTest)

FILE(GLOB files "*.cpp" "*.h")
add_executable(${PROJECT_NAME} 
		#main.cpp
		${files}
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
)