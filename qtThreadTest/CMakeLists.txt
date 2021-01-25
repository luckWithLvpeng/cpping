
project(qtThreadTest)

FILE(GLOB files "*.cpp" "*.h" "*.ui")

#生成翻译文件,默认关闭，合并代码的时候太烦
#qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ./helloworld_en.ts ./helloworld_de.ts)

#手动更新翻译文件，
add_custom_target(translations)
set(TS_FILES
	helloworld_en.ts 
	helloworld_de.ts
)
foreach(_ts_file ${TS_FILES})
    # generate a sensible name for this translation file
    get_filename_component(_ts_name ${_ts_file} NAME_WE)

    # call lupdate ourselves
    add_custom_command(
        OUTPUT "${_ts_file}"
        DEPENDS ${files}
        COMMAND ${Qt5_LUPDATE_EXECUTABLE} -recursive
${CMAKE_CURRENT_SOURCE_DIR} -ts ${_ts_file}
    )

    # create a target that depends on the generated files
    add_custom_target(translate_${_ts_name} DEPENDS ${_ts_file})

    # attach the custom target for this ts file to the parent target
    add_dependencies(translations translate_${_ts_name})
endforeach()
qt5_add_translation(QM_FILES ${TS_FILES})


add_executable(${PROJECT_NAME} 
		${files}
		${QM_FILES}
		#qtThreadTest_en.ts qtThreadTest_zh.ts
		 helloworld_en.ts helloworld_de.ts
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