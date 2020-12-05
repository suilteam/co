set(CC_SOURCES
        stack_trace/stack_trace_unix.cc
        fastring.cc
        json.cc
        path.cc
        hash/md5.cc
        hash/crc16.cc
        hash/murmur_hash.cc
        hash/base64.cc
        co/impl/scheduler.cc
        co/impl/sock.cc
        co/impl/co.cc
        co/impl/hook.cc
        co/impl/epoll.cc
        unix/fs.cc
        unix/os.cc
        unix/time.cc
        fast.cc
        flag.cc
        log.cc
        str.cc
        thread.cc
        unitest.cc)

if(UNIX)
    add_library(co
        ${CC_SOURCES}
        co/context/context.S
    )
endif()

if(WIN32)
    set(CPP_SOURCES
        ./stack_trace/stack_trace_win.cpp
        ./stack_trace/StackWalker.cpp
        ./win/os.cpp
        ./win/fs.cpp
        ./win/time.cpp
        ./co/impl/sock.cpp)

    set(ASM_SOURCES co/context/context_x86.asm)
    if(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
        set(ASM_SOURCES co/context/context_x64.asm)
    endif()

    set_property(SOURCE ${ASM_SOURCES} PROPERTY LANGUAGE ASM_MASM)

    add_library(co
        ${CC_SOURCES}
        ${CPP_SOURCES}
        ${ASM_SOURCES}
    )
endif()

install(
    TARGETS co
    LIBRARY DESTINATION lib   # shared lib installed to   ${CMAKE_INSTALL_PREFIX}/lib
    ARCHIVE DESTINATION lib   # static lib installed to   ${CMAKE_INSTALL_PREFIX}/lib
)
