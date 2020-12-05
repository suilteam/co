list(APPEND LIBS_TO_LINK co)
if(UNIX)
    list(APPEND LIBS_TO_LINK pthread dl)
endif()

set(TEST_SOURCES
        co.cc
        fast.cc
        flag.cc
        hash.cc
        json.cc
        log.cc
        stack.cc
        str.cc
        task_sched.cc
        time.cc
        tw.cc
        xx.cc)


foreach(source ${TEST_SOURCES})
    get_filename_component(name ${source} NAME_WE)
    add_executable(${name}_test ${source})

    set_target_properties(${name}_test
        PROPERTIES
            OUTPUT_NAME ${name})

    target_link_libraries(${name}_test co pthread dl)
endforeach()
