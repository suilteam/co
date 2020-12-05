set(SOURCE_FILES
    atomic.cc
    co.cc
    fast.cc
    fastream.cc
    fastring.cc
    fs.cc
    json.cc
    lru_map.cc
    main.cc
    os.cc
    path.cc
    random.cc
    str.cc
    thread.cc
    time.cc)

add_executable(unittest ${SOURCE_FILES})
target_link_libraries(unittest co)
if(UNIX)
    target_link_libraries(unittest pthread dl)
endif()