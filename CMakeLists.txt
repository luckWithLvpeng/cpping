cmake_minimum_required(VERSION 3.17)
project(cpping)

# 使用 utf-8 编码
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# 给生成的mocs和qrc文件分组
set_property(GLOBAL PROPERTY AUTOGEN_SOURCE_GROUP "Generated Files")
set_property (GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED 
  Core 
  Gui 
  Widgets 
  Multimedia 
  Network 
  OpenGL 
  Xml 
  AxContainer 
  AxServer 
  PrintSupport
  Sql
  Concurrent
	LinguistTools
)

#add_subdirectory(algorithms)
add_subdirectory(datastructure)
add_subdirectory(practice)
add_subdirectory(qtThreadTest)